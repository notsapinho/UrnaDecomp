#pragma once

#include <memory>

#include "api/gui/reports/ireportpart.h"

namespace comum {

// Reconstruction notes, not TSE's text. Recovered: the class (its RTTI, an api::IReportPart), its 20-byte layout and
// its constructor from target fn 5587, which stores the vptr and takes over two std::shared_ptr<api::IReportPart> at
// +4 and +12 (the only caller shape, std::make_shared<CParteCargos> in fns 5971 and 11946, allocates 12 + 20 bytes).
// The constructor takes them by value and moves them in: the callee owns a by-value std::shared_ptr here (libc++'s
// trivial ABI for it), so the moved-from parameters leave no store, as in 5587. Imprime (slot 2, fn 11209) walks the
// cargos of comum::CCargos::GetInst() (the records of fns 273, 2835 and 1708 name GetInst, GetCurrentEleicaoID and
// Next): it prints m_parte for each one and, when m_cabecalho is set, prints it first for a cargo whose election
// differs from the one before (from the last cargo's, for the first). The destructor is implicit and not final: its
// bodies (fns 11208, 11207, vtable slots 0 and 1) store the vptr, release m_parte, then m_cabecalho, and the deleting
// one holds that body inlined. The member and parameter names are not in the target: they are chosen from those
// roles. No record names this file: it goes beside cpartecargos.cpp, whose path the class's link-order neighbours give
// (src/units/58-uenux2-cpartecargos.mk).
class CParteCargos : public api::IReportPart {
public:
    CParteCargos(std::shared_ptr<api::IReportPart> cabecalho, std::shared_ptr<api::IReportPart> parte);

    virtual void Imprime() const override;

private:
    std::shared_ptr<api::IReportPart> m_cabecalho;
    std::shared_ptr<api::IReportPart> m_parte;
};

} // namespace comum
