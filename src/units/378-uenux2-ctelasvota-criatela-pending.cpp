// Pending member of fragment 378's vota::CPreShowProgressBar (app/vota/comum/cpreshowformvota.h), its class's key
// function, so this object emits its vtable and typeinfo; trapped so that the class links. Its body is NOT the
// target's.
// The screens this unit adds to unit 110's ctelasvota.cpp build std::make_shared<CPreShowProgressBar>() and store its
// vptr (@1536552, the vtable @1536544 that ledger/vtables.json gives as [174, 144, 13550]), so the vtable has to link.
// What it waits for:
// - vota::CPreShowProgressBar::PreShow 13550 (slot 2), 2118 B, read from its folded readout: it clears the screen (its
//   slot 4 with 1), calls vota::DesenhaDescricaoModo (fn 4620) at {320, 30}, builds one step per choice of each post of
//   comum::CCargos (the post's GetNomeNeutro, fn 1547, with " - " and GetOrdinalEscolha, fn 2258, when it has two
//   choices or more), counts the steps before the current one (vota::g_escolhaAtual, @1536340), and when there are two
//   steps or more builds an api::CStepsProgressBar in its frame and calls its Draw (fn 5504) and destructor (fn 3665).
//   The bar's constructor is inlined there: its record is cstepsprogressbar.cpp:428 (column 15, 1581916, the throw
//   "Quantidade de segmentos deve ser maior que zero"), and unit 41 has not written it
//   (src/units/41-uenux2-cstepsprogressbar.mk), so this member cannot be written yet (src/units/README.md "Pending
//   members": a callee the tree lacks). It moves into the class's file when it is written; the vtable's place in the
//   target's data, between cpoliticaexecucaoeleitor.cpp's records (@1536400 to @1536543) and ctelascargo.cpp's
//   (@1536576), is read as that file's (a reading: a cpreshowprogressbar.cpp in app/vota/eleitor/comum would sort
//   there).
#include "app/vota/comum/cpreshowformvota.h"

namespace vota {

void CPreShowProgressBar::PreShow(api::IScreen&)
{
    __builtin_trap();
}

} // namespace vota
