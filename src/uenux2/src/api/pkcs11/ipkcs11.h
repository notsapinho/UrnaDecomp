#pragma once

// api::pkcs11::IPkcs11. Reconstruction notes, not TSE's text. The class's name is its typeinfo name's
// (N3api6pkcs117IPkcs11E, ledger/strings.tsv 517073) and the records of CPolySingleton<api::pkcs11::IPkcs11>::instance
// (target fn 3704); the target has no vtable of the class or of an implementer, so every member is chosen. Three target
// bodies use the instance: comum::CGeradorBUQRCode::RetornaBlocoAssinado (inlined into fn 5604) calls slot 23 (+92),
// slot 6 (+24) with a std::vector<uebyte> by reference, which returns an object of at least 20 bytes whose vector at +8
// the caller copies, and slot 24 (+96); fn 10273, which holds comum::asn::CAssinaVotavelBu::Assinar (record 1597332),
// calls slots 23, 6 and 24 the same way; CEstadoGeral::RecuperarCertificado (fn 5635, record 1574772) calls slot 23
// and then slot 10 (+40). The members are declared up to slot 24 with pure bodies; slot 6 is named from its role (5604
// prints what it returns as the boletim's " ASSI:{}" field, and Assinar's name agrees), the others after their slots
// (slot 10's role in 5635 is not followed). The destructor in slots 0 and 1, the result's type and every name are
// chosen, and so is this path.

#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace api::pkcs11 {

// The result of IPkcs11::Assina: the caller copies the vector at +8 through GetAssinatura, then destroys the
// temporary. The two words before it, their names and types, and the accessor are chosen.
struct SResultadoAssinatura {
    uedword m_status;
    uedword m_tamanho;
    std::vector<uebyte> m_assinatura;

    const std::vector<uebyte>& GetAssinatura() const { return m_assinatura; }
};

class IPkcs11 {
public:
    virtual ~IPkcs11() = default;

    virtual void Slot2() = 0;
    virtual void Slot3() = 0;
    virtual void Slot4() = 0;
    virtual void Slot5() = 0;
    virtual SResultadoAssinatura Assina(const std::vector<uebyte>& dados) = 0;
    virtual void Slot7() = 0;
    virtual void Slot8() = 0;
    virtual void Slot9() = 0;
    virtual void Slot10() = 0;
    virtual void Slot11() = 0;
    virtual void Slot12() = 0;
    virtual void Slot13() = 0;
    virtual void Slot14() = 0;
    virtual void Slot15() = 0;
    virtual void Slot16() = 0;
    virtual void Slot17() = 0;
    virtual void Slot18() = 0;
    virtual void Slot19() = 0;
    virtual void Slot20() = 0;
    virtual void Slot21() = 0;
    virtual void Slot22() = 0;
    virtual void Slot23() = 0;
    virtual void Slot24() = 0;
};

} // namespace api::pkcs11
