#pragma once

// Reconstruction's note, not TSE's text: vota::CThreadMonitor, named by RTTI (typeinfo @1600968) and its records in
// app/vota/monitor/cthreadmonitor.cpp. Its members' names, GetInst's and this header's path are chosen, and
// src/units/116-uenux2-cthreads.mk says from what.

#include <ctime>
#include <memory>
#include <mutex>

#include "app/vota/cthreadvota.h"

namespace vota {

class CThreadMonitor final : public CThreadVota {
public:
    static CThreadMonitor& GetInst();

    ~CThreadMonitor() override;

protected:
    void Run() override;
    void ParaOutrasThreads() override;

private:
    CThreadMonitor();

    bool m_fonePlugado;
    time_t m_ultimoLog;

    static std::unique_ptr<CThreadMonitor> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
