#pragma once

#include <cstdint>
#include <filesystem>
#include <mutex>
#include <string>

#include "api/uelog/cescritorlog.h"

namespace simulador {

// Recovered: RTTI names the class, an si_class of api::CEscritorLog (vtable @1530800, typeinfo 1530828). The layout is
// read from fn 8302, into which binaryen inlined the constructor (its own frame sits inside 8302): operator new(40),
// a std::mutex at +4 (24 zero bytes) and the file's path at +28, moved from the constructor's by-value argument (the
// caller copies its path into a temporary, the constructor nulls it). The constructor then creates the path's parent
// directory (std::filesystem::path::__parent_path, fn 1840, called on +28 itself, so the member is a
// std::filesystem::path), opens the file with "wb" and closes it; the writer (slot 4, fn 8327) opens it with "ab", writes a line and releases the mutex at +4.
// The destructors store no vptr, so the class is final. The destructor is implicit: the deleting destructor (fn 8316)
// holds the base-object one's body (fn 8318), so it is not defined out of line, and the class needs no destructor of
// its own for a mutex and a string (one defined in the class with `= default` gives the same bytes). The member and
// parameter names are chosen: no record, symbol or string names them. The writer and the constructor are in
// cwasmlogd.cpp (the constructor's notes are in unit 188's fragment).
class CWasmLogd final : public api::CEscritorLog {
public:
    CWasmLogd(std::filesystem::path arquivo);

    virtual void escreve(std::uint8_t codigo, api::ESeveridade severidade, const std::string& mensagem) override;

private:
    std::mutex m_mutex;
    std::filesystem::path m_arquivo;
};

} // namespace simulador
