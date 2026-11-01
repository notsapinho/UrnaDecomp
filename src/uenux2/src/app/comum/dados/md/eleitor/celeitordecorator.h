#pragma once

#include <string>
#include <vector>

#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "ecourna/app/dados/tiposbasicos.hpp"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// A voter's register data. Recovered: the layout, 108 bytes, from its destructor (fn 379): the identities at +8, a
// std::vector of 16-byte CEleitorIdentidade (fn 708), strings at +24, +36, +52 and +68 and a vector of a trivial element
// at +80; fn 5764 reads a type at +104, and CEleitorDetalhe's optional follows at +108. The words between them have no
// reader here but +20's (NecessitaAudio, below), nothing may build one, and the members' names and the vector's element
// type are chosen.
// CEleitores's members read more of it: fns 11528 and 11527 format the 32-bit word at +0 as an int and the 16-bit one at
// +4 as unsigned, 11526 tests the word at +48 against 0, 11529 reads the strings at +24 and +36, and 5765 passes the word
// at +104 to GetIdentidadePorTipo, so it is an identifier's type. Fn 946, which CEleitores::LoadEleitorDetalhe (5764)
// calls before it copies +104 apart, copies 32 bits at +0, 16 at +4 and nothing at +6, which is padding. The widths and
// signedness are the bodies'; the accessors, their names, the int at +48 and m_tipoIdentificador's name are chosen. A
// reading, not split here: 946's 104 bytes would be an object of their own (md::CEleitor, which has records in
// celeitor.cpp), and nothing written copies one.
class CEleitorDecorator {
public:
    CEleitorIdentidade GetIdentidadePorTipo(ecourna::app::dados::ETipoIdentificadorEleitor tipo) const;

    int GetSequencial() const { return m_sequencial; }
    ueword GetSecao() const { return m_secao; }
    const std::vector<CEleitorIdentidade>& GetIdentidades() const { return m_identidades; }
    const std::string& GetNome() const { return m_nome; }
    const std::string& GetNomeUrna() const { return m_nomeUrna; }
    bool IsTTE() const { return m_tte != 0; }
    ecourna::app::dados::ETipoIdentificadorEleitor GetTipoIdentificador() const { return m_tipoIdentificador; }
    // The word at +20 is the voter's special need: comum::asn::CConversorEntidadeEleitores::ConverteNecessidadeEspecial
    // (record cconversorentidadeeleitores.cpp:38, inlined into fn 11411) maps ModuloEleitores' semNecessidade to 0 and
    // necessitaAudio to 1 (its br_table), and vota::impl::CInformacaoThreadOperador's slot 5 (fn 10579) reads +20 and
    // compares it with 1 (evidence). The member's and the accessor's names are chosen, and so is comparing here: an
    // accessor that returns the word, compared with 1 by its caller, gives the same object.
    bool NecessitaAudio() const { return m_necessidadeEspecial == 1; }

private:
    int m_sequencial;
    ueword m_secao;
    std::vector<CEleitorIdentidade> m_identidades;
    uedword m_necessidadeEspecial;
    std::string m_nome;
    std::string m_nomeUrna;
    int m_tte;
    std::string m_nomeSocial;
    uedword m_naoRecuperado4;
    std::string m_nomeMae;
    std::vector<uedword> m_impedimentos;
    uedword m_naoRecuperado5[3];
    ecourna::app::dados::ETipoIdentificadorEleitor m_tipoIdentificador;
};

} // namespace comum::md
