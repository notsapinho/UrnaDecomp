#pragma once

#include "api/util/cdatetime.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cbase.h"

namespace vota::testeteclado {

// vota::testeteclado::CPreZeresima (RTTI: si_class of vota::testeteclado::CBase; vtable @1546036 [1559, 5946, 11875,
// 7480, 1661, 218, 425, 11874, 12061, 425, 11862, 5945, 11861]): the keyboard test offered before the zerésima. It
// overrides slots 10 to 12, all pending. GetEstadoPassouNoTeste is its record's name (cprezeresima.cpp:56). final: slot
// 12 (fn 11861) calls slot 11 (fn 5945) directly (final on that member alone would do the same, a choice). The
// destructor is out of line: the deleting one (fn 5946, which CRetomada's slot 1 holds too) calls the D2 and frees
// `this`. +36 is a date and time: slot 10 sets it (fn 5476 on it), and slots 10 and 12 compare its date (fn 1261). The
// member's name is chosen.
class CPreZeresima final : public CBase {
public:
    virtual ~CPreZeresima() override;

protected:
    virtual CFormInterativoTelaVota GetTela() override;

    virtual comum::CAppState* GetEstadoPassouNoTeste() override;

    virtual comum::CAppState* GetEstadoSemTeste() override;

private:
    api::CDateTime m_dataHora;
};

} // namespace vota::testeteclado
