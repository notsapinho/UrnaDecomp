#pragma once

#include <cstddef>
#include <map>
#include <string>

#include "app/comum/dados/md/cindexer.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "asn1/asn1.h"

namespace comum::asn {

// RTTI: an si_class of ASN1::IAbstractVisitor, vtable [5698, 11408, 11407]; the path is the record's
// (cvisitanteeleitor.cpp:91, visit). fn 11523 builds it as a std::shared_ptr<CVisitanteEleitor>(new CVisitanteEleitor),
// and the block's __on_zero_shared is the shared call through the vtable (fn 172), so the class is not final.
// Recovered: the layout, 64 bytes, from that new (64 bytes, all zeroed before the vptr store: no user-provided
// constructor), the destructor (fn 5698: the map at +52, then the strings at +40, +28 and +16) and visit (fn 11407:
// the three identifiers it copies by the CHOICE's selection, the two size_t it stores at +8 and +12 as one word, and
// the map it fills from them through fn 3728, a std::map<md::CEleitorIdentidade, 8 bytes>::insert). The destructor is
// out of line: its D0 (fn 11408) calls the D2 and frees this. md::CIndexer for the two words at +8 and the map's value
// is a reading: it is the biometry offset md::CEleitor holds (celeitor.h), and visit stores these words when the decoder
// reaches the voter's biometria. Chosen: the members' names, and the word at +4, which fn 11523 sets to 1 and neither
// member here reads (its type is the plainest of its width, and its name says it is not recovered).
class CVisitanteEleitor : public ASN1::IAbstractVisitor {
public:
    ~CVisitanteEleitor() override;

    EVisitorResult visit(int index, const std::string& path, ASN1::AbstractData& data, size_t position,
                         size_t length) override;

private:
    int m_naoRecuperado4;
    md::CIndexer m_biometria;
    std::string m_inscricao;
    std::string m_cpf;
    std::string m_identificacaoLivre;
    std::map<md::CEleitorIdentidade, md::CIndexer> m_identidades;
};

} // namespace comum::asn
