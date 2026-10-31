#pragma once

#include "app/vota/eleitor/iniciovotacao/testeteclado/cbase.h"

namespace vota::testeteclado {

// vota::testeteclado::CRetomada (RTTI: si_class of vota::testeteclado::CBase; vtable @1546700 [1559, 5946, 11875, 7480,
// 1661, 218, 425, 11874, 12061, 425, 11831, 11830, 11829]): the keyboard test offered when the voting resumes. It
// overrides slots 10 to 12; slots 10 and 11 are pending. Slot 12 (fn 11829) goes back to vota::CReinicioVotacao when
// the byte at +36 is 1, a byte slot 10 (fn 11831) stores. It compares the byte with 1, where a bool would be tested
// (a reading, not measured): uebyte and the member's name are chosen. The destructor is out of line: the deleting one
// (fn 5946) is CPreZeresima's body. final is chosen, as CPreZeresima's sibling.
class CRetomada final : public CBase {
public:
    virtual ~CRetomada() override;

protected:
    virtual CFormInterativoTelaVota GetTela() override;

    virtual comum::CAppState* GetEstadoPassouNoTeste() override;

    virtual comum::CAppState* GetEstadoSemTeste() override;

private:
    uebyte m_retomada;
};

} // namespace vota::testeteclado
