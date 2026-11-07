// comum::CGravadorBU (/home/rubio/tse/uenux2/src/app/comum/gravadores/cgravadorbu.cpp, the file its records name). Its
// records are records of the target, so their lines and columns are fixed: AcrescentaVotoVotavel's throw (221:23, target
// fn 3820), GravaResultado's calls of api::CPolySingleton<api::IUrna>::instance and <IRng>::instance (484:30 and
// 485:22, fn 11629, slot 7), LeChavePublica's two throws and its api::IKernelHSM instance (542:15, 552:40 and 560:15)
// and MontaEntidadeBU's throw (636:11), both held by fn 11629. The lines between the records are blank, the original's
// content not recovered, and where each function starts is a choice; so are the lines of the functions with no record.
// Target fn 3819 (no record) follows AcrescentaVotoVotavel, written here as MontaVotosCargos with the six functions it
// holds inlined: fn 11629 calls it three times, once per vector FiltraCargos returns, with the map at +284, the object
// at +196 (a CRdv: 3819 calls its slots 3, 4, 8, 9 and 10), CCandidaturas::GetInst() and CPartidos::GetInst(). Per
// cargo it builds the votes of each votable (the nominal votes of the candidates, or of a consulta's answers, through
// the RDV's slot 3, then its blank and null votes, slots 9 and 8; the party votes of a proportional cargo, slot 4; the
// null votes of a cargo with no candidate, slot 10) and pushes an md::CVotosCargo with the byte the map holds for the
// cargo (map::at). MontaVotosVotaveis and MontaVotosNominais each run behind a frame of their own inside 3819, and
// VotosRespostas's result is built apart and moved into MontaVotosNominais's, so the three are read as external
// functions binaryen inlines into their one caller each (docs/how-to-decompile.md step 3), a reading; VotosNumeros,
// VotosCandidatos and AcrescentaVotosSemCandidato are file-local, which clang inlines, a choice that gives the target's
// code (src/units/200-uenux2-cgravadorbu.mk lists what was measured). Their names, their being free functions of comum
// (none reads class state; AcrescentaVotoVotavel is public for them, a choice), their parameter types (references where
// 3819 receives addresses) and the locals' names are chosen.
// FiltraCargos (target fn 3818, no record) is declared after them and defined after the BU's result helpers below: fn
// 11629 calls it three times, over the cargos of each election (CConfiguracaoEleicao::GetCargos, fn 3775) with the types
// MAJORITARIO, PROPORCIONAL and CONSULTA, and it copies the cargos of that type (the word at +4) into a vector it
// reserves for all of them first. In use band 3 it links after AcrescentaVotoVotavel and fn 3819 and ahead of the
// template instances clang emits at the end of the TU, 3817 (MontaResultadosVotacao's push_back of a copy) ahead of
// 3816 (the relocation FiltraCargos's reserve and push_back call): so it is read as an external function, mentioned
// first by MontaResultadosVotacao's calls and defined after it (docs/reference/facts/reading.md R8), a reading; defined
// before MontaResultadosVotacao, it gave the same bytes with 3816 linked ahead of 3817 (ld_index 5102 against 5105 in
// build/out/wasm-map/vota_web/names.tsv). Its name, its being a free function of comum (it reads no class state), its
// declaration's and definition's lines and the loop (std::copy_if was not tried) are chosen.
// The functions after MontaVotosCargos build the BU, all of them held by fn 11629 (the fragment has what each form
// scored):
// - MontaResultadosVotacaoPorEleicao and MontaResultadosVotacao, each behind a frame of its own inside fn 11629's (48
//   and 96 bytes, the second inside the first), whose arguments fn 11629 evaluates before their frames open: per
//   election of the pleito, the cargos of that election (a fresh CConfiguracaoEleicao::GetInst()'s GetCargos, fn 3775,
//   sorted), the results of its proportional, majority and consulta cargos (FiltraCargos three times; the attendance of
//   a type is the RDV's slot 10 for its first post divided by that post's number of choices, the majority's or else the
//   consulta's for both; MontaVotosCargos per type; each md::CResultadoVotacao kept when it holds totals, the
//   proportional first) and an md::CResultadoVotacaoPorEleicao with the election's id and the voters the map at +180
//   holds for its abrangencia. Read as external functions binaryen inlines (a reading, as for 3819's helpers);
//   MontaResultadoVotacao, file-local, builds one md::CResultadoVotacao, so that the votes' vector is destroyed before
//   the result is moved into the one MontaResultadosVotacao keeps (the target's order, measured). Their names, their
//   being free functions of comum (they read no class state), their parameters' types and order beyond what the
//   target passes, and the locals' names are chosen.
// - GravaResultado, the class's key function: the media's serial from the external flash's "infomidia.dat" when it
//   exists (fn 3735, then CStringUtils::BytesToHexString, else "00000000"), as CGravadorRDV::GravaResultado and
//   IGravadorEnvelope::MontaEnvelope read it; the elections' results; the header (fn 1945), the load (fn 2802), the
//   correspondence (fn 2801; eUrnaVota for a section, else eUrnaContingencia) and the urna (fns 2855 and 2854, with
//   and without the apuracao type at +260); the entity (MontaEntidadeBU) and its code (comum::asn::Codifica, the
//   converter's file: cconversorentidadebu.cpp says why); then, when +212 is set and the configuration's
//   CParametrosUrna::GetCriptografarBU is too, the coded bytes encrypted as comum::CControlaArmazenamentoDeImagens
//   encrypts an image (the IUrna's table of 1024 bytes, 32 random bytes from IRng, the public key LeChavePublica
//   reads, an ecourna CPlainText with the zone and the section, CCepescCipher::Encrypt) into an envelope with an
//   md::CSeguranca (0, 1, the cipher's key), else the coded bytes into an envelope without one; the envelope written
//   with comum::asn::GravaArquivo (fn 2724).
// - LeChavePublica: the public key "bu.pk1" under CPath::GetPathChave(), read and decrypted with the HSM's password, as
//   CControlaArmazenamentoDeImagens::LeChavePublica reads "wsq.pk1": the records sit at the same distances from each
//   other (542, 552, 560 against that file's 117, 127, 135), and the code is the same but for the path's
//   construction and the error codes (8639, 8640). Its 176-byte frame opens inside fn 11629's.
// - MontaEntidadeBU: md::CEntidadeBU with the vota data at +216 or else the SA data at +272, each with the attendance
//   detail at +296 when +192 is set, else the throw (8641); an empty std::vector<md::CHistoricoVotoImpresso> of its
//   own (its 32-byte frame holds it) goes into the entity. CEntidadeBU::ValidaCriacao's frame opens once inside its.
// The locals' names, the order of the statements no call fixes and the names of the helpers are chosen.
// - The constructor has no target index: fn 12098 holds it inlined behind a 192-byte frame of its own. That frame holds
//   a second copy of the vector and the map, moved from the ones 12098 passes, and four std::optionals made from the
//   arguments (the vota data and the attendance detail engaged, the SA data empty), copied once more before IGravador's
//   constructor (fn 1396) runs: so it delegates to a private constructor that takes those six by value (a reading).
//   The map at +284 is filled in a loop over comum::CCargos ahead of +296's store, so MontaOrdemCargos builds it in its
//   initializer (a reading). Chosen: the parameters' order and form, the private constructor's taking the extension 4,
//   the SAVD file 35, the ETipoArquivo 49, "bu.pk1" and +212's true as its own constants, and MontaOrdemCargos's name
//   and its being a file-local function.

