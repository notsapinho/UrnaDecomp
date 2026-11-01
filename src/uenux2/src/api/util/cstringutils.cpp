// api::CStringUtils: GetVersionNumber at its record's line (59). The reconstruction's own note; the blank lines stand
// for text not recovered, the SetBit records' lines (71 and 83) among them.
#include "api/util/cstringutils.h"

#include <format>

#include "api/util/eueutilerror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace api {

namespace {

// 7025 is not in api/util/eueutilerror.h yet; the constant goes when the header gains it.
constexpr auto EUE_UTIL_7025 = static_cast<EUeUtilError>(7025);

} // namespace

// (original lines 19-53: content not recovered)
#line 54
std::string CStringUtils::GetVersionNumber(const std::string& versao)
{
    const std::string expressao = "^[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+";
    const auto [inicio, fim] = ecourna::api::util::CStringUtils::FindRegex(expressao, versao);
    if (inicio != 0) {
        throw CUeUtilError(EUE_UTIL_7025, std::format("A string [{}] não representa uma versão válida", versao));
    }
    return versao.substr(0, fim);
}






















} // namespace api
