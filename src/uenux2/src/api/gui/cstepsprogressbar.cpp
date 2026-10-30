// api::CStepsProgressBar (/home/rubio/tse/uenux2/src/api/gui/cstepsprogressbar.cpp).
// Target functions of this file:
//   13550 holds the constructor, CStepsProgressBar(const uedword, const std::vector<std::string> &, const SRect &,
//         seven const TColor), inlined there (vota::CPreShowProgressBar's slot 2); its throw is the record at line 428,
//         column 15, which stays free for it (not reconstructed)
//   3665 / 10973  ~CStepsProgressBar() (complete / deleting; out of line, the D0 calls the D2)   (here)
//   10969 GetTypeName() const                                   (here)
//   10968 Rect() const                                          (here)
//   5504  Draw(IScreen&) const                                  (pending)
//   10970 Move(const SPoint&), which calls fn 1915, not named yet  (pending)
// No record falls in the destructor, GetTypeName or Rect: their lines, after the constructor's, are a choice.
// The pending members are defined in src/units/41-uenux2-cstepsprogressbar-pending.cpp.

#include "api/gui/cstepsprogressbar.h"

namespace api {

// (original lines 18-424: content not recovered)
#line 425
// <stubs>
// f13550 · 2118 B · unmatched · name unknown
// void f13550(i32, i32) { ... }
// </stubs>






CStepsProgressBar::~CStepsProgressBar() = default;

std::string CStepsProgressBar::GetTypeName() const
{
    return "CStepsProgressBar";
}

SRect CStepsProgressBar::Rect() const
{
    return m_rect;
}

} // namespace api
