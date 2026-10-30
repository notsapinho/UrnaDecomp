// Pending members: the api::CImageFieldUpdate members cimagefieldupdate.cpp does not hold yet. The class's vtable needs
// them defined; their bodies are NOT the target's, they trap. Draw is the class's key function (its first virtual
// member defined out of the class), so the vtable, the destructors (target fns 5531 and 11086) and GetTypeName (11085), which the class
// defines inline in api/gui/cimagefieldupdate.h and which match from here, are emitted in this object until Draw moves
// into the class's source, src/uenux2/src/api/gui/cimagefieldupdate.cpp.
// Its records are the constructor's throw at line 32, column 15 (CImageFieldUpdate(const SPoint &, const SharedIImage &,
// const std::chrono::milliseconds &, EAnchorPoint); binaryen inlined the constructor into fn 3059, so it has no target
// function of its own, and it is not reconstructed) and Rect's at line 80, column 12.
// Target functions:
// - Draw 11090 calls IScreen's vtable slots 22 and 24 (the image-drawing members), which api/gui/iscreen.h does not
//   declare;
// - Rect 11087 (record cimagefieldupdate.cpp:80:12) calls CPolySingleton<IScreen>'s instance, fn 512, not named yet.
// Move each into cimagefieldupdate.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/cimagefieldupdate.h"

namespace api {

void CImageFieldUpdate::Draw(IScreen&) const
{
    __builtin_trap();
}

SRect CImageFieldUpdate::Rect() const
{
    __builtin_trap();
}

} // namespace api
