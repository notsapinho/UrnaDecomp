// comum::asn::CAssinaVotavelBu::Assinar (/home/rubio/tse/uenux2/src/app/comum/gravadores/asn/cassinavotavelbu.cpp),
// whose record is a record of the target (line 89, column 21: the default argument of
// CPolySingleton<IPkcs11>::instance()), so its line is fixed; where it starts is a choice. It has no target index of its
// own: binaryen inlines it into its one caller, held by CConversorEntidadeBU::DoConverte (fn 10273), where it opens a
// frame of its own. The class's other members are in util.cpp (cassinavotavelbu.h says why).

#include "app/comum/gravadores/asn/cassinavotavelbu.h"

#include "api/pattern/cpolysingleton.h"
#include "api/pkcs11/ipkcs11.h"

namespace comum::asn {

// (original lines 14-86: content not recovered)
#line 87
std::vector<uebyte> CAssinaVotavelBu::Assinar(const std::vector<uebyte>& hash) const
{
    auto& oPkcs11 = api::CPolySingleton<api::pkcs11::IPkcs11>::instance();
    oPkcs11.Slot23();
    const api::pkcs11::SResultadoAssinatura resultado = oPkcs11.Assina(hash);
    oPkcs11.Slot24();
    return resultado.GetAssinatura();
}

} // namespace comum::asn
