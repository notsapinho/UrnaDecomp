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
// GetDescricaoModo is a static member and the order of the statics' definitions are chosen. Not written: the SRect
// {0, 0, 639, 479} at .data 1577200, 12 bytes before s_codigoRetorno, the screen's area that fns 3678 and 653 read
// (src/units/31-uenux2-cformbuilder.mk and 120-uenux2-iform.mk say why they are not written) and 12055 and 7787 too.

#include <string>
#include <vector>

#include "api/gui/capplicationcontextstack.h"
#include "api/uelog/cescritorlog.h"

namespace api {

class CApplication {
public:
    // The level ShowExceptionMsg takes: its lambda's typeinfo name (ledger/strings.tsv, 520532) mangles the type as
    // CApplication's own EExceptionLevel. Target fn 5569 returns 2 when the context in force has its word set (+48,
    // CApplicationContext::m_padrao) and 1 otherwise; the one function it reaches in the target, 5568, never reads it
    // (that body ends at its std::async's throw: src/units/171-uenux2-capplication.mk). The enumerators' names and
    // the enum's underlying type are chosen.
    enum EExceptionLevel { EXCEPTION_LEVEL_1 = 1, EXCEPTION_LEVEL_2 = 2 };

    static void InitApplication(const std::string& aplicacao, const std::string& descricao, const std::string& versao,
                                ELogAplicativos aplicativo);
    static void PushContext(CApplicationContext context);
    static CApplicationContextGuard CriaContexto(int tipo, std::string titulo, std::string descricao,
                                                 std::string detalhe);
    static void EnterLoopDoingNothing();
    static std::string GetDescricaoModo();
    // Target fn 1695: a copy of the context in force, the stack's last, or CriaContextoPadrao("Erro inesperado",
    // "Pilha de contexto vazia") when the stack is empty. No record names it: its name and its being a static member
    // (it reads s_contextos) are chosen.
    static CApplicationContext GetContexto();

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

// Target fn 5569: the level of the context in force. Its result type is a reading: 7709 and 7710 pass the result as
// 5568's first argument, ShowExceptionMsg's EExceptionLevel (5568 holds that function's lambda's async state). No
// record names it; it reads no state of the class, so it is a free function (docs/how-to-decompile.md step 3); its
// name and its namespace (api, the file's; its callers are vota's) are chosen, as in api/util/csystem.h. Its file is a
// reading of use band 2 (ledger/ordinals.tsv): ahead of 5568 and EnterLoopDoingNothing (5566, record 503), with only
// 5567 between them, read as a libc++ thread routine (it calls __thread_local_data and pthread_setspecific).
CApplication::EExceptionLevel GetExceptionLevel();

// Target fn 1696: the parts written one after the other through a std::ostringstream, the separator between two of
// them. No record names it: its name, its being a free function of api and its file are chosen; in use band 7 it
// lies right ahead of GetContexto (1695), and capplication.cpp defines it first of the two.
std::string Join(const std::vector<std::string>& partes, const std::string& separador);

} // namespace api
