// api::CScopedReportFile's constructor and destructor (the records at lines 31 and 37, held by target fn 3654) and
// api::CReport's constructor and ImprimePartes (fns 2259 and 5486). The reconstruction's note, not TSE's text: the lines
// of the code below the records are a choice; creport.h and src/units/317-uenux2-relatorios-aptos.mk say what is
// evidence and what is chosen.
#include "api/gui/reports/creport.h"

#include <utility>

#include "api/gui/ipaperrelatorios.h"
#include "api/pattern/cpolysingleton.h"

namespace api {

// (original lines 14-27: content not recovered)
#line 28
CScopedReportFile::CScopedReportFile(const std::filesystem::path& arquivo)
    : m_arquivo(arquivo)
{
    CPolySingleton<IPaperRelatorios>::instance().StartReportFile(m_arquivo.string());
}

CScopedReportFile::~CScopedReportFile()
{
    try {
        CPolySingleton<IPaperRelatorios>::instance().EndReportFile();
    } catch (...) {
    }
}

CReport::CReport(std::vector<std::shared_ptr<IReportPart>> partes)
    : m_partes(std::move(partes))
{
}

void CReport::ImprimePartes() const
{
    for (const std::shared_ptr<IReportPart>& parte : m_partes) {
        parte->Imprime();
    }
}

} // namespace api
