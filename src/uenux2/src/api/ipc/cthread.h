#pragma once

#include <exception>
#include <memory>

namespace ecourna::api::exception {
class CError;
}

namespace api {

class ISyncCtl;
class IThreadImpl;

/**
 * Thread da aplicação: a classe derivada implementa o laço de execução.
 */
class CThread {
public:
    CThread();
    virtual ~CThread();

    void Start();
    // Fn 1900, called by vota::CExecucaoVota's slots 2 and 4 (fns 10236, 10234): when the thread runs (+4 is 1), waits
    // for it through IThreadImpl's slot 3 and marks it created again (0). Out of line: the target keeps the 40-B body
    // as a function with two callers in another TU (that clang would inline it from the class is a reading, not
    // measured). The name is chosen, after the slot it calls.
    void Wait();

    // +8: the Run loops test it (fns 4349, 10204), Start clears it, and fns 10225 and 10203 set it on the other threads.
    // The member's name is chosen.
    void Stop() { m_parar = true; }

protected:
    virtual void Run() = 0;

    // Slots 3 and 4, pure here (vtable @1599952) and overridden by vota::CThreadVota (fns 7710, 7709). The parameters
    // are the overriders': 7710 tests a dynamic_cast from CError and reads +4 and +8, 7709 only calls what(). The name
    // and the overload are chosen, and no caller is left in the target: uenux2 compiles no landing pads.
    virtual void TrataErro(const ecourna::api::exception::CError& erro) = 0;
    virtual void TrataErro(const std::exception& erro) = 0;

private:
    enum EEstado {
        ESTADO_CRIADA = 0,
        ESTADO_EXECUTANDO = 1,
        ESTADO_FINALIZADA = 3,
    };

    static void* Rotina(void* parametro);

    EEstado m_estado;
    bool m_parar;
    bool m_iniciada;
    std::unique_ptr<IThreadImpl> m_pImpl;
    std::unique_ptr<ISyncCtl> m_sync;
};

} // namespace api
