#pragma once

#include <map>

#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// One byte: fn 4135 compares it with load8_u. Records name the type, and record 1536576, std::string
// vota::NomeTela(const ETelaVotacao), spells it the same way from a free function of vota, so it is not nested in a
// class. Its enumerators are not recovered, and that it is a scoped enum is chosen.
enum class ETelaVotacao : unsigned char;

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
