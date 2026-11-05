#pragma once

#include <optional>
#include <string>
#include <vector>

#include "api/hash/chasharquivo.h"
#include "app/comum/eurnafase.h"
#include "app/comum/md/ccabecalhoentidade.h"
#include "app/comum/md/cidentificacaosecao.h"
#include "app/comum/md/cidentificacaournacontingencia.h"

namespace comum::md {

// Recovered: the head of the layout, from ValidaCriacao (target fn 5855, records centidadehashes.cpp:59 and :62), which
// reads the phase at +20 and a string at +24 whose length must be 2 ("UF inválida"). The 20 bytes before it are taken
// as the entity's header, as in CEnvelopeGenerico, whose ValidaCriacao tests the phase at +20 the same way; the members
// follow ModuloHashes::EntidadeHashes's first fields (cabecalho, fase, siglaUF), and their types past the widths and
// names are chosen, and that ValidaCriacao is private. The members after +36 are read from
// comum::asn::CConversorEntidadeHashes::DoConverte (target fn 10266), which reads every member: a
// std::optional<CIdentificacaoSecao> at +36 (the municipality at +40, the zone at +44, the place at +48 and the section
// at +52, 32- and 16-bit loads, the engaged byte at +56, tested == 1), a std::optional<CIdentificacaoUrnaContingencia>
// at +60 (the municipality at +64, the zone at +68, the engaged byte at +72), the UENUX version's string at +76 and a
// std::vector<api::hash::CHashArquivo> at +88 (24-byte elements). That the two identifications are those classes (the
// type at +0 of each, which 10266 does not read, fills their 20 and 12 bytes) is a reading of the offsets: the hashes'
// writer, comum::CGravadorHashes, holds one or the other of those two classes (cgravadorhashes.h), and its
// GravaResultado (fn 11620, written) builds this entity. The getters' names and forms (GetFase by value, as 10266
// copies the phase into a temporary for Utils::ConverteFase; the rest by reference) and the members' names are chosen.
// The two constructors, one per identification, are written in centidadehashes.cpp, which binaryen inlines into fn
// 11620, their one caller (a choice: written in the class, for clang to inline, they were not measured): each copies
// the header, stores the phase, copies the UF's string, fills its own identification and leaves the other one empty,
// copies the version's string and the hashes, and calls ValidaCriacao. Their parameters' forms (references, the phase
// by value) are the copies'; their order follows the members', a choice, as is their being two constructors (one taking
// both optionals was not measured).
class CEntidadeHashes {
public:
    CEntidadeHashes(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, const std::string& siglaUF,
        const CIdentificacaoSecao& identificacaoSecao, const std::string& versaoUENUX,
        const std::vector<api::hash::CHashArquivo>& hashesArquivos);
    CEntidadeHashes(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, const std::string& siglaUF,
        const CIdentificacaoUrnaContingencia& identificacaoContingencia, const std::string& versaoUENUX,
        const std::vector<api::hash::CHashArquivo>& hashesArquivos);

    const CCabecalhoEntidade& GetCabecalho() const { return m_cabecalho; }
    EUrnaFase GetFase() const { return m_fase; }
    const std::string& GetSiglaUF() const { return m_siglaUF; }
    bool TemIdentificacaoSecao() const { return m_identificacaoSecao.has_value(); }
    const CIdentificacaoSecao& GetIdentificacaoSecao() const { return *m_identificacaoSecao; }
    bool TemIdentificacaoContingencia() const { return m_identificacaoContingencia.has_value(); }
    const CIdentificacaoUrnaContingencia& GetIdentificacaoContingencia() const { return *m_identificacaoContingencia; }
    const std::string& GetVersaoUENUX() const { return m_versaoUENUX; }
    const std::vector<api::hash::CHashArquivo>& GetHashesArquivos() const { return m_hashesArquivos; }

private:
    void ValidaCriacao() const;

    CCabecalhoEntidade m_cabecalho;
    EUrnaFase m_fase;
    std::string m_siglaUF;
    std::optional<CIdentificacaoSecao> m_identificacaoSecao;
    std::optional<CIdentificacaoUrnaContingencia> m_identificacaoContingencia;
    std::string m_versaoUENUX;
    std::vector<api::hash::CHashArquivo> m_hashesArquivos;
};

} // namespace comum::md
