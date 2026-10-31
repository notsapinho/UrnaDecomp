#include "ecourna/app/dados/asn/octetstringasn.hpp"

namespace ecourna::app::dados::asn {

ASN1::OCTET_STRING ConverteOctetos(const std::vector<uebyte>& octetos)
{
    ASN1::OCTET_STRING resultado;
    resultado.insert(resultado.begin(), octetos.begin(), octetos.end());
    return resultado;
}

std::vector<uebyte> DeconverteOctetos(const ASN1::OCTET_STRING& octetos)
{
    return std::vector<uebyte>(octetos.begin(), octetos.end());
}

} // namespace ecourna::app::dados::asn
