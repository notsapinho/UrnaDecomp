// Pending members: the api::CStepsProgressBar members src/uenux2/src/api/gui/cstepsprogressbar.cpp does not hold yet.
// The class's vtable (emitted with the destructor, its key function, in that TU) needs them defined; their bodies are
// NOT the target's, they trap. Target functions:
//   5504  Draw(IScreen&) const (slot 2, 11502 B): rebuilds the segments when m_recalcular is set, through its callees
//         5505, 5506 and 5507 (no name), and draws them through IScreen slots 17, 18 and 19 (iscreen.h's FillPath,
//         DrawPath and DrawText from a point)
// Move each into cstepsprogressbar.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/cstepsprogressbar.h"

namespace api {

void CStepsProgressBar::Draw(IScreen&) const
{
    __builtin_trap();
}

} // namespace api
