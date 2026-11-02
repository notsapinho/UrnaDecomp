// Reconstruction's note, not TSE's text: vota::CVotosEleitor's constructor and Adiciona, out of line in a file of their
// own (src/units/197-uenux2-celeitorvotando.mk says what that rests on; the class, its file and its members' names are
// chosen).
#include <utility>

#include "app/vota/eleitor/comum/cinformacaoeleitor.h"

namespace vota {

CVotosEleitor::CVotosEleitor() = default;

void CVotosEleitor::Adiciona(const comum::md::TCargoID cargo, comum::md::CVoto voto)
{
    m_votos.push_back(std::make_pair(cargo, std::move(voto)));
}

} // namespace vota
