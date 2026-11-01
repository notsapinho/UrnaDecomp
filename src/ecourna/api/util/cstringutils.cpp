#include "ecourna/api/util/cstringutils.hpp"

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <iterator>
#include <limits>
#include <set>
#include <source_location>

#include <boost/regex.hpp>

#include "ecourna/api/util/eutilerror.hpp"

namespace ecourna::api::util {

namespace {

ueqword ConverteSemSinal(const std::string& valor, int base, const char* digitosValidos, ueqword maximo,
                         std::source_location local)
{
    const std::string texto = CStringUtils::Trim(valor);

    if (texto.empty() || texto.find_first_not_of(digitosValidos) != std::string::npos) {
        throw CUtilError(EUE_VALOR_INVALIDO, "valor invalido [" + valor + "]", local);
    }

    errno = 0;
    char* fim;
    const ueqword resultado = std::strtoull(texto.c_str(), &fim, base);
    if (*fim != '\0') {
        throw CUtilError(EUE_VALOR_NAO_NUMERICO, "valor invalido [" + valor + "]", local);
    }
    if (resultado > maximo || errno == ERANGE) {
        throw CUtilError(EUE_VALOR_FORA_DA_FAIXA, "valor invalido [" + valor + "]", local);
    }
    return resultado;
}

ueint64 ConverteComSinal(const std::string& valor, const char* digitosValidos, ueint64 minimo, ueint64 maximo,
                         std::source_location local)
{
    const std::string texto = CStringUtils::Trim(valor);

    if (texto.empty() || texto.find_first_not_of(digitosValidos) != std::string::npos) {
        throw CUtilError(EUE_VALOR_INVALIDO, "valor invalido [" + valor + "]", local);
    }

    errno = 0;
    char* fim;
    const ueint64 resultado = std::strtoll(texto.c_str(), &fim, 10);
    if (*fim != '\0') {
        throw CUtilError(EUE_VALOR_NAO_NUMERICO, "valor invalido [" + valor + "]", local);
    }
    if (resultado < minimo || resultado > maximo || errno == ERANGE) {
        throw CUtilError(EUE_VALOR_FORA_DA_FAIXA, "valor invalido [" + valor + "]", local);
    }
    return resultado;
}

template <typename T>
T ConverteDecimalSemSinal(const std::string& valor, std::source_location local = std::source_location::current())
{
    char digitosValidos[] = "+-0123456789";
    return static_cast<T>(ConverteSemSinal(valor, 10, digitosValidos, std::numeric_limits<T>::max(), local));
}

template <typename T>
T ConverteDecimalComSinal(const std::string& valor, std::source_location local = std::source_location::current())
{
    char digitosValidos[] = "+-0123456789";
    return static_cast<T>(ConverteComSinal(valor, digitosValidos, std::numeric_limits<T>::min(),
                                           std::numeric_limits<T>::max(), local));
}

template <typename T>
T ConverteHexadecimal(const std::string& valor, std::source_location local = std::source_location::current())
{
    char digitosValidos[] = "xXabcdefABCDEF0123456789";
    return static_cast<T>(ConverteSemSinal(valor, 16, digitosValidos, std::numeric_limits<T>::max(), local));
}

bool NaoEhBranco(unsigned char c)
{
    return c > ' ';
}

int HexCharToInt(int c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return -1;
}

std::set<int> AcentuadasMaiusculas()
{
    return {'Ç', 'Á', 'É', 'Í', 'Ó', 'Ú', 'À', 'È', 'Ì', 'Ò', 'Ù', 'Â', 'Ê', 'Î', 'Ô', 'Û', 'Ã',
            'Õ', 'Ñ'};
}

} // namespace

void CStringUtils::Replace(std::string& valor, const std::string& de, const std::string& para)
{
    const size_t tamanhoDe = de.size();
    if (tamanhoDe == 0) {
        return;
    }
    const size_t tamanhoPara = para.size();
    for (size_t posicao = valor.find(de); posicao != std::string::npos;
         posicao = valor.find(de, posicao + tamanhoPara)) {
        valor.replace(posicao, tamanhoDe, para);
    }
}

std::string CStringUtils::Replace(const std::string& valor, const std::string& de, const std::string& para)
{
    std::string resultado = valor;
    Replace(resultado, de, para);
    return resultado;
}

void CStringUtils::Trim(std::string& valor)
{
    if (!std::empty(valor)) {
        const std::string::reverse_iterator ultimo = std::find_if(valor.rbegin(), valor.rend(), NaoEhBranco);
        valor.erase(valor.size() - (ultimo - valor.rbegin()));
        valor.erase(valor.begin(), std::find_if(valor.begin(), valor.end(), NaoEhBranco));
    }
}

std::string CStringUtils::Trim(const std::string& valor)
{
    std::string resultado = valor;
    Trim(resultado);
    return resultado;
}

std::string CStringUtils::PreencheAEsquerda(const std::string& valor, char preenchimento, size_t tamanho)
{
    std::string preenchido(valor);
    if (preenchido.size() < tamanho) {
        preenchido.insert(0, tamanho - preenchido.size(), preenchimento);
    }
    return preenchido;
}

void CStringUtils::PreencheAEsquerda(std::string& valor, char preenchimento, size_t tamanho)
{
    if (valor.size() < tamanho) {
        valor.insert(0, tamanho - valor.size(), preenchimento);
    }
}

void CStringUtils::PreencheADireita(std::string& valor, char preenchimento, size_t tamanho)
{
    if (valor.size() < tamanho) {
        valor.append(tamanho - valor.size(), preenchimento);
    }
}

std::string CStringUtils::PreencheADireita(const std::string& valor, char preenchimento, size_t tamanho)
{
    std::string preenchido(valor);
    if (preenchido.size() < tamanho) {
        preenchido.append(tamanho - preenchido.size(), preenchimento);
    }
    return preenchido;
}

std::vector<std::string> CStringUtils::Split(const std::string& valor, char separador)
{
    std::vector<std::string> partes;
    std::string resto = valor;
    size_t posicao = 0;
    while ((posicao = resto.find(separador)) != std::string::npos) {
        if (posicao == 0) {
            partes.push_back("");
        } else {
            partes.emplace_back(resto, 0, posicao);
        }
        resto.erase(0, posicao + 1);
    }
    partes.push_back(resto);
    return partes;
}

std::string& CStringUtils::RemoveZerosAEsquerda(std::string& valor)
{
    return valor.erase(0, valor.find_first_not_of('0'));
}

std::string CStringUtils::RemoveZerosAEsquerda(const std::string& valor)
{
    std::string resultado = valor;
    RemoveZerosAEsquerda(resultado);
    return resultado;
}

void CStringUtils::ToUpper(std::string& valor)
{
    std::transform(valor.begin(), valor.end(), valor.begin(), [](char caractere) -> char {
        static const std::set<int> acentuadas = [] {
            const std::set<int> maiusculas = AcentuadasMaiusculas();
            std::set<int> minusculas;
            std::transform(maiusculas.begin(), maiusculas.end(), std::inserter(minusculas, minusculas.end()),
                           [](char letra) { return letra | 32; });
            return minusculas;
        }();
        if (acentuadas.find(caractere) != acentuadas.end()) {
            return caractere & ~32;
        }
        if (isalpha(caractere)) {
            return toupper(caractere);
        }
        return caractere;
    });
}

std::string CStringUtils::ToUpper(const std::string& valor)
{
    std::string resultado = valor;
    ToUpper(resultado);
    return resultado;
}

// Blank lines below keep each std::source_location call site (the To* conversions and the throw) on
// the line the target records (ledger/source-locations.tsv).

// (original lines 238-711: content not recovered)
#line 712
uebyte CStringUtils::ToByte(const std::string& valor)
{
    return ConverteDecimalSemSinal<uebyte>(valor);
}

ueint16 CStringUtils::ToInt16(const std::string& valor)
{
    return ConverteDecimalComSinal<ueint16>(valor);
}

ueword CStringUtils::ToWord(const std::string& valor)
{
    return ConverteDecimalSemSinal<ueword>(valor);
}

ueint32 CStringUtils::ToInt32(const std::string& valor)
{
    return ConverteDecimalComSinal<ueint32>(valor);
}

ueqword CStringUtils::ToQWord(const std::string& valor)
{
    return ConverteDecimalSemSinal<ueqword>(valor);
}

uedword CStringUtils::ToDWord(const std::string& valor)
{
    return ConverteDecimalSemSinal<uedword>(valor);
}

uedword CStringUtils::HexToInt(const std::string& valor)
{
    return ConverteHexadecimal<uedword>(valor);
}

ueint64 CStringUtils::ToInt64(const std::string& valor)
{
    return ConverteDecimalComSinal<ueint64>(valor);
}

ueqword CStringUtils::HexToQWord(const std::string& valor)
{
    return ConverteHexadecimal<ueqword>(valor);
}

std::vector<uebyte> CStringUtils::HexStringToBytes(const std::string& valor)
{
    const std::string texto = Trim(valor);
    const size_t tamanho = texto.size();

    // (original lines 762-806: content not recovered)
#line 807
    if (!std::all_of(texto.begin(), texto.end(), [](char c) { return std::isxdigit(c) != 0; })) {
        throw CUtilError(EUE_HEX_INVALIDO, "valor invalido [" + texto + "]");
    }

    std::vector<uebyte> bytes;
    bytes.reserve(tamanho / 2);
    const int ultimo = static_cast<int>(tamanho) - 1;
    for (int i = 0; i < ultimo; i += 2) {
        const int alto = HexCharToInt(texto[i]);
        const int baixo = HexCharToInt(texto[i + 1]);
        if (alto >= 0 && baixo >= 0) {
            bytes.push_back(static_cast<uebyte>((alto << 4) + baixo));
        }
    }
    return bytes;
}

std::string CStringUtils::BytesToHexString(const std::vector<uebyte>& valor)
{
    static const char DIGITOS[] = "0123456789ABCDEF";
    std::string texto;
    texto.reserve(valor.size() * 2);
    for (uebyte byte : valor) {
        texto.push_back(DIGITOS[byte >> 4]);
        texto.push_back(DIGITOS[byte & 0x0F]);
    }
    return texto;
}

std::pair<size_t, size_t> CStringUtils::FindRegex(const std::string& expressao, const std::string& valor)
{
    const size_t naoEncontrada = std::string::npos;
    if (valor.empty() || expressao.empty()) {
        return {naoEncontrada, naoEncontrada};
    }
    try {
        const boost::regex regex(expressao);
        boost::cmatch resultado;
        size_t inicio = naoEncontrada;
        size_t fim = naoEncontrada;
        if (boost::regex_search(valor.data(), valor.data() + valor.size(), resultado, regex)) {
            inicio = resultado.position();
            fim = inicio + resultado.length();
        }
        return {inicio, fim};
    } catch (...) {
        return {naoEncontrada, naoEncontrada};
    }
}

} // namespace ecourna::api::util
