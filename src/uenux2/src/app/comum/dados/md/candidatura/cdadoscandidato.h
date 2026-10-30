#pragma once

#include <optional>
#include <string>

#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// The sex of a candidate, as CDadosCandidato's constructors spell it. Recovered: the type's name only.
class CSexo {
public:
    enum ESexo : int;
};

// Recovered: the layout, 52 bytes, from the copy CCandidatura's constructor makes of it (target fn 5660): the two
// strings at +0 and +12, the optional string at +24 (flag +36), 8 bytes at +40 that the records' ESexo and ESituacao
// fill, and the substitute's order at +48. The constructors' records (cdadoscandidato.cpp:35 and :65) are loaded by
// 11450, which holds them, so they are not declared here. The member names and GetNomeUrna's and GetOrdem's are chosen. The
// order is a signed char, where the records' parameter is a uebyte: 5660 loads it with i32.load8_s and formats it as an
// int, which std::format does for a signed char and does not for a char or a uebyte.
class CDadosCandidato {
public:
    enum ESituacao : int;

    const std::string& GetNomeUrna() const { return m_nomeUrna; }
    signed char GetOrdem() const { return m_ordem; }

private:
    std::string m_nome;
    std::string m_nomeUrna;
    std::optional<std::string> m_nomeSocial;
    CSexo::ESexo m_sexo;
    ESituacao m_situacao;
    signed char m_ordem;
};

} // namespace comum::md
