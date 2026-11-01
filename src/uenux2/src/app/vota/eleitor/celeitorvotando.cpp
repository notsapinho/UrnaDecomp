// Reconstruction's note, not TSE's text: vota::CEleitorVotando's ChamaEstadoProximoCargo (fn 4459, record :229),
// ProcessTick and ProcessInput (fns 7349 and 7345, no record) are written; lines 125, 131, 253, 254, 294, 410 and 427 are
// records of members not written. The lines the three take are a choice (src/units/197-uenux2-celeitorvotando.mk).
#include "app/vota/eleitor/celeitorvotando.h"

#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/cconfirmavotosemcandidato.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/votamajoritario/cpedemajoritario.h"
#include "app/vota/eleitor/votaproporcional/cpedeproporcional.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

// <stubs>
// f5500 · 6871 B · unmatched · placement: link order · name unknown
// void f5500(i32, i32) { ... }
// </stubs>

// (original lines 24-212: content not recovered)
#line 213
void CEleitorVotando::ChamaEstadoProximoCargo()
{
    const auto& cargos = comum::CCargos::GetInst();
    const auto& candidaturas = comum::CCandidaturas::GetInst();
    const auto& cargo = cargos.GetCurrent();
    const auto candidatos = candidaturas.GetCandidatos(cargo.GetID());
    comum::CAppState* proximo;
    if (candidatos.size() == 0 && !cargo.IsConsulta()) {
        proximo = &CConfirmaVotoSemCandidato::GetInst();
    } else {
        if (cargo.IsMajoritario() || cargo.IsConsulta()) {
            proximo = &CPedeMajoritario::GetInst();
        } else if (cargo.IsProporcional()) {
            proximo = &CPedeProporcional::GetInst();
        } else {
            CLogVota::GetInst().LogaErroIdentificacaoTipoCargo();
            throw CUeVotaError(EUE_VOTA_TIPO_CARGO_NAO_IDENTIFICADO, "Tipo de cargo nao identificado");
        }
    }
    if (m_pEstado != nullptr) {
        m_pEstado->FinishState();
    }
    m_pEstado = proximo;
    SetNumeroDigitado("");
    if (m_pEstado != nullptr) {
        m_pEstado->StartState();
    }
}

// (original lines 242-249: content not recovered)
#line 250
// <stubs>
// f4449 · 352 B · unmatched · name unknown
// void f4449(i32) { ... }
// </stubs>

// (original lines 255-299: content not recovered)
#line 300
void CEleitorVotando::ProcessTick(uebyte tick)
{
    if (tick == m_tick) {
        CThreadEleitor::GetInst().StopTick(m_tick);
        if (comum::CCargos::GetInst().IsPrimeiro() && g_escolhaAtual == 1) {
            CThreadOperador::GetInst().GetMensagens().Post(3);
        } else {
            CThreadOperador::GetInst().GetMensagens().Post(4);
        }
        m_emSuspensao = true;
    } else if (m_pEstado != nullptr) {
        m_pEstado->ProcessTick(tick);
    }
}

void CEleitorVotando::ProcessInput()
{
    auto& thread = CThreadEleitor::GetInst();
    thread.StopTick(m_tick);
    thread.StartTick(m_tick);
    if (m_emSuspensao) {
        CThreadOperador::GetInst().GetMensagens().Post(5);
        CLogVota::GetInst().LogaEleitorVoltouADigitar();
        m_emSuspensao = false;
    }
    if (m_pEstado != nullptr) {
        m_pEstado->ProcessInput();
    }
}

} // namespace vota

// <stubs>
// f4442 · 1183 B · unmatched · name unknown
// void f4442(i32, i32) { ... }

// f3229 · 586 B · unmatched · placement: link order · name unknown
// ? f3229() { ... }
// </stubs>
