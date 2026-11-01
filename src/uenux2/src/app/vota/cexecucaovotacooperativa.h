#pragma once

#include "app/vota/iexecucaovota.h"

namespace vota {

// vota::CExecucaoVotaCooperativa (RTTI: si_class of vota::IExecucaoVota, typeinfo @1532292; vtable @1532244 [174, 144,
// 4713, 4713, 218, 218, 218, 7823, 4708, 4705]): the other implementation of the interface. Slots 2 and 3 are one body
// (fn 4713): it gives vota::CThreadEleitor's context (+32 of the thread) a new comum::CAppStateContext built over the
// state at +4 (fn 3844, the context's constructor) and starts that context's state; slots 4 to 6 are empty (the shared
// body 218); slot 7 (fn 7823) runs CThreadEleitor's ProcessarEntrada (fn 4349) when the thread has a context and is not
// stopped; slots 8 and 9 are CExecucaoVota's bodies (fns 4708, 4705). Two slots that hold one function are two members:
// which of the two the target's source defines and which calls the other is not in the bytes.
//
// The constructor (fn 7828, out of line) stores its argument at +4 and the vptr, and returns `this`; the target's table
// holds it (slot 126), and no reconstructed code takes its address. +4 as this class's member gives the target's store
// order, the member's before the vptr's (measured: src/units/165-uenux2-app-vota-execucao.mk); as the interface's it was
// not measured. Its type, the state a context starts in, is read from fn 4713, which passes it to fn 3844; the
// member's and the parameter's names are chosen. No record names this class: the path is chosen,
// app/vota/cexecucaovotacooperativa.cpp beside iexecucaovota.cpp; its vtable and typeinfo lie in the data before
// vota::CAssinadorVota's and app/vota/comum/csincronizavota.cpp's, after mock/app/simulador/wasm/'s.
class CExecucaoVotaCooperativa : public IExecucaoVota {
public:
    explicit CExecucaoVotaCooperativa(comum::CAppState* estadoInicial);

    void Executa() override;
    void IniciaThreads() override;
    void AguardaThreads() override;
    void IniciaThreadOperador() override;
    void ParaThreadsOperadorMonitor() override;
    bool ProcessaEntradaEleitor() override;
    api::CPriorityMessageQueue<api::SMessage>& GetFilaEleitor() override;
    comum::CAppState* GetEstadoEleitor() override;

private:
    comum::CAppState* m_estadoInicial;
};

} // namespace vota
