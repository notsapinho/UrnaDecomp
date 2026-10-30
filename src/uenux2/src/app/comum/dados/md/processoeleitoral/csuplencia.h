#pragma once

#include "app/comum/dados/md/processoeleitoral/cnomescargo.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 52 bytes (the stride of CDetalheCandidato::GetSuplente, fn 1545), and the names at +4 (fn
// 3715 copies four strings from there). RTTI names the class, as the data of IConversorASN<ModuloEleicao::Suplencias,
// comum::md::CSuplencia>; no record names its file, so this path is chosen. Bytes +0 and +1 are ModuloEleicao::Suplencias'
// other fields: fn 12272 tests +1 against 1, as a bool reads (docs/reference/facts/reading.md R14). The members' names are chosen.
class CSuplencia {
public:
    const CNomesCargo& GetNomes() const { return m_nomes; }

private:
    uebyte m_ordem;
    bool m_temFoto;
    CNomesCargo m_nomes;
};

} // namespace comum::md
