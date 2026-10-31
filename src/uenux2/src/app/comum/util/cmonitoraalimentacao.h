#pragma once

// Reconstruction's note, not TSE's text: comum::util::CMonitoraAlimentacao, named by the records of
// app/comum/util/cmonitoraalimentacao.cpp at lines 24 (GetInst), 29 (CreateInst) and 52 (VerificaAlimentacao). Only
// CreateInst is written. The object is 8 bytes (fn 1898, which holds CreateInst inlined): the argument at +0 and
// 0xFFFFFF at +4. The members' names, this header's path and ELogAplicativos' using-declaration are chosen, the last
// because the record prints the type unqualified.

#include <memory>

#include "api/uelog/cescritorlog.h"

namespace comum::util {

using api::ELogAplicativos;

class CMonitoraAlimentacao {
public:
    static void CreateInst(ELogAplicativos aplicativo);

private:
    explicit CMonitoraAlimentacao(ELogAplicativos aplicativo);

    ELogAplicativos m_aplicativo;
    int m_estado;

    static std::unique_ptr<CMonitoraAlimentacao> s_inst;
};

} // namespace comum::util
