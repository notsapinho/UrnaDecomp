#pragma once

#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace comum::asn {

// Recovered: the two helpers whose records gravadores/asn/util.cpp holds (lines 26 to 54), with the signatures the records
// print. Their callers are other files' converters (fns 10287, 10291 and 11399 call ConverteSerialFlash; 10284, 10290
// and 11400 DesconverteSerialFlash), so both are external. The header's path is chosen, beside the file.
std::vector<char> ConverteSerialFlash(const std::string& serial);
std::string DesconverteSerialFlash(const std::vector<char>& serial);

// The SHA-512 digest of a string's bytes (target fn 3602): comum::asn::CAssinaVotavelBu's three hash members call it,
// and binaryen inlines them into CConversorEntidadeBU's slot 2 (fn 10273), which so holds its three calls. No record
// names it. It is defined in cassinavotavelbu.cpp, with its callers, where the target's data place the CSha512 control
// block it builds (cassinavotavelbu.h). Its declaration in this header, its name, its being a free function and its
// parameter's name are chosen.
std::vector<uebyte> CalculaHashSha512(const std::string& texto);

} // namespace comum::asn
