#pragma once

#include "api/ipc/cmessagequeue.h"

namespace comum {
class CAppState;
}

// vota::IExecucaoVota and vota::CExecucaoVota. RTTI names both (typeinfos @1600564 and @1600620; CExecucaoVota is an
// si_class of IExecucaoVota) and the path follows iexecucaovota.cpp, whose record at line 74 is GetInst's (fn 3594,
// not reconstructed), and whose data holds IExecucaoVota's typeinfo and CExecucaoVota's vtable @1600572 right after
// that record. vota::CExecucaoVotaCooperativa is the other class of the interface (vtable @1532244): it shares slots 8
// and 9 with CExecucaoVota (fns 4708 and 4705, one body each).
//
// The slots. 0 and 1 are the destructors: the control block's __on_zero_shared calls the deleting destructor at vtable
// + 4 (fn 172), and CExecucaoVota's are the shared bodies 174 and 144, a destructor that destroys nothing. 2 to 9 are
// what CExecucaoVota's bodies show: 2 starts the three threads, sleeps and waits for them (fn 10236); 3 starts them
// and sleeps (10235); 4 waits for them (10234); 5 starts the operador's thread (10233); 6 sets the operador's and the
// monitor's stop flag (10232; vota::CThreadEleitor::ParaOutrasThreads, fn 7030, calls this slot); 7 returns false here
// (the shared body 340) and runs the eleitor's ProcessarEntrada in the cooperative class (fn 7823); 8 the eleitor's
// message queue, +36 of the thread (4708); 9 the state the eleitor's context holds, or null (4705). No record or
// caller names a slot: every name and the parameter-free signatures are chosen, the result types from what each body
// returns (a reference to the queue at +36, a pointer that can be null). That the slots are pure here is chosen too:
// the interface has no vtable in the target (src/units/165-uenux2-app-vota-execucao.mk says how that was searched), and
// both derived classes fill every slot.
//
// CExecucaoVota adds no data member: GetInst (fn 3594) allocates 4 bytes for it and stores only the vptr. Its members
// are out of line in iexecucaovota.cpp (src/units/165-uenux2-app-vota-execucao.mk).

namespace vota {

class IExecucaoVota {
public:
    virtual ~IExecucaoVota() = default;

    static IExecucaoVota& GetInst();

    virtual void Executa() = 0;
    virtual void IniciaThreads() = 0;
    virtual void AguardaThreads() = 0;
    virtual void IniciaThreadOperador() = 0;
    virtual void ParaThreadsOperadorMonitor() = 0;
    virtual bool ProcessaEntradaEleitor() = 0;
    virtual api::CPriorityMessageQueue<api::SMessage>& GetFilaEleitor() = 0;
    virtual comum::CAppState* GetEstadoEleitor() = 0;
};

class CExecucaoVota : public IExecucaoVota {
public:
    void Executa() override;
    void IniciaThreads() override;
    void AguardaThreads() override;
    void IniciaThreadOperador() override;
    void ParaThreadsOperadorMonitor() override;
    bool ProcessaEntradaEleitor() override;
    api::CPriorityMessageQueue<api::SMessage>& GetFilaEleitor() override;
    comum::CAppState* GetEstadoEleitor() override;
};

} // namespace vota
