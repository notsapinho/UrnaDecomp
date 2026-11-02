#pragma once

// Reconstruction's note, not TSE's text. api::CApplication, in part: the class's name and EnterLoopDoingNothing's are
// the records' (capplication.cpp 503:32, a static member); InitApplication's name, class and parameter types are the
// typeinfo name of its local class (ledger/strings.tsv, 519992). The path of this header is chosen, beside the records'
// file, and so is every other member's name; the statics' types are chosen beyond the widths the bytes give:
// - s_finalizar and s_codigoRetorno are what target fn 5566 reads: a byte at .bss 1839209 tested for non-zero, and a
//   word at .data 1577212 whose initial bytes are -1 and which the loop compares signed with 0. InitApplication (fn
//   11159) stores -1 into the word; fn 11151 reads both with the same test and is not written.
// - s_aplicacao, s_descricao and s_versao are the three strings InitApplication assigns at .bss 1839168, 1839180 and
//   1839192, in its parameters' order, and s_aplicativo the word it stores its fourth parameter in, at 1839204.
// - s_contextos is the stack at .bss 1839212 that InitApplication clears, PushContext (fn 3684) pushes on, Pop (fn 5553)
//   takes from and CriaContexto (fn 676) hands to a guard.
// The class's other members (the records of ShowExceptionMsgScreen, LogExceptionMsg and EnterLoopBeeping's lambda) are
// not written.
//
// Two more statics and GetDescricaoModo (fn 5564), from the target's data and 5564's body. A word whose initial value
// is 48 lies at .data 1577208, 4 bytes before s_codigoRetorno, and a byte at .bss 1839208, the byte before s_finalizar.
// 5564 reads both (their only readers but 7787, which reads the word) and returns "DEMONSTRAÇÃO" when the byte is 1,
// otherwise "SIMULADO" for the word's 50 and "TREINAMENTO" for 51, else an empty string; fns 502 and 4620 call it. Its
// place in the uses-2 band of ledger/ordinals.tsv, between 5566 (EnterLoopDoingNothing) and 5563 (InitApplication's
// local facet's deleting destructor), puts it in capplication.cpp after EnterLoopDoingNothing. Widths and values are the
// bytes'; every name, the types beyond their widths (a bool tested as 1, an int compared as a 32-bit word), that
// GetDescricaoModo is a static member and the order of the statics' definitions are chosen.
//
// s_areaTela is the SRect {0, 0, 639, 479} at .data 1577200, 12 bytes before s_codigoRetorno: the screen's area. Fn 3678
// (api::CFormBuilder::AddLabeledKey) passes its address to GetLabeledKeyPos (fn 5544) twice, and fns 653, 7787, 12040 and
// 12055 read it, none storing to it: 653 its left, right and bottom, 12040 its bottom, 7787 and 12055 its eight bytes at
// once (`/usr/bin/grep -rlE 'i32\.const 157720[0-7]($|[^0-9])' build/out/splat/pieces/asm` lists those five). GetAreaTela
// returns it and has no target function: binaryen inlines it into its one caller, 3678, whose calls of 5544 keep their
// area argument as the target's do. With 3678 naming the static itself, our link folds that argument into 5544
// (src/units/31-uenux2-cformbuilder.mk has both measurements), which fits a call binaryen inlines only after its
// dead-argument elimination (a reading). The names, the static's being a public member, the accessor and its being out
// of line here are chosen; the values and the width are the bytes'.

#include <string>

#include "api/gui/capplicationcontextstack.h"
#include "api/gui/primitives.h"
#include "api/uelog/cescritorlog.h"

namespace api {

class CApplication {
public:
    static void InitApplication(const std::string& aplicacao, const std::string& descricao, const std::string& versao,
                                ELogAplicativos aplicativo);
    static void PushContext(CApplicationContext context);
    static CApplicationContextGuard CriaContexto(int tipo, std::string titulo, std::string descricao,
                                                 std::string detalhe);
    static void EnterLoopDoingNothing();
    static std::string GetDescricaoModo();

    static const SRect& GetAreaTela();

    static SRect s_areaTela;

    static bool s_finalizar;
    static int s_codigoRetorno;
    static int s_modo;
    static bool s_demonstracao;
    static std::string s_aplicacao;
    static std::string s_descricao;
    static std::string s_versao;
    static ELogAplicativos s_aplicativo;
    static CApplicationContextStack s_contextos;

private:
    static CApplicationContextGuard CriaContexto(CApplicationContext contexto);
};

} // namespace api
