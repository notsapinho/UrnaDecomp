#pragma once

#include <cstddef>
#include <map>
#include <memory>
#include <string>

#include "app/comum/dados/md/cindexer.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "asn1/asn1.h"

namespace comum::asn {

// RTTI: an si_class of ASN1::IAbstractVisitor, vtable [5698, 11408, 11407]; the path is the record's
// (cvisitanteeleitor.cpp:91, visit). fn 11523 builds it as a std::shared_ptr<CVisitanteEleitor>(new CVisitanteEleitor),
// and the block's __on_zero_shared is the shared call through the vtable (fn 172), so the class is not final.
// Recovered: the layout, 64 bytes, from that new (64 bytes) and the constructor 11523 holds after it, the destructor
// (fn 5698: the map at +52, then the strings at +40, +28 and +16) and visit (fn 11407:
// the three identifiers it copies by the CHOICE's selection, the two size_t it stores at +8 and +12 as one word, and
// the map it fills from them through fn 3728, a std::map<md::CEleitorIdentidade, 8 bytes>::insert). The destructor is
// out of line: its D0 (fn 11408) calls the D2 and frees this. md::CIndexer for the two words at +8 and the map's value
// is a reading: it is the biometry offset md::CEleitor holds (celeitor.h), and visit stores these words when the decoder
// reaches the voter's biometria. Chosen: the members' names, and the word at +4, which Prepara sets to 1 and neither
// member here reads (its type is the plainest of its width, and its name says it is not recovered).
// The constructor is user-provided and out of line in cvisitanteeleitor.cpp, with no target function of its own (11523
// holds it; binaryen inlined its one call): after the new, 11523 zeroes +56 and then +4 to +52 with 4-byte-aligned
// i64 stores, stores the vptr, then the map's begin at +52. Measured on objects of this TU's flags: that constructor
// compiled alone gives exactly that order; value-initialization with no user-provided constructor clears from +0 at
// operator new's alignment before the vptr (docs/reference/facts/codegen.md C9), and the same constructor inline puts
// the vptr store between the +56 store and the others. Its initializers are chosen: zeroing the two scalars, or every
// member, or naming the base's constructor too, give the same object.
class CVisitanteEleitor : public ASN1::IAbstractVisitor {
public:
    CVisitanteEleitor();
    ~CVisitanteEleitor() override;

    EVisitorResult visit(int index, const std::string& path, ASN1::AbstractData& data, size_t position,
                         size_t length) override;

    // What comum::asn::IConversorParcialASN::Desconverte does with the visitor before the read (target fn 11523 holds
    // it inlined there, at the head of Desconverte's frame): the word at +4 set to 1, then the decoder's list, the
    // paths of the voters' identifications and of their biometria, each paired with this visitor (an initializer list:
    // both strings built, then copied with the shared_ptr into the vector's 40 bytes). The two steps and their order
    // are the target's; that they are one static member of this class, its name and its parameter are chosen. That
    // the step is the visitor class's is a reading: the photos' instance in fn 7787 stores 0 at its visitor's +4 and
    // builds its list with two push_backs, so Desconverte's template takes it from its TVisitor.
    static ASN1::TVectorAbstractVisitor Prepara(const std::shared_ptr<CVisitanteEleitor>& visitante)
    {
        visitante->m_naoRecuperado4 = 1;
        return {{"EntidadeEleitores.eleitores.eleitor.identificacaoEleitor.OF", visitante},
                {"EntidadeEleitores.eleitores.eleitor.biometria", visitante}};
    }

private:
    int m_naoRecuperado4;
    md::CIndexer m_biometria;
    std::string m_inscricao;
    std::string m_cpf;
    std::string m_identificacaoLivre;
    std::map<md::CEleitorIdentidade, md::CIndexer> m_identidades;
};

} // namespace comum::asn
