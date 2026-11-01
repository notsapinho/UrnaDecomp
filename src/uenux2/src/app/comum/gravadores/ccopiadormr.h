#pragma once

#include <string>

#include "app/comum/gravadores/iresultado.h"

namespace comum {

// RTTI: comum::CCopiadorMR, a class with no base, and CCopiadorWSQMR, an si_class of it; both vtables are [11638, 5872,
// 5874, 5873]. fn 12134 (records of ccopiaresultadoparamr.cpp) builds them with std::make_shared, 16 bytes each.
// Recovered: the layout and the constructors. CCopiadorMR's constructor (fn 1276) stores the vptr and builds the string
// at +4 with CGravadorUtil::DeterminaNomeArquivo (fn 3798) from its five arguments, which it passes on unchanged; fn
// 12134 calls it nine times with nine extensions, and CCopiadorWSQMR's (fn 3827, which calls it and stores its own
// vptr) three times. The base-object destructor (fn 11638, slot 0, a thunk into binaryen's merged body fn 1723) stores
// the vptr and frees the string, and the deleting one (fn 5872, slot 1, a thunk into fn 1722) holds the same body and
// frees `this`: a destructor with the inline hint or a cheap one defined in the class (docs/reference/facts/reading.md
// R5). It is declared, since a class with no base has a virtual destructor only when it says so; `= default` in the
// class gives both rows (they match), chosen; the `inline` form was not measured. CCopiadorWSQMR adds no member and
// overrides nothing (its slots are this class's): its destructor is implicit. Slots 2 and 3 (fns 5874, 5873) are out
// of line, so Slot2 is the key function; neither is reconstructed, and no evidence names them: they are named after
// their slot. Not final: the blocks' __on_zero_shared go through the vtable (fn 411).
// The directory is placement rule 2's reading: no record names either class, and the vtables and constructors lie in
// link order between gravadores/cassinador.cpp and gravadores/md/cdependenciascontratos.cpp (data, use bands).
// The two constructors are in two files, ccopiadormr.cpp and ccopiadorwsqmr.cpp: in one, clang inlines 1276 into 3827,
// which the target does not (unit 160's fragment has the measurement). Chosen: the file names, that this header
// declares both classes, the parameters' types (those of DeterminaNomeArquivo, which takes them) and the member's name.
class CCopiadorMR {
public:
    CCopiadorMR(TMunicipioID municipio, TZonaID zona, TSecaoID secao, char fase, EExtensaoArquivoResultado extensao);
    virtual ~CCopiadorMR() = default;

    virtual void Slot2();
    virtual void Slot3();

private:
    std::string m_nomeArquivo;
};

class CCopiadorWSQMR : public CCopiadorMR {
public:
    CCopiadorWSQMR(TMunicipioID municipio, TZonaID zona, TSecaoID secao, char fase, EExtensaoArquivoResultado extensao);
};

} // namespace comum
