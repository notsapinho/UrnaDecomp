#pragma once

#include <optional>
#include <string>

#include "app/comum/dados/md/eleitor/celeitordecorator.h"
#include "app/comum/dados/md/eleitor/celeitordinamico.h"
#include "app/comum/dados/md/etipoimpedimento.h"

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
// MarcaHabilitado's parameter type. Nothing builds it.
class CEleitorDetalhe {
public:
    void ConfereDadosDinamicos(const std::string& funcao) const;

    const md::CEleitorDecorator& GetEleitor() const { return m_eleitor; }
    bool TemDadosDinamicos() const { return m_dinamico.has_value(); }
    const md::CEleitorDinamico& GetDinamico() const;
    void MarcaHabilitado(const CEleitorDadosHabilitacao& dados);
    void MarcaVotou();
    md::ETipoImpedimento GetImpedimento() const;

private:
    md::CEleitorDecorator m_eleitor;
    std::optional<md::CEleitorDinamico> m_dinamico;
    md::ETipoImpedimento m_impedimentoP1;
    md::ETipoImpedimento m_impedimentoP2;
};

} // namespace comum
