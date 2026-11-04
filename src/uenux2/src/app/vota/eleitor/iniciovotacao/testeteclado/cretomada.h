#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/iniciovotacao/testeteclado/cbase.h"

namespace vota::testeteclado {

// vota::testeteclado::CRetomada (RTTI: si_class of vota::testeteclado::CBase; vtable @1546700 [1559, 5946, 11875, 7480,
// 1661, 218, 425, 11874, 12061, 425, 11831, 11830, 11829]): the keyboard test offered when the voting resumes. It
// overrides slots 10 to 12; slot 10 is pending. Slot 11 (fn 11830) goes back to vota::CReinicioVotacao, and first, on a
// load whose urna type is 51, sets the vote state's m_tecladoTestadoPosConversao when it is clear and saves the state.
// Slot 12 (fn 11829) goes back to it when the byte at +36 is 1, a byte slot 10 (fn 11831) stores. It compares the byte
// with 1, where a bool would be tested (a reading, not measured): uebyte and the member's name are chosen. The
// destructor is out of line: the deleting one (fn 5946) is CPreZeresima's body. A singleton: GetInst, inlined by
// binaryen into its one caller, vota::CAjusteInicial::StartState (fn 7160), builds the 40-byte object over CBase's
// constructor (fn 5948) with +36 cleared, keeps it in a static std::unique_ptr (@1834996, destroyed at exit by fn
// 11833) under a static std::mutex (@1834972, by fn 11832), and deletes the old object with a direct call of the D2 (fn
// 1559, CBase's body, which slot 0 holds) and no call through the vtable: final (a final destructor alone would allow
// the same call, a reading not measured, so final on the class is chosen, as CPreZeresima's). CPreZeresima's shape,
// whose names GetInst and the statics take (chosen).
class CRetomada final : public CBase {
public:
    virtual ~CRetomada() override;

    static CRetomada& GetInst();

protected:
    virtual CFormInterativoTelaVota GetTela() override;

    virtual comum::CAppState* GetEstadoPassouNoTeste() override;

    virtual comum::CAppState* GetEstadoSemTeste() override;

private:
    CRetomada();

    static std::mutex s_mutex;
    static std::unique_ptr<CRetomada> s_inst;

    uebyte m_retomada;
};

} // namespace vota::testeteclado
