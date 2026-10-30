// Pending members: the api::CTextField members src/uenux2/src/api/gui/ctextfield.cpp does not hold yet. The class's
// vtable (emitted with GetTypeName in that TU) needs them defined; their bodies are NOT the target's, they trap.
// Target function: Rect 10951 (record ctextfield.cpp:55:21; calls fn 3889, which has no name yet).
// Move it into ctextfield.cpp when it is reconstructed and delete this file.
#include "api/gui/ctextfield.h"

namespace api {

SRect CTextField::Rect() const
{
    __builtin_trap();
}

} // namespace api
