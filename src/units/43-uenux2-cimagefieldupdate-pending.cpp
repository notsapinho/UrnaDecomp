// Pending members: the api::CImageFieldUpdate members not reconstructed yet. The class's vtable needs them defined;
// their bodies are NOT the target's, they trap. Draw is the class's key function (its first virtual member defined out
// of the class), so the vtable, the destructors (target fns 5531 and 11086) and GetTypeName (11085), which the class
// defines inline in api/gui/cimagefieldupdate.h and which match from here, are emitted in this object until Draw moves
// into the class's source. That source is src/uenux2/src/api/gui/cimagefieldupdate.cpp, which no file of ours holds:
// its records are the constructor's throw at line 32, column 15 (CImageFieldUpdate(const SPoint &, const SharedIImage &,
// const std::chrono::milliseconds &, EAnchorPoint); binaryen inlined the constructor into fn 3059, so it has no target
// function of its own, and it is not reconstructed) and Rect's at line 80, column 12.
// Target functions:
// - Draw 11090 calls IScreen's vtable slots 22 and 24 (the image-drawing members), which api/gui/iscreen.h does not
//   declare;
// - Show 11089 and Hide 11088 call slots 2 and 3 (Start and Stop in api/util/itimer.h) of the api::ITimer at +44
//   (m_timer), which the class header only declares;
// - Rect 11087 (record cimagefieldupdate.cpp:80:12) calls CPolySingleton<IScreen>'s instance, fn 512, not named yet;
// - Move 2241 is binaryen's one body for CTextField, CImageField, CDSImageField, CImageFieldUpdate, CTextFieldBlinking
//   and CTextFieldUpdate; it reads the field's IForm<IScreen> through IsVisible and Refresh (api/gui/iform.h).
// Move each into cimagefieldupdate.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/cimagefieldupdate.h"

namespace api {

void CImageFieldUpdate::Draw(IScreen&) const
{
    __builtin_trap();
}

void CImageFieldUpdate::Show()
{
    __builtin_trap();
}

void CImageFieldUpdate::Hide()
{
    __builtin_trap();
}

SRect CImageFieldUpdate::Rect() const
{
    __builtin_trap();
}

void CImageFieldUpdate::Move(const SPoint&)
{
    __builtin_trap();
}

} // namespace api
