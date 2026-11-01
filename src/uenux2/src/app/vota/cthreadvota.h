#pragma once

#include <chrono>
#include <cstddef>
#include <exception>
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
