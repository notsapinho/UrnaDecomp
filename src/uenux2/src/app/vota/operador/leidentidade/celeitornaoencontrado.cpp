// vota::CEleitorNaoEncontrado: no record names this file or any of its members; the reconstruction's notes are in
// celeitornaoencontrado.h and src/units/161-uenux2-app-vota-operador-identidade.mk.
#include "app/vota/operador/leidentidade/celeitornaoencontrado.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CEleitorNaoEncontrado::~CEleitorNaoEncontrado() = default;

void CEleitorNaoEncontrado::LogaImpedimento()
{
    CLogVota::GetInst().loga("Eleitor não encontrado para o identificador informado");
}

} // namespace vota
