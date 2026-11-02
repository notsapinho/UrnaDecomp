#pragma once

#include <optional>
#include <string>

#include "app/comum/eurnafase.h"
#include "app/comum/md/cideleitoral.h"
#include "app/comum/md/cidentificacaourna.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// The records of the constructor spell these; nothing here reads a value of either.
enum ESistemaJE : int;

namespace md {

enum ETipoPacote : int;

// Recovered: the layout, 40 bytes, which the constructor stores at +4 of the class (fn 11437, where binaryen inlined
// it). fn 11437 builds one in its frame: a CIDEleitoral at +0, the phase at +8 (Utils::DesconverteFase's result),
// then the entity's three optional fields in their order, each with its engaged flag: a string at +12 (flag at +24), a
// 32-bit word at +28 (flag at +32) and a 16-bit word at +36 (flag at +38). The elements' copy (fn 5669) and the vector's
// destroy (fn 3863) read the same layout: the copy moves +0 to +12 as words, the string only when its flag is 1, then
// the 11 bytes from +28; the destroy frees the string only when its flag is 1. The three getters are the records'
// (cidpacote.cpp:67, 75 and 83, whose return types say which optional is which), declared and not written there. The
// member names are chosen.
class CIDPacote {
public:
    std::string UF() const;
    TMunicipioID Municipio() const;
    TZonaID Zona() const;

private:
    CIDEleitoral m_idEleitoral;
    EUrnaFase m_fase;
    std::optional<std::string> m_uf;
    std::optional<TMunicipioID> m_municipio;
    std::optional<TZonaID> m_zona;
};

// The layout, 72 bytes, from the constructor as fn 11437 holds it (records ccabecalhopacote.cpp:33, :36, :39): the type
// at +0, the identifier at +4, the two strings at +44 and +56, the system at +68. The constructor is declared here and
// not written. The member names are not in the target.
class CCabecalhoPacote {
public:
    CCabecalhoPacote(const ETipoPacote tipo, const CIDPacote& id, const std::string& primeiro, const std::string& segundo,
        const ESistemaJE sistema);

private:
    ETipoPacote m_tipo;
    CIDPacote m_id;
    std::string m_primeiro;
    std::string m_segundo;
    ESistemaJE m_sistema;
};

} // namespace md

} // namespace comum
