#pragma once

#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Where an entity sits in an indexed file: the records name the type (comum::md::CIndexer, in
// CEleitor::GetOffsetBiometria's, celeitor.cpp:79, and in legravaentidade.h's LeEntidadeEm and LeEntidadeBiometria).
// Recovered: 8 bytes aligned to 4 (CEleitor's constructor, target fn 5668, stores it as one i64 at +92, and the flag of
// the std::optional that holds it sits at +100). Its members, their names and this header's path are chosen: no record
// names the file.
// The constructors: comum::asn::CVisitanteEleitor::visit (target fn 11407) stores the position and length the decoder
// passes it as one i64 at +8 and keeps that copy as the map's value. Through the constructor visit gives that store; a
// std::pair<size_t, size_t> in its place gives two i32 stores (measured in the whole link: 51 over 594 rows against 26
// over 582, operand-only). That this is the type visit stores, rather than another of the same two words, is a reading
// from CEleitor's member. Their being inline, the parameters and the defaulted default constructor are chosen.
class CIndexer {
public:
    CIndexer() = default;
    CIndexer(uedword offset, uedword tamanho) : m_offset(offset), m_tamanho(tamanho) {}

    // legravaentidade.h's LeEntidadeBiometria seeks to the first word and reads as many bytes as the second (fn 1937,
    // which holds it inlined); the accessors and their names are chosen.
    uedword GetOffset() const { return m_offset; }
    uedword GetTamanho() const { return m_tamanho; }

private:
    uedword m_offset;
    uedword m_tamanho;
};

} // namespace comum::md
