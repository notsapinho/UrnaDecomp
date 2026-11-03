#pragma once

#include "app/vota/eleitor/iniciovotacao/testeteclado/cbase.h"

namespace vota::testeteclado {

// vota::testeteclado::CRetomada (RTTI: si_class of vota::testeteclado::CBase; vtable @1546700 [1559, 5946, 11875, 7480,
// 1661, 218, 425, 11874, 12061, 425, 11831, 11830, 11829]): the keyboard test offered when the voting resumes. It
// overrides slots 10 to 12; slot 10 is pending. Slot 11 (fn 11830) goes back to vota::CReinicioVotacao, and first, on a
// load whose urna type is 51, sets the vote state's m_tecladoTestadoPosConversao when it is clear and saves the state.
// Slot 12 (fn 11829) goes back to it when the byte at +36 is 1, a byte slot 10 (fn 11831) stores. It compares the byte
// with 1, where a bool would be tested (a reading, not measured): uebyte and the member's name are chosen. The
// destructor is out of line: the deleting one (fn 5946) is CPreZeresima's body. final is chosen, as CPreZeresima's
// sibling.
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
