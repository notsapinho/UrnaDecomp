// Reconstruction's note, not TSE's text: the executable TU of the web voting simulator. Its three records fix lines 361,
// 515 and 592; every other line is a choice, and src/units/170-uenux2-wasm-vota-web.mk says what is recovered, what is
// chosen and what waits.
#include <cstddef>
#include <cstdlib>
#include <cxxabi.h>
#include <emscripten/emscripten.h>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <typeinfo>
#include <vector>

#include "api/audio/crhvoicetexttospeech.h"
#include "api/audio/isound.h"
#include "api/gui/capplication.h"
#include "api/gui/instrucaomenu.h"
#include "api/hwil/ifingerprepare.h"
#include "api/hwil/iinput.h"
#include "api/ipc/posix/cposixmutex.h"
#include "api/ipc/posix/cposixrwmutex.h"
#include "api/ipc/posix/cposixsemaphore.h"
#include "api/pattern/cpolysingleton.h"
#include "api/pattern/igenericfactory.h"
#include "api/util/cajustedatahora.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/crespostas.h"
#include "app/comum/iinterfacesavd.h"
#include "app/vota/cexecucaovotacooperativa.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/eleitor/celeitorvotando.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/comum/ipoliticaexecucaoeleitor.h"
#include "app/vota/eleitor/isincronismovotoeleitor.h"
#include "app/vota/eleitor/votaproporcional/cpedeproporcional.h"
#include "app/vota/iexecucaovota.h"
#include "app/vota/log/clogvota.h"
#include "ecourna/api/security/cprng.hpp"
#include "ecourna/api/security/csymmetriccipherfactory.hpp"
#include "ecourna/api/util/cstringutils.hpp"
#include "uenux2/mock/app/comum/cappinfobuilder.h"
#include "uenux2/mock/app/simulador/wasm/cfingerpreparesimulador.h"
#include "uenux2/mock/app/simulador/wasm/cwasmnulltexttospeech.h"
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

// The options votaInit reads from its argument, a JSON text: the value after the quoted key and its colon, past
// blanks (target fns 14477, 11571 and 11546, which votaInit invokes through table slots 4, 22 and 23; each builds
// its own copy of the text). LeInt returns 1 when the key or a number is missing: it is in the table, so binaryen
// folds none of its arguments, and its wasm type has two. Names and parameter names are chosen, and so is the
// anonymous namespace (an inline function gives the same place: deferred, after votaInit, slots 62 to 64 theirs).
bool LeBool(const char* opcoes, const std::string& chave, bool padrao)
{
    if (opcoes != nullptr) {
        const std::string texto(opcoes);
        size_t posicao = texto.find("\"" + chave + "\"");
        if (posicao != std::string::npos) {
            posicao = texto.find(':', posicao);
            if (posicao != std::string::npos) {
                posicao = texto.find_first_not_of(" \t\r\n", posicao + 1);
                if (posicao != std::string::npos) {
                    if (texto.compare(posicao, 4, "true") == 0) {
                        padrao = true;
                    } else if (texto.compare(posicao, 5, "false") == 0) {
                        padrao = false;
                    }
                }
            }
        }
    }
    return padrao;
}

int LeInt(const char* opcoes, const std::string& chave)
{
    if (opcoes == nullptr) {
        return 1;
    }
    const std::string texto(opcoes);
    size_t posicao = texto.find("\"" + chave + "\"");
    if (posicao != std::string::npos) {
        posicao = texto.find(':', posicao);
        if (posicao != std::string::npos) {
            posicao = texto.find_first_not_of(" \t\r\n", posicao + 1);
            if (posicao != std::string::npos) {
                char* fim = nullptr;
                const long valor = std::strtol(texto.c_str() + posicao, &fim, 10);
                if (fim != texto.c_str() + posicao) {
                    return valor;
                }
            }
        }
    }
    return 1;
}

