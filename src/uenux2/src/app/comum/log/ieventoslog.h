#pragma once

// comum::IEventosLog: the application's log of events. RTTI gives the class and no base; its vtable (@1552852) holds
// only the two destructors, the shared bodies 174 and 144, and a __shared_ptr_pointer<IEventosLog*, default_delete<...>>
// keeps its instance. vota::CLogVota (RTTI: si_class of this class) is the one derived class; CPolySingleton<IEventosLog>
// (fn 837) holds it.
// - No key function: the typeinfo (@1532816) is the copy of vota::CLogVota's object, just after that class's vtable, and
//   the vtable is the copy of ieventoslog.cpp's object, before its records, emitted by the constructor. The destructor's
//   form is chosen: an empty one gives these shared bodies however it is written.
// - The constructor is defined in ieventoslog.cpp: fn 184 keeps this class's vptr store under CLogVota's, which reads as
//   binaryen's inlining of an out-of-line constructor, since clang drops such a store from one it inlines (a reading:
//   fn 184, in vota/log/clogvota.cpp, matches with it out of line). It has no target function.
// - +4 is the application code: fn 184 stores 1, and fn 233 and every inlined copy pass it as api::CLoga::loga's first
//   argument. The member's name is chosen.
// - loga, 233: no record names it. Its class is read from its callers, which call it on what fn 837 returns (fns 5876,
//   6045) and on fn 184's result; its name and its severity 1 are chosen from CLoga::loga, its one callee.
// - LogaCargaBateria: no record names it. Fn 5875, CLogComum::LogaNivelBateria, holds it after a second stack prologue,
//   so binaryen inlined an out-of-line function; it reads +4 of the instance, so it is a member of this class, and it
//   holds ConverteStatusBateria in its own frame, with the string's length folded into the format argument (clang
//   inlined it, the same TU), so it is in ieventoslog.cpp. ConverteFonteAlim has a prologue of its own there: binaryen's.
// - ConverteStatusBateria is declared `inline`, a choice at this tree's level: unit 111's fragment has the measurement.
// - The three Converte members: the records' text has no `static`, so they are members, with `this` removed by binaryen.
// ERelatoriosUE and its values: the record names the type, unqualified, so the namespace is chosen; the values are the
// cases of fn 5879 and each name is chosen from the text its case returns. The parameter types are the records'.

#include <string>

#include "api/uelog/cescritorlog.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

enum ERelatoriosUE {
    RELATORIO_ZERESIMA = 0,
    RELATORIO_ZERESIMA_APURACAO = 1,
    RELATORIO_ZERESIMA_SECAO = 2,
    RELATORIO_BU = 3,
    RELATORIO_BUJ = 4,
    RELATORIO_RDV = 5,
    RELATORIO_AUTOTESTE = 6,
    RELATORIO_COMPROVANTE_CARGA = 7,
    RELATORIO_HASHES_ARQUIVOS = 8,
    RELATORIO_BIM = 9,
    RELATORIO_ARQUIVOS_ELEITORES_CANDIDATOS = 10,
    RELATORIO_RESUMO_ZERESIMA = 11,
    RELATORIO_ELEITORES_HABILITADOS_BIOGRAFICAMENTE = 12,
};

class IEventosLog {
public:
    explicit IEventosLog(api::ELogAplicativos aplicativo);
    virtual ~IEventosLog() = default;

    void loga(const std::string& mensagem);
    void LogaCargaBateria(uebyte fonte, uebyte status);

    std::string ConverteERelatoriosUE(const ERelatoriosUE relatorio);
    std::string ConverteFonteAlim(const uebyte fonte);
    inline std::string ConverteStatusBateria(const uebyte status);

protected:
    // protected: vota::CLogVota's members that fns 6017, 10776 and 10779 hold inlined read it and call api::CLoga::loga
    // themselves. The access is chosen; that a derived class reads it is the evidence.
    api::ELogAplicativos m_aplicativo;
};

} // namespace comum
