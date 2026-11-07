#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "app/comum/dados/md/candidatura/cdadoscandidato.h"

namespace comum {

// Data sources of a candidature's texts and photo (RTTI, in the arguments of api::CDataText and api::CDataImage; fns
// 4185 and 4129 build those with std::make_shared). Recovered: the names only. A source is callable. The path is
// chosen, beside ccandidaturas.h.

// The number of the current candidacy, zero-padded to its post's digit count. fn 12742,
// CDataText<CCandidaturasDSNumero>::GetText, holds the call operator inlined: it builds the literal
// "CCandidaturasDSNumero" for GetCandidaturaAtual, reads the post's digit count from CConfiguracaoEleicao (fns 187 and
// 861, the byte at +12 of the post) and only then the candidacy's 32-bit number at +4, and formats both with "{:0{}}"
// (two unsigned arguments, 198). The operator is in ccandidaturasds.cpp, a chosen file
// (src/units/180-uenux2-ccandidaturasds.mk). The class holds nothing the bodies read.
class CCandidaturasDSNumero {
public:
    std::string operator()() const;
};

// The name on the ballot of the current candidacy's holder or of one of its substitutes. fn 5807, the call operator,
// builds the literal "CCandidaturasDSNome" for GetCandidaturaAtual, reads a byte of its object as the substitute's order
// (0, the holder) and copies the string at +12 of that candidate (md::CDadosCandidato::GetNomeUrna), as
// CCandidaturasDSSexo's does for its sex (fn 5806): the member is that byte. The member's name and type, the constructor
// and its being explicit are chosen, as CCandidaturasDSSexo's are.
class CCandidaturasDSNome {
public:
    explicit CCandidaturasDSNome(uebyte suplente) : m_suplente(suplente) {}

    std::string operator()() const;

private:
    uebyte m_suplente;
};

// The photo of the current candidacy's holder or of one of its substitutes. fn 4129 (vota's adicionaImagem over it,
// app/vota/eleitor/comum/ctelasvota.cpp) stores a byte of its object beside CDataImage<CCandidaturasDSFoto>'s vptr, the
// order its callers pass (fn 4184 passes 0, the holder; fn 4181 passes its own parameter): the member is that byte, as
// CCandidaturasDSNome's is. The member's name and type, the constructor and its being explicit are chosen, as
// CCandidaturasDSNome's are. The call operator is in ccandidaturas.cpp; CDataImage<CCandidaturasDSFoto>::GetData
// (fn 12641) holds it inlined (src/units/378-uenux2-ctelasvota-criatela.mk says what it reads).
class CCandidaturasDSFoto {
public:
    explicit CCandidaturasDSFoto(uebyte suplente) : m_suplente(suplente) {}

    std::vector<uint8_t> operator()() const;

private:
    uebyte m_suplente;
};

// The sex of the current candidacy's holder or of one of its substitutes. fn 5806 builds the literal
// "CCandidaturasDSSexo" for GetCandidaturaAtual and reads a byte of its object as the substitute's order (0, the
// holder); fn 2268 builds the object from that order. No RTTI names the class: its name is the literal's, chosen, as
// fn 5807 builds "CCandidaturasDSNome", the name of the class whose CDataText (fn 12649) calls it. The member, the
// constructor and the call operator's form are chosen too. The call operator is in ccandidaturas.cpp, a chosen file
// (src/units/89-uenux2-clocal.mk).
class CCandidaturasDSSexo {
public:
    explicit CCandidaturasDSSexo(uebyte suplente) : m_suplente(suplente) {}

    md::CSexo::ESexo operator()() const;

private:
    uebyte m_suplente;
};

} // namespace comum
