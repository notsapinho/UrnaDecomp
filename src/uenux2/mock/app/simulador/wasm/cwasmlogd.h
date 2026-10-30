#pragma once

#include <cstdint>
#include <mutex>
#include <string>

#include "api/uelog/cescritorlog.h"

namespace simulador {

// Recovered: RTTI names the class, an si_class of api::CEscritorLog (vtable @1530800, typeinfo 1530828). The layout is
// read from fn 8302, into which binaryen inlined the constructor (its own frame sits inside 8302): operator new(40),
// a std::mutex at +4 (24 zero bytes) and a std::string at +28, moved from the constructor's by-value argument (the
// caller copies its string into a temporary, the constructor nulls it). The constructor then opens that file with
// "wb" and closes it; the writer (slot 4, fn 8327) opens it with "ab", writes a line and releases the mutex at +4.
// The destructors store no vptr, so the class is final. The destructor is implicit: the deleting destructor (fn 8316)
// holds the base-object one's body (fn 8318), so it is not defined out of line, and the class needs no destructor of
// its own for a mutex and a string (one defined in the class with `= default` gives the same bytes). The member and
// parameter names are chosen: no record, symbol or string names them. Neither the constructor nor the writer is
// reconstructed (src/units/62-uenux2-cwasmlogd-pending.cpp).
class CWasmLogd final : public api::CEscritorLog {
public:
    CWasmLogd(std::string arquivo);

    virtual void escreve(std::uint8_t codigo, api::ESeveridade severidade, const std::string& mensagem) override;

private:
    std::mutex m_mutex;
    std::string m_arquivo;
};

} // namespace simulador
