// Unit 100's source. The pointer every default argument of api::CPolySingleton calls through, and the function it holds
// (fn 11265, table slot 284). The file is chosen: the target's pointer is the first word of the data of the executable
// TU (0x174a30, the word before that TU's first record), whose code no object here can compile (docs/reference/facts/levels.md, V1).
// The function is not inline: its guard is read as a plain byte, with no `& 1`, which is an internal variable's guard.
#include "api/pattern/cpolysingletonlist.h"

namespace api {

static TPolySingletonsInfo& polySingletonsInfoPadrao()
{
    static TPolySingletonsInfo info;
    info.m_depuracao = true;
    return info;
}

TPolySingletonsInfo& (*g_polySingletonsInfo)() = polySingletonsInfoPadrao;

} // namespace api
