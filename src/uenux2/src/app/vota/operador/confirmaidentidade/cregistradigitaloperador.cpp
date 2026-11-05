// vota::CRegistraDigitalOperador's file, the path its records give:
// /home/rubio/tse/uenux2/src/app/vota/operador/confirmaidentidade/cregistradigitaloperador.cpp. The reconstruction's
// note, not TSE's text: the records fix StartState's lines (95 and 98), FinishState's (104 and 105), ProcessTick's
// three singletons (143 to 145) and BiometriaMesarioPresenteNosEleitores's two (328 and 371); every other line is a
// choice, the blank ones the original's unknown lines. src/units/221-uenux2-app-comum-constructors.mk has the notes,
// and those on comum::md::CComparecimentoMesarioPK's constructor, which ccomparecimentomesariopk.cpp defines now.
#include "app/vota/operador/confirmaidentidade/cregistradigitaloperador.h"

#include <algorithm>
#include <cmath>
#include <format>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/cbmpconversor.h"
#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/hwil/ifingerdetection.h"
#include "api/hwil/ifingermatcher.h"
#include "api/hwil/ifingerscanner.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/ccontroladorreconhecimetomesario.h"
#include "app/comum/comparecimentomesario/cregistradormesario.h"
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"
#include "app/vota/operador/confirmaidentidade/cdigitalnaocapturada.h"
#include "app/vota/operador/confirmaidentidade/cinformaeleitorpodevotar.h"
#include "app/vota/operador/confirmaidentidade/cparametrosimagemdigital.h"
#include "app/vota/operador/confirmaidentidade/ctentativacapturadigitalesgotada.h"
#include "app/vota/operador/cthreadoperador.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CRegistraDigitalOperador::~CRegistraDigitalOperador() = default;

std::unique_ptr<CRegistraDigitalOperador> CRegistraDigitalOperador::s_inst;
std::mutex CRegistraDigitalOperador::s_mutex;

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaRegistraDigitalOperador()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField("MESÁRIO:", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Posicione seu dedo POLEGAR ou INDICADOR", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("sobre o sensor", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: não habilitar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaDigitalCapturadaOperador()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBeep(1);
    builder.AddTextField("Digital capturada", api::SPoint{20, 1}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("Por favor aguarde", api::SPoint{20, 3}, api::ALINHAMENTO_CENTRO);
    return builder.GetInteractiveForm("", true);
}

CRegistraDigitalOperador::CRegistraDigitalOperador()
    : comum::CAppState(EVENTO_ENTRADA | EVENTO_TICK)
    , m_tickCaptura(CThreadOperador::GetInst().AddStoppedTick(15000))
    , m_tickEspera(CThreadOperador::GetInst().AddStoppedTick(50))
    , m_form(TelaRegistraDigitalOperador())
    , m_formCapturada(TelaDigitalCapturadaOperador())
    , m_tentativasRestantes(3)
{
}

CRegistraDigitalOperador& CRegistraDigitalOperador::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CRegistraDigitalOperador());
    }
    return *s_inst;
}

// (original lines 87-90: content not recovered)
#line 91
void CRegistraDigitalOperador::StartState()
{
    CLogVota::GetInst().LogaSolicitaDigitalMesario();
    m_form->Slot2();
    api::CPolySingleton<api::IFingerScanner>::instance().Slot7(2);
    CThreadOperador::GetInst().StartTick(m_tickCaptura);
    CThreadOperador::GetInst().StartTick(m_tickEspera);
    api::CPolySingleton<api::IFingerScanner>::instance().Slot3();
    m_pNextState = this;
}

void CRegistraDigitalOperador::FinishState()
{
    api::CPolySingleton<api::IFingerScanner>::instance().Slot7(0);
    api::CPolySingleton<api::IFingerScanner>::instance().Slot6();
}

