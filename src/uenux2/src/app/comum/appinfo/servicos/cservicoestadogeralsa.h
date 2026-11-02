#pragma once

#include "app/comum/appinfo/servicos/iservicoestado.h"
#include "app/comum/eflashorigem.h"
#include "app/comum/eurnaturno.h"

namespace comum::md::estadoaplicacao {

class CEstadoGeralSA;

} // namespace comum::md::estadoaplicacao

namespace comum::asn {

class CConversorEstadoGeralSA;

} // namespace comum::asn

namespace comum {

// RTTI names the class and its base (vtable @1558168, slot 2 target fn 11565, whose record is
// cservicoestadogeralsa.cpp:32). GetPathArquivo reads the origin at +4 and the turn at +8, 4 bytes each, which it
// passes to CPath::GetPathTrab: the members' types are chosen as that function's record's (EFlashOrigem, EUrnaTurno),
// and their names too. The constructor (thunk 11566 of fn 3897, binaryen's merge of the three classes' constructors)
// stores the turn, the origin and the vptr, and when the turn is 51 (TURNO_ATUAL) takes the turn from the state fn 3791
// reads through a CServicoEstadoGeral (fn 1941). It is declared, with the parameter types of the members it stores, and
// not written: 3791 is not (src/units/206-uenux2-app-comum-appinfo-servicos.mk). This header's path is chosen.
class CServicoEstadoGeralSA : public IServicoEstado<md::estadoaplicacao::CEstadoGeralSA, asn::CConversorEstadoGeralSA> {
public:
    CServicoEstadoGeralSA(EFlashOrigem origem, EUrnaTurno turno);

    std::filesystem::path GetPathArquivo() override;

private:
    EFlashOrigem m_origem;
    EUrnaTurno m_turno;
};

} // namespace comum
