// Pending member: the api::CSubReport member src/uenux2/src/api/gui/csubreport.h does not define yet. The vtable needs
// it defined; its body is NOT the target's, it traps. Declared out of line, it is the class's key function, so the
// vtable, the implicit destructors (target fns 12014 and 12013) and the inline slots 2-5 and 7 (3874, 12012, 12011,
// 12010, 12008) are emitted in this object until it moves into the class. Target function:
// - ImprimeParte (slot 6, fn 12009) is `void ImprimeParte() const override { m_parte->Imprime(); }`, defined in the
//   class like the other slots: it calls slot 2 of the +28 pointee, api::IReportPart, whose slot 2 is `Imprime() const`
//   by the records of its implementations (comum::CParteCandidatosMajoritarios::Imprime, cpartecandidatos.cpp:75).
//   csubreport.h only forward-declares IReportPart, whose header is api/gui/reports/ireportpart.h.
// Move it into csubreport.h, which then includes that header, and delete this file and its rule.
#include "api/gui/csubreport.h"

namespace api {

void CSubReport::ImprimeParte() const
{
    __builtin_trap();
}

} // namespace api
