#pragma once

#include <chrono>
#include <cstddef>
#include <exception>
#include <map>
#include <memory>

#include "api/ipc/cthread.h"
#include "api/util/ctickmanager.h"
#include "app/comum/cappstatecontext.h"

namespace vota {

/**
 * Base das threads da votação (eleitor, operador, monitor): cada uma tem os seus ticks.
 */
class CThreadVota : public api::CThread {
public:
    uebyte AddTick(size_t milissegundos);
    // Fn 4640: the target's callers (fns 1285 and 5979) store the i64 1000 in their frame and pass its address, and
    // the body reads its low word as CTickManager::AddTick's size_t. So the parameter is a reference to a 64-bit
    // count of milliseconds; std::chrono::milliseconds is chosen, the type records of this tree spell for an interval
    // (`const std::chrono::milliseconds &`, api::CTextFieldUpdate's constructor). No record names the member: the name
    // is AddTick's, a choice.
    uebyte AddTick(const std::chrono::milliseconds& tempo);
    // Fn 807: CTickManager::AddStoppedTick of m_ticks (fn 5452), named with it.
    uebyte AddStoppedTick(size_t milissegundos);
    // No target function of its own: vota::CVerificaHorarioZeresima's constructor (inlined into fn 5947) stores the i64
    // 2000 in its frame and passes the low word of that slot to CTickManager::AddStoppedTick (fn 5452) on this thread's
    // +20, a value read back from the frame (docs/reference/facts/reading.md R10). This overload, out of line here and
    // inlined by binaryen into its one caller, gives that: fn 5947 matches with it. The overload, its parameter's type
    // and its name are chosen after AddTick's.
    uebyte AddStoppedTick(const std::chrono::milliseconds& tempo);
    void StopTick(uebyte id);
    void StartTick(uebyte id);
    // The state of this thread's ticks (api::CTickManager::GetEstadoTicks), inlined into target fn 10409. The accessor,
    // its name and its being defined in the class are chosen.
    std::map<uebyte, api::CTickManager::EEstadoTick> GetEstadoTicks() const { return m_ticks.GetEstadoTicks(); }

    // The state of the context at +32, or null when there is no context; and a new context over a state, whose state is
    // then started. vota::CExecucaoVota's slot 9 and vota::CExecucaoVotaCooperativa's slots 2, 3 and 9 (fns 4705, 4713)
    // hold this code on vota::CThreadEleitor with the signs of a function binaryen inlined (an if with a result where
    // clang's own code returns twice; the state read before the context is allocated);
    // src/units/165-uenux2-app-vota-execucao.mk has the measurement. That they are this class's members, out of line in
    // cthreadvota.cpp, and their names are chosen.
    comum::CAppState* GetEstado() const;
    void IniciaContexto(comum::CAppState* estado);

protected:
    void TrataErro(const ecourna::api::exception::CError& erro) override;
    void TrataErro(const std::exception& erro) override;

    // Slot 5, pure here (vtable @1532452). Its overriders stop the other threads: fns 10225 and 10203 set the flag of
    // the two others, and 7030 calls slot 6 of vota::IExecucaoVota. The name is chosen from that.
    virtual void ParaOutrasThreads() = 0;

private:
    api::CTickManager m_ticks;
    std::unique_ptr<comum::CAppStateContext> m_contexto;
};

} // namespace vota
