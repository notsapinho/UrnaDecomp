#pragma once

#include <string>

#include "ecourna/api/uetypes.hpp"

namespace comum {

// The records of the constructor spell these; nothing here reads a value of either.
enum ESistemaJE : int;

namespace md {

enum ETipoPacote : int;

// 40 bytes: the constructor stores them at +4 of the class (fn 11437, where binaryen inlined it). Only the size is
// recovered here; the class's file, cidpacote.cpp, has records and is not written.
class CIDPacote {
    alignas(4) unsigned char m_bytes[40];
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
