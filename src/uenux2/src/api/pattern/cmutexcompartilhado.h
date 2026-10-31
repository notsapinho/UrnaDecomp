#pragma once

// api::CMutexCompartilhado and api::CTravaLeitura: the lock of api::TPolySingletonsInfo. No record or RTTI names either
// class: their names, this file, the members' names and that the lock is a class of its own are chosen.
//
// What the bytes give, from fns 512 and 3387 (offsets here; add 16 for the info object's):
//   +0        a std::mutex; +24 and +72 a std::condition_variable each; +120 the readers; +124 the waiting writers; +128 a
//             flag that keeps readers out as the writers do. 132 bytes, so not std::shared_mutex (124, api/gui/iform.h).
// lock_shared takes the mutex in a std::unique_lock, waits on +24 and adds a reader; unlock_shared drops a reader and
// signals +72 when it was the last and a writer waits. A mutex lock leaves no call in this build (reading.md §R15).
//
// lock takes the mutex in a std::unique_lock, counts itself among the waiting writers, waits on +72 and sets the flag.
// unlock clears the flag and signals +72 when a writer waits, else +24. promove trades a reader for the flag.
//
// The target holds unlock_shared's throw inlined in 57 functions, so clang inlines it (how-to step 3). `inline` on
// unlock_shared and on ~CTravaLeitura gives that, and each without it gives a call: the forms are in unit 100's fragment.

#include <condition_variable>
#include <mutex>
#include <stdexcept>

namespace api {

class CMutexCompartilhado {
public:
    void lock_shared()
    {
        std::unique_lock<std::mutex> trava(m_mutex);
        m_leitoresCv.wait(trava, [this] { return !m_escritor && m_escritoresAguardando == 0; });
        ++m_leitores;
    }

    inline void unlock_shared()
    {
        std::lock_guard<std::mutex> trava(m_mutex);
        if (m_leitores <= 0) {
            throw std::runtime_error("unlock_shared() called with no shared owner");
        }
        if (--m_leitores == 0 && m_escritoresAguardando > 0) {
            m_escritoresCv.notify_one();
        }
    }

    void lock()
    {
        std::unique_lock<std::mutex> trava(m_mutex);
        ++m_escritoresAguardando;
        m_escritoresCv.wait(trava, [this] { return !m_escritor && m_leitores == 0; });
        --m_escritoresAguardando;
        m_escritor = true;
    }

    void unlock()
    {
        std::unique_lock<std::mutex> trava(m_mutex);
        if (!m_escritor) {
            throw std::runtime_error("unlock() called when no writer is active");
        }
        m_escritor = false;
        if (m_escritoresAguardando > 0) {
            m_escritoresCv.notify_one();
        } else {
            m_leitoresCv.notify_all();
        }
    }

    void promove()
    {
        std::unique_lock<std::mutex> trava(m_mutex);
        if (m_leitores <= 0) {
            throw std::runtime_error("unlock_shared_and_lock() requires an active shared owner");
        }
        --m_leitores;
        ++m_escritoresAguardando;
        m_escritoresCv.wait(trava, [this] { return !m_escritor && m_leitores == 0; });
        m_escritor = true;
        --m_escritoresAguardando;
    }

private:
    std::mutex m_mutex;
    std::condition_variable m_leitoresCv;
    std::condition_variable m_escritoresCv;
    int m_leitores = 0;
    int m_escritoresAguardando = 0;
    bool m_escritor = false;
};

class CTravaLeitura {
public:
    explicit CTravaLeitura(CMutexCompartilhado& mutex) : m_mutex(mutex) { m_mutex.lock_shared(); }
    inline ~CTravaLeitura()
    {
        if (m_ativa) {
            m_mutex.unlock_shared();
        }
    }

    std::unique_lock<CMutexCompartilhado> promove()
    {
        m_mutex.promove();
        m_ativa = false;
        return std::unique_lock<CMutexCompartilhado>(m_mutex, std::adopt_lock);
    }

private:
    CMutexCompartilhado& m_mutex;
    bool m_ativa = true;
};

} // namespace api
