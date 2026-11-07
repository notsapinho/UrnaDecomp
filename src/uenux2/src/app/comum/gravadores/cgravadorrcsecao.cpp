// comum::CGravadorRCSecao (/home/rubio/tse/uenux2/src/app/comum/gravadores/cgravadorrcsecao.cpp): GravaResultado
// (target fn 11616, record at line 110) and the functions it holds inlined by binaryen, LeChavePublica (records at lines
// 65, 75 and 83) among them; CriaIdentidadeEleitor (fn 5845, record 230) and ConverteComparecimentoMesario (fn 5841);
// the constructor, which fn 12098 holds inlined (no index; unrooted). src/units/122-uenux2-app-comum-gravadores.mk
// says what each rests on. This header comment, the includes and the lines of the functions with no record are the
// reconstruction's.
#include "app/comum/gravadores/cgravadorrcsecao.h"

#include <algorithm>
#include <filesystem>
#include <format>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "api/hwil/ikernelhsm.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "app/comum/carquivosresultado.h"
#include "app/comum/comparecimentomesario/cregistradormesario.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/comum/gravadores/asn/cconversorresultadournacadastro.h"
#include "app/comum/gravadores/cgravadorutil.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"
#include "app/comum/justificativa/cjustificador.h"
#include "asn1/modules/ModuloEnvelopeChave.h"
#include "ecourna/api/io/asn/serialization.hpp"
#include "ecourna/api/security/cepesc/ccepesccipher.hpp"
#include "ecourna/api/security/cepesc/cplaintext.hpp"
#include "ecourna/api/security/csymmetriccipherfactory.hpp"
#include "ecourna/api/security/irng.hpp"
#include "ecourna/api/security/isymmetriccipher.hpp"
#include "ecourna/app/dados/cnumerocpf.hpp"
#include "ecourna/app/dados/cnumeroidentificacaolivre.hpp"
#include "ecourna/app/dados/cnumeroinscricaoeleitoral.hpp"

namespace comum {

using namespace ecourna::app::dados;

CGravadorRCSecao::CGravadorRCSecao(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona, TLocalID local,
    TSecaoID secao, char fase, char situacao)
    : IGravador(municipio, zona, local, secao, fase, EXTENSAO_JUFA_DAT, static_cast<ESavdArquivoUE>(39)),
      m_dataHora(dataHora), m_faseUrna(CGravadorUtil::ConverteFaseEcourna(fase)),
      m_situacao(CGravadorUtil::ConverteSituacaoArquivoEcourna(situacao))
{
}

// (original lines 55-60: content not recovered)
#line 61
std::vector<uebyte> CGravadorRCSecao::LeChavePublica() const
{
    const std::filesystem::path arquivo = CPath::GetPathChave() / "jufa.pk1";
    if (!api::CSystem::ExistFile(arquivo)) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8655,
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

    if (chave.empty()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8656,
                                      "O arquivo " + arquivo.string() + " está vazio");
    }
    return chave;
}

// (original lines 89-95: content not recovered)
#line 96
void CGravadorRCSecao::GravaResultado(api::CFile& arquivo) const
{
    const CCabecalhoEntidade cabecalho(boost::posix_time::from_iso_string(FormataDataHora(m_dataHora)),
                                       CConfiguracaoEleicao::GetInst().GetPleito().GetID(),
                                       CCabecalhoEntidade::TIPO_ID_PLEITO);
    const CMunicipioZona municipioZona(ecourna::app::dados::TMunicipioID{m_municipio},
                                       ecourna::app::dados::TZonaID{m_zona});
    const CIdentificacaoSecaoEleitoral identificacao(municipioZona, ecourna::app::dados::TLocalID{m_local},
                                                     ecourna::app::dados::TSecaoID{m_secao});
    const CComparecimentoSecao comparecimento(identificacao, ObtemComparecimentoEleitores());
    const CDadosComparecimento dados(ObtemJustificativas(), comparecimento, ObtemMesariosAbertura(),
                                     ObtemMesariosEncerramento());

    if (CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetCriptografarJUFA()) {
        auto& geradorRng = api::CPolySingleton<ecourna::api::security::IRng>::instance();
        std::vector<uebyte> aleatorio(32);
        geradorRng.Generate(aleatorio);
        const std::vector<uebyte> salt(aleatorio.begin(), aleatorio.begin() + 16);
        const std::vector<uebyte> info(aleatorio.begin() + 16, aleatorio.end());
        const ecourna::api::cepesc::CInfoSalt infoSalt(salt, info);

        const ecourna::api::cepesc::CPlainText texto(LeChavePublica(), asn::CodificaDadosComparecimento(dados),
                                                     infoSalt);
        const ecourna::api::cepesc::CCepescCipher cifrador;
        const ecourna::api::cepesc::CCipheredOut cifrado = cifrador.Encrypt(texto);

        const CDadosCifracao dadosCifracao(cifrado.GetChave(), infoSalt.GetSalt(), infoSalt.GetInfo());
        const CDadosComparecimentoCifrado comparecimentoCifrado(dadosCifracao, cifrado.GetConteudo());
        const CResultadoUrnaCadastro resultado(cabecalho, m_faseUrna, "10.23.0.1 - DESENVOLVIMENTO", m_situacao,
                                               comparecimentoCifrado);
        asn::GravaArquivo(arquivo, resultado);
    } else {
        const CResultadoUrnaCadastro resultado(cabecalho, m_faseUrna, "10.23.0.1 - DESENVOLVIMENTO", m_situacao,
                                               dados);
        asn::GravaArquivo(arquivo, resultado);
    }
}

