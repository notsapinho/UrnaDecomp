// api::CStringUtils: GetVersionNumber and the two SetBit at their records' lines (59, 71 and 83). The reconstruction's
// own note; the blank lines stand for text not recovered.
#include "api/util/cstringutils.h"

#include <cctype>
#include <format>
#include <numeric>

#include "api/util/eueutilerror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace api {

namespace {

// 7025 is not in api/util/eueutilerror.h yet; the constant goes when the header gains it.
constexpr auto EUE_UTIL_7025 = static_cast<EUeUtilError>(7025);

} // namespace

// (original lines 21-53: content not recovered)
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

// (original lines 64-67: content not recovered)
#line 68
void CStringUtils::SetBit(uebyte& byte, const uebyte bit, const bool valor)
{
    if (bit > 7) {
        throw CUeUtilError(EUE_UTIL_BIT_FORA_DOS_LIMITES, std::format("Bit fora dos limites ({})", bit));
    }
    byte = (byte & ~(1 << bit)) | (valor << bit);
}

// (original lines 76-78: content not recovered)
#line 79
void CStringUtils::SetBit(std::vector<uebyte>& bytes, const size_t bit, const bool valor)
{
    const size_t indice = bit / 8;
    if (indice >= bytes.size()) {
        throw CUeUtilError(EUE_UTIL_BIT_FORA_DOS_LIMITES_DO_VETOR,
                           std::format("Bit fora dos limites ({}) do vetor ({})", bit, bytes.size()));
    }
    SetBit(bytes[indice], bit % 8, valor);
}

bool CStringUtils::CasaRegex(const std::string& padrao, const std::string& valor)
{
    return ecourna::api::util::CStringUtils::FindRegexPosition(padrao.substr(7), valor) != std::string::npos;
}

bool CStringUtils::CasaCaractere(char mascara, char caractere)
{
    switch (mascara) {
    case '#':
        return isdigit(caractere);
    case '@':
        return isalpha(caractere);
    case '?':
        return isalnum(caractere) || caractere == '-' || caractere == '_';
    default:
        return false;
    }
}

std::string CStringUtils::JuntaTags(const std::vector<std::pair<std::string, std::string>>& tags)
{
    std::string texto =
        std::accumulate(tags.begin(), tags.end(), std::string(),
                        [](const std::string& acumulado, const std::pair<std::string, std::string>& tag) {
                            return acumulado + tag.first + ":" + tag.second + " ";
                        });
    if (!texto.empty()) {
        texto.pop_back();
    }
    return texto;
}

} // namespace api
