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
// in our link: AdicionaItem stands for fn 1693, AddItem; its body is no target function's. fn 1693 also calls
// CMenuItem::UpdateRect (fn 3657), whose other target callers are 3655 (CMenuItem::SetSearchText, written) and 11884 (not
// reconstructed), so AdicionaItem calls it too, or binaryen would inline it into SetSearchText. SetSearchText has two
// target callers, 11884 and 11888, neither reconstructed: BuscaItem stands for both and calls it twice.
#include <memory>

#include "api/gui/cinputmenufield.h"

extern "C" {
extern const char cinputmenufield_vt[] __asm__("_ZTVN3api15CInputMenuFieldE");
void cinputmenufield_destroy_item(void*) __asm__(
    "_ZNSt3__212__destroy_atB8ne210108IN3api9CMenuItemETnNS_9enable_ifIXntsr8is_arrayIT_EE5valueEiE4typeELi0EEEvPS4_");
void cmenuitem_updaterect(void*) __asm__("_ZN3api9CMenuItem10UpdateRectEv");
void* cmenuitem_setsearchtext(void*, const void*) __asm__(
    "_ZN3api9CMenuItem13SetSearchTextERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

__attribute__((noinline)) std::shared_ptr<api::IInputValidation> ValidacaoMenu(api::CInputMenuField* menu)
{
    return std::make_shared<api::CMenuValidation>(menu);
}

__attribute__((noinline)) void AdicionaItem(void* item)
{
    cmenuitem_updaterect(item);
    cinputmenufield_destroy_item(item);
}

__attribute__((noinline)) void* BuscaItem(void* item, const void* busca)
{
    cmenuitem_setsearchtext(item, busca);
    return cmenuitem_setsearchtext(item, busca);
}

void* volatile w10899_sink;
const void* volatile w84_sink;

struct SW10899Roots {
    SW10899Roots()
    {
        w10899_sink = reinterpret_cast<void*>(&ValidacaoMenu);
        w84_sink = cinputmenufield_vt;
        w84_sink = reinterpret_cast<const void*>(&AdicionaItem);
        w84_sink = reinterpret_cast<const void*>(&BuscaItem);
    }
} w10899_roots;

} // namespace
