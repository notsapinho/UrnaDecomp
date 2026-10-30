#pragma once

#include <memory>

#include "api/gui/reports/ireportpart.h"

namespace comum {

// Reconstruction notes, not TSE's text. The class is named by RTTI (an si_class of api::IReportPart). Its D2 and D0 are
// CParteCandidatos's 2876 and 5590, one body in the target, so it has that class's layout, 44 bytes, and is final like
// it (cpartecandidatos.h says why, and src/units/77-uenux2-ireportpart.mk what else gives the same bytes). Imprime
// (fn 11203) prints m_cabecalho, one of three parts chosen by fields of what fns 273 and 332 return, then m_rodape,
// calling slot 2 of each. Their element type, the member names, the order of the constructor's parameters and this
// header's path are chosen: no record names the class. The constructor is out of line in cparterdv.cpp,
// inlined by binaryen into its one caller, fn 5971 (the fragment has the evidence), and takes its arguments by value.
class CParteRdv final : public api::IReportPart {
public:
    CParteRdv(std::shared_ptr<api::IReportPart> cabecalho, std::shared_ptr<api::IReportPart> parte1, std::shared_ptr<api::IReportPart> parte2,
              std::shared_ptr<api::IReportPart> parte3, std::shared_ptr<api::IReportPart> rodape);

    virtual void Imprime() const override;

private:
    std::shared_ptr<api::IReportPart> m_cabecalho;
    std::shared_ptr<api::IReportPart> m_parte1;
    std::shared_ptr<api::IReportPart> m_parte2;
    std::shared_ptr<api::IReportPart> m_parte3;
    std::shared_ptr<api::IReportPart> m_rodape;
};

} // namespace comum
