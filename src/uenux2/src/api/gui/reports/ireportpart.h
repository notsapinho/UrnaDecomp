#pragma once

namespace api {

// Reconstruction notes, not TSE's text. Recovered: the virtual destructor and Imprime, slots 0-1 and 2 of the vtables
// of every class that implements the interface (comum::CParteCargos, CParteEleitores, CParteRdv, CParteCandidatos,
// CParteCandidatosMajoritarios, CParteCandidatosProporcionais, CParteCandidatosConsultas and api::CFormPart: the RTTI
// of each names this base, and each vtable has these three slots only). Imprime's name and const are the records' of
// CParteCandidatosMajoritarios::Imprime and CParteCandidatosConsultas::Imprime (relatorios/cpartecandidatos.cpp:75
// and :174). The target has this class's typeinfo and no vtable: every member is inline or pure. No record names this
// file: its path is chosen, beside the report code of api/gui/reports/ (whose creport.cpp the records name).
class IReportPart {
public:
    virtual ~IReportPart() = default;

    virtual void Imprime() const = 0;
};

} // namespace api