#include "app/comum/gravadores/cgravadorbu.h"

#include <algorithm>
#include <filesystem>
#include <format>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "api/hwil/ikernelhsm.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/carquivosresultado.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/carregaarquivo.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/crdv.h"
#include "app/comum/dados/md/correspondencia/ccarga.h"
#include "app/comum/dados/md/correspondencia/ccorrespondenciaresultado.h"
#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/comum/gravadores/asn/cconversorentidadebu.h"
#include "app/comum/gravadores/asn/cconversorenvelopegenerico.h"
#include "app/comum/gravadores/cgravadorutil.h"
#include "app/comum/gravadores/md/cenvelopegenerico.h"
#include "app/comum/gravadores/md/chistoricovotoimpresso.h"
#include "app/comum/gravadores/md/cvotoscargo.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"
#include "app/comum/md/cseguranca.h"
#include "asn1/modules/ModuloEnvelopeChave.h"
#include "ecourna/api/io/asn/serialization.hpp"
#include "ecourna/api/security/cepesc/ccepesccipher.hpp"
#include "ecourna/api/security/cepesc/cplaintext.hpp"
#include "ecourna/api/security/csymmetriccipherfactory.hpp"
#include "ecourna/api/security/irng.hpp"
#include "ecourna/api/security/isymmetriccipher.hpp"
#include "ecourna/api/util/cstringutils.hpp"
#include "ecourna/app/dados/asn/midias/cconversorinformacaomidia.hpp"

