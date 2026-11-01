#pragma once

// Reconstruction's note, not TSE's text. api::CApplication, in part: the class's name and EnterLoopDoingNothing's are
// the records' (capplication.cpp 503:32, a static member); the path of this header is chosen, beside the records' file.
// The two statics are what target fn 5566 reads, with their widths from the bytes: a byte at .bss 1839209 tested for
// non-zero, and a word at .data 1577212 whose initial bytes are -1 and which the loop compares signed with 0. Their
// names, the bool and int types and their order are chosen. Fn 11159 stores -1 into the word and fn 11151 reads both
// with the same test; neither is written. The class's other members (the records of ShowExceptionMsgScreen,
// LogExceptionMsg and EnterLoopBeeping's lambda, InitApplication, which stores three strings at 1839168, 1839180 and
// 1839192) are not written.
//
// Two more statics and GetDescricaoModo (fn 5564), from the target's data and 5564's body. A word whose initial value
// is 48 lies at .data 1577208, 4 bytes before s_codigoRetorno, and a byte at .bss 1839208, the byte before s_finalizar.
// 5564 reads both (their only readers but 7787, which reads the word) and returns "DEMONSTRAÇÃO" when the byte is 1,
// otherwise "SIMULADO" for the word's 50 and "TREINAMENTO" for 51, else an empty string; fns 502 and 4620 call it. Its
// place in the uses-2 band of ledger/ordinals.tsv, between 5566 (EnterLoopDoingNothing) and 5563 (InitApplication's
// local facet's deleting destructor), puts it in capplication.cpp after EnterLoopDoingNothing. Widths and values are the
// bytes'; every name, the types beyond their widths (a bool tested as 1, an int compared as a 32-bit word), that
// GetDescricaoModo is a static member and the order of the definitions are chosen. Not written: the SRect
// {0, 0, 639, 479} at .data 1577200, 12 bytes before s_codigoRetorno, the screen's area that fns 3678 and 653 read
// (src/units/31-uenux2-cformbuilder.mk and 120-uenux2-iform.mk say why they are not written) and 12055 and 7787 too.

#include <string>

namespace api {

class CApplication {
public:
    static void EnterLoopDoingNothing();
    static std::string GetDescricaoModo();

    static bool s_finalizar;
    static int s_codigoRetorno;
    static int s_modo;
    static bool s_demonstracao;
};

} // namespace api
