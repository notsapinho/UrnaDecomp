#pragma once

// api::CReport, a report of parts printed in order. Reconstruction notes, not TSE's text. RTTI names the class through
// its member's lambda (`api::(anonymous namespace)::DoPrintJob(api::CReport const&, std::string const&, std::string
// const&)::$_0`, the __func whose vtable is @1583752); no record names its header, so this path is chosen, beside
// creport.cpp, whose records (api::CScopedReportFile's, held by fn 3654, @1583720 and @1583736) the data put
// DoPrintJob's lambda's vtable right after (@1583752); that the constructor and ImprimePartes are defined there too is
// a reading.
//
// Recovered: the layout, a vector of std::shared_ptr<IReportPart> (12 bytes). Fn 2259, the constructor, zeroes the
// object and moves into it the vector it is given. Of its five callers (fns 7787, 11908, 11943, 11946, 12105), 11908,
// the one read, builds that vector from an initializer list of parts (each element copied, its count raised) right
// before the call and destroys it after, so the parameter is a vector by value, and destroys the object inline (the
// vector's elements released, then its storage freed): the destructor is implicit. Fn 11908 prints it through
// DoPrintJob, in a 96-byte frame of its own: read as CReport::Imprime, which binaryen inlines, with DoPrintJob inlined
// into it by clang (only 11908 holds DoPrintJob's lambda, so Imprime has one caller). The lambda (fn 10884) calls fn
// 5486 on the captured report, which calls slot 2 (IReportPart::Imprime) of each part in order.
//
// Chosen: the member's name; Imprime's name and parameters (DoPrintJob's are the RTTI's) and ImprimePartes's name;
// that both are members and const (they read the vector only; free functions taking the report give the same code).

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

} // namespace api
