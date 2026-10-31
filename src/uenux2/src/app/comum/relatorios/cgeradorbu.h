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

#include <string>
#include <vector>

#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/crdvvota.h"
#include "app/comum/relatorios/cgeradorbubase.h"

namespace comum {

class CGeradorBU final : public CGeradorBUBase<CRdvVota, CEleitores> {
public:
    ~CGeradorBU() override;

protected:
    virtual void ImprimePreTexto() const override;

private:
    std::vector<std::string> m_historicoCargas;
};

} // namespace comum
