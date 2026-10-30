// api::CMovieField (/home/rubio/tse/uenux2/src/api/gui/cmoviefield.cpp, the file Rect's record names).
// Target functions of this file:
//   5524 / 11065  ~CMovieField() (base-object / deleting)   (here; out of line: the D0 calls the D2 and drops its
//                 result; written as a call to Hide: Hide's two stores spelled out give the same object)
//   11064 Draw(IScreen&) const                                    (pending)
//   11063 Rect() const   record at line 53, column 12; calls fn 512, not named yet   (pending)
//   11062 Move(const SPoint&), 11061 Show()                       (pending)
//   11060 Hide()                                                  (here)
//   11059 GetTypeName() const   a thunk into binaryen's merge 2904 (pending)
// The constructor has no target function of its own (it is inlined, with std::make_shared, into fn 5543; its lambda's
// std::function members are fns 11054-11058) and is not reconstructed: it calls ITimerScheduler::GetInst (fn 1259),
// which has no body of ours. The definitions follow the target's order (the uses-1 band 11059-11065 of
// ledger/ordinals.tsv: D0, Draw, Rect, Move, Show, Hide, GetTypeName); no record falls in the destructor or Hide, so
// their lines are a choice: the destructor above Rect's line 53, Hide below it. The pending members are defined in
// src/units/52-uenux2-cmoviefield-pending.cpp.

#include "api/gui/cmoviefield.h"

#include "api/util/itimer.h"

namespace api {

// (original lines 23-39: content not recovered)
#line 40
CMovieField::~CMovieField()
{
    Hide();
}









































void CMovieField::Hide()
{
    m_timer->Stop();
    m_visivel = 0;
}

} // namespace api
