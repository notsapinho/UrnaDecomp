#pragma once

// Reconstruction's note, not TSE's text. api::CApplication, in part: the class's name and EnterLoopDoingNothing's are
// the records' (capplication.cpp 503:32, a static member); the path of this header is chosen, beside the records' file.
// The two statics are what target fn 5566 reads, with their widths from the bytes: a byte at .bss 1839209 tested for
// non-zero, and a word at .data 1577212 whose initial bytes are -1 and which the loop compares signed with 0. Their
// names, the bool and int types and their order are chosen. Fn 11159 stores -1 into the word and fn 11151 reads both
// with the same test; neither is written. The class's other members (the records of ShowExceptionMsgScreen,
// LogExceptionMsg and EnterLoopBeeping's lambda, InitApplication, which stores three strings at 1839168, 1839180 and
// 1839192) are not written.

namespace api {

class CApplication {
public:
    static void EnterLoopDoingNothing();

    static bool s_finalizar;
    static int s_codigoRetorno;
};

} // namespace api
