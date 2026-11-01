// Roots: reach api::CPolySingleton<T>::instance (api/pattern/cpolysingleton.h) the way the target's callers do, until they
// land. The target calls each instance from real code, as `CPolySingleton<T>::instance()` with both default arguments
// (fn 11132 does it for IScreen, all in 49 bytes), and binaryen keeps it out of line. w100_usa makes that call twice, so
// each instance has two call sites, and calls has<T> once more, which the target does in another function (fn 5566 for
// IScreen), so has<T> stays out of line too: a member with one caller is inlined, and the target's are calls.
//
// w100_falha is the one thing here no T asks for. It was written to keep fn 403's two arguments from dead-argument
// elimination, but 1497 calls 403 with others: without it no row of a --no-kinds scan moves. It stays until a scan with
// kinds says the same. It is in a cold function because clang inlines the operator in a hot one, and that would be no
// call.
//
// w100_usa and w100_todos are stand-ins with a body no target function has. w100_usa passes both arguments, an empty
// std::source_location for the record a real caller's default argument makes: a record here would be none of the target's.
#include <memory>
#include <source_location>
#include <stdexcept>
#include <string>

#include "api/audio/isound.h"
#include "api/gui/ipaperrelatorios.h"
#include "api/gui/iresource.h"
#include "api/gui/iscreen.h"
#include "api/hwil/ibeep.h"
#include "api/hwil/ifingerprepare.h"
#include "api/hwil/iimpressorarelatorios.h"
#include "api/hwil/iinput.h"
#include "api/hwil/ipower.h"
#include "api/hwil/iurna.h"
#include "api/ipc/irwsyncctl.h"
#include "api/ipc/isemaphore.h"
#include "api/ipc/isyncctl.h"
#include "api/ipc/ithreadimpl.h"
#include "api/pattern/cpolysingleton.h"
#include "api/pattern/igenericfactory.h"
#include "api/uelog/cescritorlog.h"
#include "api/util/cajustedatahora.h"
#include "api/util/iajustedatahora.h"
#include "api/util/isystemdatetime.h"
#include "api/util/itimerscheduler.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"
#include "app/comum/iinterfaceinit.h"
#include "app/comum/iinterfacesavd.h"
#include "app/comum/log/ieventoslog.h"
#include "app/comum/relatorios/ccalculacv.h"
#include "app/comum/validamidia/ivalidamidia.h"
#include "app/vota/eleitor/comum/ipoliticaexecucaoeleitor.h"
#include "app/vota/eleitor/fimvotacao/cmostraqrcodebu.h"
#include "app/vota/eleitor/iajusteinicial.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/igeradorteclas.h"
#include "app/vota/eleitor/isincronismovotoeleitor.h"
#include "app/vota/iexecucaovota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "ecourna/api/security/irng.hpp"
#include "ecourna/api/security/isymmetriccipherfactory.hpp"

// The vector's __swap_out_circular_buffer (target fn 5786) holds table slot 171, the executable TU's invoke of it, and
// fn 631 keeps a call to it. Our link has no such invoke, so its one caller would inline it: this takes its address.
extern "C" void w100_troca(int, int) __asm__("_ZNSt3__26vectorIN3api18SPolySingletonInfoENS_9allocatorIS2_EEE26__swap_out_circular_bufferERNS_14__split_bufferIS2_RS4_EE");

