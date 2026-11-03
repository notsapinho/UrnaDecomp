// vota::CEleitorNaoPossuiCargosParaVotar: no record names this file or any of its members; the reconstruction's notes
// are in celeitornaopossuicargosparavotar.h and src/units/104-uenux2-app-vota-estados.mk.
#include "app/vota/operador/leidentidade/celeitornaopossuicargosparavotar.h"

namespace vota {

CEleitorNaoPossuiCargosParaVotar::~CEleitorNaoPossuiCargosParaVotar() = default;

CEleitorNaoPossuiCargosParaVotar& CEleitorNaoPossuiCargosParaVotar::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorNaoPossuiCargosParaVotar());
    }
    return *s_inst;
}

std::unique_ptr<CEleitorNaoPossuiCargosParaVotar> CEleitorNaoPossuiCargosParaVotar::s_inst;
std::mutex CEleitorNaoPossuiCargosParaVotar::s_mutex;

namespace {

std::string TextoNaoApto()
{
    return "não está apto a votar nesta eleição.";
}

std::string TextoVazio()
{
    return " ";
}

} // namespace

CEleitorNaoPossuiCargosParaVotar::CEleitorNaoPossuiCargosParaVotar()
    : IEleitorImpedidoVotar(&TextoNaoApto, &TextoVazio, 1)
{
}

} // namespace vota
