#pragma once

// api::CReport, a report of parts printed in order, and api::CScopedReportFile, which brackets printing it into a file.
// Reconstruction notes, not TSE's text. RTTI names CReport through its member's lambda (`api::(anonymous
// namespace)::DoPrintJob(api::CReport const&, std::string const&, std::string const&)::$_0`, the __func whose vtable is
// @1583752), and the records name CScopedReportFile's constructor and destructor (creport.cpp:31 and :37, @1583720 and
// @1583736, held by fn 3654). No record names this header, so its path is chosen, beside creport.cpp.
//
// Recovered: CReport's layout, a vector of std::shared_ptr<IReportPart> (12 bytes). Fn 2259, the constructor, zeroes the
// object and moves into it the vector it is given. Of its five callers (fns 7787, 11908, 11943, 11946, 12105), 11908,
// the one read, builds that vector from an initializer list of parts (each element copied, its count raised) right
// before the call and destroys it after, so the parameter is a vector by value, and destroys the object inline (the
// vector's elements released, then its storage freed): the destructor is implicit. Fn 11908 prints it through
// DoPrintJob, in a 96-byte frame of its own: read as CReport::Imprime, which binaryen inlines, with DoPrintJob inlined
// into it by clang (only 11908 holds DoPrintJob's lambda, so Imprime has one caller). The lambda (fn 10884) and fn 3654
// call fn 5486, ImprimePartes, on the report, which calls slot 2 (IReportPart::Imprime) of each part in order.
//
// CScopedReportFile (fn 3654 holds both members behind frames of their own, binaryen's inlining): the constructor
// copies the path it is given into its 12-byte member and calls slot 5 of CPolySingleton<IPaperRelatorios>::instance()
// (fn 905; StartReportFile, ipaper.h) with a copy of the path's string; the destructor calls slot 6 (EndReportFile) and
// destroys the member. The destructor's record is at column 9, inside a block: a try with an empty catch (...), a
// choice that no byte shows (uenux2 builds without -fexceptions). Fn 3654, GeraArquivoRelatorio, builds the object from
// the std::string it is given (the path's temporary freed right after the constructor) around ImprimePartes. Its callers
// (fns 11943, 11946, 12105) copy a string right before the call and free the copy after: a const reference bound to a
// path's string(), the form written, or a std::string by value (when 3654 shared creport.cpp's TU, pnpm wasm score
// gave both forms 51 over 184 rows on whole links).
//
// Chosen: the members' names; Imprime's name and parameters (DoPrintJob's are the RTTI's) and ImprimePartes's name;
// that both are members and const (they read the vector only; free functions taking the report give the same code);
// GeraArquivoRelatorio's name, its being a free function of api and its parameters' forms; the member's being a path
// and the copy through string() (a std::string member passed to a by-value parameter is another reading, not built);
// which file holds which function (src/units/317-uenux2-relatorios-aptos.mk has what decided it).

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/reports/ireportpart.h"

namespace api {

class CReport {
public:
    explicit CReport(std::vector<std::shared_ptr<IReportPart>> partes);

    void Imprime(const std::string& titulo, const std::string& via) const;
    void ImprimePartes() const;

private:
    std::vector<std::shared_ptr<IReportPart>> m_partes;
};

class CScopedReportFile {
public:
    explicit CScopedReportFile(const std::filesystem::path& arquivo);
    ~CScopedReportFile();

private:
    std::filesystem::path m_arquivo;
};

void GeraArquivoRelatorio(const std::string& arquivo, const CReport& relatorio);

} // namespace api
