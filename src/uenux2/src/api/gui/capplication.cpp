// Reconstruction's note, not TSE's text: api::CApplication (/home/rubio/tse/uenux2/src/api/gui/capplication.cpp), in
// part. The records fix line 503 (EnterLoopDoingNothing, target fn 5566) and keep 303, 377, 432 and 478 blank
// (QRCodeSRC::build, ShowExceptionMsgScreen, LogExceptionMsg and EnterLoopBeeping's lambda, not written). Every other
// line, the statics' place and the include order are chosen: src/units/171-uenux2-capplication.mk has the rest.
#include "api/gui/capplication.h"

#include "api/gui/iscreen.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"

namespace api {

bool CApplication::s_finalizar = false;
int CApplication::s_codigoRetorno = -1;

// (original lines 16-497: content not recovered)
#line 498
void CApplication::EnterLoopDoingNothing()
{
    if (!s_finalizar) {
        do {
            if (CPolySingletonList::has<IScreen>()) {
                auto& screen = CPolySingleton<IScreen>::instance();
                screen.Slot37();
            }
            CSystem::Dorme(1000);
        } while (!s_finalizar && s_codigoRetorno <= 0);
    }
}

} // namespace api
