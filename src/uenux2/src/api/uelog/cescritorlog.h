#pragma once

#include <cstdint>
#include <string>

namespace api {

// Recovered: the records of src/api/uelog/cescritorlog.cpp name ELogOperacoesLogD (fazOperacao's parameter), and
// api::CLoga::loga's (cloga.cpp:26) ELogAplicativos and ESeveridade. The records print them unqualified, so their
// namespace (api, the class's) and this header are chosen. No evidence names an enumerator, so none is recovered;
// the bodies show the values they accept: an application code below 61 (fn 10260 throws "{} - O codigo da
// aplicacao deve ser menor que {} [{}]" with 61 for a code from 61 up) and an operation from 230 to 240 (fn 10262
// throws below 230 and above 240).
enum ELogAplicativos {};
enum ESeveridade {};
enum ELogOperacoesLogD {};

// Recovered: RTTI names api::CEscritorLog (typeinfo 1599616, among the records of cescritorlog.cpp), a polymorphic
// class with no base, and its one implementer, simulador::CWasmLogd (vtable @1530800). The target has no vtable of
// CEscritorLog's own (ledger/vtables.json lists none): CWasmLogd's constructor, inlined into fn 8302, stores only
// CWasmLogd's vptr. Its slots are CWasmLogd's: the destructor's two, fazOperacao (slot 2, fn 10262, records
// cescritorlog.cpp:38/44), the application's log call (slot 3, fn 10260) and the writer both of them call through the
// vtable (slot 4), which CWasmLogd overrides (fn 8327). The class has no data member (CWasmLogd's first one is at +4)
// and its destructor has an empty body: CWasmLogd's destructors store no vptr, not even this class's, which clang
// leaves out only for such a destructor. Slot 3 checks its first argument with api::confereAppValida (record
// cescritorlog.cpp:28, inlined), passing it "loga", and api::CLoga::loga (fn 433) calls it with its own three
// arguments: hence its name and parameter types. Slot 4 takes the code as a byte (slot 3 passes it masked with 255),
// the severity and the text; fazOperacao passes it the operation and 1. The name of slot 4, its parameter types other
// than the severity, that it is pure, and every parameter name are chosen: no record, symbol or string names them.
class CEscritorLog {
public:
    virtual ~CEscritorLog() = default;

    virtual void fazOperacao(ELogOperacoesLogD operacao);
    virtual void loga(ELogAplicativos aplicativo, ESeveridade severidade, const std::string& mensagem);
    virtual void escreve(std::uint8_t codigo, ESeveridade severidade, const std::string& mensagem) = 0;
};

} // namespace api
