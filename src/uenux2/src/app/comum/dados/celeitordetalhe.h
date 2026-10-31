#pragma once

#include <optional>
#include <string>

#include "app/comum/dados/md/eleitor/celeitordecorator.h"
#include "app/comum/dados/md/eleitor/celeitordinamico.h"

namespace comum {

class CEleitorDadosHabilitacao;

// Recovered: the layout: a CEleitorDecorator at +0 and a std::optional<CEleitorDinamico> at +108, from what fn 1270 destroys
// (its record's constructor, line 49, takes one of each); the byte at +192 ConfereDadosDinamicos (target fn 3770) reads is
// the optional's flag. ConfereDadosDinamicos, GetDinamico (fn 1271) and MarcaHabilitado are written. Chosen: the members'
// names, the two accessors, GetDinamico's const and const& result, MarcaHabilitado's parameter type. Nothing builds it.
class CEleitorDetalhe {
public:
    void ConfereDadosDinamicos(const std::string& funcao) const;

    const md::CEleitorDecorator& GetEleitor() const { return m_eleitor; }
    bool TemDadosDinamicos() const { return m_dinamico.has_value(); }
    const md::CEleitorDinamico& GetDinamico() const;
    void MarcaHabilitado(const CEleitorDadosHabilitacao& dados);

private:
    md::CEleitorDecorator m_eleitor;
    std::optional<md::CEleitorDinamico> m_dinamico;
};

} // namespace comum
