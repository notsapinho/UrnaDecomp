// Reconstruction's note, not TSE's text: the file's one record, line 181, is vota::CInformacaoEleitor::CarregarDadosEstaticos(),
// which fn 7787 holds inlined and which is not written. The four objects below (the three in .bss in the target's
// .bss order) and AdicionaVoto sit at chosen lines (src/units/197-uenux2-celeitorvotando.mk).
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"

namespace vota {

std::string g_numeroDigitado;

comum::md::CCedula g_votosEleitor;

void AdicionaVoto(const comum::md::TCargoID cargo, const comum::md::CVoto& voto)
{
    g_votosEleitor.Adiciona(cargo, voto);
}

api::CDateTime g_dataHoraDesligamento;

comum::md::TQtdEscolha g_escolhaAtual = 1;

} // namespace vota
