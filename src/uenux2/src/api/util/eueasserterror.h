#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

// Reconstruction's note. RTTI names ecourna::api::exception::CBaseError<api::EUeAssertError, SErrorLimits{3400, 4200}>
// (typeinfo 1532588), the type 25 target functions throw through fn 463, its constructor. Each throw passes a code of its
// own (3400 to 3485, one per site) and the text of a condition: "Assert (", the condition as the source spells it, and
// ")". "Assert (right >= l)" goes with 3400 in api::SRect::Left (fn 5488, record primitives.cpp 20:37). A record made
// inside a macro expansion holds the invocation's closing parenthesis (docs/reference/facts/reading.md R19), so each of
// the four SRect records at column 37 is a macro invocation that closes there. The conditions differ in length (10,
// 11, 9 and 8 characters for Left, Top, Right and Bottom), so the four close at one column only if the codes differ the
// other way, as the suffixes LEFT, TOP, RIGHT and BOTTOM do after one prefix: that is evidence for the suffixes. The
// condition's text is: the macro stringizes its argument. Chosen: the macro's name and its two parameters, the
// enumerators' prefix and this file's path. The values are the codes the target throws.
enum EUeAssertError {
    // api::SRect's setters (records primitives.cpp 20, 26, 32 and 38): Left in fn 5488, Right in fn 5487, Top and Bottom
    // inlined into fn 5537
    EUA_RECT_LEFT = 3400,
    EUA_RECT_TOP = 3401,
    EUA_RECT_RIGHT = 3402,
    EUA_RECT_BOTTOM = 3403,
    // vota::CQuerImprimirBU::StartState (fn 12035, records cquerimprimirbu.cpp 40:102 and 41:85): the texts "Assert
    // (poInfo.GetVota().GetEstadoVota() == EAVIMPRIMIRBU)" and "Assert (poInfo.GetVota().GetQtdBU() == 0)". With the
    // invocation indented four columns and the code qualified as api::, the columns leave 34 characters for each name;
    // the names are chosen to that length
    EUA_QUERIMPRIMIRBU_ESTADO_INVALIDO = 3474,
    EUA_QUERIMPRIMIRBU_QTD_BU_NAO_ZERO = 3475,
};

using CUeAssertError = ecourna::api::exception::CBaseError<EUeAssertError, ecourna::api::exception::SErrorLimits{3400, 4200}>;

} // namespace api

#define ASSERT(condicao, codigo)                                                 \
    do {                                                                         \
        if (!(condicao)) {                                                       \
            throw ::api::CUeAssertError(codigo, "Assert (" #condicao ")");       \
        }                                                                        \
    } while (0)
