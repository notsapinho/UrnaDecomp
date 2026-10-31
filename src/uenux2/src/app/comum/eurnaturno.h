#pragma once

#include <format>

namespace comum {

// The urna's turn, 4 bytes wide. The name is the records' (comum::CAppInfo::IndiceTurno, comum::CPath::GetPathTrab,
// comum::asn::Utils::ConverteTurno, DesconverteTurno). The values are evidence: IndiceTurno (target fn 1553) takes 49 and
// 50 as the indices 0 and 1, and reads 51 as "the turn of the load"; ConverteTurno and DesconverteTurno (target fns 11401,
// 11402, which hold them inlined) take the characters '0' to '2', one per ModuloTiposEleitorais::Turno. The enumerators'
// names, the character spelling, the comum:: scope and this path are chosen.
enum EUrnaTurno {
    SEM_TURNO = '0',
    TURNO_1 = '1',
    TURNO_2 = '2',
    TURNO_ATUAL = '3',
};

} // namespace comum

// IndiceTurno's message passes the turn through table slot 474, the handle of target fn 9868. The base is chosen.
template <>
struct std::formatter<comum::EUrnaTurno> : std::formatter<unsigned int> {
    template <typename FormatContext>
    auto format(comum::EUrnaTurno valor, FormatContext& contexto) const
    {
        return std::formatter<unsigned int>::format(static_cast<unsigned int>(valor), contexto);
    }
};
