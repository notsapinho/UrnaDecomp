#pragma once

#include <map>
#include <string>

#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// One byte: fn 4135 compares it with load8_u. Records name the type, and record 1536576, std::string
// vota::NomeTela(const ETelaVotacao), spells it the same way from a free function of vota, so it is not nested in a
// class. That it is a scoped enum is chosen. NomeTela (fn 6718) switches over the values 0 to 17 and returns one screen
// name for each, and throws for any other: the enumerators' names are chosen from those names, the values are
// evidence. The CConfereVotoEmCargo instances and the states' screens agree with them (the instance over
// CConfirmaVotoNominal has 2, over CCandidatoInapto 14, CConfirmaVotoSemCandidato's screen is 17).
enum class ETelaVotacao : unsigned char {
    TELA_INICIAL = 0,
    TELA_COMPLETA = 1,
    TELA_CONFERENCIA_VOTO_NOMINAL = 2,
    TELA_VOTO_BRANCO = 3,
    TELA_CONFERENCIA_VOTO_BRANCO = 4,
    TELA_VOTO_PROPORCIONAL_NULO_INCOMPLETO = 5,
    TELA_VOTO_NULO = 6,
    TELA_CONFERENCIA_VOTO_NULO = 7,
    TELA_PARTIDO = 8,
    TELA_VOTO_LEGENDA_INCOMPLETO = 9,
    TELA_CONFERENCIA_VOTO_LEGENDA = 10,
    TELA_CANDIDATO_INEXISTENTE = 11,
    TELA_CONFERENCIA_CANDIDATO_INEXISTENTE = 12,
    TELA_CANDIDATO_INAPTO = 13,
    TELA_CONFERENCIA_CANDIDATO_INAPTO = 14,
    TELA_CANDIDATO_REPETIDO = 15,
    TELA_CONFERENCIA_CANDIDATO_REPETIDO = 16,
    TELA_CARGO_SEM_CANDIDATO = 17,
};

std::string NomeTela(const ETelaVotacao tela);


// The element of CTelasVota's outer map. Records 1536592 and 1536608 give the constructor (fn 2386), and 1536624 GetTela,
// which fn 4135 inlines with its `this` at the node's +20; all three are in ctelascargo.cpp. Recovered: the layout: 2386
// stores its TCargoID at +0 with i32.store8 and starts a map at +4, and 4135 reads that byte with i32.load8_u for the
// first {} of its message and walks the map at +4. The inner map's types are record 1536832's (ctelasvota.h). Both members
// are declared only, this header's path beside ctelascargo.cpp is chosen, and so are the data members' names.
class CTelasCargo {
public:
    using TMapa = std::map<ETelaVotacao, CFormInterativoTelaVota>;

    CTelasCargo(const comum::TCargoID id, const TMapa& telas);

    CFormInterativoTelaVota GetTela(const ETelaVotacao tela) const;

private:
    comum::TCargoID m_id;
    TMapa m_telas;
};

} // namespace vota
