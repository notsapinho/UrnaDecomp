#include "app/vota/eleitor/cconfirmavotoemcargo.h"

namespace vota {

CConfirmaVotoEmCargo::CConfirmaVotoEmCargo(int eventos, uebyte tela, int tipoVoto)
    : CVotacaoStateAudio(eventos), m_tela(tela), m_tipoVoto(tipoVoto)
{
}

} // namespace vota

// <stubs>
// f5928 · 20 B · unmatched · name unknown
// void f5928(i32, i32, i32) { ... }
// </stubs>
