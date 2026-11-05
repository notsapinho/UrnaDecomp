// vota::CMostraEleitorVotando (/home/rubio/tse/uenux2/src/app/vota/operador/aguardaeleitor/cmostraeleitorvotando.cpp).
// Reconstruction's note, not TSE's text. Records: 10426's (ProcessInput) at line 64, column 22, and 10425's (ProcessKey,
// SalvaHabilitacaoEleitor's) at 127 and 159, column 31; the other lines are chosen (unit 142's fragment says why).
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "api/gui/cmtformbuilder.h"
#include "api/hwil/iinput.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cinfomtlcd.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/celeitordadoshabilitacao.h"
#include "app/comum/gravadores/pathwsq.h"
#include "app/comum/reconhecimentobiometrico/ccontrolaarmazenamentodeimagens.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/operador/aguardaeleitor/celeitordemorando.h"
#include "app/vota/operador/aguardaeleitor/celeitorvotounaovotou.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"
#include "app/vota/operador/csincronismooperador.h"
#include "app/vota/operador/cthreadoperador.h"
#include "ecourna/api/util/cstringutils.hpp"
namespace vota {
CMostraEleitorVotando::~CMostraEleitorVotando() = default;

namespace {
std::string TextoAudioAtivado()
{
    if ((CThreadEleitor::Existe() && CEstadoAudio::GetInst().Ativo()) || IsAudioAtivadoMesario()) {
        return "ÁUDIO ATIVADO";
    }
    return " ";
}
} // namespace

CMostraEleitorVotando::CMostraEleitorVotando()
    : comum::CAppState(EVENTO_TECLA | EVENTO_ENTRADA)
    , m_nome(std::make_shared<std::string>())
    , m_form(CriaForm(m_nome))
{
}
CMostraEleitorVotando& CMostraEleitorVotando::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMostraEleitorVotando());
    }
    return *s_inst;
}
std::unique_ptr<CMostraEleitorVotando> CMostraEleitorVotando::s_inst;
std::mutex CMostraEleitorVotando::s_mutex;

void CMostraEleitorVotando::StartState()
{
    *m_nome = CThreadOperador::GetInst().GetTextoEleitor();
    m_form->Slot2();
    comum::CInfoMTLCD::GetInst().MostraIconeBateria();
    m_pNextState = this;
}
void CMostraEleitorVotando::ProcessInput()
{
    auto& terminal = api::CPolySingleton<api::IInputMT>::instance();
    if (terminal.HasKey()) {
        terminal.GetKey();
    }
}

