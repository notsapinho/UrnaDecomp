#pragma once

namespace api {

/**
 * Implementação da thread na plataforma (simulador::CWasmThread no wasm), criada pela IGenericFactory<IThreadImpl>.
 */
// Recovered: the destructor, Create (slot 2, simulador::CWasmThread::Create's record) and the three other slots
// CWasmThread fills (mock/app/simulador/wasm/cwasmthread.h says how each is named). The file's path, the parameter
// names, the types of Slot4's and every member but Create's name, and the four being pure are not in the target.
class IThreadImpl {
public:
    virtual ~IThreadImpl() = default;

    virtual void Create(void* (*rotina)(void*), void* parametro) = 0;
    virtual void Wait() = 0;
    virtual void Slot4(int, int) = 0;
    virtual void Yield() = 0;
};

} // namespace api
