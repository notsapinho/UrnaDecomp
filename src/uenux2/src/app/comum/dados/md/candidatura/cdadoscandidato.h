#pragma once

#include <optional>
#include <string>

#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// The sex of a candidate, as CDadosCandidato's constructors spell it. Recovered: the type's name, and the three values
// comum::asn::Utils::DesconverteSexo returns (target fn 11450 holds it): 0, 1 and 2 for the entity's sexoNaoInformado,
// sexoMasculino and sexoFeminino. The enumerators' names are chosen from those.
class CSexo {
public:
    enum ESexo : int {
        SEXO_NAO_INFORMADO,
        SEXO_MASCULINO,
        SEXO_FEMININO,
    };
};

// Recovered: the layout, 52 bytes, from the copy CCandidatura's constructor makes of it (target fn 5660) and from the
// four constructors comum::asn::CConversorDadosCandidato::DoDesconverte (target fn 11450) holds: the two strings at +0
// and +12, the optional string at +24 (flag +36), CSexo::ESexo at +40, ESituacao at +44 and the substitute's order at
// +48. 11450 fills them from the entity's codigo, nomeUrna, nomeFonetico, sexo and ordemSuplencia, which name the
// members; the names themselves, and GetNomeUrna's and GetOrdem's, are chosen. The four constructors are defined in
// cdadoscandidato.cpp, where the two that take an order have their records (:35 and :65), and binaryen inlined each
// into 11450, its one caller: each by-value string the caller moves into the object is still tested and freed after the
// constructor, which clang folds away when it inlines a constructor it sees. The order is a signed char, where the
// records' parameter is a uebyte: 5660 loads it with i32.load8_s and formats it as an int, which std::format does for a
// signed char and does not for a char or a uebyte. ESituacao's enumerators are not recovered: 11450 passes 0 or 1 (its
// converter's flag, inverted).
class CDadosCandidato {
public:
    enum ESituacao : int;

    CDadosCandidato(std::string codigo, std::string nomeUrna, CSexo::ESexo sexo, ESituacao situacao);
    CDadosCandidato(std::string codigo, std::string nomeUrna, std::string nomeFonetico, CSexo::ESexo sexo,
                    ESituacao situacao);
    CDadosCandidato(std::string codigo, std::string nomeUrna, CSexo::ESexo sexo, ESituacao situacao, uebyte ordem);
    CDadosCandidato(std::string codigo, std::string nomeUrna, std::string nomeFonetico, CSexo::ESexo sexo,
                    ESituacao situacao, uebyte ordem);

    const std::string& GetNomeUrna() const { return m_nomeUrna; }
    signed char GetOrdem() const { return m_ordem; }

private:
    std::string m_codigo;
    std::string m_nomeUrna;
    std::optional<std::string> m_nomeFonetico;
    CSexo::ESexo m_sexo;
    ESituacao m_situacao;
    signed char m_ordem;
};

} // namespace comum::md