void CRegistraDigitalOperador::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        CThreadOperador::GetInst().StopTick(m_tickCaptura);
        CThreadOperador::GetInst().StopTick(m_tickEspera);
        CLogVota::GetInst().LogaHabilitacaoCanceladaCapturaDigitalMesario();
        m_pNextState = &CPedeIdentidade::GetInst();
    }
}

namespace {
double CalculaEntropia(const api::TSharedImageVector& imagem);
} // namespace

void CRegistraDigitalOperador::ProcessTick(uebyte tick)
{
    if (tick != m_tickCaptura && tick != m_tickEspera) {
        return;
    }
    if (tick == m_tickCaptura) {
        CThreadOperador::GetInst().StopTick(m_tickCaptura);
        CThreadOperador::GetInst().StopTick(m_tickEspera);
        if (--m_tentativasRestantes == 0) {
            m_tentativasRestantes = 3;
            m_pNextState = &CTentativaCapturaDigitalEsgotada::GetInst();
            CLogVota::GetInst().LogaHabilitacaoCanceladaCapturaDigitalMesario();
        } else {
            m_pNextState = &CDigitalNaoCapturada::GetInst();
        }
        return;
    }
    if (tick != m_tickEspera) {
        return;
    }

    auto& detectorDedos = api::CPolySingleton<api::IFingerDetection>::instance();
    auto& scannerDedos = api::CPolySingleton<api::IFingerScanner>::instance();
    auto& urnaAtual = api::CPolySingleton<api::IUrna>::instance();

    api::TSharedImageVector imagem;
    double maiorEntropia = 0;
    int amostras = 0;
    while (amostras < 3) {
        const api::TSharedImageVector captura = scannerDedos.Slot4();
        if (captura->size() != static_cast<std::size_t>(scannerDedos.Slot0())) {
            return;
        }
        const double entropia = CalculaEntropia(captura);
        if (urnaAtual.Modelo() == 2009 || urnaAtual.Modelo() == 2010 || urnaAtual.Modelo() == 2020 ||
            urnaAtual.Modelo() == 2022) {
            imagem = captura;
            break;
        }
        if (entropia > 4.0) {
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
        m_formCapturada->Slot2();
        scannerDedos.Slot7(1);
        if (urnaAtual.Modelo() <= 2019) {
            api::CBmpConversor::InvertColors(imagem->data(), scannerDedos.Slot2(), scannerDedos.Slot1());
        }
        api::CBmpConversor::VerticalFlip(imagem->data(), scannerDedos.Slot2(), scannerDedos.Slot1());
        const std::vector<uebyte> wsq =
            CConversorWsq::GetInst().ConverteParaWsq(*imagem, scannerDedos.Slot2(), scannerDedos.Slot1(), "");
        const api::TSharedImageVector digital = std::make_shared<std::vector<uebyte>>(wsq.begin(), wsq.end());
        CControlaReconhecimento::RegistraDigitalMesario(*digital);
        IdentificaMesario();
        CThreadOperador::GetInst().StopTick(m_tickCaptura);
        CThreadOperador::GetInst().StopTick(m_tickEspera);
        impl::IInformacaoThreadOperador::GetInst().SetBiometriaOperador();
        m_pNextState = &CInformaEleitorPodeVotar::GetInst();
    }
}

void CRegistraDigitalOperador::IdentificaMesario()
{
    if (BuscaMesarioSecaoComBiometria() || BuscaMesarioSecaoSemBiometria() || BuscaMesarioForaSecao()) {
        return;
    }
    const bool coletada = comum::CControladorReconhecimentoMesario::GetInst().BiometriaPresenteNosNaoRegistrados(
        CControlaReconhecimento::GetDigitalRegistrada());
    if (!coletada) {
        CLogVota::GetInst().LogaCapturadaDigitalMesario();
        CLogVota::GetInst().loga(
            "Não encontrou digital coletada em nenhum dos arquivos, vai salvar a digital em novo arquivo.");
        comum::CControladorReconhecimentoMesario::GetInst().SalvarBiometriaMesarioNaoRegistrado(
            CControlaReconhecimento::GetDigitalRegistrada());
    } else {
        CLogVota::GetInst().loga("Digital coletada bate com uma digital gravada após o registro inicial de mesário. "
                                 "Não é possível associar a habilitação a um mesário.");
    }
}

bool CRegistraDigitalOperador::BuscaMesarioSecaoComBiometria()
{
    const auto mesarios = comum::CRegistradorMesario::GetInst().GetMesariosSecaoComBiometria();
    const comum::md::CEleitorIdentidade* encontrado = nullptr;
    for (const auto& [mesario, comparecimento] : mesarios) {
        if (BiometriaMesarioPresente(mesario, comparecimento.GetIdArquivo().value_or(999999))) {
            encontrado = &mesario;
            break;
        }
    }
    if (encontrado == nullptr) {
        return false;
    }
    CLogVota::GetInst().LogaMesarioHabilitouEleitor(encontrado->GetIdentificador());
    return true;
}

bool CRegistraDigitalOperador::BuscaMesarioSecaoSemBiometria()
{
    const auto mesarios = comum::CRegistradorMesario::GetInst().GetMesariosSecaoSemBiometria();
    const comum::md::CEleitorIdentidade* encontrado = nullptr;
    for (const auto& [mesario, comparecimento] : mesarios) {
        if (BiometriaMesarioPresente(mesario, comparecimento.GetIdArquivo().value_or(999999))) {
            encontrado = &mesario;
            break;
        }
    }
    if (encontrado == nullptr) {
        return false;
    }
    CLogVota::GetInst().LogaMesarioHabilitouEleitor(encontrado->GetIdentificador());
    return true;
}

bool CRegistraDigitalOperador::BuscaMesarioForaSecao()
{
    const auto mesarios = comum::CRegistradorMesario::GetInst().GetMesariosForaSecao();
    const comum::md::CEleitorIdentidade* encontrado = nullptr;
    for (const auto& [mesario, comparecimento] : mesarios) {
        if (BiometriaMesarioPresente(mesario, comparecimento.GetIdArquivo().value_or(999999))) {
            encontrado = &mesario;
            break;
        }
    }
    if (encontrado == nullptr) {
        return false;
    }
    CLogVota::GetInst().LogaMesarioHabilitouEleitor(encontrado->GetIdentificador());
    return true;
}

bool CRegistraDigitalOperador::BiometriaMesarioPresente(const comum::md::CEleitorIdentidade& mesario, int idArquivo)
{
    const bool presenteNosEleitores = BiometriaMesarioPresenteNosEleitores(mesario);
    CControlaReconhecimento::SetMesarioRegistrado("");
    if (presenteNosEleitores) {
        if (idArquivo != 999999) {
            const std::string mensagem = std::format("Biometria do mesário {} encontrada em eleitores ({})",
                                                     mesario.GetIdentificador(), idArquivo);
            CLogVota::GetInst().loga(mensagem);
        } else {
            const std::string mensagem =
                std::format("Biometria do mesário {} encontrada em eleitores", mesario.GetIdentificador());
            CLogVota::GetInst().loga(mensagem);
        }
        CControlaReconhecimento::SetMesarioRegistrado(mesario.GetIdentificador());
        return true;
    }
    const std::vector<uebyte> digital = CControlaReconhecimento::GetDigitalRegistrada();
    if (comum::CControladorReconhecimentoMesario::GetInst().BiometriaPresenteNosRegistrados(digital, idArquivo)) {
        const std::string mensagem = std::format("Biometria do mesário {} encontrada nos arquivos coletados ({})",
                                                 mesario.GetIdentificador(), idArquivo);
        CLogVota::GetInst().loga(mensagem);
        CControlaReconhecimento::SetMesarioRegistrado(mesario.GetIdentificador());
        return true;
    }
    if (idArquivo != 999999) {
        const std::string mensagem =
            std::format("Biometria coletada não é do mesário {} ({})", mesario.GetIdentificador(), idArquivo);
        CLogVota::GetInst().loga(mensagem);
    } else {
        const std::string mensagem = std::format("Biometria coletada não é do mesário {}", mesario.GetIdentificador());
        CLogVota::GetInst().loga(mensagem);
    }
    return false;
}

namespace {
// Chosen: these two functions, their names and their internal linkage (the target holds the map in ProcessTick's own
// frame). The counts come back by value for the map's stores (src/units/221-uenux2-app-comum-constructors.mk).
std::map<uebyte, int> ContaOcorrencias(const std::vector<uebyte>::const_iterator inicio,
                                       const std::vector<uebyte>::const_iterator fim)
{
    std::map<uebyte, int> ocorrencias;
    for (auto it = inicio; it != fim; ++it) {
        ++ocorrencias[*it];
    }
    return ocorrencias;
}

double CalculaEntropia(const api::TSharedImageVector& imagem)
{
    const std::map<uebyte, int> ocorrencias = ContaOcorrencias(imagem->cbegin(), imagem->cend());
    double soma = 0;
    for (const auto& [valor, quantidade] : ocorrencias) {
        const double probabilidade = static_cast<double>(quantidade) / static_cast<int>(imagem->size());
        soma += probabilidade * std::log2(probabilidade);
    }
    return -soma;
}

} // namespace

// (original lines 322-324: content not recovered)
#line 325
bool CRegistraDigitalOperador::BiometriaMesarioPresenteNosEleitores(const comum::md::CEleitorIdentidade& mesario)
{

    auto& digitais = api::CPolySingleton<api::IFingerScanner>::instance();
    std::vector<uebyte> modelo;
    CParametrosImagemDigital::GetInst().ExtraiTemplate(CControlaReconhecimento::GetDigitalRegistrada(), digitais.Slot2(),
                                                       digitais.Slot1(), modelo);
    const comum::md::CComparecimentoMesario* comparecimento =
        comum::CRegistradorMesario::GetInst().Find(comum::md::CComparecimentoMesarioPK(mesario, 1));
    std::vector<comum::md::CDedo::TipoDedo> dedos;
    if (comparecimento == nullptr) {
        dedos.reserve(2);
        dedos.push_back(static_cast<comum::md::CDedo::TipoDedo>(1));
        dedos.push_back(static_cast<comum::md::CDedo::TipoDedo>(6));
        dedos.push_back(static_cast<comum::md::CDedo::TipoDedo>(2));
        dedos.push_back(static_cast<comum::md::CDedo::TipoDedo>(7));
    } else if (comparecimento->GetDedoHabilitacao() == 0) {
        return false;
    } else {
        dedos.push_back(comparecimento->GetDedoHabilitacao());
    }
    const std::map<comum::md::CEleitorIdentidade, comum::CEleitorDetalhe> eleitores =
        comum::CEleitores::GetInst().GetRegistros();
    const auto eleitor = eleitores.find(mesario);
    if (eleitor == eleitores.end()) {
        return false;
    }
    for (const comum::md::CDedo::TipoDedo& dedo : dedos) {
        if (eleitor->second.GetBiometria().TemDedo(dedo)) {
            const std::vector<api::SXYT> minucias = eleitor->second.GetBiometria().GetDedo(dedo).GetMinucias();
            const int limiar = comum::CControladorReconhecimentoMesario::GetInst().GetLimiar();

            // (original lines 357-370: content not recovered)
#line 371
            auto& matcher = api::CPolySingleton<api::IFingerMatcher>::instance();
            if (matcher.Slot2(modelo, minucias, limiar)) {
                return true;
            }
        }
    }
    return false;
}

} // namespace vota
