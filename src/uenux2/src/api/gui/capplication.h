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

#include <string>

#include "api/gui/capplicationcontextstack.h"
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

    static bool s_finalizar;
    static int s_codigoRetorno;
    static std::string s_aplicacao;
    static std::string s_descricao;
    static std::string s_versao;
    static ELogAplicativos s_aplicativo;
    static CApplicationContextStack s_contextos;

private:
    static void PushContextoInicial(std::string titulo, std::string descricao);
    static CApplicationContextGuard CriaContexto(CApplicationContext contexto);
};

} // namespace api
