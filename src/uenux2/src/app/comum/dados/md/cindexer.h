#pragma once

#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Where an entity sits in an indexed file: the records name the type (comum::md::CIndexer, in
// CEleitor::GetOffsetBiometria's, celeitor.cpp:79, and in legravaentidade.h's LeEntidadeEm and LeEntidadeBiometria).
// Recovered: 8 bytes aligned to 4 (CEleitor's constructor, target fn 5668, stores it as one i64 at +92, and the flag of
// the std::optional that holds it sits at +100). Its members, their names and this header's path are chosen: no record
// names the file.
class CIndexer {
private:
    uedword m_offset;
    uedword m_tamanho;
};

} // namespace comum::md
