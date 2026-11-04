// Pending members of comum::CGeradorRelVersaoPacoteDados (src/units/287-uenux2-cgeradorrelversaopacotedados.mk). The
// class's vtable needs every slot defined; these bodies are NOT the target's, they trap. Move each into
// src/uenux2/src/app/comum/relatorios/cgeradorrelversaopacotedados.cpp when it is reconstructed, and delete this file
// with the last.
//
// - ImprimeTituloJE (target fn 11223, slot 3, 2163 B): it calls comum::CRelUtil's IncluiCabecalhoEleicoesMZS (fn
//   1543), ImprimeResumoCorrespondencia (1541) and ImprimeSeparadorFase (2785), CPE::CreateInst and Existe (2787,
//   2788), CAppInfo::LeGeralInterno (2273) and fns 1921 and 1922, not written, and builds the std::function of its
//   lambda (vtable @1576316, slots 11221, 11219, 2881, 11218 and 11217, which come with it). The lambda returns
//   comum::SQtdeAptos straight from CEleitores::QuantidadeAptos (2881 passes its result's address through), which
//   celeitores.h declares returning a struct of its own: it waits for that header.
#include "app/comum/relatorios/cgeradorrelversaopacotedados.h"

namespace comum {

void CGeradorRelVersaoPacoteDados::ImprimeTituloJE()
{
    __builtin_trap();
}

} // namespace comum
