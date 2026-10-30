// Pending members: the api::CImageFieldUpdate members cimagefieldupdate.cpp does not hold yet. The class's vtable (emitted
// with Draw, its key function, in that TU, with the inline destructors and GetTypeName) needs them defined; their bodies
// are NOT the target's, they trap.
// Its records are the constructor's throw at line 32, column 15 (CImageFieldUpdate(const SPoint &, const SharedIImage &,
// const std::chrono::milliseconds &, EAnchorPoint); binaryen inlined the constructor into fn 3059, so it has no target
// function of its own, and it is not reconstructed) and Rect's at line 80, column 12.
// Target functions:
// - Rect 11087 (record cimagefieldupdate.cpp:80:12) calls CPolySingleton<IScreen>'s instance, fn 512, not named yet.
// Move each into cimagefieldupdate.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/cimagefieldupdate.h"

namespace api {

SRect CImageFieldUpdate::Rect() const
{
    __builtin_trap();
}

} // namespace api
