// Reconstruction's note, not TSE's text: the executable TU of the web voting simulator. Its three records fix lines 361,
// 515 and 592; every other line is a choice, and src/units/170-uenux2-wasm-vota-web.mk says what is recovered, what is
// chosen and what waits.
#include <cstddef>
#include <cstdlib>
#include <cxxabi.h>
#include <emscripten/emscripten.h>
#include <exception>
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <typeinfo>
#include <vector>

#include "api/audio/isound.h"
#include "api/gui/capplication.h"
#include "api/hwil/ifingerprepare.h"
#include "api/hwil/iinput.h"
#include "api/ipc/posix/cposixmutex.h"
#include "api/ipc/posix/cposixrwmutex.h"
#include "api/ipc/posix/cposixsemaphore.h"
#include "api/pattern/cpolysingleton.h"
#include "api/pattern/igenericfactory.h"
#include "api/util/cajustedatahora.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/crespostas.h"
#include "app/comum/iinterfacesavd.h"
#include "app/vota/cexecucaovotacooperativa.h"
#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/eleitor/celeitorvotando.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/comum/ipoliticaexecucaoeleitor.h"
#include "app/vota/eleitor/isincronismovotoeleitor.h"
#include "app/vota/eleitor/votaproporcional/cpedeproporcional.h"
#include "app/vota/iexecucaovota.h"
#include "ecourna/api/security/cprng.hpp"
#include "ecourna/api/security/csymmetriccipherfactory.hpp"
#include "ecourna/api/util/cstringutils.hpp"
#include "uenux2/mock/app/simulador/wasm/cfingerpreparesimulador.h"
#include "uenux2/mock/app/simulador/wasm/cwasmthread.h"
#include "uenux2/mock/app/simulador/wasm/cwasmwebsound.h"
#include "uenux2/mock/app/simulador/wasm/simulador.h"
#include "uenux2/mock/app/simulador/wasm/wasmjs.h"

extern "C" {
// the JavaScript side (EM_JS, src/web/wasm_shim.cpp)
void js_use_external_keyboard(void);
int js_ler_dimensao_tela(int dimensao, int padrao);
}

namespace api {

static TPolySingletonsInfo& polySingletonsInfoPadrao()
{
    static TPolySingletonsInfo info;
    info.m_depuracao = true;
    return info;
}

TPolySingletonsInfo& (*g_polySingletonsInfo)() = polySingletonsInfoPadrao;

} // namespace api

namespace {

// (original lines 71-279: content not recovered)
#line 280
std::string Desmangle(const char* nome)
{
    int status = 0;
    char* legivel = abi::__cxa_demangle(nome, nullptr, nullptr, &status);
    std::string resultado = (status == 0 && legivel != nullptr) ? legivel : (nome != nullptr ? nome : "");
    std::free(legivel);
    return resultado;
}

std::string NomeEstadoEleitor()
{
    comum::CAppState* estado = vota::IExecucaoVota::GetInst().GetEstadoEleitor();
    if (estado != nullptr) {
        return Desmangle(typeid(*estado).name());
    }
    return "";
}

std::string NomeSubestadoEleitor()
{
    const auto* votando = dynamic_cast<vota::CEleitorVotando*>(vota::IExecucaoVota::GetInst().GetEstadoEleitor());
    if (votando == nullptr || votando->GetEstadoCargo() == nullptr) {
        return "";
    }
    return Desmangle(typeid(*votando->GetEstadoCargo()).name());
}

std::string ListaCandidatos()
{
    std::ostringstream lista;
    lista << '[';
    try {
        if (comum::CCargos::GetInst().IsFim()) {
            lista << ']';
            return lista.str();
        }
        const comum::TCargoID cargo = comum::CCargos::GetInst().GetCurrentCargoID();
        const comum::CCandidaturas& candidaturas = comum::CCandidaturas::GetInst();
        bool primeiro = true;
        for (const comum::TCandidatoID numero : comum::CCandidaturas::GetInst().GetCandidatos(cargo)) {
            const auto candidatura = candidaturas.GetRegistros().find(comum::ChaveResposta(cargo, numero));
            if (candidatura == candidaturas.GetRegistros().end()) {
                continue;
            }
            if (!primeiro) {
                lista << ',';
            }
            lista << "{\"number\":" << candidatura->second.GetCandidatoID() << ","
                  << "\"name\":\"" << simulador::EscapaJson(candidatura->second.GetTitular().GetNomeUrna()) << "\","
                  << "\"party\":" << candidatura->second.GetPartidoID() << ","
                  << "\"apt\":" << (candidatura->second.GetTitular().GetSituacao() == 0 ? "true" : "false") << '}';
            primeiro = false;
        }
    } catch (...) {
    }
    lista << ']';
    return lista.str();
}

void ReportaErro(const std::string& mensagem)
{
    const std::string evento = std::string("{\"message\":\"") + simulador::EscapaJson(mensagem) + "\"}";
    simulador::ConsoleError(mensagem);
    simulador::EmitEvent("vota:error", evento);
}

} // namespace

