#pragma once

#include <optional>

#include "app/comum/dados/md/candidatura/ccandidatura.h"
#include "app/comum/dados/md/rdv/cvoto.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// The identification of a votable in the BU (ModuloBoletimUrna::IdentificacaoVotavel holds a partido and a codigo).
// Recovered: the layout, 8 bytes, and the constructor (fn 5864): the code at +0 (i32.store), the party at +4
// (i32.store16). comum::CGravadorBU::AcrescentaVotoVotavel (fn 3820, record cgravadorbu.cpp:221) builds it from its
// TCandidatoID argument and 0 or a party number read as a 16-bit word. Chosen: the class's name (no evidence names it),
// its path beside CVotosVotavel, the member names.
class CIdentificacaoVotavel {
public:
    CIdentificacaoVotavel(TCandidatoID codigo, TPartidoID partido);

private:
    TCandidatoID m_codigo;
    TPartidoID m_partido;
};

// Named by the function-name text "...comum::asn::(anonymous namespace)::CriaVotosVotavel(const md::CVotosVotavel &,
// const TCargoID, const ueword)" at 396499 of the data (ledger/strings.tsv). Recovered: the layout, 24 bytes, and the
// two constructors, which AcrescentaVotoVotavel (fn 3820) calls with its md::CVoto::ETipo, TCandidatoID and TQtdEleitor
// arguments: the type at +0, the candidate at +4 (i32.store), the count at +8 (i32.store16), and an optional
// identification at +12, engaged at +20: fn 2856 leaves it empty (byte 0 at +12, the null state, and at +20), fn 5863
// copies the 8 bytes it is given and stores 1 at +20. Chosen: the path (rule 4 of docs/how-to-decompile.md step 3, in
// gravadores/md/ with the BU's data classes), the member names, the count's type (ueword: the record's TQtdEleitor is
// not declared in comum), and that the identification is passed by const reference.
class CVotosVotavel {
public:
    CVotosVotavel(CVoto::ETipo tipo, TCandidatoID candidato, ueword quantidade);
    CVotosVotavel(CVoto::ETipo tipo, TCandidatoID candidato, ueword quantidade,
        const CIdentificacaoVotavel& identificacao);

private:
    CVoto::ETipo m_tipo;
    TCandidatoID m_candidato;
    ueword m_quantidade;
    std::optional<CIdentificacaoVotavel> m_identificacao;
};

} // namespace comum::md
