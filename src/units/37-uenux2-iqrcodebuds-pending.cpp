// Pending of unit 37: the slot of vota::CMostraQRCodeBU not reconstructed, with a trapping body so that its vtable
// links.
// - StartState (slot 2, target fn 12055, record cmostraqrcodebu.cpp:70, the default source_location of
//   CPolySingleton<comum::IInterfaceInit>::instance()). It is not written: after the demo-mode test and IQRCodeBUDS's
//   index reset it gets CTelasVota::GetInst() (fn 407) and builds the screen in a 208-byte frame of a function binaryen
//   inlined (an api::CInteractiveFormBuilder: AddStatusHeader, fn 502; a CQRCodeImage, fn 3662, over a std::function of
//   fn 12053; a CTextFieldMultiLine, fn 5498, over fn 12054; CTextFields named "Confirma", "AcaoConfirma", "Acao3",
//   "3", "Acao9", "9" and "Pagina", the last over fn 12052; AddLabeledKey, fn 2243; GetFormularioInterativo, fn 576,
//   "telaQRCodeBU"), with coordinates from the 8-byte object at @1577200. The three text functions (fns 12052 to 12054,
//   table slots 1507 to 1505, `std::string (*)()`) are not written either; they call GetQRDSInst (fn 1956). StartState
//   then calls AjustaTela (fn 5982), which 37-uenux2-iqrcodebuds-roots.cpp stands for meanwhile.
#include "app/vota/eleitor/fimvotacao/cmostraqrcodebu.h"

namespace vota {

void CMostraQRCodeBU::StartState()
{
    __builtin_trap();
}

} // namespace vota