void SinalizaSincronismo(api::CPriorityMessageQueue<api::SMessage>& fila);

// (original lines 350-355: content not recovered)
#line 356
namespace {

class CPoliticaExecucaoEleitorWeb : public vota::impl::IPoliticaExecucaoEleitor {
public:

    void LimpaBufferInput() const override { api::CPolySingleton<api::IInputKbd>::instance().Clear(); }
};


class CVotaWebEngine {
public:

    // (original lines 368-424: content not recovered)
#line 425
    std::string EstadoJson() const
    {
        const std::string estado = NomeEstadoEleitor();
        const std::string subestado = NomeSubestadoEleitor();
        const std::string tela = subestado.find("CInstrucaoVotacaoAcessibilidade") != std::string::npos ? "accessibility" : "";

        bool proporcional = false;
        try {
            const comum::CCargos& cargos = comum::CCargos::GetInst();
            if (!cargos.IsFim()) {
                proporcional = cargos.GetCurrent().IsProporcional();
            }
        } catch (...) {
        }

        bool legendaValida = false;
        try {
            const comum::CCargos& cargos = comum::CCargos::GetInst();
            if (proporcional && !cargos.IsFim() && vota::g_numeroDigitado.size() >= 2) {
                const ueword partido = ecourna::api::util::CStringUtils::ToWord(vota::g_numeroDigitado.substr(0, 2));
                legendaValida = vota::LegendaValida(cargos.GetCurrentCargoID(), partido);
            }
        } catch (...) {
            legendaValida = false;
        }

        std::string_view modo;
        if (!m_inicializado) {
            modo = "inicio";
        } else if (m_encerrado) {
            modo = "fim";
        } else if (m_aguardando || estado.find("CSincronismo") != std::string::npos) {
            modo = "gravando";
        } else if (tela == "accessibility") {
            modo = "accessibility";
        } else if (subestado.find("Branco") != std::string::npos) {
            modo = "branco";
        } else if (subestado.find("CPedeNominal") != std::string::npos) {
            modo = legendaValida && proporcional ? "legendaOuNominal" : "nulo";
        } else if (subestado.find("VotoLegenda") != std::string::npos ||
                   subestado.find("CandidatoInexistente") != std::string::npos) {
            modo = legendaValida && proporcional ? "legenda" : "nulo";
        } else if (subestado.find("Nulo") != std::string::npos || subestado.find("Inexistente") != std::string::npos ||
                   subestado.find("Inapto") != std::string::npos || subestado.find("Repetido") != std::string::npos) {
            modo = "nulo";
        } else {
            modo = "nominal";
        }
        const bool confirmacao = subestado.find("VotoNominal") != std::string::npos ||
                                 subestado.find("MajoritarioValido") != std::string::npos;

        std::ostringstream json;
        json << "{\"initialized\":" << (m_inicializado ? "true" : "false") << ','
             << "\"done\":" << (m_encerrado ? "true" : "false") << ','
             << "\"audioEnabled\":" << (m_audioHabilitado ? "true" : "false") << ','
             << "\"audioEleitorHabilitado\":" << (m_audioEleitorHabilitado ? "true" : "false") << ','
             << "\"state\":\"" << simulador::EscapaJson(estado) << "\""
             << ",\"guide\":{\"voteMode\":\"" << simulador::EscapaJson(std::string(modo)) << "\""
             << ",\"legendaValida\":" << (legendaValida ? "true" : "false")
             << ",\"confirmacao\":" << (confirmacao ? "true" : "false") << '}';
        if (!subestado.empty()) {
            json << ",\"substate\":\"" << simulador::EscapaJson(subestado) << "\"";
        }
        if (!tela.empty()) {
            json << ",\"screen\":\"" << simulador::EscapaJson(tela) << "\"";
        }
        try {
            if (!tela.empty()) {
                json << ",\"candidates\":[]";
            } else if (!comum::CCargos::GetInst().IsFim()) {
                const comum::md::CCargo& cargo = comum::CCargos::GetInst().GetCurrent();
                const char* tipo = cargo.IsProporcional() ? "proporcional" : "majoritario";
                json << ",\"cargo\":{\"id\":" << static_cast<unsigned>(cargo.GetID()) << ","
                     << "\"name\":\"" << simulador::EscapaJson(cargo.GetNomeNeutro()) << "\","
                     << "\"digits\":" << static_cast<unsigned>(cargo.GetNumeroDigitos()) << ","
                     << "\"tipo\":\"" << tipo << "\"";
                if (cargo.IsProporcional()) {
                    json << ",\"legendaDigits\":2";
                }
                json << '}';
                json << ",\"candidates\":" << ListaCandidatos();
            }
        } catch (...) {
            json << ",\"candidates\":[]";
        }
        json << '}';
        return json.str();
    }

