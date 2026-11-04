#pragma once

namespace vota {

// The voter's photo on the operator's LCD (comum::CInfoMTLCD): fn 3616 shows it after reading the voter's register, or
// one of two fixed images, and records what was shown through vota::impl::IInformacaoThreadOperador; fn 3617 shows the
// image of a photo that cannot be shown. vota::CNomeEleitor's, IConfirmaJustificativa's and IEleitorImpedidoVotar's
// StartState call 3616 (fns 10501, 10589, 10625), and 3616 alone calls 3617, three times. No record, slot or string
// names them: their names, their being free functions of vota and this header's path are chosen
// (src/units/319-uenux2-app-vota-operador-comum.mk).
void MostraFotoIndisponivel();
void ApresentaFotoEleitor();

} // namespace vota
