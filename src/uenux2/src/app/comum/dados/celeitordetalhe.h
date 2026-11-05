#pragma once

#include <optional>
#include <string>

#include "app/comum/dados/md/eleitor/cbiometriaeleitor.h"
#include "app/comum/dados/md/eleitor/celeitordecorator.h"
#include "app/comum/dados/md/eleitor/celeitordinamico.h"
#include "app/comum/dados/md/etipoimpedimento.h"
#include "app/comum/eurnaturno.h"

namespace comum {

class CEleitorDadosHabilitacao;

// Recovered: the layout: a CEleitorDecorator at +0 and a std::optional<CEleitorDinamico> at +108, from what fn 1270
// destroys (its record's constructor, line 49, takes one of each); the byte at +192 ConfereDadosDinamicos (target fn
// 3770) reads is the optional's flag. The record of the constructor (line 49) takes two md::ETipoImpedimento after
// them: GetImpedimento (target fn 3769) reads +200 when the load's turn is TURNO_2 and +196 otherwise, which makes them
// the impediments of the first and the second turn, at +196 and +200 (a reading of that test: nothing else gives the
// members' order). ConfereDadosDinamicos, GetDinamico (fn 1271), MarcaHabilitado, MarcaVotou and GetImpedimento are
// written. MarcaVotou passes its own name to ConfereDadosDinamicos (the literal "MarcaVotou" in target fn 10210, which
// holds it inlined), as GetDinamico and MarcaHabilitado pass theirs: the name is read from that literal.
// Chosen: the members' names, the two accessors, GetDinamico's const and const& result, GetImpedimento's name,
// MarcaHabilitado's parameter type.
// The constructors: CEleitores::LoadEleitorDetalhe (fn 5764) builds the record one of two ways, with the voter's
// dynamic data (the record's constructor, line 49, which throws code 7829 when the data's voter is not the decorator's
// identity, held behind a frame of its own in 5764: out of line here, binaryen inlined it) or without it (the optional
// left empty, no frame). For the one without the data, its being out of line beside the other, its parameters and its
// line are chosen (not measured against an inline form).
class CEleitorDetalhe {
public:
    CEleitorDetalhe(const md::CEleitorDecorator& eleitor, const md::ETipoImpedimento impedimentoP1,
        const md::ETipoImpedimento impedimentoP2);
    CEleitorDetalhe(const md::CEleitorDecorator& eleitor, const md::CEleitorDinamico& dinamico,
        const md::ETipoImpedimento impedimentoP1, const md::ETipoImpedimento impedimentoP2);

    void ConfereDadosDinamicos(const std::string& funcao) const;

    const md::CEleitorDecorator& GetEleitor() const { return m_eleitor; }
    bool TemDadosDinamicos() const { return m_dinamico.has_value(); }
    // The dynamic data as they are, with no check: comum::CGeradorRelEleitoresHabBiograf's report (held by target fn
    // 12105) tests the optional's flag (+192) and reads the comparecimento state (+140) and the kind of enabling (+144)
    // in place, with no call of GetDinamico (fn 1271). The accessor, its name and its being inline here are chosen.
    const std::optional<md::CEleitorDinamico>& GetDadosDinamicos() const { return m_dinamico; }
    const md::CEleitorDinamico& GetDinamico() const;
    void MarcaHabilitado(const CEleitorDadosHabilitacao& dados);
    void MarcaVotou();
    md::ETipoImpedimento GetImpedimento() const;
    // fn 2266: whether the voter has no impediment in the current turn, GetImpedimento() == 0 with GetImpedimento
    // inlined (+196 or +200 by the load's turn), which clang does in this file only; band 5 puts the function between
    // ccargods.cpp's and celeitores.cpp's in link order. Its callers count the voters who can vote (fn 2823 below,
    // CEleitores's slot 0 fn 2824, and fns 10635, 11233, 11616). The name, its being a member and its const are chosen.
    bool SemImpedimento() const;
    // fn 1937, records celeitordetalhe.cpp:94 and :101: the voter's biometry, read from the section's file of voters
    // ("el") or of voters temporarily transferred to it ("tte") at the voter's CIndexer and converted under an
    // md::CParametro of the voter's identity of its own type, its byte vector and that CIndexer.
    md::CBiometriaEleitor GetBiometria() const;
    // The impediment of the turn given. vota::CEleitorEncontrado::StartState (fn 10635) holds this code inlined twice
    // (comum::CAppInfo::GetInst and its const GetGeral, fns 185 and 457, the turn's test, the load of +196 or +200)
    // beside three calls of GetImpedimento (fn 3769), which reads the same members out of line; the target functions
    // whose pieces hold the two offsets and a call of 457 are 2266, 3769, 7787 and 10635 (`/usr/bin/grep -rlE
    // 'i32\.const 196' build/out/splat/pieces/asm | xargs /usr/bin/grep -lE 'i32\.const 200' | xargs /usr/bin/grep -lE
    // 'call 457'`). That code is written as a member a header defines, reading the private members the base header
    // declares: its being a member, this one, its name, its parameter and its being inline are chosen.
    md::ETipoImpedimento GetImpedimentoTurno(EUrnaTurno turno) const
    {
        return turno == TURNO_2 ? m_impedimentoP2 : m_impedimentoP1;
    }

private:
    // The path of that file: fn 1937 holds it behind a 64-byte frame of its own (binaryen's inlining,
    // docs/reference/facts/reading.md R10), after a br_table on the voter's transfer kind that sends 0 and 4 to "el" and
    // the rest to "tte". Its name and its being a const member are chosen (src/units/98-uenux2-app-comum-dados.mk).
    std::string GetArquivoBiometria() const;
    md::CEleitorDecorator m_eleitor;
    std::optional<md::CEleitorDinamico> m_dinamico;
    md::ETipoImpedimento m_impedimentoP1;
    md::ETipoImpedimento m_impedimentoP2;
};

} // namespace comum
