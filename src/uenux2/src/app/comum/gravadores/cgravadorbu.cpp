// comum::CGravadorBU (/home/rubio/tse/uenux2/src/app/comum/gravadores/cgravadorbu.cpp, the file its records name): the
// static AcrescentaVotoVotavel, target fn 3820, whose throw sits on its record's line and column (221:23); the lines
// above it are blank, the original's content not recovered, and where the function starts is a choice. The file's other
// records (lines 484, 485, 542, 552, 560 and 636) belong to GravaResultado (fn 11629, slot 7), which holds
// LeChavePublica and MontaEntidadeBU inlined and is not written (src/units/200-uenux2-cgravadorbu-pending.cpp).
// Target fn 3819 (no record) follows AcrescentaVotoVotavel, written here as MontaVotosCargos with the six functions it
// holds inlined: GravaResultado calls it three times, once per vector FiltraCargos returns, with the map at +284, the
// object at +196 (a CRdv: 3819 calls its slots 3, 4, 8, 9 and 10), CCandidaturas::GetInst() and CPartidos::GetInst().
// Per cargo it builds the votes of each votable (the nominal votes of the candidates, or of a consulta's answers,
// through the RDV's slot 3, then its blank and null votes, slots 9 and 8; the party votes of a proportional cargo, slot
// 4; the null votes of a cargo with no candidate, slot 10) and pushes an md::CVotosCargo with the byte the map holds
// for the cargo (map::at). MontaVotosVotaveis and MontaVotosNominais each run behind a frame of their own inside 3819,
// and VotosRespostas's result is built apart and moved into MontaVotosNominais's, so the three are read as external
// functions binaryen inlines into their one caller each (docs/how-to-decompile.md step 3), a reading; VotosNumeros,
// VotosCandidatos and AcrescentaVotosSemCandidato are file-local, which clang inlines, a choice that gives the target's
// code (src/units/200-uenux2-cgravadorbu.mk lists what was measured). Their names, their being free functions of comum
// (none reads class state; AcrescentaVotoVotavel is public for them, a choice), their parameter types (references where
// 3819 receives addresses) and the locals' names are chosen.
// FiltraCargos (target fn 3818, no record) follows them: GravaResultado calls it three times, over the cargos of each
// election (CConfiguracaoEleicao::GetCargos, fn 3775) with the types MAJORITARIO, PROPORCIONAL and CONSULTA, and it
// copies the cargos of that type (the word at +4) into a vector it reserves for all of them first. In use band 3 it
// links after AcrescentaVotoVotavel and fn 3819 and ahead of the template and inline instances clang emits at the end
// of the TU (3817, 3816; and 3815, igravadorenvelope.cpp.o's in our link, this object's by a reading): so it is read as
// an external function defined after them (docs/reference/facts/reading.md R8), a reading; its name, its being a free
// function of comum (it reads no class state), its line and the loop (std::copy_if was not tried) are chosen. The file
// ends here.

#include "app/comum/gravadores/cgravadorbu.h"

#include <format>

#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/crdv.h"
#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/comum/gravadores/md/cvotoscargo.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum {

// (original lines 41-203: content not recovered)
#line 204
void CGravadorBU::AcrescentaVotoVotavel(TVetorVotosVotaveis& votos, md::CVoto::ETipo tipo, TCandidatoID candidato,
    TQtdEleitor quantidade, const md::CCargo& cargo)
{
    if (quantidade == 0) {
        return;
    }

    if (tipo == md::CVoto::BRANCO || tipo == md::CVoto::NULO || tipo == md::CVoto::NULO_CARGO_SEM_CANDIDATO) {
        votos.push_back(md::CVotosVotavel(tipo, candidato, quantidade));
    } else if (cargo.IsConsulta()) {
        votos.push_back(md::CVotosVotavel(tipo, candidato, quantidade, md::CIdentificacaoVotavel(candidato, 0)));
    } else {
        TPartidoID partido;
        const md::CCandidatura* candidatura = CCandidaturas::GetInst().Busca(cargo.GetID(), candidato);
        if (candidatura == nullptr) {
            const md::CPartido* legenda = CPartidos::GetInst().Find(candidato);
            if (legenda == nullptr) {
                throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8638,
                    std::format("Candidato {} / cargo {} não existe", candidato, cargo.GetID()));
            }
            partido = legenda->GetNumero();
        } else {
            partido = candidatura->GetPartidoID();
        }
        votos.push_back(md::CVotosVotavel(tipo, candidato, quantidade, md::CIdentificacaoVotavel(candidato, partido)));
    }
}