namespace comum {


namespace {

std::map<md::TCargoID, uebyte> MontaOrdemCargos()
{
    std::map<md::TCargoID, uebyte> ordem;
    CCargos::GetInst().RemoveFiltro();
    CCargos& cargos = CCargos::GetInst();
    cargos.OrdenaPorImpressao();
    uebyte posicao = 0;
    for (cargos.Reset(); !cargos.IsFim(); cargos.Next()) {
        ordem.emplace(cargos.GetCurrent().GetID(), ++posicao);
    }
    return ordem;
}

} // namespace

CGravadorBU::CGravadorBU(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona, TLocalID local,
    TSecaoID secao, char fase, const api::CDateTime& dataHoraEmissao,
    const md::estadoaplicacao::CDadoCorrespondencia& correspondencia, std::vector<std::string> historicoCodigosCarga,
    std::map<md::ETipoAbrangencia, SQtdeAptos> qtdAptos, bool temDetalhamento, ueword qtdEleitoresCompareceram,
    const CRdv* rdv, const md::CDadosBUVota& dadosVota,
    const ecourna::app::dados::CDetalhamentoComparecimento& detalhamento)
    : CGravadorBU(dataHora, municipio, zona, local, secao, fase, dataHoraEmissao, correspondencia,
          std::move(historicoCodigosCarga), std::move(qtdAptos), temDetalhamento, qtdEleitoresCompareceram, rdv,
          dadosVota, std::nullopt, std::nullopt, detalhamento)
{
}

CGravadorBU::CGravadorBU(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona, TLocalID local,
    TSecaoID secao, char fase, const api::CDateTime& dataHoraEmissao,
    const md::estadoaplicacao::CDadoCorrespondencia& correspondencia, std::vector<std::string> historicoCodigosCarga,
    std::map<md::ETipoAbrangencia, SQtdeAptos> qtdAptos, bool temDetalhamento, ueword qtdEleitoresCompareceram,
    const CRdv* rdv, std::optional<md::CDadosBUVota> dadosVota, std::optional<md::CTipoApuracaoSA> tipoApuracao,
    std::optional<md::CDadosBUSA> dadosSA,
    std::optional<ecourna::app::dados::CDetalhamentoComparecimento> detalhamento)
    : IGravador(municipio, zona, local, secao, fase, EXTENSAO_BU_DAT, static_cast<ESavdArquivoUE>(35)),
      m_dataHora(dataHora), m_dataHoraEmissao(dataHoraEmissao), m_faseUrna(CGravadorUtil::ConverteFase(fase)),
      m_tipoArquivo(TIPO_ARQUIVO_VOTACAO_UE), m_correspondencia(correspondencia),
      m_historicoCodigosCarga(std::move(historicoCodigosCarga)), m_qtdAptos(std::move(qtdAptos)),
      m_temDetalhamento(temDetalhamento), m_qtdEleitoresCompareceram(qtdEleitoresCompareceram), m_rdv(rdv),
      m_arquivoChave("bu.pk1"), m_criptografa(true), m_dadosVota(dadosVota), m_tipoApuracao(tipoApuracao),
      m_dadosSA(dadosSA), m_ordemCargos(MontaOrdemCargos()), m_detalhamento(detalhamento)
{
}

// (original lines 165-203: content not recovered)
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

std::vector<md::CCargo> FiltraCargos(const std::vector<md::CCargo>& cargos, md::CCargo::ETipo tipo);

namespace {

md::CResultadoVotacao MontaResultadoVotacao(md::CCargo::ETipo tipo, CGravadorBU::TQtdEleitor comparecimento,
    const std::vector<md::CCargo>& cargos, const std::map<md::TCargoID, uebyte>& ordemCargos, const CRdv& rdv,
    const CCandidaturas& candidaturas, const CPartidos& partidos)
{
    return md::CResultadoVotacao(tipo, comparecimento,
        MontaVotosCargos(cargos, ordemCargos, rdv, candidaturas, partidos));
}

} // namespace

std::vector<md::CResultadoVotacao> MontaResultadosVotacao(const std::vector<md::CCargo>& cargos,
    const std::map<md::TCargoID, uebyte>& ordemCargos, const CRdv& rdv, const CCandidaturas& candidaturas,
    const CPartidos& partidos)
{
    std::vector<md::CResultadoVotacao> resultados;
    const std::vector<md::CCargo> majoritarios = FiltraCargos(cargos, md::CCargo::MAJORITARIO);
    const std::vector<md::CCargo> proporcionais = FiltraCargos(cargos, md::CCargo::PROPORCIONAL);
    const std::vector<md::CCargo> consultas = FiltraCargos(cargos, md::CCargo::CONSULTA);

    CGravadorBU::TQtdEleitor comparecimento = 0;
    if (!majoritarios.empty()) {
        comparecimento = rdv.Cargo(majoritarios.at(0).GetID()) / majoritarios.at(0).GetQtdeEscolhas();
    } else if (!consultas.empty()) {
        comparecimento = rdv.Cargo(consultas.at(0).GetID()) / consultas.at(0).GetQtdeEscolhas();
    }
    CGravadorBU::TQtdEleitor comparecimentoProporcional = 0;
    if (!proporcionais.empty()) {
        comparecimentoProporcional =
            rdv.Cargo(proporcionais.at(0).GetID()) / proporcionais.at(0).GetQtdeEscolhas();
    }

    md::CResultadoVotacao resultado = MontaResultadoVotacao(md::CCargo::PROPORCIONAL, comparecimentoProporcional,
        proporcionais, ordemCargos, rdv, candidaturas, partidos);
    if (resultado.GetTotaisVotosCargo().size() > 0) {
        resultados.push_back(resultado);
    }
    resultado = MontaResultadoVotacao(md::CCargo::MAJORITARIO, comparecimento, majoritarios, ordemCargos, rdv,
        candidaturas, partidos);
    if (resultado.GetTotaisVotosCargo().size() > 0) {
        resultados.push_back(resultado);
    }
    resultado = MontaResultadoVotacao(md::CCargo::CONSULTA, comparecimento, consultas, ordemCargos, rdv,
        candidaturas, partidos);
    if (resultado.GetTotaisVotosCargo().size() > 0) {
        resultados.push_back(resultado);
    }
    return resultados;
}

std::vector<md::CResultadoVotacaoPorEleicao> MontaResultadosVotacaoPorEleicao(const md::TVectorEleicaoPE& eleicoes,
    const std::map<md::TCargoID, uebyte>& ordemCargos, const std::map<md::ETipoAbrangencia, SQtdeAptos>& qtdAptos,
    const CRdv& rdv, const CCandidaturas& candidaturas, const CPartidos& partidos)
{
    std::vector<md::CResultadoVotacaoPorEleicao> resultados;
    for (const md::CEleicaoPE& eleicao : eleicoes) {
        const md::TEleicaoID idEleicao = eleicao.GetID();
        const std::vector<md::CCargo> cargos = CConfiguracaoEleicao::GetInst().GetCargos(idEleicao, true);
        const std::vector<md::CResultadoVotacao> resultadosVotacao =
            MontaResultadosVotacao(cargos, ordemCargos, rdv, candidaturas, partidos);
        const md::CResultadoVotacaoPorEleicao resultado(idEleicao, qtdAptos.at(eleicao.GetAbrangencia()),
            resultadosVotacao);
        resultados.push_back(resultado);
    }
    return resultados;
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

// (original lines 406-447: content not recovered)
#line 448
void CGravadorBU::GravaResultado(api::CFile& arquivo) const
{
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    const EUrnaTipo tipoUrna = geral.GetDadoCarga().GetTipoUrna();

    std::string numeroSerieFV("00000000");
    const std::filesystem::path arquivoInfoMidia = CPath::GetPathEstatico(FLASH_EXTERNA) / "infomidia.dat";
    if (api::CSystem::ExistFile(arquivoInfoMidia)) {
        const ecourna::app::dados::CInformacaoMidia informacaoMidia =
            CarregaArquivoEcourna<ecourna::app::dados::asn::CConversorInformacaoMidia>(arquivoInfoMidia);
        numeroSerieFV = ecourna::api::util::CStringUtils::BytesToHexString(
            informacaoMidia.GetDadosGeracaoMidia().GetSerialMidia().GetSerial());
    }

    const CConfiguracaoEleicao& configuracao = CConfiguracaoEleicao::GetInst();
    const std::vector<md::CResultadoVotacaoPorEleicao> resultados =
        MontaResultadosVotacaoPorEleicao(configuracao.GetPleito().GetEleicoes(), m_ordemCargos, m_qtdAptos, *m_rdv,
            CCandidaturas::GetInst(), CPartidos::GetInst());
    const md::CCabecalhoEntidade cabecalho(m_dataHora, configuracao.GetPleito().GetID(), md::TIPO_CABECALHO_PLEITO);
    const md::estadoaplicacao::CLocalidadeEleitoral secaoCarga = m_correspondencia.GetSecaoCarga();
    const md::CCarga carga(m_correspondencia.GetNumeroInternoUrna(), m_correspondencia.GetNumeroSerieFC(),
        m_correspondencia.GetDataHoraCarga(), m_correspondencia.GetCodigoCarga(),
        m_correspondencia.GetIdentificadorGeradorMidia());
    const md::CCorrespondenciaResultado correspondencia(secaoCarga.GetMunicipio(), secaoCarga.GetZona(),
        secaoCarga.GetSecao(), carga, m_secao != 0 ? eUrnaVota : eUrnaContingencia);
    const md::CUrna urna = m_tipoApuracao
        ? md::CUrna(tipoUrna, "10.23.0.1 - DESENVOLVIMENTO", correspondencia, m_tipoArquivo, numeroSerieFV,
              *m_tipoApuracao)
        : md::CUrna(tipoUrna, "10.23.0.1 - DESENVOLVIMENTO", correspondencia, m_tipoArquivo, numeroSerieFV);
    const md::CEntidadeBU entidade = MontaEntidadeBU(cabecalho, urna, resultados, m_historicoCodigosCarga);
    const std::vector<char> codificado = asn::Codifica(entidade);

    if (m_criptografa && configuracao.GetParametrosUrna().GetCriptografarBU()) {
        std::vector<uebyte> dados(codificado.size());
        std::copy(codificado.begin(), codificado.end(), dados.begin());
        uebyte tabelaCriptografia[1024];
        auto& hardwareUrna = api::CPolySingleton<api::IUrna>::instance();
        auto& rand = api::CPolySingleton<ecourna::api::security::IRng>::instance();
        hardwareUrna.Slot4(tabelaCriptografia);
        std::vector<uebyte> numeroAleatorio(32);
        rand.Generate(numeroAleatorio);
        const std::vector<uebyte> chave = LeChavePublica();
        const ecourna::api::cepesc::CPlainText texto(m_zona, m_secao,
            std::vector<uebyte>(tabelaCriptografia, tabelaCriptografia + sizeof(tabelaCriptografia)), numeroAleatorio,
            chave, dados);
        const ecourna::api::cepesc::CCepescCipher cifrador;
        const ecourna::api::cepesc::CCipheredOut cifrado = cifrador.Encrypt(texto);
        const md::CSeguranca seguranca(0, 1, cifrado.GetChave());
        const md::CEnvelopeGenerico envelope(cabecalho, m_faseUrna, m_municipio, m_zona, std::optional<TLocalID>(m_local),
            m_secao, md::CEnvelopeGenerico::ENVELOPE_BOLETIM_URNA, seguranca, cifrado.GetConteudo(), urna.GetTipoUrna());
        asn::GravaArquivo(arquivo, envelope);
    } else {
        const std::vector<uebyte> conteudo(codificado.begin(), codificado.end());
        const md::CEnvelopeGenerico envelope(cabecalho, m_faseUrna, m_municipio, m_zona, std::optional<TLocalID>(m_local),
            m_secao, md::CEnvelopeGenerico::ENVELOPE_BOLETIM_URNA, conteudo, urna.GetTipoUrna());
        asn::GravaArquivo(arquivo, envelope);
    }
}

// (original lines 507-537: content not recovered)
#line 538
std::vector<uebyte> CGravadorBU::LeChavePublica() const
{
    const std::filesystem::path arquivo = CPath::GetPathChave() / "bu.pk1";
    if (!api::CSystem::ExistFile(arquivo)) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8639,
                                      "O arquivo " + arquivo.string() + " não existe");
    }

