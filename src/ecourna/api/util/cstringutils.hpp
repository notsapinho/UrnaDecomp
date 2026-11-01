#pragma once
#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace ecourna::api::util {

class CStringUtils {
public:
    static void Trim(std::string& valor);
    static std::string Trim(const std::string& valor);
    static std::string PreencheAEsquerda(const std::string& valor, char preenchimento, size_t tamanho);
    // fn 3512: pads in place on the left up to a length (callers 566 and 2798, which pass '0'); fn 3511: pads in place
    // on the right (callers 10726, 11972, 11973); fn 1881: pads a copy on the right (callers 1542, 2248, 11188, 11253,
    // 11478, which pass ' '). No record names them: the names, after PreencheAEsquerda's, the in-place and copying
    // overloads, after Trim's, and their being members of this class are chosen (src/units/00-*.mk says why this file)
    static void PreencheAEsquerda(std::string& valor, char preenchimento, size_t tamanho);
    static void PreencheADireita(std::string& valor, char preenchimento, size_t tamanho);
    static std::string PreencheADireita(const std::string& valor, char preenchimento, size_t tamanho);
    // fn 3510: erases a string's leading '0's in place (callers 566 and 2798); fn 5159: the same on a copy (callers 566
    // and 3723). No record names them: names, overloads and class are chosen as above
    static std::string& RemoveZerosAEsquerda(std::string& valor);
    static std::string RemoveZerosAEsquerda(const std::string& valor);

    static uebyte ToByte(const std::string& valor);
    static ueint16 ToInt16(const std::string& valor);
    static ueword ToWord(const std::string& valor);
    static ueint32 ToInt32(const std::string& valor);
    static ueqword ToQWord(const std::string& valor);
    static uedword ToDWord(const std::string& valor);
    static uedword HexToInt(const std::string& valor);
    static ueint64 ToInt64(const std::string& valor);
    static ueqword HexToQWord(const std::string& valor);
    static std::vector<uebyte> HexStringToBytes(const std::string& valor);
    // fn 1243: two upper-case hex digits per byte (callers 9257, 5604, 5634, 5636, 10273, 11587, 11626, 11629)
    static std::string BytesToHexString(const std::vector<uebyte>& valor);

    // The api/sql/sqlite callers' helpers: ToLower in place (fn 5158, Latin-1 aware), its copying form (fn 1879) and
    // Replace of a char by a string (fn 9398); no record names ToLower, a chosen name. They are defined in
    // src/units/12-ecourna-api-sql-sqlite-externs.cpp until api/util/cstringutils.cpp is reconstructed around them.
    static void ToLower(std::string& valor);
    static std::string ToLower(const std::string& valor);
    static void Replace(std::string& valor, char de, const std::string& para);
};

} // namespace ecourna::api::util
