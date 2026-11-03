// vota::CEleitorImpedidoJustificar: no record names this file or any of its members; the reconstruction's notes are in
// celeitorimpedidojustificar.h and src/units/104-uenux2-app-vota-estados.mk.
#include "app/vota/operador/leidentidade/celeitorimpedidojustificar.h"

namespace vota {

CEleitorImpedidoJustificar::~CEleitorImpedidoJustificar() = default;

CEleitorImpedidoJustificar& CEleitorImpedidoJustificar::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorImpedidoJustificar());
    }
    return *s_inst;
}

std::unique_ptr<CEleitorImpedidoJustificar> CEleitorImpedidoJustificar::s_inst;
std::mutex CEleitorImpedidoJustificar::s_mutex;

namespace {

std::string TextoImpedidoVotarOuJustificar()
{
    return "está impedido de votar ou justificar.";
}

std::string TextoProcurarCartorio()
{
    return "Eleitor deve procurar cartório eleitoral";
}

} // namespace

CEleitorImpedidoJustificar::CEleitorImpedidoJustificar()
    : IEleitorImpedidoVotar(&TextoImpedidoVotarOuJustificar, &TextoProcurarCartorio, 1)
{
}

} // namespace vota