std::shared_ptr<api::IForm<api::IScreenMT>> CMostraEleitorVotando::CriaForm(std::shared_ptr<std::string> nome)
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_1);
    if (comum::CAppInfo::EhTreinamentoEleitor()) {
        builder.AddTextField("TREINAMENTO DE ELEITORES", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    } else {
        builder.AddTextField(&comum::CEleitorDadoNomeParaUrna::Text, api::SPoint{1, 1}, "{:35}", api::ALINHAMENTO_ESQUERDA);
        builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
        builder.AddTextField("Seq:", api::SPoint{32, 2}, api::ALINHAMENTO_ESQUERDA);
        builder.AddTextField(&comum::CEleitorDadoSequencial::Text, api::SPoint{40, 2}, "{:04}", api::ALINHAMENTO_DIREITA);
        builder.AddTextField("Seção:", api::SPoint{30, 3}, api::ALINHAMENTO_ESQUERDA);
        builder.AddTextField(&comum::CEleitorDadoSecao::Text, api::SPoint{40, 3}, "{:04}", api::ALINHAMENTO_DIREITA);
    }
    builder.AddTextField(&TextoAudioAtivado, api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(api::CTextSource(nome), api::SPoint{1, 4});
    return builder.GetForm("");
}

void CMostraEleitorVotando::ProcessKey(uebyte tecla)
{
    switch (tecla) {
        case 13:
            CSincronismoOperador::GetInst().SetSincronizado(false);
            m_pNextState = &CSincronismoOperador::GetInst();
            *m_nome = std::string(" ");
            break;
        case 3:
            CEleitorDemorando::GetInst().SetVotou(false);
            m_pNextState = &CEleitorDemorando::GetInst();
            break;
        case 4:
            CEleitorDemorando::GetInst().SetVotou(true);
            m_pNextState = &CEleitorDemorando::GetInst();
            break;
        case 2:
            CEleitorVotouNaoVotou::GetInst().SetVotou(false);
            m_pNextState = &CEleitorVotouNaoVotou::GetInst();
            break;
        case 9:
            *m_nome = CThreadOperador::GetInst().GetTextoEleitor();
            m_form->Slot2();
            break;
        case 6:
            SalvaHabilitacaoEleitor();
            break;
    }
}
void CMostraEleitorVotando::SalvaHabilitacaoEleitor()
{
    if (!(comum::CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase() == comum::FASE_TREINAMENTO &&
          comum::CAppInfo::GetInst().GetVota().GetTreinamentoEleitor())) {
        switch (impl::IInformacaoThreadOperador::GetInst().GetEstadoBiometria()) {
            case impl::IInformacaoThreadOperador::BiometriaEleitor: {
                if (!EhTreinamento()) {
                    const std::vector<uebyte> digital = CControlaReconhecimento::GetDigitalCapturada();
                    if (digital.empty()) {
                        throw CUeVotaError(EUE_VOTA_SEM_DADOS_BIOMETRIA_ELEITOR,
                                           "Não há dados salvos de biometria do eleitor.");
                    }
                    ArmazenaImagemHabilitado(digital, CControlaReconhecimento::GetTentativaRegistrada(),
                                             CControlaReconhecimento::GetDedoCorrente());
                }
                const comum::CEleitorDadosHabilitacao dados(
                    GetIdentidadeEleitor(), comum::CEleitorDadosHabilitacao::HABILITACAO_BIOMETRICA, TipoAtivacaoAudio(),
                    CControlaReconhecimento::GetInst().GetDadosBiometriaEleitor(), GetApresentacaoFotoEleitor());
                comum::CEleitores::GetInst().MarcaEleitorFoiHabilitado(dados);
                break;
            }

            // (original lines 140-150: content not recovered)
#line 151
            case impl::IInformacaoThreadOperador::BiometriaOperador: {
                if (!EhTreinamento()) {
                    const std::vector<uebyte> digitalEleitor = CControlaReconhecimento::GetDigitalCapturada();
                    if (!digitalEleitor.empty()) {
                        ArmazenaImagemNaoHabilitado(digitalEleitor, CControlaReconhecimento::GetTentativaRegistrada());
                    }
                    const std::vector<uebyte> digitalMesario = CControlaReconhecimento::GetDigitalRegistrada();
                    if (digitalMesario.empty()) {
                        throw CUeVotaError(EUE_VOTA_SEM_DADOS_BIOMETRIA_MESARIO,
                                           "Não há dados salvos de biometria do mesário.");
                    }
                    ArmazenaImagemOperador(digitalMesario);
                }
                if (!CControlaReconhecimento::GetDedoRegistrado().empty()) {
                    const comum::CEleitorDadosHabilitacao dados(
                        GetIdentidadeEleitor(), comum::CEleitorDadosHabilitacao::HABILITACAO_MESARIO, TipoAtivacaoAudio(),
                        CControlaReconhecimento::GetInst().GetDadosBiometriaMesario(), GetApresentacaoFotoEleitor());
                    comum::CEleitores::GetInst().MarcaEleitorFoiHabilitado(dados);
                } else {
                    const comum::CEleitorDadosHabilitacao dados(
                        GetIdentidadeEleitor(), comum::CEleitorDadosHabilitacao::HABILITACAO_MESARIO, TipoAtivacaoAudio(),
                        CControlaReconhecimento::GetInst().GetDadosBiometriaOperador(), GetApresentacaoFotoEleitor());
                    comum::CEleitores::GetInst().MarcaEleitorFoiHabilitado(dados);
                }
                break;
            }
            case impl::IInformacaoThreadOperador::SemBiometria: {
                const comum::CEleitorDadosHabilitacao dados(
                    GetIdentidadeEleitor(), comum::CEleitorDadosHabilitacao::HABILITACAO_SEM_BIOMETRIA, TipoAtivacaoAudio(),
                    CControlaReconhecimento::GetInst().GetDadosSemBiometria(), GetApresentacaoFotoEleitor());
                comum::CEleitores::GetInst().MarcaEleitorFoiHabilitado(dados);
                break;
            }
            default:
                break;
        }
    }
}

int TipoAtivacaoAudio()
{
    if (CEstadoAudio::GetInst().Modo0Selecionado()) {
        return 0;
    }
    return CEstadoAudio::GetInst().Modo1Selecionado() ? 1 : 2;
}

void ArmazenaImagemHabilitado(const std::vector<uebyte>& wsq, uebyte tentativa, uebyte dedo)
{
    const comum::md::CEleitorDecorator& eleitor = comum::CEleitores::GetInst().GetCurrent()->GetEleitor();
    const std::string titulo = eleitor.GetIdentidadePorTipo(eleitor.GetTipoIdentificador()).GetIdentificador();
    const std::string nomeArquivo = ecourna::api::util::CStringUtils::PreencheAEsquerda(titulo, '0', 12) +
                                    std::format("-{:02}-{:02}", tentativa, dedo);
    const std::filesystem::path diretorio = comum::GetPathWsqHabilitado();
    const std::filesystem::path diretorioExterno = comum::GetPathWsqHabilitadoExterno();
    comum::CControlaArmazenamentoDeImagens::ArmazenaImagem(wsq, nomeArquivo, diretorio, diretorioExterno, "");
}

void ArmazenaImagemNaoHabilitado(const std::vector<uebyte>& wsq, uebyte tentativa)
{
    const comum::md::CEleitorDecorator& eleitor = comum::CEleitores::GetInst().GetCurrent()->GetEleitor();
    const std::string titulo = eleitor.GetIdentidadePorTipo(eleitor.GetTipoIdentificador()).GetIdentificador();
    const std::string nomeArquivo =
        ecourna::api::util::CStringUtils::PreencheAEsquerda(titulo, '0', 12) + std::format("-{:02}Err", tentativa);
    const std::filesystem::path diretorio = comum::GetPathWsqNaoHabilitado();
    const std::filesystem::path diretorioExterno = comum::GetPathWsqNaoHabilitadoExterno();
    comum::CControlaArmazenamentoDeImagens::ArmazenaImagem(wsq, nomeArquivo, diretorio, diretorioExterno, "");
}
void ArmazenaImagemOperador(const std::vector<uebyte>& wsq)
{
    const comum::md::CEleitorDecorator& eleitor = comum::CEleitores::GetInst().GetCurrent()->GetEleitor();
    const std::string titulo = eleitor.GetIdentidadePorTipo(eleitor.GetTipoIdentificador()).GetIdentificador();
    const std::string nomeArquivo = ecourna::api::util::CStringUtils::PreencheAEsquerda(titulo, '0', 12) + "_Operador";
    const std::filesystem::path diretorio = comum::GetPathWsqOperador();
    const std::filesystem::path diretorioExterno = comum::GetPathWsqOperadorExterno();
    comum::CControlaArmazenamentoDeImagens::ArmazenaImagem(wsq, nomeArquivo, diretorio, diretorioExterno, "");
}

} // namespace vota
