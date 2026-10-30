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
// The extern template keeps fn 252, std::operator+(string&&, string&&), libc++'s: it is matched from libc++.a, which
// links after this object, and with an instantiation here this object's copy wins the link and the match goes. Without
// this line exactly 252 leaves `match`. It holds until a real uenux2 TU instantiates that operator: the fragment has both.
//
// w100_usa and w100_todos are stand-ins with a body no target function has. w100_usa passes both arguments, an empty
// std::source_location for the record a real caller's default argument makes: a record here would be none of the target's.
#include <source_location>
#include <stdexcept>
#include <string>

#include "api/gui/ipaperrelatorios.h"
#include "api/gui/iresource.h"
#include "api/gui/iscreen.h"
#include "api/hwil/ibeep.h"
#include "api/hwil/iinput.h"
#include "api/hwil/ipower.h"
#include "api/hwil/iurna.h"
#include "api/ipc/isemaphore.h"
#include "api/ipc/isyncctl.h"
#include "api/pattern/cpolysingleton.h"
#include "api/pattern/igenericfactory.h"
#include "api/uelog/cescritorlog.h"
#include "api/util/iajustedatahora.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"
#include "app/comum/iinterfaceinit.h"
#include "app/comum/log/ieventoslog.h"
#include "app/comum/relatorios/ccalculacv.h"
#include "ecourna/api/security/irng.hpp"

extern template std::string std::operator+<char, std::char_traits<char>, std::allocator<char>>(std::string&&, std::string&&);

namespace {

template <typename T>
inline int w100_usa()
{
    const std::source_location local;
    T& a = api::CPolySingleton<T>::instance(api::g_polySingletonsInfo(), local);
    T& b = api::CPolySingleton<T>::instance(api::g_polySingletonsInfo(), local);
    return &a == &b ? 3 : (api::CPolySingletonList::has<T>() ? 5 : 7);
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
        w100_usa<comum::IControladorRegistraMesarios>() + w100_usa<api::IGenericFactory<api::ISyncCtl>>();
}

int (*volatile w100_sink)();
void (*volatile w100_sink_falha)(const char*);

struct SW100Roots {
    SW100Roots()
    {
        w100_sink = w100_todos;
        w100_sink_falha = w100_falha;
    }
} w100_roots;

} // namespace
