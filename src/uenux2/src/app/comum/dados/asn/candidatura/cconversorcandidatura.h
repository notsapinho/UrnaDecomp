#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/candidatura/ccandidatura.h"
#include "asn1/modules/ModuloCandidatos.h"

namespace comum::asn {

// Reads one candidacy; the conversion the other way is the base's default DoConverte (the vtable's slot 2 is
// IConversorASN's, target fn 11446). RTTI names the class and its base (vtable @1562284). The constructor (fn 5712) is
// out of line, a call that comum::asn::CConversorCandidaturas::DoDesconverte (fn 11445) makes twice per party, passing
// its returned this on: it stores a byte at +4, a 16-bit word at +6 and a byte at +8, which DoDesconverte (fn 11448)
// passes to md::CCandidatura's constructor as its post and party (TCargoID, TPartidoID: the record's types of those
// parameters) and to CConversorDadosCandidato's constructor (whose byte its DoDesconverte inverts into the candidate's
// ESituacao); 11445 passes 1 for a party's candidatosAptos and 0 for its candidatosInaptos. The members' and the
// parameters' names are chosen, and so is the flag's type, bool (it is stored and passed as a byte); no record names
// this header's path: the directory mirrors md::CCandidatura's (docs/how-to-decompile.md step 3, rule 3) and the file
// name is the class's.
class CConversorCandidatura : public IConversorASN<ModuloCandidatos::Candidatura, md::CCandidatura> {
public:
    CConversorCandidatura(md::TCargoID cargo, TPartidoID partido, bool apto);

protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    md::TCargoID m_cargo;
    TPartidoID m_partido;
    bool m_apto;
};

} // namespace comum::asn
