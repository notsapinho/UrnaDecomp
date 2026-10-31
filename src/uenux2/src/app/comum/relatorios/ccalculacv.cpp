// comum::CCalculaCV (/home/rubio/tse/uenux2/src/app/comum/relatorios/ccalculacv.cpp). This comment is the
// reconstruction's. The file's records are the constructor's (lines 58, 65 and 74, held by fn 12110, which inlines it)
// and IncluiString's (line 109, fns 942 and 5967); neither is reconstructed, and their lines stay blank. Written here:
// the destructor, fn 5614, and DestroyInst, which fn 3698 (comum::CGeradorBU's destructor) holds inlined by binaryen and
// which has no target function of its own; neither has a record, and their lines are a choice, after the records.
// src/units/139-uenux2-cgeradorbu.mk says what places DestroyInst in another TU than its caller.
#include "app/comum/relatorios/ccalculacv.h"

#include <typeinfo>

#include "api/pattern/cpolysingletonlist.h"

namespace comum {

// (original lines 15-54: content not recovered)
#line 55
// <stubs>
// f12110 · 17349 B · unmatched · name unknown
// void f12110(i32) { ... }
// </stubs>

// (original lines 60-105: content not recovered)
#line 106
// <stubs>
// f5967 · 554 B · unmatched · name unknown
// void f5967(i32, i32) { ... }

// f942 · 107 B · unmatched · name unknown
// void f942(i32, i32) { ... }
// </stubs>













CCalculaCV::~CCalculaCV() = default;

void CCalculaCV::DestroyInst()
{
    api::TPolySingletonsInfo& info = api::g_polySingletonsInfo();
    api::CPolySingletonList::remove(typeid(CCalculaCV).name(), info);
}

} // namespace comum