std::string FormataDataHora(const api::CDateTime& dataHora)
{
    const api::CDate& data = dataHora.GetData();
    const api::CTime& hora = dataHora.GetHora();
    return std::format("{:04}{:02}{:02}T{:02}{:02}{:02}", data.GetAno(), data.GetMes(), data.GetDia(), hora.GetHora(),
                       hora.GetMinuto(), hora.GetSegundo());
}

static CIdentificacaoJustificativa CriaJustificativa(const CNumeroInscricaoEleitoral& titulo,
                                                     const CJustificadorDetalhe& detalhe)
{
    const TSharedIdentificadorEleitor eleitor =
        std::make_shared<CNumeroInscricaoEleitoral>(CNumeroInscricaoEleitoral(titulo.GetNumero()));
    return CIdentificacaoJustificativa(CRegistroIdentificacaoEleitor(eleitor), TAno(detalhe.GetAno()));
}

TVectorIdentificacaoJustificativa ObtemJustificativas()
{
    TVectorIdentificacaoJustificativa justificativas;
    if (CJustificador::HasInst()) {
        for (const auto& [titulo, detalhe] : CJustificador::GetInst().GetRegistros()) {
            justificativas.push_back(CriaJustificativa(titulo, detalhe));
        }
    }
    return justificativas;
}

std::vector<md::CComparecimentoMesario> ObtemRegistrosMesariosAbertura()
{
    std::vector<md::CComparecimentoMesario> registros;
    for (const auto& [chave, registro] : CRegistradorMesario::GetInst().GetRegistros()) {
        if (chave.GetPeriodoPresente() == 1) {
            registros.push_back(md::CComparecimentoMesario(registro));
        }
    }
    return registros;
}

TVectorComparecimentoMesario ObtemMesariosAbertura()
{
    TVectorComparecimentoMesario mesarios;
    if (CRegistradorMesario::HasInst()) {
        for (const md::CComparecimentoMesario& registro : ObtemRegistrosMesariosAbertura()) {
            mesarios.push_back(ConverteComparecimentoMesario(registro));
        }
    }
    return mesarios;
}

std::vector<md::CComparecimentoMesario> ObtemRegistrosMesariosEncerramento()
{
    std::vector<md::CComparecimentoMesario> registros;
    for (const auto& [chave, registro] : CRegistradorMesario::GetInst().GetRegistros()) {
        if (chave.GetPeriodoPresente() == 2) {
            registros.push_back(md::CComparecimentoMesario(registro));
        }
    }
    return registros;
}

TVectorComparecimentoMesario ObtemMesariosEncerramento()
{
    TVectorComparecimentoMesario mesarios;
    if (CRegistradorMesario::HasInst()) {
        for (const md::CComparecimentoMesario& registro : ObtemRegistrosMesariosEncerramento()) {
            mesarios.push_back(ConverteComparecimentoMesario(registro));
        }
    }
    return mesarios;
}

