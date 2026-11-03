#pragma once

#include "app/comum/appinfo/servicos/iservicoestado.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversorestadogeralsa.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralsa.h"
#include "app/comum/eflashorigem.h"
#include "app/comum/eurnaturno.h"

namespace comum {

// RTTI names the class and its base (vtable @1558168, slot 2 target fn 11565, whose record is
// cservicoestadogeralsa.cpp:32). GetPathArquivo reads the origin at +4 and the turn at +8, 4 bytes each, which it
// passes to CPath::GetPathTrab: the members' types are chosen as that function's record's (EFlashOrigem, EUrnaTurno),
// and their names too. The constructor (thunk 11566 of fn 3897, binaryen's merge of the three classes' constructors)
// stores the turn, the origin and the vptr, and when the turn is 51 (TURNO_ATUAL) takes the turn from the state fn 3791
// (Carrega) reads through a named CServicoEstadoGeral (fn 1941): a temporary gives another frame
// (src/units/206-uenux2-app-comum-appinfo-servicos.mk). Its parameter types are those of the members it stores. This
// header's path is chosen.
class CServicoEstadoGeralSA : public IServicoEstado<md::estadoaplicacao::CEstadoGeralSA, asn::CConversorEstadoGeralSA> {
public:
    CServicoEstadoGeralSA(EFlashOrigem origem, EUrnaTurno turno);

    std::filesystem::path GetPathArquivo() override;

private:
    EFlashOrigem m_origem;
    EUrnaTurno m_turno;
};

} // namespace comum
