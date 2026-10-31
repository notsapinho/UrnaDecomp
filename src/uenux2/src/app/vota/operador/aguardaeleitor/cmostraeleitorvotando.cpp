// vota::CMostraEleitorVotando (/home/rubio/tse/uenux2/src/app/vota/operador/aguardaeleitor/cmostraeleitorvotando.cpp).
// Reconstruction's note, not TSE's text. Its records are records of the target:
//   10426  virtual void ProcessInput()   record at line 64, column 22 (the default argument of CPolySingleton's instance)
//   10425  ProcessKey (slot 6)           records at lines 127 and 159, column 31 (not written)
// The destructor's line is a choice; src/units/142-uenux2-app-vota-estados-448.mk has the other notes.

#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"

#include "api/hwil/iinput.h"
#include "api/pattern/cpolysingleton.h"

namespace vota {

CMostraEleitorVotando::~CMostraEleitorVotando() = default;

// (original lines 16-61: content not recovered)
#line 62
void CMostraEleitorVotando::ProcessInput()
{
    auto& terminal = api::CPolySingleton<api::IInputMT>::instance();
    if (terminal.HasKey()) {
        terminal.GetKey();
    }
}

} // namespace vota
