// Reconstruction's note, not TSE's text: vota::impl::ISincronismoVotoEleitor's destructor, its key function, and
// GetInst, whose one record is line 67, column 98, the closing parenthesis of
// POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO's invocation (api/pattern/polysingletongetinst.h). The destructor's
// line is chosen; src/units/241-uenux2-app-vota-eleitor.mk says what the target shows.
#include "app/vota/eleitor/csincronismovotoeleitor.h"

#include "api/pattern/polysingletongetinst.h"

namespace vota::impl {

// (original lines 11-64: content not recovered)
#line 65
ISincronismoVotoEleitor::~ISincronismoVotoEleitor() = default;

POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(ISincronismoVotoEleitor, CSincronismoVotoEleitor)

} // namespace vota::impl