std::string LeTexto(const char* opcoes, const std::string& chave, const std::string& padrao)
{
    if (opcoes == nullptr) {
        return padrao;
    }
    const std::string texto(opcoes);
    size_t posicao = texto.find("\"" + chave + "\"");
    if (posicao == std::string::npos) {
        return padrao;
    }
    posicao = texto.find(':', posicao);
    if (posicao == std::string::npos) {
        return padrao;
    }
    posicao = texto.find_first_not_of(" \t\r\n", posicao + 1);
    if (posicao == std::string::npos || texto[posicao] != '"') {
        return padrao;
    }
    std::string valor;
    bool escapado = false;
    for (size_t i = posicao + 1; i < texto.size(); ++i) {
        const char c = texto[i];
        if (!escapado) {
            if (c == '\\') {
                escapado = true;
                continue;
            }
            if (c == '"') {
                return valor;
            }
        }
        escapado = false;
        valor.push_back(c);
    }
    return padrao;
}

comum::EUrnaFase CodigoFase(const std::string& fase)
{
    if (fase == "oficial" || fase == "o") {
        return comum::FASE_OFICIAL;
    }
    if (fase == "simulado" || fase == "s") {
        return comum::FASE_SIMULADO;
    }
    return comum::FASE_TREINAMENTO;
}

// Target fns 11818 and 11733: a file written when absent, its directories first (std::ofstream's default mode), and
// the stand-in signatures written into each flash's files with it. Names chosen.
void GravaSeAusente(const std::filesystem::path& arquivo, const std::string& conteudo)
{
    if (!std::filesystem::exists(arquivo)) {
        std::filesystem::create_directories(arquivo.parent_path());
        std::ofstream saida(arquivo);
        saida << conteudo;
    }
}

// The directories votaInit creates on both flashes, and the serial number file. A function of its own, inlined:
// with the loop in place, clang lays out the code after it inside the loop's exit test, and the table's slots 9 to
// 18 come in another order than the target's (the TU compiled at its rule, both forms). Its name and linkage are
// chosen.
void CriaDiretorios()
{
    for (const comum::EFlashOrigem origem : {comum::FLASH_INTERNA, comum::FLASH_EXTERNA}) {
        std::filesystem::create_directories(comum::CPath::GetPathEstatico(origem));
        std::filesystem::create_directories(comum::CPath::GetPathDinamico(origem));
        std::filesystem::create_directories(comum::CPath::GetPathDinamico(origem) / "tmp");
        std::filesystem::create_directories(comum::CPath::GetPathTrab(origem, comum::TURNO_1));
        std::filesystem::create_directories(comum::CPath::GetPathTrab(origem, comum::TURNO_2));
        GravaSeAusente(comum::CPath::GetPathRootSemSA(origem) / "serialv.dat", "ABCDDCBA");
    }
}

void AssinaArquivos()
{
    const std::string assinatura = "assinatura simulada para vota_web_wasm";
    const std::vector<std::string> arquivos = {"eg.vsu", "gap.vsu", "sa.vsu", "vota.vsu", "rdv.vsu", "uenux.vsu"};
    for (const comum::EFlashOrigem origem : {comum::FLASH_INTERNA, comum::FLASH_EXTERNA}) {
        GravaSeAusente(comum::CPath::GetPathDinamico(origem) / "eg.vsu", assinatura);
        for (const comum::EUrnaTurno turno : {comum::TURNO_1, comum::TURNO_2}) {
            const std::filesystem::path trab = comum::CPath::GetPathTrab(origem, turno);
            for (const std::string& arquivo : arquivos) {
                GravaSeAusente(trab / arquivo, assinatura);
            }
        }
    }
}

// (original lines 222-279: content not recovered)
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
void HabilitaAudioEleitor(api::CPriorityMessageQueue<api::SMessage>& fila);
void LiberaEleitor(api::CPriorityMessageQueue<api::SMessage>& fila);

inline std::filesystem::path PathEstadoGeral()
{
    return comum::CPath::GetPathDinamico(comum::FLASH_INTERNA);
}
namespace {

class CPoliticaExecucaoEleitorWeb : public vota::impl::IPoliticaExecucaoEleitor {
public:

