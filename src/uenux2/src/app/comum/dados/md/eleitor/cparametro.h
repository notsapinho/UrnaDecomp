#pragma once

#include <vector>

#include "app/comum/dados/md/cindexer.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// What a voter's ciphered biometry is read under: the records name the type (md::CParametro, the parameter of
// comum::asn::IConversorBiometriaASN's Desconverte and of legravaentidade.h's LeEntidadeBiometria). Recovered: the
// layout, 36 bytes. comum::CEleitorDetalhe::GetBiometria (target fn 1937) builds one from the voter's identity of its
// type (fn 708's result: the text at +0 and the type at +12, copied), the byte vector of md::CEleitor at +16 (copied)
// and CEleitor::GetOffsetBiometria's CIndexer at +28 (one i64 copy), and reads the offset and the length there for the
// seek and the read; comum::asn::CConversorBiometriaEleitorCifrada's slot 3 (fn 11419) reads the vector at +16 and the
// text at +0. The constructor's form (inline, by const reference) gives those copies; its being a constructor, the
// accessors, every name and this header's path are chosen: no record names the file.
class CParametro {
public:
    CParametro(const CEleitorIdentidade& identidade, const std::vector<uebyte>& biometria, const CIndexer& offset)
        : m_identidade(identidade), m_biometria(biometria), m_offset(offset)
    {
    }

    const CEleitorIdentidade& GetIdentidade() const { return m_identidade; }
    const std::vector<uebyte>& GetBiometria() const { return m_biometria; }
    const CIndexer& GetOffset() const { return m_offset; }

private:
    CEleitorIdentidade m_identidade;
    std::vector<uebyte> m_biometria;
    CIndexer m_offset;
};

} // namespace comum::md
