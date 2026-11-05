#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "app/comum/dados/md/cindexer.h"
#include "app/comum/dados/md/municipiozona/cmunicipio.h"

namespace comum {

namespace md {

// One entry of md::CIndicesFotos (record cindicesfotos.cpp:30, const CIndiceFoto &comum::md::CIndicesFotos::at(size_t)
// const). Its layout is CVisitanteFoto's vector element: a std::string followed by where the photo sits in the
// candidates' photo file, its position and length (20 bytes). That the visitor's element is this class is presumed, not
// read: target fn 5659, which builds such a 20-byte object from a std::string and the pair (called by
// CVisitanteFoto::visit 11442 and CIndexadorFotos 11441), is this constructor by that shape alone. The pair is a
// md::CIndexer: comum::CFotos::GetImagem (fn 3755) seeks to its first word and reads as many bytes as its second through
// legravaentidade.h's LeEntidadeEm, whose records (:92, :98) spell that parameter `const comum::md::CIndexer &`, with no
// conversion between (a reading; an 8-byte pair of another name, converted, gives the same code). It took the name
// SIndiceFoto before, from the record cfotos.cpp:39, which 3755 shows to name the photo map's whole value (cfotos.h). The
// member names are not recovered; fn 11441 passes each entry's two parts back to the constructor, which GetCodigo and
// GetIndexer (names chosen) give it. CIndexer's inline constructor gives visit's one i64 store after its sequencer's,
// as the pair's own constructor did (unit 36's fragment has that measurement).
class CIndiceFoto {
public:
    CIndiceFoto(const std::string& codigo, const CIndexer& indexer);

    const std::string& GetCodigo() const { return m_codigo; }
    const CIndexer& GetIndexer() const { return m_indexer; }

private:
    std::string m_codigo;
    CIndexer m_indexer;
};

// The photos' index of one municipality: what comum::asn::CIndexadorFotos::DoDesconverte (target fn 11441) builds, the
// municipality of the entity's abrangencia at +0 and a copy of the entries at +4. The record of at (cindicesfotos.cpp:30,
// inlined into fn 7787) names the class and that member. The constructor's form, defined in cindicesfotos.cpp, and the
// member names are chosen.
class CIndicesFotos {
public:
    CIndicesFotos(TMunicipioID municipio, const std::vector<CIndiceFoto>& indices);

    const CIndiceFoto& at(size_t indice) const;

private:
    TMunicipioID m_municipio;
    std::vector<CIndiceFoto> m_indices;
};

} // namespace md
} // namespace comum
