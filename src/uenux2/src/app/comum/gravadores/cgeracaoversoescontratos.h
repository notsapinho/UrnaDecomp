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
// object's +0 and fn 12098 passes it the singleton), and its name, its parameters' names, the members' names and access
// are chosen. GetInst and the constructor are written in cgeracaoversoescontratos.cpp and compared with nothing: their
// one caller, fn 12098, is not written, so wasm-ld drops them (src/units/268-uenux2-cgeracaoversoescontratos.mk says
// what they are read from and what is chosen). The constructor's two parameters, the paths the members' constructors
// take, are chosen. The destructor is fn 5866 (the four maps from +36 down), defined out of line in
// cgeracaoversoescontratos.cpp: its target callers, 12098 (a std::unique_ptr's delete after GetInst's push) and 11636
// (__on_zero_shared of the std::shared_ptr block push<T> builds, push's record for this class following GetInst's in
// the target's data), call it and then free `this`, which a delete gives in a TU that defines the destructor out of
// line and not in one that sees the implicit one or only a declaration (measured, in
// src/units/268-uenux2-cgeracaoversoescontratos.mk). Declaring it first and its `= default` are choices.
class CGeracaoVersoesContratos {
public:
    ~CGeracaoVersoesContratos();

    CGeracaoVersoesContratos(const std::string& dependencias, const std::string& versoes);

    static CGeracaoVersoesContratos& GetInst();

    std::set<std::string> ObtemDependencias(const std::string& contrato, std::set<std::string>& dependencias);

private:
    md::CDependenciasContratos m_dependencias;
    md::CVersoesContratos m_versoes;
};

} // namespace comum
