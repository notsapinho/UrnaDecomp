#pragma once

namespace comum {

// The records of comum::asn::Utils::ConverteTurno and DesconverteTurno spell the type. Its values are evidence: the
// characters '0' to '2' (target fns 11401, 11402, which hold those two inlined), one per ModuloTiposEleitorais::Turno.
// The enumerators' names are chosen, from the generated ones; the header's path too, beside eurnafase.h.
enum EUrnaTurno {
    eUrnaSemTurno = '0',
    eUrnaTurno1 = '1',
    eUrnaTurno2 = '2',
};

} // namespace comum