    void LimpaBufferInput() const override { api::CPolySingleton<api::IInputKbd>::instance().Clear(); }
};


class CVotaWebEngine {
public:

    // (original lines 368-508: content not recovered)
#line 509
    int Init(const char* opcoes)
    {
        try {
            m_audioEleitorHabilitado = LeBool(opcoes, "audioEleitorHabilitado", false);
            m_audioHabilitado = LeBool(opcoes, "reproduzirAudio", true);
            api::CPolySingleton<api::ITextToSpeech>::set(new simulador::CWasmNullTextToSpeech());
            api::CPolySingleton<api::ISound>::instance().Mute(!m_audioHabilitado);
            CriaDiretorios();
            AssinaArquivos();
            if (!std::filesystem::exists(PathEstadoGeral() / "eg.bin")) {
                const int pe = LeInt(opcoes, "pe");
                const int municipio = LeInt(opcoes, "municipio");
                const int zona = LeInt(opcoes, "zona");
                const int secao = LeInt(opcoes, "secao");
                const int turno = LeInt(opcoes, "turno");
                const comum::EUrnaFase fase = CodigoFase(LeTexto(opcoes, "fase", "te"));
                const std::string uf = LeTexto(opcoes, "uf", "ee");
                comum::teste::CAppInfoBuilder builder(pe);
                builder.SetFase(fase)
                    .SetTurno(turno == 2 ? comum::TURNO_2 : comum::TURNO_1)
                    .SetTipoUrna(comum::eUrnaVota)
                    .SetLocalidade(municipio, zona, secao);
                builder.SetUF(ecourna::api::util::CStringUtils::ToUpper(uf));
                builder.PreparaVotacao(true);
                builder.SalvaTudo(false, {comum::teste::EMidia::INTERNA, comum::teste::EMidia::EXTERNA});
                AssinaArquivos();
            }
            comum::CAppInfo::GetInst().CarregaGeral();
            const comum::md::estadoaplicacao::CEstadoGeral& geral = comum::CAppInfo::GetInst().GetGeral();
            vota::CLogVota& log = vota::CLogVota::GetInst();
            log.LogaInicioAplicacao(geral.GetDadoCarga().GetTurno());
            log.LogaVersaoAplicacao();
            vota::CTelasVota::CreateInst();
            vota::CEstadoAudio::GetInst().GeraDadosDinamicos();
            AssinaArquivos();
            if (m_audioEleitorHabilitado) {
                if (!std::filesystem::exists("/etc/RHVoice") || !std::filesystem::exists("/share/RHVoice")) {
                    throw std::runtime_error("dados do RHVoice nao foram carregados para habilitar o audio do eleitor");
                }
                api::CPolySingleton<api::ITextToSpeech>::set(new api::CRHVoiceTextToSpeech("/"));
            } else {
                api::CPolySingleton<api::ITextToSpeech>::set(new simulador::CWasmNullTextToSpeech());
            }
            comum::CAppInfo::GetInst().GetVota().SetEstadoVota(comum::EAVVOTAR);
            comum::CAppInfo::GetInst().GetVota().MarcaInicioAquisicao();
            vota::CSincronizaVota::SincronizaEstadoGeralVota();
            AssinaArquivos();
            vota::IExecucaoVota& execucao = vota::IExecucaoVota::GetInst();
            execucao.IniciaThreads();
            if (m_audioEleitorHabilitado) {
                HabilitaAudioEleitor(execucao.GetFilaEleitor());
            } else {
                vota::CEstadoAudio::GetInst().Desativa();
            }
            LiberaEleitor(execucao.GetFilaEleitor());
            m_inicializado = true;
            m_encerrado = false;
            m_estado = EstadoJson();
            simulador::EmitEvent("vota:state", m_estado);
            return 1;
        } catch (const std::exception& erro) {
            ReportaErro(erro.what());
        } catch (...) {
            ReportaErro("erro desconhecido em votaInit");
        }
        return 0;
    }

    // (original lines 577-588: content not recovered)
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

extern "C" int votaInit(const char* opcoes)
{
    return Engine().Init(opcoes);
}

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
