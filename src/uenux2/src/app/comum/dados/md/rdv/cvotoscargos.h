#pragma once

#include <map>
#include <string>

#include "app/comum/dados/md/rdv/cvotos.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

using TCargoID = uebyte;
using TEleicaoID = unsigned int;

class CVotosCargos {
public:
    // Recovered: 12 bytes. comum::asn::CConversorVotosCargo's constructor (fn 5683) copies them (an i64 and an i32), and
    // CConversorEleicoesVota::DoConverte (fn 11350) builds one from a md::CCargo: its id (byte +0), the word at +4, the
    // bytes at +12 and +13. The map compares the id alone (fn 3893's search loads the byte at node+16 and reads the
    // CVotos at node+28). CConversorVotosCargo compares the id and the byte at +9 with an entity's cargo and
    // quantidadeEscolhas (fns 11352, 11351). The member names and the word's type are chosen.
    struct SCargoInfo {
        TCargoID cargo;
        int tipo;
        uebyte numeroDigitos;
        uebyte quantidadeEscolhas;
        bool operator<(const SCargoInfo& outro) const { return cargo < outro.cargo; }
    };
    using TMapa = std::map<SCargoInfo, CVotos>;

    explicit CVotosCargos(TMapa mapa);

    // Accessors comum::CRdvVota's slots 0 and 1 (fns 5733, 11490) and md::CVotosEleicoesVota::Comparecimento (fn 5639)
    // need: they walk the map's nodes, and 5639 divides the first cargo's vote count by its quantidadeEscolhas (the
    // byte at +9). The names and their being in the class are chosen.
    const TMapa& GetMapa() const { return m_mapa; }
    TQtdVoto Comparecimento() const
    {
        const auto& [cargo, votos] = *m_mapa.begin();
        return votos.Total() / cargo.quantidadeEscolhas;
    }

    // The sum of the cargos' quantidadeEscolhas (fn 5642, called twice by fn 4454); its name is chosen.
    uebyte QuantidadeEscolhas() const;
    const CVotos& GetVotos(TCargoID cargo) const;
    TQtdVoto Candidato(TCargoID cargo, std::string numero) const;
    TQtdVoto Legenda(TCargoID cargo, std::string numero) const;
    TQtdVoto Partido(TCargoID cargo, std::string numero) const;
    TQtdVoto Nominais(TCargoID cargo) const;
    TQtdVoto Legendas(TCargoID cargo) const;
    TQtdVoto Nulos(TCargoID cargo) const;
    TQtdVoto Brancos(TCargoID cargo) const;
    TQtdVoto Cargo(TCargoID cargo) const;
    // Out of line: md::CVotosEleicoesVota::Compativel (fn 5638) holds it inlined by binaryen, its result tested again.
    // The name is chosen.
    bool Compativel(const CVotosCargos& outro) const;

private:
    TMapa m_mapa;
};

} // namespace comum::md
