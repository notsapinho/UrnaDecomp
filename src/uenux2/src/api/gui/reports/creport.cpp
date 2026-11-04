// api::CReport's members (target fns 2259 and 5486) and DoPrintJob, which fn 11908 holds inlined through
// CReport::Imprime. The reconstruction's note, not TSE's text: the file's records are api::CScopedReportFile's
// (lines 31 and 37, held by fn 3654, not written), whose lines stay blank; the lines of the code below them are a
// choice. creport.h and src/units/317-uenux2-relatorios-aptos.mk say what is evidence and what is chosen.
#include "api/gui/reports/creport.h"

#include <functional>
#include <utility>

#include "api/gui/csubreport.h"
#include "api/hwil/clp.h"

namespace api {

// (original lines 15-27: content not recovered)
#line 28
// <stubs>
// f3654 · 393 B · unmatched · name unknown
// void f3654(i32, i32) { ... }
// </stubs>








namespace {

void DoPrintJob(const CReport& relatorio, const std::string& titulo, const std::string& via)
{
    const CSubReport subRelatorio(titulo, via, true);
    CLp::GetInst().Imprime(subRelatorio, [&relatorio] { relatorio.ImprimePartes(); });
}

} // namespace

CReport::CReport(std::vector<std::shared_ptr<IReportPart>> partes)
    : m_partes(std::move(partes))
{
}

void CReport::Imprime(const std::string& titulo, const std::string& via) const
{
    DoPrintJob(*this, titulo, via);
}

void CReport::ImprimePartes() const
{
    for (const std::shared_ptr<IReportPart>& parte : m_partes) {
        parte->Imprime();
    }
}

} // namespace api
