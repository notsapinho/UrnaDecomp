#include "app/comum/dados/celeitores.h"

#include "ecourna/api/pattern/singleton.hpp"

namespace comum {

// (original lines 7-40: content not recovered)
#line 41
std::unique_ptr<CEleitores> CEleitores::s_instance;
std::mutex CEleitores::s_mutex;

SINGLETON_IMPL_GET_INST(CEleitores, s_mutex, s_instance)

CEleitores::~CEleitores() = default;

} // namespace comum

// <stubs>
// f6734 · 6461 B · unmatched · name unknown
// void f6734(i32) { ... }

// f5761 · 3007 B · unmatched · name unknown
// void f5761(i32, i32) { ... }

// f2825 · 1011 B · unmatched · name unknown
// void f2825(i32, i32) { ... }

// f2824 · 2557 B · unmatched · placement: link order · name unknown
// void f2824(i32, i32) { ... }

// f10210 · 334 B · unmatched · name unknown
// void f10210(i32) { ... }

// f7377 · 2313 B · unmatched · name unknown
// void f7377(i32) { ... }

// f5765 · 597 B · unmatched · name unknown
// void f5765(i32, i32) { ... }

// f11529 · 796 B · unmatched · name unknown
// void f11529(i32, i32) { ... }

// f11528 · 564 B · unmatched · name unknown
// void f11528(i32, i32) { ... }

// f11527 · 564 B · unmatched · name unknown
// void f11527(i32, i32) { ... }

// f11526 · 235 B · unmatched · name unknown
// void f11526(i32) { ... }
// </stubs>
