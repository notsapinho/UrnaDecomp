#include "app/comum/comparecimentomesario/estados/cpededigitalmesario.h"

#include <cmath>
#include <format>
#include <map>
#include <string>
#include <vector>

#include "api/gui/cbmpconversor.h"
#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/iform.h"
#include "api/hwil/ifingerdetection.h"
#include "api/hwil/ifingermatcher.h"
#include "api/hwil/ifingerscanner.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "app/comum/comparecimentomesario/ccontroladorreconhecimetomesario.h"
#include "app/comum/comparecimentomesario/estados/cdigitalmesarionaoreconhecida.h"
#include "app/comum/comparecimentomesario/estados/cgestordadomesario.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"
#include "app/comum/dados/celeitordetalhe.h"
#include "app/vota/operador/confirmaidentidade/cparametrosimagemdigital.h"

namespace comum {

CPedeDigitalMesario::~CPedeDigitalMesario() = default;

std::unique_ptr<CPedeDigitalMesario> CPedeDigitalMesario::s_inst;
std::mutex CPedeDigitalMesario::s_mutex;

// (original lines 34-40: content not recovered)
#line 41
namespace {

class CNomeMesariosUrnaDS {
public:
    static std::string Text(const std::string& formato)
    {
        auto& controladorMesario = api::CPolySingleton<IControladorRegistraMesarios>::instance();
        if (!controladorMesario.Slot13()) {
            return controladorMesario.GetTituloMesario();
        }
        std::string nome;
        const md::CEleitorDecorator eleitor = controladorMesario.Slot14()->GetEleitor();
        if (!eleitor.GetNomeUrna().empty()) {
            nome = eleitor.GetNomeUrna().substr(0, 40);
        } else {
            nome = eleitor.GetNome().substr(0, 40);
        }
        return std::vformat(formato, std::make_format_args(nome));
    }
};

} // namespace

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaPedeDigitalMesario()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBuzz(52, 5);
    builder.AddTextField("Solicite que o(a) mesário(a)", api::SPoint{1, 1}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField(&CNomeMesariosUrnaDS::Text, api::SPoint{1, 2}, "{:2}", api::ALINHAMENTO_CENTRO);
    builder.AddTextField("posicione POLEGAR ou INDICADOR no sensor", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: Cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaAguardeDigitalMesario()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField("Por favor, aguarde.", api::SPoint{1, 2}, api::ALINHAMENTO_CENTRO);
    return builder.GetInteractiveForm("", true);
}

CPedeDigitalMesario::CPedeDigitalMesario()
    : CAppState(EVENTO_ENTRADA | EVENTO_TICK)
    , m_tickCaptura(GetControlador().AddTick(15000))
    , m_tickEspera(GetControlador().AddTick(50))
    , m_form(TelaPedeDigitalMesario())
    , m_formAguarde(TelaAguardeDigitalMesario())
{
}

CPedeDigitalMesario& CPedeDigitalMesario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeDigitalMesario());
    }
    return *s_inst;
}
void CPedeDigitalMesario::StartState()
{
    GetControlador().LogaPedidoBiometriaMesario();
    m_form->Slot2();
    api::CPolySingleton<api::IFingerScanner>::instance().Slot7(2);
    GetControlador().StartTick(m_tickCaptura);
    GetControlador().StartTick(m_tickEspera);
    api::CPolySingleton<api::IFingerScanner>::instance().Slot3();
    SetNextState(this);
}

// (original lines 113-114: content not recovered)
#line 115
void CPedeDigitalMesario::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeTituloMesario::GetInst();
    }
}

