// api::CTextFieldUpdate (/home/rubio/tse/uenux2/src/api/gui/ctextfieldupdate.cpp).
// Target functions of this file:
//   3658  CTextFieldUpdate(const SPoint&, const SharedIText&, const std::chrono::milliseconds&, const SFont&, TColor,
//         TColor)  record at line 38, column 15 (the null-text throw); not reconstructed: it calls
//         ITimerScheduler::GetInst (fn 1259), which has no body of ours yet, so line 38 stays free for it
//   5495 / 10917  ~CTextFieldUpdate() (base-object / deleting)   (here; out of line: the D0 calls the D2)
//   10916 Draw(IScreen&) const, 10915 Show(), 10914 Hide()       (pending)
//   10913 Rect() const     record at line 73, col 21; calls fn 3889, not named yet   (pending)
//   10912 GetTypeName() const                                    (here)
//   2241  Move(const SPoint&)  one body binaryen shares with five other fields   (pending)
// The definitions follow the target's order (the uses-1 band 10912-10917 in ledger/ordinals.tsv: D0, Draw, Show, Hide,
// Rect, GetTypeName); no record falls in the destructor or GetTypeName, so their lines are a choice. The pending
// members are defined in src/units/42-uenux2-ctextfieldupdate-pending.cpp.

#include "api/gui/ctextfieldupdate.h"

namespace api {

// (original lines 19-34: content not recovered)
#line 35
// <stubs>
// f3658 · 303 B · unmatched · name unknown
// ? f3658(i32, i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 40-41: content not recovered)
#line 42
CTextFieldUpdate::~CTextFieldUpdate() = default;

































std::string CTextFieldUpdate::GetTypeName() const
{
    return "CTextFieldUpdate";
}

} // namespace api
