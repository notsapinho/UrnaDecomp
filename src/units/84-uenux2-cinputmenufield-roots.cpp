// Roots: keep api::CMenuValidation's vtable (@1583300, slots 2 and 3 are fns 10900 and 10899) in the skeleton link the way
// the target keeps it. In the target the vtable is referenced by the class's constructor, which fn 3675 holds with
// std::make_shared<CMenuValidation>; no target function calls 10899 directly. fn 3675 is not reconstructed, so this
// stand-in builds the object the same way, which also instantiates __shared_ptr_emplace<api::CMenuValidation>, the
// control block of target fns 10892 and 10891. It includes the class header for make_shared (src/units/README.md,
// "Companion files"). Compiled with APP_CXXFLAGS, like the other stand-ins.
//
// api::CInputMenuField's vtable (@1583356): in the target only its constructor stores it, inlined into fn 3675 (not
// reconstructed), so the sink takes its address, which keeps every slot. Two functions of cinputmenufield.cpp have direct
// callers that are not reconstructed, and binaryen would inline each into its one caller here: std::__destroy_at of a
// CMenuItem (fn 5490; target callers 1693 and 5491, the destructor) and CInputMenuField::Reposiciona (fn 2770; target
// callers 1693, 3675 and 10895, Move). AdicionaItem stands for fn 1693, AddItem, which calls both; its body is no target
// function's. Declared through asm labels, so it instantiates nothing.
#include <memory>

#include "api/gui/cinputmenufield.h"

extern "C" {
extern const char cinputmenufield_vt[] __asm__("_ZTVN3api15CInputMenuFieldE");
void cinputmenufield_destroy_item(void*) __asm__(
    "_ZNSt3__212__destroy_atB8ne210108IN3api9CMenuItemETnNS_9enable_ifIXntsr8is_arrayIT_EE5valueEiE4typeELi0EEEvPS4_");
void cinputmenufield_reposiciona(void*) __asm__("_ZN3api15CInputMenuField11ReposicionaEv");
}

namespace {

__attribute__((noinline)) std::shared_ptr<api::IInputValidation> ValidacaoMenu(api::CInputMenuField* menu)
{
    return std::make_shared<api::CMenuValidation>(menu);
}

__attribute__((noinline)) void AdicionaItem(void* item, void* menu)
{
    cinputmenufield_destroy_item(item);
    cinputmenufield_reposiciona(menu);
}

void* volatile w10899_sink;
const void* volatile w84_sink;

struct SW10899Roots {
    SW10899Roots()
    {
        w10899_sink = reinterpret_cast<void*>(&ValidacaoMenu);
        w84_sink = cinputmenufield_vt;
        w84_sink = reinterpret_cast<const void*>(&AdicionaItem);
    }
} w10899_roots;

} // namespace
