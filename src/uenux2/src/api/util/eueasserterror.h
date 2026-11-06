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
    // comum::CImprimirIdentificacaoMesariosFinal::GetNomeMesario (fn 5385, record
    // cimprimiridentificacaomesariosfinal.cpp 229:84): the text "Assert (mesario)". With the invocation indented four
    // columns and the code qualified as api::, the column leaves 58 characters for the name, chosen to that length
    EUA_IMPRIMIRIDENTIFICACAOMESARIOSFINAL_MESARIO_INEXISTENTE = 3409,
    // comum::CDataSourcesRelatorio<comum::CRdvVota, comum::CEleitores>::DetalheCandidatoZE (fn 11973, record
    // cdatasourcesrelatorio.h 152:80): the text "Assert (qtd == 0u)". With the invocation indented eight columns (a member
    // defined in its class) and the code qualified as api::, the column leaves 48 characters for the name; the name is
    // chosen to that length
    EUA_DATASOURCESRELATORIO_DETALHECANDIDATOZE_VOTO = 3410,
    // vota::GetQuantidadeMaximaBUsAdicionais (fn 4582, record votadefs.cpp 135:97): the text "Assert (numImpresso >=
    // numObrigatorias)". With the invocation indented four columns and the code qualified as api::, the column leaves
    // 48 characters for the name, chosen to that length
    EUA_QUANTIDADEMAXIMABUSADICIONAIS_IMPRESSO_MENOR = 3449,
    // vota::CEmitirMaisBU::StartState (fn 12082, records cemitirmaisbu.cpp 46:100 and 47:114): the texts "Assert
    // (appInfo.GetVota().GetEstadoVota() == EAVENCERRADA)" and "Assert (appInfo.GetVota().GetEstadoEncerramento() ==
    // EAEFIMDOSTRABALHOS)". With the invocations indented four columns and the codes qualified api::, the columns leave
    // 32 characters for each name, chosen to that length
    EUA_EMITIRMAISBU_ESTADO_INVALIDO = 3452,
    EUA_EMITIRMAISBU_FIMDOSTRABALHOS = 3453,
    // vota::CGeraRelatorios::StartState (fn 12105, record cgerarelatorios.cpp 51:104): the text "Assert
    // (poInfo.GetVota().GetEstadoVota() == EAVGERARRELATORIOS)". With the invocation indented four columns and the code
    // qualified api::, the column leaves 31 characters for the name, chosen to that length
    EUA_GERARELATORIOS_EST_INVALIDO = 3455,
    // vota::CVerificaQtdBUsAdicionais::StartState (fn 12023, records cverificaqtdbusadicionais.cpp 36:102 and 37:116):
    // the texts "Assert (egVota.GetEstadoVota() == EAVENCERRADA)" and "Assert (egVota.GetEstadoEncerramento() ==
    // EAEFIMDOSTRABALHOS)". With the invocations indented four columns and the codes qualified api::, the columns leave
    // 45 characters for each name, chosen to that length
    EUA_VERIFICAQTDBUSADICIONAIS_ESTADO_ENCERRADA = 3461,
    EUA_VERIFICAQTDBUSADICIONAIS_ENCERRAMENTO_FIM = 3462,
    // vota::CImprimindoBim::StartState (fn 12071, records cimprimindobim.cpp 50:87 and 51:107): the texts "Assert
    // (vota.GetEstadoVota() == EAVENCERRADA)" and "Assert (vota.GetEstadoEncerramento() == EAEIMPRIMIROBRIGATORIABU)".
    // With the invocations indented four columns and the codes qualified api::, the columns leave 32 characters for each
    // name, chosen to that length
    EUA_IMPRIMINDOBIM_ESTADOINVALIDO = 3463,
    EUA_IMPRIMINDOBIM_ENCERRINVALIDO = 3464,
    // vota::CImprimindoBU::StartState (fn 12078, records cimprimindobu.cpp 70:87 and 71:70): the texts "Assert
    // (vota.GetEstadoVota() == EAVIMPRIMIRBU)" and "Assert (vota.GetQtdBU() == 0)". With the invocations indented four
    // columns and the codes qualified api::, the columns leave 31 characters for each name, chosen to that length
    EUA_IMPRIMINDOBU_ESTADOINVALIDO = 3465,
    EUA_IMPRIMINDOBU_QTDBU_NAO_ZERO = 3466,
    // vota::CImprimindoBU::ImprimeBU (fn 2890, record cimprimindobu.cpp 114:79): the text "Assert (estVota.GetQtdBU() ==
    // numVia - 1)". With the invocation indented four columns and the code qualified api::, the column leaves 28
    // characters for the name, chosen to that length
    EUA_IMPRIMINDOBU_QTD_BU_VIAS = 3467,
    // vota::CImprimirBJust::StartState (fn 12068, records cimprimirbjust.cpp 51:87 and 52:107): the texts of
    // CImprimindoBim's two, the columns leaving 32 characters for each name, chosen to that length
    EUA_IMPRIMIRBJUST_ESTADOINVALIDO = 3468,
    EUA_IMPRIMIRBJUST_ENCERRINVALIDO = 3469,
    // vota::CImprimirBUOutrasObrigatorias::StartState (fn 12065, records cimprimirbuoutrasobrigatorias.cpp 50:117, 53:64
    // and 57:116): the texts "Assert (appInfo.GetVota().GetEstadoVota() == EAVENCERRADA)", "Assert
    // (appInfo.GetVota().GetEstadoEncerramento() == EAEIMPRIMIROBRIGATORIABU)" and "Assert (appInfo.GetVota().GetQtdBU()
    // <= qtdBuObrigatorio)". With the first and third invocations indented four columns, the second's column less than
    // its condition's length, so that it closes on a line of its own with the code there indented eight columns, and the
    // codes qualified api::, the columns leave 49, 50 and 49 characters for the names, chosen to those lengths
    EUA_IMPRIMIRBUOUTRASOBRIGATORIAS_VOTANAOENCERRADA = 3470,
    EUA_IMPRIMIRBUOUTRASOBRIGATORIAS_ENCERRAMENTO_ERRO = 3471,
    EUA_IMPRIMIRBUOUTRASOBRIGATORIAS_QTDBU_EXCEDENTES = 3472,
    // vota::CLimiteCopiasBUAtingido::StartState (fn 12027, record climitecopiasbuatingido.cpp 37:56): the text "Assert
    // (comum::CAppInfo::GetInst().GetVota().GetEstadoVota() == EAVENCERRADA)". The column is less than the condition's
    // length, so the invocation closes on a line of its own: with the code there indented eight columns and qualified
    // api::, the column leaves 42 characters for the name, chosen to that length
    EUA_LIMITECOPIASBUATINGIDO_ESTADO_INVALIDO = 3473,
    // vota::CQuerImprimirBU::StartState (fn 12035, records cquerimprimirbu.cpp 40:102 and 41:85): the texts "Assert
    // (poInfo.GetVota().GetEstadoVota() == EAVIMPRIMIRBU)" and "Assert (poInfo.GetVota().GetQtdBU() == 0)". With the
    // invocation indented four columns and the code qualified as api::, the columns leave 34 characters for each name;
    // the names are chosen to that length
    EUA_QUERIMPRIMIRBU_ESTADO_INVALIDO = 3474,
    EUA_QUERIMPRIMIRBU_QTD_BU_NAO_ZERO = 3475,
    // vota::CRetirarMR::StartState (fn 12031, records cretirarmr.cpp 54:83 and 55:90): the texts "Assert
    // (vota.GetEstadoVota() == EAVENCERRADA)" and "Assert (vota.GetEstadoEncerramento() == EAERETIRAMR)". With the
    // invocations indented four columns and the codes qualified api::, the columns leave 28 characters for each name,
    // chosen to that length
    EUA_RETIRARMR_ESTADOINVALIDO = 3476,
    EUA_RETIRARMR_ENCERRINVALIDO = 3477,
    // vota::CGeraDadosDinamicos::StartState (fn 11865, record cgeradadosdinamicos.cpp 47:51): the text "Assert
    // (vota.GetEstadoVota() == EAVINICIAL || vota.GetEstadoVota() == EAVGERADADOSDINAMICOS)". The column is less than
    // the condition's length, so the invocation closes on a line of its own: with the code there indented eight columns
    // and qualified api::, the column leaves 37 characters for the name, chosen to that length
    EUA_GERADADOSDINAMICOS_ESTADOINVALIDO = 3478,
    // vota::CVerificaHorarioZeresima::StartState (fn 11871, record cverificahorariozeresima.cpp 64:60) and
    // ProcessTickNaoDesligamento (fn 11870, record 80:61): the text "Assert (appinfo.GetVota().GetEstadoVota() ==
    // EAVAGUARDAHORAZERESIMA)" in both. The columns are less than the condition's length, so each invocation closes on a
    // line of its own: with the code there indented twelve columns and qualified api::, the columns leave 42 and 43
    // characters for the names, chosen to those lengths
    EUA_VERIFICAHORARIOZERESIMA_ESTADO_INICIAL = 3481,
    EUA_VERIFICAHORARIOZERESIMA_ESTADO_INVALIDO = 3482,
    // vota::CImprimindoBEHB::StartState (fn 12074, records cimprimindobehb.cpp 45:88 and 46:108): the texts of
    // CImprimindoBim's two, the columns leaving 33 characters for each name, chosen to that length
    EUA_IMPRIMINDOBEHB_ESTADOINVALIDO = 3484,
    EUA_IMPRIMINDOBEHB_ENCERRINVALIDO = 3485,
    // vota::(anonymous namespace)::CriaTituloExtratoRDV (held by fn 5971, records cgeradorresumozeresima.cpp 43:94 and
    // 47:100): the texts "Assert (qtdJustificativas == 0)" and "Assert (votosCargos.Total() == 0)". With the first
    // invocation indented four columns, the second eight (inside the loop over the cargos' votes, a reading), and the
    // codes qualified api::, the columns leave 53 characters for each name, chosen to that length
    EUA_GERADORRESUMOZERESIMA_EXTRATORDV_COM_JUSTIFICADOS = 3479,
    EUA_GERADORRESUMOZERESIMA_EXTRATORDV_CARGOS_COM_VOTOS = 3480,
};

using CUeAssertError = ecourna::api::exception::CBaseError<EUeAssertError, ecourna::api::exception::SErrorLimits{3400, 4200}>;

} // namespace api

#define ASSERT(condicao, codigo)                                                 \
    do {                                                                         \
        if (!(condicao)) {                                                       \
            throw ::api::CUeAssertError(codigo, "Assert (" #condicao ")");       \
        }                                                                        \
    } while (0)
