// vota::CEscolheOpcao (/home/rubio/tse/uenux2/src/app/vota/operador/outrasopcoes/cescolheopcao.cpp). This comment is
// the reconstruction's. The file's records are StartState's (fn 10690, not reconstructed), lines 150 to 152; they stay
// blank. Written here: the destructor (fns 2752 and 10691), whose line is a choice before the records, in its use band's
// order, and COpcaoDS's call operator, which has no record and no target function of its own: binaryen inlined it into
// fn 10685, CDataText<COpcaoDS>::GetText. Its line is a choice, after the records.
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

#include <format>
#include <syslog.h>

#include "api/gui/cinteractiveform.h"
#include "api/gui/iscreenmt.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"

namespace vota {

// (original lines 18-139: content not recovered)
#line 140
CEscolheOpcao::~CEscolheOpcao() = default;

// (original lines 142-145: content not recovered)
#line 146
void CEscolheOpcao::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    syslog(LOG_INFO, "%s:%d> %d", __func__, __LINE__, api::CPolySingleton<api::IUrna>::instance().Modelo() >= 2020);
    if (api::CPolySingleton<api::IUrna>::instance().Modelo() >= 2020) {
        api::CPolySingleton<api::IScreenMT>::instance().Slot19(1);
    }
}





std::string CEscolheOpcao::COpcaoDS::operator()() const
{
    return std::format("{}-{}", m_numero, m_texto());
}

} // namespace vota
