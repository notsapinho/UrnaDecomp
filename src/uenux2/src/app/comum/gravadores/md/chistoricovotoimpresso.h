#pragma once

#include "api/util/cdatetime.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout's head only, from comum::asn::CConversorHistoricoVotoImpresso::DoConverte (target fn 10276),
// which copies the words at +0 and +4 into ModuloBoletimUrna::HistoricoVotoImpresso's idImpressoraVotos and
// idRepositorioVotos and hands +8 to fn 1080, which builds the entity's dataHoraLigamento (1080 stores
// ModuloTiposEleitorais::DataHoraJE's vptr). The class name is the RTTI's of the converter's base. No record names this
// file: the path mirrors the converter's (docs/how-to-decompile.md step 3, rule 3). Chosen: the members' names, their
// unsigned type, and that +8 is an api::CDateTime. The constructor is not recovered, so nothing may construct the
// class. The getters are what fn 10276 reads, the date by reference (fn 1080 takes its address); their names are
// chosen.
class CHistoricoVotoImpresso {
public:
    uedword GetIdImpressoraVotos() const { return m_idImpressoraVotos; }
    uedword GetIdRepositorioVotos() const { return m_idRepositorioVotos; }
    const api::CDateTime& GetDataHoraLigamento() const { return m_dataHoraLigamento; }

private:
    uedword m_idImpressoraVotos;
    uedword m_idRepositorioVotos;
    api::CDateTime m_dataHoraLigamento;
};

} // namespace comum::md
