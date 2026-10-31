#pragma once

// api::IGenericFactory<AP>: the head alone. RTTI gives the instances and no base, and AP is the records' name for the
// parameter. Slot 2 is Create with no argument: api::CThread's constructor (fn 3598) calls it for the
// std::unique_ptr it stores, and slots 3 and 4 are the two overloads whose records are at lines 44 and 50, not written. Only typeid in api::CPolySingleton<T> needs an instance complete. The virtual destructor is in the first slot, as the control block's __on_zero_shared shows (fn 172 calls vtable + 4).

#include <memory>

namespace api {

template <typename AP>
class IGenericFactory {
public:
    virtual ~IGenericFactory() = default;

    virtual std::unique_ptr<AP> Create() = 0;
};

} // namespace api

// <stubs>
// f10872 · 21 B · unmatched · name unknown
// ? f10872(i32, i32) { ... }

// f10868 · 21 B · unmatched · name unknown
// ? f10868(i32, i32) { ... }

// f10863 · 21 B · unmatched · name unknown
// ? f10863(i32, i32) { ... }

// f10845 · 21 B · unmatched · name unknown
// ? f10845(i32, i32) { ... }

// f10871 · 21 B · unmatched · name unknown
// ? f10871(i32, i32) { ... }

// f10865 · 21 B · unmatched · name unknown
// ? f10865(i32, i32) { ... }

// f10856 · 21 B · unmatched · name unknown
// ? f10856(i32, i32) { ... }

// f10839 · 21 B · unmatched · name unknown
// ? f10839(i32, i32) { ... }
// </stubs>
