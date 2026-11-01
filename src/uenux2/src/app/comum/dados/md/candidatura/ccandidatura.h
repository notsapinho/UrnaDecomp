#pragma once

#include <vector>

#include "app/comum/dados/md/candidatura/cdadoscandidato.h"
#include "app/comum/dados/md/rdv/cvotoscargos.h"

namespace comum {

// Spelled unqualified by the records of comum::CCandidaturas and of CCandidatura's constructor. Their widths are the
// constructor's stores (target fn 5660): a 16-bit word, a 32-bit word.
using TPartidoID = ueword;
using TCandidatoID = uedword;

namespace md {

// Recovered: the layout, 72 bytes, from the constructor (fn 5660, records ccandidatura.cpp:37 to :55): the post at +0,
// the party at +2, the candidate at +4, the holder at +8, the substitutes at +60. The member names are not in the target.
class CCandidatura {
public:
    CCandidatura(const TCargoID cargo, const TPartidoID partido, const TCandidatoID candidato,
        const CDadosCandidato& titular, const std::vector<CDadosCandidato>& suplentes);

    // The names are chosen: comum::CCargoDSNomeSexoCandidato's call operator (fn 2268) compares the byte at +0 with the
    // current post's id, and CCandidaturasDSSexo's (fn 5806) reads the holder at +8 when it asks for no substitute.
    TCargoID GetCargoID() const { return m_cargo; }
    // The names are chosen: comum::CCandidaturas's members (fns 2272, 2840) read the 16-bit word at +2 and the 32-bit
    // word at +4.
    TPartidoID GetPartidoID() const { return m_partido; }
    TCandidatoID GetCandidatoID() const { return m_candidato; }
    const CDadosCandidato& GetTitular() const { return m_titular; }
    const CDadosCandidato& GetSuplente(uebyte ordem) const;

private:
    TCargoID m_cargo;
    TPartidoID m_partido;
    TCandidatoID m_candidato;
    CDadosCandidato m_titular;
    std::vector<CDadosCandidato> m_suplentes;
};

} // namespace md
} // namespace comum
