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

} // namespace comum::asn
