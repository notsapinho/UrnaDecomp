#pragma once

#include <memory>
#include <mutex>

#include "api/util/cdatetime.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cbase.h"

namespace vota::testeteclado {

// vota::testeteclado::CPreZeresima (RTTI: si_class of vota::testeteclado::CBase; vtable @1546036 [1559, 5946, 11875,
// 7480, 1661, 218, 425, 11874, 12061, 425, 11862, 5945, 11861]): the keyboard test offered before the zerésima. It
// overrides slots 10 to 12: GetEstadoPassouNoTeste (slot 11, fn 5945) is its record's name (cprezeresima.cpp:56), and
// slots 10 and 12 are pending. final: slot 12 (fn 11861) calls slot 11 (fn 5945) directly, and GetInst deletes the old
// object through the D2 (fn 1559) with no call through the vtable (final on that member alone would give the first,
// a choice). The destructor is out of line: the deleting one (fn 5946, which CRetomada's slot 1 holds too) calls the
// D2 and frees `this`. +36 is a date and time: slot 10 sets it (fn 5476 on it), and slots 10 and 12 compare its date
// (fn 1261). A singleton: GetInst, inlined by binaryen into its one caller, vota::CVerificaEleicaoPassou::StartState
// (fn 11914), builds the 48-byte object over CBase's constructor (fn 5948) and clears +36 with CDateTime(0) (fn 1000),
// and keeps it in a static std::unique_ptr (@1834744, destroyed at exit by fn 11864) under a static std::mutex
// (@1834720, by fn 11863), unit 104's shape. The member's name, GetInst's and the statics' are chosen.
class CPreZeresima final : public CBase {
public:
    virtual ~CPreZeresima() override;

    static CPreZeresima& GetInst();

protected:
    virtual CFormInterativoTelaVota GetTela() override;

    virtual comum::CAppState* GetEstadoPassouNoTeste() override;

    virtual comum::CAppState* GetEstadoSemTeste() override;

private:
    CPreZeresima();

    static std::mutex s_mutex;
    static std::unique_ptr<CPreZeresima> s_inst;

    api::CDateTime m_dataHora;
};

} // namespace vota::testeteclado
