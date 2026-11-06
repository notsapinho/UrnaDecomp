// Reconstruction's note, not TSE's text: vota::impl::ISincronismoVotoEleitor's destructor, its key function, GetInst,
// whose one record is line 67, column 98, the closing parenthesis of POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO's
// invocation (api/pattern/polysingletongetinst.h), and CSincronismoVotoEleitor::Sincroniza (fn 7174). Every line but
// 67 is chosen; src/units/241-uenux2-app-vota-eleitor.mk says what the target shows.
#include "app/vota/eleitor/csincronismovotoeleitor.h"

#include "api/pattern/polysingletongetinst.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/log/clogvota.h"

namespace vota::impl {

// (original lines 14-64: content not recovered)
#line 65
ISincronismoVotoEleitor::~ISincronismoVotoEleitor() = default;

POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(ISincronismoVotoEleitor, CSincronismoVotoEleitor)

bool CSincronismoVotoEleitor::Sincroniza()
{
    CTelasVota::GetInst().IncrementaBarraSincronismo();
    CSincronizaVota::SincronizaVotoMI();
    CTelasVota::GetInst().IncrementaBarraSincronismo();
    CLogVota::GetInst().LogaVotoComputado();
    CTelasVota::GetInst().IncrementaBarraSincronismo();
    CSincronizaVota::SincronizaVotoMV();
    CTelasVota::GetInst().IncrementaBarraSincronismo();
    return true;
}

} // namespace vota::impl
