// vota::CEleitorNaoTemIdadeMinima: no record names this file or any of its members; the reconstruction's notes are in
// celeitornaotemidademinima.h and src/units/104-uenux2-app-vota-estados.mk.
#include "app/vota/operador/leidentidade/celeitornaotemidademinima.h"

namespace vota {

CEleitorNaoTemIdadeMinima::~CEleitorNaoTemIdadeMinima() = default;

CEleitorNaoTemIdadeMinima& CEleitorNaoTemIdadeMinima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorNaoTemIdadeMinima());
    }
    return *s_inst;
}

std::unique_ptr<CEleitorNaoTemIdadeMinima> CEleitorNaoTemIdadeMinima::s_inst;
std::mutex CEleitorNaoTemIdadeMinima::s_mutex;

namespace {

std::string TextoImpedido()
{
    return "está impedido de votar ou justificar";
}

std::string TextoSemIdadeMinima()
{
    return "por não ter idade mínima";
}

} // namespace

CEleitorNaoTemIdadeMinima::CEleitorNaoTemIdadeMinima()
    : IEleitorImpedidoVotar(&TextoImpedido, &TextoSemIdadeMinima, 1)
{
}

} // namespace vota
