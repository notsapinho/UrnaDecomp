#pragma once
#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace ecourna::app::dados {

// A media serial number: 8 hexadecimal digits, kept as bytes.
class CSerialMidia {
public:
    explicit CSerialMidia(const std::string& serial);

    // The serial as hexadecimal text (fn 9257, used by app/dados/asn/midias/cconversordadosgeracaomidia.cpp).
    std::string ToString() const;

    // The serial's bytes: comum::IGravadorEnvelope's builder (inlined into uenux2's target fn 11626) passes the member
    // at +32 of a CInformacaoMidia, this class's vector, to CStringUtils::BytesToHexString itself, not ToString. The
    // name is chosen.
    const std::vector<uebyte>& GetSerial() const { return m_serial; }

private:
    static bool ValidaSerial(const std::string& serial);

    std::vector<uebyte> m_serial;
};

} // namespace ecourna::app::dados
