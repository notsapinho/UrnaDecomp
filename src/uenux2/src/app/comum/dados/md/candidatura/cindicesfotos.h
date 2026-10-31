#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "app/comum/dados/md/municipiozona/cmunicipio.h"

namespace comum {

// Where one photo sits in the candidates' photo file. The record cfotos.cpp:39 names the type,
// md::CFotoCandidato comum::GetFotoPara(const std::string &, const SIndiceFoto &), spelled unqualified inside
// namespace comum; its two members are the position and the length that CVisitanteFoto::visit receives (size_t in
// visit's record) and stores side by side (target fn 11442).
struct SIndiceFoto {
    size_t posicao;
    size_t tamanho;
};

namespace md {

// One entry of md::CIndicesFotos (record cindicesfotos.cpp:30, const CIndiceFoto &comum::md::CIndicesFotos::at(size_t)
// const). Its layout is CVisitanteFoto's vector element: a std::string followed by an SIndiceFoto, 20 bytes. That the
// visitor's element is this class is presumed, not read: target fn 5659, which builds such a 20-byte object from a
// std::string and an SIndiceFoto (called by CVisitanteFoto::visit 11442 and CIndexadorFotos 11441), is this constructor
// by that shape alone. The member names are not recovered; fn 11441 passes each entry's two parts back to the
// constructor, which GetCodigo and GetIndice (names chosen) give it.
class CIndiceFoto {
public:
    CIndiceFoto(const std::string& codigo, const SIndiceFoto& indice);

    const std::string& GetCodigo() const { return m_codigo; }
    const SIndiceFoto& GetIndice() const { return m_indice; }

private:
    std::string m_codigo;
    SIndiceFoto m_indice;
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