namespace {

void AcrescentaVotosSemCandidato(CGravadorBU::TVetorVotosVotaveis& votos, md::CVoto::ETipo tipo,
    md::TQtdVoto quantidade)
{
    if (quantidade != 0) {
        votos.push_back(md::CVotosVotavel(tipo, 0, quantidade));
    }
}

CGravadorBU::TVetorVotosVotaveis VotosNumeros(const std::vector<TCandidatoID>& numeros, const md::CCargo& cargo,
    const CRdv& rdv)
{
    CGravadorBU::TVetorVotosVotaveis votos;
    const uebyte digitos = cargo.GetNumeroDigitos();
    const md::TCargoID idCargo = cargo.GetID();
    for (const TCandidatoID& numero : numeros) {
        const md::TQtdVoto quantidade = rdv.Candidato(idCargo, numero, digitos);
        CGravadorBU::AcrescentaVotoVotavel(votos, md::CVoto::NOMINAL, numero, quantidade, cargo);
    }
    return votos;
}

CGravadorBU::TVetorVotosVotaveis VotosCandidatos(const md::CCargo& cargo, const CRdv& rdv,
    const CCandidaturas& candidaturas)
{
    const std::vector<TCandidatoID> candidatos = candidaturas.GetCandidatosPartido(cargo.GetID(), 0);
    return VotosNumeros(candidatos, cargo, rdv);
}

} // namespace

CGravadorBU::TVetorVotosVotaveis VotosRespostas(const md::CCargo& cargo, const CRdv& rdv)
{
    std::vector<TCandidatoID> numeros;
    const md::TVectorRespostaConsulta respostas = cargo.GetDetalheConsulta().GetRespostas();
    for (std::size_t i = 0; i < respostas.size(); i++) {
        numeros.push_back(respostas[i].GetNumero());
    }
    return VotosNumeros(numeros, cargo, rdv);
}

CGravadorBU::TVetorVotosVotaveis MontaVotosNominais(const md::CCargo& cargo, const CRdv& rdv,
    const CCandidaturas& candidaturas)
{
    CGravadorBU::TVetorVotosVotaveis votos;
    if (cargo.IsConsulta()) {
        votos = VotosRespostas(cargo, rdv);
    } else {
        votos = VotosCandidatos(cargo, rdv, candidaturas);
    }
    const md::TCargoID idCargo = cargo.GetID();
    AcrescentaVotosSemCandidato(votos, md::CVoto::BRANCO, rdv.Brancos(idCargo));
    AcrescentaVotosSemCandidato(votos, md::CVoto::NULO, rdv.Nulos(idCargo));
    return votos;
}

CGravadorBU::TVetorVotosVotaveis MontaVotosVotaveis(const md::CCargo& cargo, const CRdv& rdv,
    const CCandidaturas& candidaturas, const CPartidos& partidos)
{
    CGravadorBU::TVetorVotosVotaveis votos;
    if (cargo.IsConsulta() || candidaturas.ExisteCandidato(cargo.GetID())) {
        const CGravadorBU::TVetorVotosVotaveis nominais = MontaVotosNominais(cargo, rdv, candidaturas);
        const bool proporcional = cargo.IsProporcional();
        CGravadorBU::TVetorVotosVotaveis legendas;
        if (proporcional) {
            const md::TCargoID idCargo = cargo.GetID();
            for (const auto& [numero, partido] : partidos.GetRegistros()) {
                const md::TQtdVoto quantidade = rdv.Legenda(idCargo, numero);
                CGravadorBU::AcrescentaVotoVotavel(legendas, md::CVoto::LEGENDA, numero, quantidade, cargo);
            }
        }
        votos = nominais;
        votos.insert(votos.end(), legendas.cbegin(), legendas.cend());
    } else {
        AcrescentaVotosSemCandidato(votos, md::CVoto::NULO_CARGO_SEM_CANDIDATO, rdv.Cargo(cargo.GetID()));
    }
    return votos;
}

std::vector<md::CVotosCargo> MontaVotosCargos(const std::vector<md::CCargo>& cargos,
    const std::map<md::TCargoID, uebyte>& ordemCargos, const CRdv& rdv, const CCandidaturas& candidaturas,
    const CPartidos& partidos)
{
    std::vector<md::CVotosCargo> votosCargos;
    for (const md::CCargo& cargo : cargos) {
        const CGravadorBU::TVetorVotosVotaveis votos = MontaVotosVotaveis(cargo, rdv, candidaturas, partidos);
        votosCargos.push_back(md::CVotosCargo(cargo.GetID(), ordemCargos.at(cargo.GetID()), votos));
    }
    return votosCargos;
}

std::vector<md::CCargo> FiltraCargos(const std::vector<md::CCargo>& cargos, md::CCargo::ETipo tipo)
{
    std::vector<md::CCargo> filtrados;
    filtrados.reserve(cargos.size());
    for (const md::CCargo& cargo : cargos) {
        if (cargo.GetTipo() == tipo) {
            filtrados.push_back(cargo);
        }
    }
    return filtrados;
}

} // namespace comum
