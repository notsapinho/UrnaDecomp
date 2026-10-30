// Pending members: the simulador::CWasmLogd and api::CEscritorLog virtual members no source holds yet. CWasmLogd's
// vtable (@1530800) is emitted with escreve, its key function (the destructor is implicit), and needs every slot
// defined; CEscritorLog's key function is fazOperacao. Their bodies are NOT the target's, they trap. With the vtable
// this object also emits CWasmLogd's implicit destructors (target fns 8318 and 8316, slots 0 and 1), the compiler's
// code for the class definition in src/uenux2/mock/app/simulador/wasm/cwasmlogd.h; they move with the vtable when
// escreve is written into mock/app/simulador/wasm/cwasmlogd.cpp (beside the constructor). Target functions, by slot
// of CWasmLogd's vtable, and what each waits for:
//   2  10262  api::CEscritorLog::fazOperacao(ELogOperacoesLogD), records cescritorlog.cpp:38:15 and :44:15: two
//             std::format throws of ecourna::api::exception::CBaseError<api::EUeUeLogError, {6950, 7000}> (typeinfo
//             1599588; codes 6951 and 6952) through fn 3601, no-candidate, then slot 4 with the operation and 1
//   3  10260  api::CEscritorLog::loga, the name and parameter types chosen (cescritorlog.h says from what): inlines
//             the file's api::confereAppValida(const std::string &, ELogAplicativos) (record cescritorlog.cpp:28:15,
//             after the line-38 and line-44 records, so internal or inline: docs/reference/facts/reading.md R8), which
//             throws code 6950 the same way, then calls slot 4
//   4  8327   simulador::CWasmLogd::escreve, the name chosen: formats "{}|{}|{}|{}|{}|{}|{}", appends it to m_arquivo
//             (fopen "ab", fwrite, fputc, fflush, fclose) and calls fn 5152 (no-candidate) with 2 and the line; it
//             releases m_mutex through fn 150, which is std::mutex::~mutex in our link and both ~mutex and unlock in
//             the target's (a std::lock_guard needs that merge first)
// The stubs of 10262 and 10260 were the last ones of src/uenux2/src/api/uelog/cescritorlog.cpp, a stub-only file the
// generator removed when their slots joined this vtable: whoever writes fazOperacao and slot 3 writes that file again,
// with the throws on the record lines 28, 38 and 44 (ledger/source-locations.tsv). The constructor (inlined into
// fn 8302, no target function of its own) is not reconstructed either. Move each member into its class's source when
// it is reconstructed; delete this file with the last one.
#include <cstdint>
#include <string>

#include "uenux2/mock/app/simulador/wasm/cwasmlogd.h"

namespace api {

void CEscritorLog::fazOperacao(ELogOperacoesLogD)
{
    __builtin_trap();
}

void CEscritorLog::loga(ELogAplicativos, ESeveridade, const std::string&)
{
    __builtin_trap();
}

} // namespace api

namespace simulador {

void CWasmLogd::escreve(std::uint8_t, api::ESeveridade, const std::string&)
{
    __builtin_trap();
}

} // namespace simulador