// (original lines 122-126: content not recovered)
#line 127
void CPedeDigitalMesario::ProcessTick(uebyte tick)
{
    if (tick != m_tickCaptura && tick != m_tickEspera) {
        return;
    }
    if (tick == m_tickCaptura) {
        PararTicks();
        m_pNextState = &CDigitalMesarioNaoReconhecida::GetInst();
        return;
    }
    if (tick != m_tickEspera) {
        return;
    }

    auto& detectorDedos = api::CPolySingleton<api::IFingerDetection>::instance();
    auto& scannerDedos = api::CPolySingleton<api::IFingerScanner>::instance();
    auto& urnaAtual = api::CPolySingleton<api::IUrna>::instance();

    api::TSharedImageVector imagem;
    float maiorEntropia = 0;
    int amostras = 0;
    while (amostras < 3) {
        const api::TSharedImageVector captura = scannerDedos.Slot4();
        if (captura->size() != static_cast<std::size_t>(scannerDedos.Slot0())) {
            return;
        }
        if (urnaAtual.Modelo() == 2009 || urnaAtual.Modelo() == 2010 || urnaAtual.Modelo() == 2020 ||
            urnaAtual.Modelo() == 2022) {
            imagem = captura;
            break;
        }
        const float entropia = CalculaEntropia(captura);
        if (entropia > 4.0f) {
            if (entropia > maiorEntropia) {
                imagem = api::TSharedImageVector(captura);
                maiorEntropia = entropia;
            }
            ++amostras;
        } else {
            return;
        }
    }
    if (detectorDedos.Slot2(imagem.get())) {
        m_formAguarde->Slot2();

        // (original lines 172-181: content not recovered)
#line 182
        api::CPolySingleton<api::IFingerScanner>::instance().Slot7(1);
        api::CSystem::Dorme(1000);
        if (urnaAtual.Modelo() <= 2019) {
            api::CBmpConversor::InvertColors(imagem->data(), scannerDedos.Slot2(), scannerDedos.Slot1());
        }
        api::CBmpConversor::VerticalFlip(imagem->data(), scannerDedos.Slot2(), scannerDedos.Slot1());
        const std::vector<uebyte> wsq =
            vota::CConversorWsq::GetInst().ConverteParaWsq(*imagem, scannerDedos.Slot2(), scannerDedos.Slot1(), "");
        const api::TSharedImageVector digital = std::make_shared<std::vector<uebyte>>(wsq.begin(), wsq.end());
        if (GetControlador().Slot13()) {
            const bool temBiometria = GetControlador().Slot14()->GetEleitor().TemBiometria();
            auto& reconhecimento = CControladorReconhecimentoMesario::GetInst();
            if (temBiometria) {
                reconhecimento.SetEstadoBiometria(
                    static_cast<md::CComparecimentoMesario::EstadoReconhecimentoBiometrico>(2));
                if (!ExecutaBatimentoDigitalMesario(digital, scannerDedos.Slot2(), scannerDedos.Slot1())) {
                    SalvaDigitalMesario(digital);
                }
            } else {
                reconhecimento.SetEstadoBiometria(
                    static_cast<md::CComparecimentoMesario::EstadoReconhecimentoBiometrico>(3));
                SalvaDigitalMesario(digital);
            }
            GetControlador().LogaMesarioEleitorDaSecao();
        } else {
            CControladorReconhecimentoMesario::GetInst().SetEstadoBiometria(
                static_cast<md::CComparecimentoMesario::EstadoReconhecimentoBiometrico>(3));
            SalvaDigitalMesario(digital);
            GetControlador().LogaMesarioNaoEleitorDaSecao();
        }
        m_pNextState = &CGestorDadoMesario::GetInst();
    }
}

void CPedeDigitalMesario::PararTicks()
{
    GetControlador().StopTick(m_tickCaptura);
    GetControlador().StopTick(m_tickEspera);
}

float CalculaEntropia(const api::TSharedImageVector& imagem)
{
    std::map<uebyte, int> ocorrencias;
    for (const uebyte valor : *imagem) {
        ++ocorrencias[valor];
    }
    float soma = 0;
    for (const auto& [valor, quantidade] : ocorrencias) {
        const float probabilidade = static_cast<float>(quantidade) / static_cast<int>(imagem->size());
        soma += probabilidade * std::log2(probabilidade);
    }
    return -soma;
}

// (original lines 236-250: content not recovered)
#line 251
bool CPedeDigitalMesario::ExecutaBatimentoDigitalMesario(const api::TSharedImageVector& imagem, const long largura,
                                                         const long altura)
{
    std::vector<uebyte> modelo;
    vota::CParametrosImagemDigital::GetInst().ExtraiTemplate(*imagem, modelo);
    PararTicks();
    const std::vector<md::CDedo::TipoDedo> dedos = {
        static_cast<md::CDedo::TipoDedo>(1), static_cast<md::CDedo::TipoDedo>(6), static_cast<md::CDedo::TipoDedo>(2),
        static_cast<md::CDedo::TipoDedo>(7)};
    std::vector<int> scores(dedos.size());
    int falhas = 0;
    auto& reconhecedorDasDigitais = api::CPolySingleton<api::IFingerMatcher>::instance();
    for (const md::CDedo::TipoDedo& dedo : dedos) {
        if (GetControlador().Slot14()->GetBiometria().TemDedo(dedo)) {
            const std::vector<api::SXYT> minucias = GetControlador().Slot14()->GetBiometria().GetDedo(dedo).GetMinucias();
            if (reconhecedorDasDigitais.Slot2(modelo, minucias,
                                              CControladorReconhecimentoMesario::GetInst().GetLimiar())) {
                GetControlador().LogaConferenciaBiometriaMesario();
                CControladorReconhecimentoMesario::GetInst().SetDedo(dedo);
                return true;
            }
            scores[falhas] = reconhecedorDasDigitais.Slot4();
            ++falhas;
        }
    }
    GetControlador().LogaDigitalNaoCorresponde(scores);
    return false;
}

void CPedeDigitalMesario::SalvaDigitalMesario(const api::TSharedImageVector& digital)
{
    PararTicks();
    const std::string titulo = GetControlador().GetTituloMesario();
    CControladorReconhecimentoMesario::GetInst().SalvarBiometriaMesarioRegistrado(*digital, titulo);
    CControladorReconhecimentoMesario::GetInst().SetDedo(static_cast<md::CDedo::TipoDedo>(0));
}

// (original lines 288-295: content not recovered)
#line 296
void CPedeDigitalMesario::FinishState()
{
    api::CPolySingleton<api::IFingerScanner>::instance().Slot7(0);
    api::CPolySingleton<api::IFingerScanner>::instance().Slot6();
}

const IControladorRegistraMesarios& CPedeDigitalMesario::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

} // namespace comum