    // (original lines 514-516: content not recovered)
#line 517
    int Tick()
    {
        if (!m_inicializado || m_encerrado) {
            return 0;
        }
        try {
            const std::string antes = NomeEstadoEleitor();
            vota::IExecucaoVota::GetInst().ProcessaEntradaEleitor();
            const std::string depois = NomeEstadoEleitor();
            if (depois.find("CSincronismoEleitor") != std::string::npos) {
                const double agora = emscripten_get_now();
                if (!m_aguardando) {
                    m_aguardando = true;
                    m_avisado = false;
                    m_avisos = 0;
                    m_proximoAviso = agora + 120;
                } else if (!m_avisado && !(agora < m_proximoAviso)) {
                    if (m_avisos < 4) {
                        vota::CTelasVota::GetInst().IncrementaBarraSincronismo();
                        m_proximoAviso = agora + 160;
                        ++m_avisos;
                    } else {
                        SinalizaSincronismo(vota::IExecucaoVota::GetInst().GetFilaEleitor());
                        m_avisado = true;
                    }
                }
            } else {
                m_aguardando = false;
                m_avisado = false;
                m_avisos = 0;
                m_proximoAviso = 0;
            }
            if (depois.find("CAguardaMensagem") != std::string::npos && antes != depois) {
                m_encerrado = true;
            }
            const std::string estado = EstadoJson();
            if (depois != antes || estado != m_estado) {
                m_estado = estado;
                simulador::EmitEvent("vota:state", m_estado);
            }
            if (m_encerrado && depois.find("CAguardaMensagem") != std::string::npos && antes != depois) {
                simulador::EmitEvent("vota:done", EstadoJson());
            }
            return 1;
        } catch (const std::exception& erro) {
            ReportaErro(erro.what());
        } catch (...) {
            ReportaErro("erro desconhecido em votaTick");
        }
        return 0;
    }

    const char* GetStateJson()
    {
        m_estado = EstadoJson();
        return m_estado.c_str();
    }

    // (original lines 575-588: content not recovered)
#line 589
    void SetAudioEnabled(bool habilitado)
    {
        m_audioHabilitado = habilitado;
        api::CPolySingleton<api::ISound>::instance().Mute(!habilitado);
    }

    void PressKey(const char* tecla)
    {
        if (tecla) {
            simulador::PushKey(tecla);
        }
    }

private:
    bool m_inicializado = false;
    bool m_encerrado = false;
    bool m_audioHabilitado = true;
    bool m_audioEleitorHabilitado = false;
    bool m_aguardando = false;
    bool m_avisado = false;
    int m_avisos = 0;
    double m_proximoAviso = 0;
    std::string m_estado = "{}";
};

std::unique_ptr<CVotaWebEngine> g_engine;

CVotaWebEngine& Engine()
{
    if (!g_engine) {
        g_engine = std::make_unique<CVotaWebEngine>();
    }
    return *g_engine;
}

// the SAVD channel of the wasm build, which answers every message with an empty response
constexpr ueint32 ESTADO_SAVD_WASM = 212593824;

class CWasmSavd : public comum::IInterfaceSavd {
public:
    void Escreve(const std::vector<uebyte>&) override {}

