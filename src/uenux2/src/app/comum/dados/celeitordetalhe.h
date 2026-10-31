#pragma once

#include <optional>
#include <string>

#include "app/comum/dados/md/eleitor/celeitordecorator.h"
#include "app/comum/dados/md/eleitor/celeitordinamico.h"

namespace comum {

// Recovered: the layout: a CEleitorDecorator at +0 and a std::optional<CEleitorDinamico> at +108, from what fn 1270 destroys
// (its record's constructor, line 49, takes one of each); the byte at +192 ConfereDadosDinamicos (target fn 3770) reads is
// the optional's flag. Only that member is reconstructed, the members' names are chosen, and nothing may construct this
// class yet.
class CEleitorDetalhe {
public:
    void ConfereDadosDinamicos(const std::string& funcao) const;

private:
    md::CEleitorDecorator m_eleitor;
    std::optional<md::CEleitorDinamico> m_dinamico;
};

} // namespace comum
