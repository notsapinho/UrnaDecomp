#pragma once
#include <vector>

#include "asn1/asn1.h"
#include "ecourna/api/uetypes.hpp"

namespace ecourna::app::dados::asn {

// A byte vector as an ASN.1 OCTET STRING and back (fns 9063 and 5095). Names and file are chosen: no record names
// them. Both stay out of line in the target, called by the converters of app/dados/asn/resultadournacadastro.
ASN1::OCTET_STRING ConverteOctetos(const std::vector<uebyte>& octetos);
std::vector<uebyte> DeconverteOctetos(const ASN1::OCTET_STRING& octetos);

} // namespace ecourna::app::dados::asn
