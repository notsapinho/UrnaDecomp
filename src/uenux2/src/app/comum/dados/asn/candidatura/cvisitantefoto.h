#pragma once

#include <string>
#include <vector>

#include "app/comum/dados/md/candidatura/cindicesfotos.h"
#include "asn1/asn1.h"

namespace comum::asn {

// The visitor the partial BER decoder calls back while it reads ModuloFotosCandidatos::EntidadeFotosCandidatos
// (comum::asn::IConversorParcialASN<ModuloFotosCandidatos::EntidadeFotosCandidatos, md::CIndicesFotos, CVisitanteFoto>,
// whose Desconverte, inlined into comum::CCandidaturas::LoadFromFile 7787, creates it with new, 28 bytes). RTTI: an
// si_class of ASN1::IAbstractVisitor; vtable @1562436 [~CVisitanteFoto D2 5709, D0 11443, visit 11442].
// visit's records (cvisitantefoto.cpp:40-63) spell its declaration.
class CVisitanteFoto : public ASN1::IAbstractVisitor {
public:
    virtual ~CVisitanteFoto();

    virtual EVisitorResult visit(int indice, const std::string& caminho, ASN1::AbstractData& dado, size_t posicao,
                                 size_t tamanho) override;

    // What comum::asn::CIndexadorFotos::DoDesconverte (target fn 11441) reads at +16; the name is chosen.
    const std::vector<md::CIndiceFoto>& GetIndices() const { return m_indices; }

private:
    // +4: 0 or 1, which of the two fields of a photo visit expects next (its throws: "Sequenciador com valor errado ...")
    int m_sequenciador;
    // +8: position and length of the photo being read
    SIndiceFoto m_indice;
    // +16: one entry per photo read (element type presumed, cindicesfotos.h)
    std::vector<md::CIndiceFoto> m_indices;
};

} // namespace comum::asn
