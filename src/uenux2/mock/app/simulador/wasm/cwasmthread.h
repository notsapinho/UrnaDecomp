#pragma once

#include <vector>

#include "api/ipc/ithreadimpl.h"

namespace simulador {

// what Create queues: the routine and its parameter, a flag Wait polls, and the id its log line prints (a chosen name
// and chosen member names; the bodies show 16 bytes, a 32-bit read of +8 and the id at +12)
struct SContextoThread;

// Recovered: RTTI names the class (an si_class of api::IThreadImpl, vtable @1528392) and a record its Create, at
// mock/app/simulador/wasm/cwasmthread.cpp 31:15. The layout is read from its members: m_contexto at +4, 0 when no
// thread was created. Wait and Yield are named after the text their log lines print; Slot4 is named after its slot (fn
// 1528, one empty body many classes share, so nothing shows its parameters' types but the wasm type). The destructors
// are the shared 174 and 144, so the destructor is implicit or destroys nothing; implicit is chosen.
class CWasmThread : public api::IThreadImpl {
public:
    virtual void Create(void* (*rotina)(void*), void* parametro) override;
    virtual void Wait() override;
    virtual void Slot4(int, int) override {}
    virtual void Yield() override;

private:
    static std::vector<SContextoThread*> s_contextos;
    static int s_proximoId;

    SContextoThread* m_contexto = nullptr;
};

} // namespace simulador
