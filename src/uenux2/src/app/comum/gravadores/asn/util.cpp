// comum::asn's serial-number helpers (/home/rubio/tse/uenux2/src/app/comum/gravadores/asn/util.cpp) and, last, the SHA-512
// helper CalculaHashSha512 (target fn 3602, no record: its place is its use band's, after DesconverteSerialFlash; its
// name is chosen). The serial helpers' throws are records of the target, so their positions in this file are fixed:
//   3605  ConverteSerialFlash     records at lines 26 and 31, column 15
//   3604  DesconverteSerialFlash  record at line 54, column 15

#include "app/comum/gravadores/asn/util.h"

#include <format>

#include "app/comum/gravadores/euecomumgravadoreserror.h"
#include "ecourna/api/security/csha.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::asn {

// (original lines 17-22: content not recovered)
#line 23
std::vector<char> ConverteSerialFlash(const std::string& serial)
{
    if (serial.size() != 8) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8631, "Serial inválido [" + serial + "]");
    }


    if (serial.find_first_not_of("0123456789ABCDEFabcdef") != std::string::npos) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8632, "Serial inválido [" + serial + "]");
    }

    std::vector<char> resultado;
    for (std::size_t i = 0; i < 4; ++i) {
        char byte[3] = {0};
        byte[0] = serial[2 * i];
        byte[1] = serial[2 * i + 1];
        const char valor = static_cast<char>(ecourna::api::util::CStringUtils::HexToInt(byte));
        resultado.push_back(valor);
    }
    return resultado;
}


std::string DesconverteSerialFlash(const std::vector<char>& serial)
{
    std::string resultado;
    for (std::size_t i = 0; i < serial.size(); ++i) {
        resultado += std::format("{:02X}", static_cast<uebyte>(serial[i]));
    }

    if (serial.size() != 4) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8633, "Serial inválido [" + resultado + "]");
    }
    return resultado;
}


std::vector<uebyte> CalculaHashSha512(const std::string& texto)
{
    std::shared_ptr<ecourna::api::security::IHash> hash(new ecourna::api::security::CSha512());
    hash->Reset();
    const std::vector<uebyte> dados(texto.begin(), texto.end());
    hash->Update(dados);
    return hash->Finish();
}

} // namespace comum::asn