// (original lines 205-209: content not recovered)
#line 210
ecourna::app::dados::TSharedIdentificadorEleitor CGravadorRCSecao::CriaIdentidadeEleitor(
    const comum::md::CEleitorIdentidade& identidade) const
{
    switch (identidade.GetTipo()) {
        case ecourna::app::dados::TipoIDInscricaoEleitoral: {
            const ecourna::app::dados::CNumeroInscricaoEleitoral numero(identidade.GetIdentificador());
            return std::make_shared<ecourna::app::dados::CNumeroInscricaoEleitoral>(numero);
        }
        case ecourna::app::dados::TipoIDCPF: {
            const ecourna::app::dados::CNumeroCPF numero(identidade.GetIdentificador());
            return std::make_shared<ecourna::app::dados::CNumeroCPF>(numero);
        }
        case ecourna::app::dados::TipoIDNumeroLivre: {
            const ecourna::app::dados::CNumeroIdentificacaoLivre numero(identidade.GetIdentificador());
            return std::make_shared<ecourna::app::dados::CNumeroIdentificacaoLivre>(numero);
        }
        default:
            break;
    }

    throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8654,
        std::format("Tipo de identidade invalida: {}", static_cast<int>(identidade.GetTipo())));
}

static CComparecimentoMesario::EEstadoColetaDigital ConverteEstadoColetaDigital(
    const bool pertenceSecao, const md::CComparecimentoMesario::EstadoReconhecimentoBiometrico estadoBiometria,
    const md::CDedo::TipoDedo dedoHabilitacao)
{
    if (estadoBiometria == 1) {
        return CComparecimentoMesario::EstadoColetaDigitalNaoInformado;
    }
    if (pertenceSecao && estadoBiometria == 2 && dedoHabilitacao) {
        return CComparecimentoMesario::NaoColetadaReconhecidaNoCadastro;
    }
    if (pertenceSecao && estadoBiometria == 2 && !dedoHabilitacao) {
        return CComparecimentoMesario::ColetadaDigitalNaoReconhecidaNoCadastro;
    }
    if (pertenceSecao && estadoBiometria != 2) {
        return CComparecimentoMesario::ColetadaMesarioNaoPossuiDigitalNoCadastro;
    }
    return CComparecimentoMesario::ColetadaMesarioNaoPertenceASecao;
}

CComparecimentoMesario ConverteComparecimentoMesario(const md::CComparecimentoMesario& mesario)
{
    const TSharedIdentificadorEleitor identificador = std::make_shared<CNumeroInscricaoEleitoral>(
        CNumeroInscricaoEleitoral(std::string(mesario.GetMesario().GetIdentificador())));
    const CRegistroIdentificacaoEleitor registro(identificador);
    const boost::posix_time::ptime dataHoraColeta =
        boost::posix_time::from_time_t(mesario.GetDataHoraRegistro().ConvertToLocalTime());
    return CComparecimentoMesario(registro, dataHoraColeta,
                                  ConverteEstadoColetaDigital(mesario.PertenceSecao(), mesario.GetEstadoBiometria(),
                                                              mesario.GetDedoHabilitacao()));
}

