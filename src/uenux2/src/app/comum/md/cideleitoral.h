#pragma once

#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout only, 8 bytes, from comum::asn::CConversorCabecalhoPacote::DoDesconverte (target fn 11437),
// which builds one through fn 1081, which stores its first argument at +0 and its second at +4, with the entity's
// identifier first and 1, 2 or 3 second, one per alternative of ModuloTiposEleitorais::IDEleitoral. fn 1081 is matched as
// comum::md::estadoaplicacao::CAjusteDataHora's constructor; that it is this class's too, one body binaryen keeps for
// both, is a reading. The three static members are the records' (cideleitoral.cpp:21, 29 and 37), declared and not
// written; the constructor, the member names and the type of the second word are chosen. The path is chosen, beside the
// records' cideleitoral.cpp.
class CIDEleitoral {
public:
    static CIDEleitoral CriaProcessoEleitoral(uedword id);
    static CIDEleitoral CriaPleito(uedword id);
    static CIDEleitoral CriaEleicao(uedword id);

private:
    CIDEleitoral(uedword id, int tipo);

    uedword m_id;
    int m_tipo;
};

} // namespace comum::md
