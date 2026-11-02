// vota::CRelVotaUtil: no record names this file, its path is chosen (src/units/246-uenux2-crelvotautil.mk says why).
// The reconstruction's note, not TSE's text.
#include "app/vota/eleitor/iniciovotacao/crelvotautil.h"

#include "api/gui/cpaperformbuilder.h"
#include "api/gui/csubreport.h"
#include "api/hwil/clp.h"

namespace vota {

void CRelVotaUtil::CortaPapel()
{
    api::CPaperFormBuilder builder;
    builder.AddNewLine(2);
    builder.AddCut();
    api::CLp::GetInst().Imprime(api::CSubReport("", "", false), [&builder] { builder.Build()->Slot2(); });
}

} // namespace vota
