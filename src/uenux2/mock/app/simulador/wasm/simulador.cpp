// Reconstruction's note, not TSE's text: the wasm simulator's start (fn 8302) and the pieces binaryen inlined into it.
// No record names this file: its path, every name and the order of the definitions are chosen
// (src/units/188-uenux2-simulador.mk says what each rests on).
#include "simulador.h"

#include <cstdlib>
#include <filesystem>
#include <memory>
#include <utility>

#include "api/audio/isound.h"
#include "api/audio/itexttospeech.h"
#include "api/gui/iscreen.h"
#include "api/gui/iscreenmt.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/isystemdatetime.h"
#include "api/util/itimerscheduler.h"
#include "app/comum/cpath.h"
#include "cwasmbeep.h"
#include "cwasminit.h"
#include "cwasminputkbd.h"
#include "cwasminputmt.h"
#include "cwasmlogd.h"
#include "cwasmnullpaper.h"
#include "cwasmnullprinter.h"
#include "cwasmnullsound.h"
#include "cwasmnulltexttospeech.h"
#include "cwasmresource.h"
#include "cwasmscreen.h"
#include "cwasmscreenmt.h"
#include "cwasmsystemdatetime.h"
#include "cwasmtimerscheduler.h"
#include "uenux2/mock/api/hwil/cpowermock.h"
#include "uenux2/mock/api/hwil/curnamock.h"

namespace simulador {

SConfiguracao::SConfiguracao(int parametro, std::string nome, api::TPosition largura, api::TPosition altura)
    : m_parametro(parametro)
    , m_nome(std::move(nome))
    , m_largura(largura)
    , m_altura(altura)
{
}

void InicializaAmbiente()
{
    comum::CPath::SetPathRoot("/");
    std::filesystem::create_directories("/uenux");
    setenv("PROJECT_DIR", ".", 1);
    setenv("BUILD_DIR", "/", 1);
}

void InicializaDispositivos(const SConfiguracao& configuracao)
{
    api::ITimerScheduler::CreateInst<CWasmTimerScheduler>();
    api::CPolySingleton<comum::IInterfaceInit>::set(new CWasmInit(configuracao.m_parametro));
    api::CPolySingleton<api::IScreen>::set(new CWasmScreen(configuracao.m_largura, configuracao.m_altura));
    api::CPolySingleton<api::IScreenMT>::set(new CWasmScreenMT);
    api::CPolySingleton<api::IInputKbd>::set(new CWasmInputKbd);
    api::CPolySingleton<api::IInputMT>::set(new CWasmInputMT);
    api::CPolySingleton<api::IResource>::set(new CWasmResource);
    api::CPolySingleton<api::IUrna>::set(new api::teste::CUrnaMock);
    api::CPolySingleton<api::IPower>::set(new api::teste::CPowerMock);
    api::CPolySingleton<api::IBeep>::set(new CWasmBeep);
    api::CPolySingleton<api::ISound>::set(new CWasmNullSound);
    api::CPolySingleton<api::IPaperRelatorios>::set(new CWasmNullPaper);
    api::CPolySingleton<api::IImpressoraRelatorios>::set(new CWasmNullPrinter);
    api::CPolySingleton<api::ITextToSpeech>::set(new CWasmNullTextToSpeech);
    api::CPolySingleton<api::ISystemDateTime>::set(new CWasmSystemDateTime);
}

void InicializaLog()
{
    const std::filesystem::path arquivo = comum::CPath::GetPathLog() / "logd.dat";
    api::CPolySingleton<api::CEscritorLog>::set(new CWasmLogd(arquivo));
}

void Inicializa(const SConfiguracao& configuracao, std::function<void()> aoIniciar)
{
    InicializaAmbiente();
    InicializaDispositivos(configuracao);
    InicializaLog();
    aoIniciar();
}

} // namespace simulador
