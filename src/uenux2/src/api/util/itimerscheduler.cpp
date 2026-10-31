// Reconstruction's note, not TSE's text. GetInst's record is line 23, column 12. api::CTimerScheduler and api::CTimer are
// here by data order, as api::CSystemDateTime is in isystemdatetime.cpp: their vtables (@1585396, @1585352), typeinfos and
// __shared_ptr_emplace<CTimer>'s lie right before this file's record at 1585468; only fn 5444 stores CTimerScheduler's vptr
// and only fn 10846, its CreateTimer, CTimer's. The classes' headers are a choice; src/units/101-uenux2-api-util-singletons.mk
// says what each member here matches and how the order of the definitions was read.

#include "api/util/ctimer.h"
#include "api/util/ctimerscheduler.h"
#include "api/util/itimerscheduler.h"

namespace api {

// (original lines 13-17: content not recovered)
#line 18
ITimerScheduler& ITimerScheduler::GetInst()
{
    if (!CPolySingletonList::has<ITimerScheduler>()) {
        CreateInst<CTimerScheduler>();
    }
    return CPolySingleton<ITimerScheduler>::instance();
}

CTimer::~CTimer()
{
    Stop();
}

bool CTimer::IsRunning() const
{
    return m_rodando;
}

void CTimer::Start()
{
    Stop();
    m_rodando = true;
    m_thread = std::thread([this] {
        while (m_rodando) {
            std::unique_lock<std::mutex> trava(m_mutex);
            if (!m_condicao.wait_for(trava, m_intervalo, [this] { return !m_rodando; })) {
                m_callback();
            }
        }
    });
}

void CTimer::SetInterval(std::chrono::milliseconds interval)
{
    m_intervalo = interval;
}

void CTimer::Stop()
{
    std::lock_guard<std::mutex> trava(m_mutexThread);
    m_rodando = false;
    m_condicao.notify_one();
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

std::shared_ptr<ITimer> CTimerScheduler::CreateTimer(const std::chrono::milliseconds& interval, std::function<void()> callback)
{
    return std::make_shared<CTimer>(interval, callback);
}

} // namespace api
