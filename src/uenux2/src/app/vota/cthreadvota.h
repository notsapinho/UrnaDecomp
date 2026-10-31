#pragma once

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