    void RecebeMensagem(ueint32& estado, std::vector<uebyte>& dados, size_t tamanho) override
    {
        estado = ESTADO_SAVD_WASM;
        if (tamanho != sizeof(comum::ueRespostaSavd)) {
            throw std::invalid_argument("CWasmSavd::RecebeMensagem - mensagem de tamanho invalido");
        }
        comum::ueRespostaSavd resposta{};
        resposta.marca = 254;
        const uebyte* bytes = reinterpret_cast<const uebyte*>(&resposta);
        dados.assign(bytes, bytes + sizeof(resposta));
    }

    ueint32 Slot4() override { return ESTADO_SAVD_WASM; }
};

class CSincronismoVotoEleitorWeb : public vota::impl::ISincronismoVotoEleitor {
public:
    bool Sincroniza() override { return true; }
};


} // namespace

extern "C" void votaPressKey(const char* tecla)
{
    Engine().PressKey(tecla);
}

extern "C" int votaTick(void)
{
    return Engine().Tick();
}

extern "C" void votaSetAudioEnabled(int habilitado)
{
    Engine().SetAudioEnabled(habilitado);
}

extern "C" const char* votaGetStateJson(void)
{
    return Engine().GetStateJson();
}

void HabilitaAudioEleitor(api::CPriorityMessageQueue<api::SMessage>& fila)
{
    api::SMessage mensagem;
    mensagem.m_tipo = 9;
    mensagem.m_fila = &fila;
    fila.Insert(mensagem);
}

void LiberaEleitor(api::CPriorityMessageQueue<api::SMessage>& fila)
{
    api::SMessage mensagem;
    mensagem.m_tipo = 1;
    mensagem.m_fila = &fila;
    fila.Insert(mensagem);
}

void SinalizaSincronismo(api::CPriorityMessageQueue<api::SMessage>& fila)
{
    api::SMessage mensagem;
    mensagem.m_tipo = 5;
    mensagem.m_fila = &fila;
    fila.Insert(mensagem);
}


int main()
{
    js_use_external_keyboard();
    const api::TPosition largura = js_ler_dimensao_tela(0, 1280);
    const api::TPosition altura = js_ler_dimensao_tela(1, 800);
    const simulador::SConfiguracao configuracao(10, "VOTA Web", largura, altura);

    api::CApplication::InitApplication("VOTA", "Software de Votação", "10.23.0.1 - DESENVOLVIMENTO", static_cast<ELogAplicativos>(1));

    api::CPolySingleton<comum::IInterfaceSavd>::set(new CWasmSavd());
    api::CPolySingleton<ecourna::api::security::IRng>::set(new ecourna::api::security::CPrng(0));
    api::CPolySingleton<ecourna::api::security::ISymmetricCipherFactory>::set(new ecourna::api::security::CSymmetricCipherFactory);
    api::CPolySingleton<api::IFingerPrepare>::set(new simulador::CFingerPrepareSimulador);
    api::CAjusteDataHora::Registra();
    api::CPolySingleton<api::IGenericFactory<api::IThreadImpl>>::set(new api::CDefaultGenericFactory<api::IThreadImpl, simulador::CWasmThread>);
    api::CPolySingleton<api::IGenericFactory<api::ISyncCtl>>::set(new api::CDefaultGenericFactory<api::ISyncCtl, api::CPosixMutex>);
    api::CPolySingleton<api::IGenericFactory<api::IRWSyncCtl>>::set(new api::CDefaultGenericFactory<api::IRWSyncCtl, api::CPosixRWMutex>);
    api::CPolySingleton<api::IGenericFactory<api::ISemaphore>>::set(new api::CDefaultGenericFactory<api::ISemaphore, api::CPosixSemaphore>);
    api::CPolySingleton<vota::impl::IPoliticaExecucaoEleitor>::set(new CPoliticaExecucaoEleitorWeb);
    api::CPolySingleton<vota::impl::ISincronismoVotoEleitor>::set(new CSincronismoVotoEleitorWeb);
    api::CPolySingleton<vota::IExecucaoVota>::set(new vota::CExecucaoVotaCooperativa(&vota::CAguardaMensagem::GetInst()));

    simulador::Inicializa(configuracao, [] {
        api::CPolySingleton<api::ISound>::set(new simulador::CWasmWebSound());
        simulador::EmitEvent("vota:ready", "{}");
    });
    return 0;
}
