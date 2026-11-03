// comum::CGravadorBU (/home/rubio/tse/uenux2/src/app/comum/gravadores/cgravadorbu.cpp, the file its records name): the
// static AcrescentaVotoVotavel, target fn 3820, whose throw sits on its record's line and column (221:23); the lines
// above it are blank, the original's content not recovered, and where the function starts is a choice. The file's other
// records (lines 484, 485, 542, 552, 560 and 636) belong to GravaResultado (fn 11629, slot 7), which holds LeChavePublica
// and MontaEntidadeBU inlined and is not written (src/units/200-uenux2-cgravadorbu-pending.cpp). FiltraCargos (target
// fn 3818, no record) follows AcrescentaVotoVotavel: GravaResultado calls it three times, over the cargos of each
// election (CConfiguracaoEleicao::GetCargos, fn 3775) with the types MAJORITARIO, PROPORCIONAL and CONSULTA, and it
// copies the cargos of that type (the word at +4) into a vector it reserves for all of them first. In use band 3 it
// links after AcrescentaVotoVotavel and fn 3819 (unnamed, not written) and ahead of the template and inline instances
// of this object (fns 3817, 3816 and 3815), which clang emits at the end of the TU: so it is read as an external
// function defined after AcrescentaVotoVotavel (docs/reference/facts/reading.md R8), a reading; its name, its being a
// free function of comum (it reads no class state), its line and the loop (std::copy_if was not tried) are chosen. The
// file ends here.

#include "app/comum/gravadores/cgravadorbu.h"

#include <format>

#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum {

// (original lines 26-203: content not recovered)
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
