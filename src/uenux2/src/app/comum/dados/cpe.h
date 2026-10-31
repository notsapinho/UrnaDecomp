#pragma once

#include <memory>
#include <mutex>
#include <string>

#include "app/comum/dados/md/processoeleitoral/cprocessoeleitoral.h"

namespace comum {

// Recovered: the layout, 204 bytes: CreateInst (fn 2787) allocates 204, copies a CProcessoEleitoral to +0, stores a word
// at +176 and fills +180 through fn 5726; the destructor (fn 5598) frees a string at +188 and calls fn 2830 on +0. The
// bytes at +180 and +200 have no reader here. The members' names and those bytes' types are chosen.
class CPE {
public:
    ~CPE();

    static CPE& GetInst();

private:
    md::CProcessoEleitoral m_processo;
    int m_origem;
    unsigned m_naoRecuperado1[2];
    std::string m_nome;
    unsigned m_naoRecuperado2;

    static std::mutex s_mutex;
    static std::unique_ptr<CPE> s_instancia;
};

} // namespace comum
