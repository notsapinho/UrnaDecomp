#pragma once

#include <set>
#include <string>

#include "app/comum/gravadores/md/cdependenciascontratos.h"
#include "app/comum/gravadores/md/cversoescontratos.h"

namespace comum {

// Reconstruction: the record of GetInst (cgeracaoversoescontratos.cpp:38, `static CGeracaoVersoesContratos
// &comum::CGeracaoVersoesContratos::GetInst()`) names the class and its file. Target fn 12098 stores that record and
// holds GetInst inlined with the constructor (a reading): it allocates 48 bytes, runs the INI loader (fn 5480) on +0
// and on +24 and reads one value of each with CDependenciasContratos::GetValor (fn 3826) and
// CVersoesContratos::GetValor (fn 3825); later it calls fn 3825 on the object's +24 and fn 5869 on the object itself.
// ObtemDependencias is fn 5869: it calls fn 3826 on its `this` plus 0. Its being a member is a reading (it reads the
// object's +0 and fn 12098 passes it the singleton), and its name, its parameters' names, the members' names and
// access are chosen. GetInst is declared only: the constructor waits for fn 5480, and its one caller, fn 12098, is not
// written. The destructor (fn 5866, the four maps from +36 down, called by fn 12098 and fn 11636) is implicit here and
// not written: its band place follows md/cversoesarquivos.cpp's rows, not this file's.
class CGeracaoVersoesContratos {
public:
    static CGeracaoVersoesContratos& GetInst();

    std::set<std::string> ObtemDependencias(const std::string& contrato, std::set<std::string>& dependencias);

private:
    md::CDependenciasContratos m_dependencias;
    md::CVersoesContratos m_versoes;
};

} // namespace comum
