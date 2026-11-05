#pragma once

// api::pkcs11::IPkcs11. Reconstruction notes, not TSE's text. The class's name is its typeinfo name's
// (N3api6pkcs117IPkcs11E, ledger/strings.tsv 517073) and the records of CPolySingleton<api::pkcs11::IPkcs11>::instance
// (target fn 3704); the target has no vtable of the class or of an implementer, so every member is chosen. Three target
// bodies use the instance: comum::CGeradorBUQRCode::RetornaBlocoAssinado (inlined into fn 5604) calls slot 23 (+92),
// slot 6 (+24) with a std::vector<uebyte> by reference, which returns an object of at least 20 bytes whose vector at +8
// the caller copies, 8-aligned in comum::asn::CAssinaVotavelBu::Assinar's frame (the 8 bytes at its head one 64-bit
// word here: two 32-bit words put it 4 bytes higher, unit 321's fragment), and slot 24 (+96); fn 10273, which holds
// comum::asn::CAssinaVotavelBu::Assinar (record 1597332), calls slots 23, 6 and 24 the same way;
// CEstadoGeral::RecuperarCertificado (fn 5635, record 1574772) calls slot 23, slot 10 (+40) and slot 24. The members
// are declared up to slot 24 with pure bodies; slot 6 is named from its role (5604 prints what it returns as the
// boletim's " ASSI:{}" field, and Assinar's name agrees), slot 10 from its role in 5635 (below), the others after their
// slots. The destructor in slots 0 and 1, the results' types and every name are chosen, and so is this path.

#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace api::pkcs11 {

// The result of IPkcs11::Assina: the caller copies the vector at +8 through GetAssinatura, then destroys the
// temporary. The 64-bit word before it, its name and type, and the accessor are chosen.
struct SResultadoAssinatura {
    ueqword m_status;
    std::vector<uebyte> m_assinatura;

    const std::vector<uebyte>& GetAssinatura() const { return m_assinatura; }
};

// The result of IPkcs11::LeCertificado (slot 10), which fn 5635 keeps as the certificate whose hex text fn 5634 prints
// in QR codes: 5635 passes the result's address at +12 of a 48-byte frame, copies the vector at +0 into its static
// (std::vector's __assign_with_size, fn 1681, the copy assignment from an lvalue) and frees it before slot 24, as a
// temporary of the statement does. A 36-byte object, 4-aligned, gives that frame (measured on cestadogeral.cpp's
// object; a std::vector<uebyte> result gives 16 bytes and +4, measured in the whole link with pnpm wasm score); the 24
// bytes after the vector, which 5635 neither reads nor destroys, their name and type, and the accessor are chosen.
struct SResultadoCertificado {
    std::vector<uebyte> m_certificado;
    uebyte m_resto[24];

    const std::vector<uebyte>& GetCertificado() const { return m_certificado; }
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
    virtual SResultadoCertificado LeCertificado() = 0;
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