namespace {

template <typename T>
inline int w100_usa()
{
    const std::source_location local;
    T& a = api::CPolySingleton<T>::instance(api::g_polySingletonsInfo(), local);
    T& b = api::CPolySingleton<T>::instance(api::g_polySingletonsInfo(), local);
    return &a == &b ? 3 : (api::CPolySingletonList::has<T>() ? 5 : 7);
}

// fn 8986, the executable TU's push, is has<IGenericFactory<IThreadImpl>>'s other caller beside the constructor of CThread
__attribute__((noinline)) int w100_has_fabrica()
{
    return api::CPolySingletonList::has<api::IGenericFactory<api::IThreadImpl>>() ? 9 : 11;
}

[[noreturn]] __attribute__((noinline, cold)) void w100_falha(const char* detalhe)
{
    using namespace std::string_literals;
    throw std::runtime_error("outro texto, de outro comprimento: "s + detalhe);
}

__attribute__((noinline)) int w100_todos()
{
    return w100_usa<api::IScreen>() + w100_usa<api::IBeep>() + w100_usa<api::IPower>() + w100_usa<api::IUrna>() + w100_usa<api::IResource>() +
        w100_usa<api::IInputMT>() + w100_usa<comum::CCalculaCV>() + w100_usa<api::IPaperRelatorios>() + w100_usa<comum::IEventosLog>() +
        w100_usa<api::IAjusteDataHora>() + w100_usa<ecourna::api::security::IRng>() + w100_usa<api::CEscritorLog>() +
        w100_usa<comum::IInterfaceInit>() + w100_usa<api::IGenericFactory<api::ISemaphore>>() +
        w100_usa<comum::IControladorRegistraMesarios>() + w100_usa<api::IGenericFactory<api::ISyncCtl>>() + w100_usa<comum::IInterfaceSavd>();
}

// Stands for fn 8302's call of CPolySingleton<T>::set, which keeps the function out of line: fns 4879 and 4890 have two
// callers in the target, and 5444 and 1155 are one each.
template <typename T>
__attribute__((noinline)) void w100_define(std::unique_ptr<T> instancia, int vezes)
{
    for (int i = 0; i < vezes; ++i) {
        api::CPolySingleton<T>::set(std::move(instancia));
    }
}

// Stands for the callers of the two GetInst that have not landed: 502, 652, 1265, 2024, 3059, 3673, 5543, 5904 and 8302
// for fn 1259, whose 3658 is in the link, and 10226, 10870 and 11862 for fn 1155, whose 479, 1382, 1898, 2230, 5472,
// 5473, 10874 and 10875 are in the link.
__attribute__((noinline)) int w100_getinst()
{
    int soma = &api::ITimerScheduler::GetInst() == &api::ITimerScheduler::GetInst() ? 2 : 4;
    soma += &api::ISystemDateTime::GetInst() == &api::ISystemDateTime::GetInst() ? 6 : 8;
    return soma;
}

// The control block of each singleton: __shared_ptr_pointer<T*, default_delete<T>, allocator<T>>. The target's builder is
// push<T>, or the shared_ptr constructor its thunks hold (10335, 10547, ...: a merged 1010 with that vptr), and each stores
// that vtable. w100_bloco is never called, uses no constructor of T, and is no target function: it reads the count back.
template <typename T>
long w100_bloco(std::unique_ptr<T> instancia)
{
    const std::shared_ptr<T> bloco(std::move(instancia));
    return bloco.use_count();
}

// Libc++ destructors the target keeps out of line, and uenux2's objects inline: two call sites each, in optnone functions
// where clang leaves the calls. A search of these target callers in splat/matched.txt says when a stand-in can go: of
// them only 871's 3095, 3328 and 8059 match, and each calls it in our link.
// - 321, __allocating_buffer<char>: 455 1091 2893 2927 3882 5344 5384 5758 7667 8758 8834 8911 8986 9039 9135 9233 10090 10212.
// - 871, unique_lock<mutex>: 624 1126 3095 3328 4771 5560 8059 13621 13974.
// - 388, shared_ptr<void>: 455 518 640 1091 1928 2154 2584 2650 3373 3882 4180 4774 5384 5707 5750 7667 8089 8090 8092 8096
//   8101 8758 8834 8911 8986 9039 9135 9233 9495 10090 11530. These calls hold no match: 388 stays no-candidate, since this
//   copy has an early exit where the target nests the ifs.
__attribute__((optnone, noinline)) void w100_destroi_a(std::shared_ptr<void>* ponteiro, std::unique_lock<std::mutex>* trava, std::__format::__allocating_buffer<char>* buffer)
{
    ponteiro->~shared_ptr();
    trava->~unique_lock();
    buffer->~__allocating_buffer();
}

__attribute__((optnone, noinline)) void w100_destroi_b(std::shared_ptr<void>* ponteiro, std::unique_lock<std::mutex>* trava, std::__format::__allocating_buffer<char>* buffer)
{
    buffer->~__allocating_buffer();
    trava->~unique_lock();
    ponteiro->~shared_ptr();
}

int (*volatile w100_sink)();
void* volatile w100_sink_bloco;
void (*volatile w100_sink_registra)();
int (*volatile w100_sink_getinst)();
void (*volatile w100_sink_timer)(std::unique_ptr<api::ITimerScheduler>, int);
void (*volatile w100_sink_datahora)(std::unique_ptr<api::ISystemDateTime>, int);
void (*volatile w100_sink_falha)(const char*);

struct SW100Roots {
    SW100Roots()
    {
        w100_sink = w100_todos;
        w100_sink_registra = api::CAjusteDataHora::Registra;
        w100_sink_getinst = w100_has_fabrica;
        w100_sink_bloco = reinterpret_cast<void*>(&w100_destroi_a);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_destroi_b);
        w100_sink_bloco = reinterpret_cast<void*>(&api::CPolySingletonList::depura);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_troca);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IAjusteDataHora>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IBeep>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IFingerPrepare>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IGenericFactory<api::IRWSyncCtl>>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IGenericFactory<api::ISemaphore>>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IGenericFactory<api::ISyncCtl>>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IGenericFactory<api::IThreadImpl>>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IImpressoraRelatorios>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IInputKbd>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IInputMT>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IPaperRelatorios>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IPower>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IResource>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IScreen>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::ISound>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::ISystemDateTime>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::ITimerScheduler>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::IUrna>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<api::CEscritorLog>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<comum::IControladorRegistraMesarios>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<comum::IInterfaceInit>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<comum::IInterfaceSavd>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<comum::impl::IValidaMidia>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<ecourna::api::security::IRng>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<ecourna::api::security::ISymmetricCipherFactory>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<vota::IAjusteInicial>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<vota::IExecucaoVota>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<vota::IQRCodeBUDS>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<vota::impl::IInformacaoThreadOperador>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<vota::impl::IPoliticaExecucaoEleitor>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<vota::impl::ISincronismoVotoEleitor>);
        w100_sink_bloco = reinterpret_cast<void*>(&w100_bloco<vota::testeteclado::impl::IGeradorTeclas>);
        w100_sink_getinst = w100_getinst;
        w100_sink_timer = w100_define<api::ITimerScheduler>;
        w100_sink_datahora = w100_define<api::ISystemDateTime>;
        w100_sink_falha = w100_falha;
    }
} w100_roots;

} // namespace
