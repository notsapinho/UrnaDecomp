// Roots: keep api::CMenuValidation's vtable (@1583300, slots 2 and 3 are fns 10900 and 10899) in the skeleton link the way
// the target keeps it. In the target the vtable is referenced by the class's constructor, which fn 3675 holds with
// std::make_shared<CMenuValidation>; no target function calls 10899 directly. fn 3675 is not reconstructed, so this
// stand-in builds the object the same way, which also instantiates __shared_ptr_emplace<api::CMenuValidation>, the
// control block of target fns 10892 and 10891. It includes the class header for make_shared (src/units/README.md,
// "Companion files"). Compiled with APP_CXXFLAGS, like the other stand-ins.
//
// api::CInputMenuField's vtable (@1583356): in the target only its constructor stores it, inlined into fn 3675 (not
// reconstructed), so the sink takes its address, which keeps every slot. std::__destroy_at of a CMenuItem (fn 5490) has
// two target callers, 1693 and 5491 (the destructor), and binaryen would inline it into the destructor, its one caller
// in our link: AdicionaItem stands for fn 1693, AddItem; its body is no target function's. Declared through an asm label,
// so it instantiates nothing.
#include <memory>

#include "api/gui/cinputmenufield.h"

extern "C" {
extern const char cinputmenufield_vt[] __asm__("_ZTVN3api15CInputMenuFieldE");
void cinputmenufield_destroy_item(void*) __asm__(
    "_ZNSt3__212__destroy_atB8ne210108IN3api9CMenuItemETnNS_9enable_ifIXntsr8is_arrayIT_EE5valueEiE4typeELi0EEEvPS4_");
}

namespace {

__attribute__((noinline)) std::shared_ptr<api::IInputValidation> ValidacaoMenu(api::CInputMenuField* menu)
{
    return std::make_shared<api::CMenuValidation>(menu);
}

__attribute__((noinline)) void AdicionaItem(void* item)
{
    cinputmenufield_destroy_item(item);
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
