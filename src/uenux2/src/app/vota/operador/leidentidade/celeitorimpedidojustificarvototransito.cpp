// vota::CEleitorImpedidoJustificarVotoTransito: no record names this file or any of its members; the reconstruction's
// notes are in celeitorimpedidojustificarvototransito.h and src/units/104-uenux2-app-vota-estados.mk.
#include "app/vota/operador/leidentidade/celeitorimpedidojustificarvototransito.h"

namespace vota {

CEleitorImpedidoJustificarVotoTransito::~CEleitorImpedidoJustificarVotoTransito() = default;

CEleitorImpedidoJustificarVotoTransito& CEleitorImpedidoJustificarVotoTransito::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorImpedidoJustificarVotoTransito());
    }
    return *s_inst;
}

std::unique_ptr<CEleitorImpedidoJustificarVotoTransito> CEleitorImpedidoJustificarVotoTransito::s_inst;
std::mutex CEleitorImpedidoJustificarVotoTransito::s_mutex;

namespace {

std::string TextoImpedidoVotarOuJustificar()
{
    return "está impedido de votar ou justificar.";
}

std::string TextoSolicitouVotoEmTransito()
{
    return "Eleitor solicitou voto em trânsito";
}

} // namespace

CEleitorImpedidoJustificarVotoTransito::CEleitorImpedidoJustificarVotoTransito()
    : IEleitorImpedidoVotar(&TextoImpedidoVotarOuJustificar, &TextoSolicitouVotoEmTransito, 1)
{
}

} // namespace vota