TVectorEstadoComparecimento CGravadorRCSecao::ObtemComparecimentoEleitores() const
{
    TVectorEstadoComparecimento eleitores;
    for (const auto& [identidade, detalhe] : CEleitores::GetInst().GetRegistros()) {
        if (!detalhe.SemImpedimento()) {
            continue;
        }
        const md::CEleitorDinamico& dinamico = detalhe.GetDinamico();
        const TSharedIdentificadorEleitor principal = CriaIdentidadeEleitor(identidade);
        const TSharedIdentificadorEleitor habilitacao = CriaIdentidadeEleitor(dinamico.GetIdentidadeHabilitacao());
        switch (dinamico.GetEstadoComparecimento()) {
            case CEstadoComparecimento::Faltou:
                eleitores.emplace_back(CRegistroIdentificacaoEleitor(habilitacao, principal),
                                       CEstadoComparecimento::Faltou);
                break;
            case CEstadoComparecimento::SemCargoParaVotar:
                eleitores.emplace_back(
                    CRegistroIdentificacaoEleitor(habilitacao, principal), CEstadoComparecimento::SemCargoParaVotar,
                    dinamico.GetApresentacaoFoto(),
                    static_cast<CEstadoComparecimento::ESituacaoHabilitacaoAudio>(dinamico.GetTipoAtivacaoAudio()));
                break;
            default: {
                const auto situacao =
                    static_cast<CEstadoComparecimento::ESituacaoComparecimento>(dinamico.GetEstadoComparecimento());
                switch (dinamico.GetTipoHabilitacao()) {
                    case 0:
                        eleitores.emplace_back(
                            CRegistroIdentificacaoEleitor(habilitacao, principal), situacao,
                            dinamico.GetApresentacaoFoto(),
                            static_cast<CEstadoComparecimento::ESituacaoHabilitacaoAudio>(dinamico.GetTipoAtivacaoAudio()));
                        break;
                    case 2: {
                        const CHabilitacaoBiometrica biometrica = CriaHabilitacaoPorMesario(dinamico);
                        eleitores.emplace_back(
                            CRegistroIdentificacaoEleitor(habilitacao, principal), situacao,
                            dinamico.GetApresentacaoFoto(),
                            static_cast<CEstadoComparecimento::ESituacaoHabilitacaoAudio>(dinamico.GetTipoAtivacaoAudio()),
                            biometrica);
                        break;
                    }
                    case 1: {
                        const CHabilitacaoBiometrica biometrica(
                            dinamico.GetNumeroTentativa(), TScoreHabilitacao(dinamico.GetScoreHabilitacao()),
                            static_cast<CDedo::ETipoDedo>(dinamico.GetDedoHabilitacao()),
                            CErroLeituraBiometria(static_cast<EErroLeituraBiometria>(dinamico.GetErroDecifrarBiometria())));
                        eleitores.emplace_back(
                            CRegistroIdentificacaoEleitor(habilitacao, principal), situacao,
                            dinamico.GetApresentacaoFoto(),
                            static_cast<CEstadoComparecimento::ESituacaoHabilitacaoAudio>(dinamico.GetTipoAtivacaoAudio()),
                            biometrica);
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
        }
    }
    return eleitores;
}

CHabilitacaoBiometrica CriaHabilitacaoPorMesario(const md::CEleitorDinamico& dinamico)
{
    if (dinamico.TemTituloMesarioHabilitacao()) {
        const TSharedIdentificadorEleitor mesario = std::make_shared<CNumeroInscricaoEleitoral>(
            CNumeroInscricaoEleitoral(dinamico.GetTituloMesarioHabilitacao().GetIdentificador()));
        const CEstadoHabilitacaoPorCodigo estado(ObtemSituacaoReconhecimentoMesario(dinamico),
                                                 CRegistroIdentificacaoEleitor(mesario));
        return CHabilitacaoBiometrica(
            dinamico.GetNumeroTentativa(), TScoreHabilitacao(dinamico.GetScoreHabilitacao()),
            static_cast<CDedo::ETipoDedo>(dinamico.GetDedoHabilitacao()),
            CErroLeituraBiometria(static_cast<EErroLeituraBiometria>(dinamico.GetErroDecifrarBiometria())), estado);
    }
    const CEstadoHabilitacaoPorCodigo estado(CEstadoHabilitacaoPorCodigo::NaoReconhecido);
    return CHabilitacaoBiometrica(
        dinamico.GetNumeroTentativa(), TScoreHabilitacao(dinamico.GetScoreHabilitacao()),
        static_cast<CDedo::ETipoDedo>(dinamico.GetDedoHabilitacao()),
        CErroLeituraBiometria(static_cast<EErroLeituraBiometria>(dinamico.GetErroDecifrarBiometria())), estado);
}

CEstadoHabilitacaoPorCodigo::ESituacaoReconhecimentoMesario ObtemSituacaoReconhecimentoMesario(
    const md::CEleitorDinamico& dinamico)
{
    if (!dinamico.TemTituloMesarioHabilitacao() || !CRegistradorMesario::HasInst()) {
        return CEstadoHabilitacaoPorCodigo::NaoReconhecido;
    }
    const auto& registros = CRegistradorMesario::GetInst().GetRegistros();
    const auto registro = std::find_if(registros.begin(), registros.end(), [dinamico](const auto& par) {
        return par.first.GetMesario() == dinamico.GetTituloMesarioHabilitacao() && par.first.GetPeriodoPresente() == 1;
    });
    if (registro == registros.end()) {
        return CEstadoHabilitacaoPorCodigo::NaoReconhecido;
    }
    if (!registro->second.PertenceSecao()) {
        return CEstadoHabilitacaoPorCodigo::ReconhecidoDigitalRegistroMesarios;
    }
    return registro->second.GetDedoHabilitacao() ? CEstadoHabilitacaoPorCodigo::ReconhecidoDigitalCadastroUrna
                                                 : CEstadoHabilitacaoPorCodigo::ReconhecidoDigitalRegistroMesarios;
}

} // namespace comum
