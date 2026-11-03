// vota::CEleitorOptouPorVotarEmTransito: no record names this file or any of its members; the reconstruction's notes
// are in celeitoroptouporvotaremtransito.h and src/units/104-uenux2-app-vota-estados.mk.
#include "app/vota/operador/leidentidade/celeitoroptouporvotaremtransito.h"

namespace vota {

CEleitorOptouPorVotarEmTransito::~CEleitorOptouPorVotarEmTransito() = default;

CEleitorOptouPorVotarEmTransito& CEleitorOptouPorVotarEmTransito::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorOptouPorVotarEmTransito());
    }
    return *s_inst;
}

std::unique_ptr<CEleitorOptouPorVotarEmTransito> CEleitorOptouPorVotarEmTransito::s_inst;
std::mutex CEleitorOptouPorVotarEmTransito::s_mutex;

namespace {

std::string TextoOptouPorVotarEmTransito()
{
    return "Optou por votar em trânsito";
}

std::string TextoVazio()
{
    return " ";
}

} // namespace

CEleitorOptouPorVotarEmTransito::CEleitorOptouPorVotarEmTransito()
    : IEleitorImpedidoVotar(&TextoOptouPorVotarEmTransito, &TextoVazio, 0)
{
}

} // namespace vota