    ModuloEnvelopeChave::EntidadeChave entidade;
    ecourna::api::io::DeserializeFromFile(entidade, arquivo);
    const std::vector<uebyte> chaveCifrada(entidade.get_chave().begin(), entidade.get_chave().end());

    ecourna::api::security::CSymmetricCipherFactory fabrica;

    const std::vector<uebyte> senhas = api::CPolySingleton<api::IKernelHSM>::instance().GetSenha();
    const std::string senha(senhas.begin(), senhas.end());
    const std::shared_ptr<ecourna::api::security::ISymmetricCipher> cifra = fabrica.Create(senha);

    std::vector<uebyte> chave;
    cifra->Decrypt(chaveCifrada, chave);

    if (chave.size() == 0) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8640,
                                      "O arquivo " + arquivo.string() + " está vazio");
    }
    return chave;
}

// (original lines 566-609: content not recovered)
#line 610
md::CEntidadeBU CGravadorBU::MontaEntidadeBU(const md::CCabecalhoEntidade& cabecalho, const md::CUrna& urna,
    const std::vector<md::CResultadoVotacaoPorEleicao>& resultados,
    const std::vector<std::string>& historicoCodigosCarga) const
{
    const std::vector<md::CHistoricoVotoImpresso> historicoVotoImpresso;
    if (m_dadosVota.has_value()) {
        if (m_temDetalhamento) {
            return md::CEntidadeBU(cabecalho, m_faseUrna, urna, m_municipio, m_zona, m_local, m_secao,
                m_qtdEleitoresCompareceram, resultados, historicoCodigosCarga, *m_dadosVota, m_dataHoraEmissao,
                historicoVotoImpresso, *m_detalhamento);
        }
        return md::CEntidadeBU(cabecalho, m_faseUrna, urna, m_municipio, m_zona, m_local, m_secao,
            m_qtdEleitoresCompareceram, resultados, historicoCodigosCarga, *m_dadosVota, m_dataHoraEmissao,
            historicoVotoImpresso);
    }
    if (m_dadosSA.has_value()) {
        if (m_temDetalhamento) {
            return md::CEntidadeBU(cabecalho, m_faseUrna, urna, m_municipio, m_zona, m_local, m_secao,
                m_qtdEleitoresCompareceram, resultados, historicoCodigosCarga, *m_dadosSA, m_dataHoraEmissao,
                historicoVotoImpresso, *m_detalhamento);
        }
        return md::CEntidadeBU(cabecalho, m_faseUrna, urna, m_municipio, m_zona, m_local, m_secao,
            m_qtdEleitoresCompareceram, resultados, historicoCodigosCarga, *m_dadosSA, m_dataHoraEmissao,
            historicoVotoImpresso);
    }

    throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8641, "Dados específicos do aplicativo não presentes");
}

} // namespace comum
