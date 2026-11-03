#pragma once

// Reconstruction's note, not TSE's text: comum::util::CMonitoraAlimentacao, named by the records of
// app/comum/util/cmonitoraalimentacao.cpp at lines 24 (GetInst), 29 (CreateInst) and 52 (VerificaAlimentacao). The object
// is 8 bytes (fn 1898, which holds CreateInst inlined): the argument at +0 and the word 0xFFFFFF at +4, which
// VerificaAlimentacao (inlined into fn 10226) reads and writes as four bytes: +4 the power source last logged, +5 and +6
// the internal and the external battery's status last logged (reset together to 0xFF by a 16-bit store when the source
// changes), +7 a count of the changes logged, compared with 20. The members' names, this header's path and
// ELogAplicativos' using-declaration are chosen, the last because the record prints the type unqualified; that the four
// bytes are uebyte members is a reading of those accesses.

#include <memory>
#include <mutex>

#include "api/uelog/cescritorlog.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::util {

using api::ELogAplicativos;

class CMonitoraAlimentacao {
public:
    static CMonitoraAlimentacao& GetInst();
    static void CreateInst(ELogAplicativos aplicativo);

    void VerificaAlimentacao();

private:
    explicit CMonitoraAlimentacao(ELogAplicativos aplicativo);

    ELogAplicativos m_aplicativo;
    uebyte m_fonte;
    uebyte m_statusBatInt;
    uebyte m_statusBatExt;
    uebyte m_eventos;

    static std::unique_ptr<CMonitoraAlimentacao> s_instancia;
    static std::mutex s_mutex;
};

} // namespace comum::util
