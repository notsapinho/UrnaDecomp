#pragma once

// comum::CGeradorBU. Reconstruction notes, not TSE's text. RTTI gives the class, an si_class of
// comum::CGeradorBUBase<comum::CRdvVota, comum::CEleitores>; its records are in cgeradorbu.cpp, and no record names a
// header, so this path is chosen. Its vtable (@1575156) has six slots: the D2 (fn 3698), the D0 (fn 11258),
// ImprimePreTexto (fn 11256, its record cgeradorbu.cpp:257) and the base's three.
//
// Recovered: the layout past the base's 116 bytes and the destructor. fn 12110 builds the object, copying a
// std::vector<std::string> to +116, and ImprimePreTexto (fn 11256) walks that vector after it loads the title at 230329
// in ledger/strings.tsv, the load-code history's, so the member's name is chosen from that title. The class is final: its
// D2 does not open with its own vptr store (docs/reference/facts/reading.md R4). The destructor is out of line, in
// cgeradorbu.cpp: the D0 calls the D2 and then frees (R5). The constructor's parameter list is not recovered, and
// nothing here declares it.

#include <memory>
#include <string>
#include <vector>

#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/crdvvota.h"
#include "app/comum/relatorios/cgeradorbubase.h"

namespace comum {

// Fn 3699, no record: a form of the title it is given (style 1, left), a new line and the current position's name
// upper-cased and centred in 38 columns of '-' (comum::CPadDS over CToUpperDS over CCargoDSNome, fn 5613's instance).
// Its callers are fns 5971 (vota::CriaPartesExtratoRDV, with the phase's separator), 11946 and 12110. Its name,
// its parameter's type, its being a free function of comum and its file (cgeradorbu.cpp, one of the two the use band
// leaves: src/units/325-uenux2-geradores-zeresima.mk) are chosen.
std::shared_ptr<api::IForm<api::IPaper>> CriaTituloCargo(const std::string& titulo);

class CGeradorBU final : public CGeradorBUBase<CRdvVota, CEleitores> {
public:
    ~CGeradorBU() override;

protected:
    virtual void ImprimePreTexto() const override;

private:
    std::vector<std::string> m_historicoCargas;
};

} // namespace comum
