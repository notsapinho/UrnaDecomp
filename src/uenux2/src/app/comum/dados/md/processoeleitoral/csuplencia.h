#pragma once

#include "app/comum/dados/md/processoeleitoral/cnomescargo.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 52 bytes (the stride of CDetalheCandidato::GetSuplente, fn 1545), and the names at +4 (fn
// 3715 copies four strings from there). RTTI names the class, as the data of IConversorASN<ModuloEleicao::Suplencias,
// comum::md::CSuplencia>; no record names its file, so this path is chosen. Bytes +0 and +1 are ModuloEleicao::Suplencias'
// other fields: fn 12272 tests +1 against 1, as a bool reads (docs/reference/facts/reading.md R14). The members' names are chosen.
// The constructor is what comum::asn::CConversorSuplencia::DoDesconverte (fn 11359) holds: the order at +0 and the
// photo flag at +1 from the entity's ordem and temFoto, and a copy of the names. It is defined out of line, in
// csuplencia.cpp, and binaryen inlined it into 11359, its one caller: the copy of the last name and the destruction of
// the caller's temporary stay two tests of one byte there, which clang joins when it inlines a constructor defined in
// the class (measured). The file's path and the parameters' order are chosen.
class CSuplencia {
public:
    CSuplencia(uebyte ordem, bool temFoto, const CNomesCargo& nomes);

    const CNomesCargo& GetNomes() const { return m_nomes; }

private:
    uebyte m_ordem;
    bool m_temFoto;
    CNomesCargo m_nomes;
};

} // namespace comum::md
