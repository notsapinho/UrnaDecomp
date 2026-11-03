#pragma once

#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 8 bytes, from comum::asn::CConversorCabecalhoPacote::DoDesconverte (target fn 11437), which
// builds one through fn 1081, which stores its first argument at +0 and its second at +4, with the entity's
// identifier first and 1, 2 or 3 second, one per alternative of ModuloTiposEleitorais::IDEleitoral. fn 1081 is one body
// binaryen keeps for several two-word constructors (comum::md::estadoaplicacao::CAjusteDataHora's among them); this
// class's, out of line in cidpacote.cpp (fragment 273 says why), is byte-identical to it, and its match line names
// this one now, the first in our link. The three static members are the records' (cideleitoral.cpp:21, 29 and 37);
// fn 11438 reads the two words back (Utils::ConverteIdPacote, which turns the kind 1, 2 or 3 into the CHOICE's
// selection 0, 1 or 2). The constructor's parameters, the getters, ETipo and the member names are chosen. The path is
// chosen, beside the records' cideleitoral.cpp.
class CIDEleitoral {
public:
    enum ETipo {
        TIPO_PROCESSO_ELEITORAL = 1,
        TIPO_PLEITO,
        TIPO_ELEICAO,
    };

    static CIDEleitoral CriaProcessoEleitoral(uedword id);
    static CIDEleitoral CriaPleito(uedword id);
    static CIDEleitoral CriaEleicao(uedword id);

    uedword GetId() const { return m_id; }
    ETipo GetTipo() const { return m_tipo; }

private:
    CIDEleitoral(uedword id, ETipo tipo);

    uedword m_id;
    ETipo m_tipo;
};

} // namespace comum::md
