#pragma once

#include "app/comum/appinfo/servicos/iservicoestado.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversorestadogeralgap.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralgap.h"
#include "app/comum/eflashorigem.h"
#include "app/comum/eurnaturno.h"

namespace comum {

// RTTI names the class and its base (vtable @1558112, slot 2 target fn 11567, whose record is
// cservicoestadogeralgap.cpp:32). GetPathArquivo reads the origin at +4 and the turn at +8, 4 bytes each, which it
// passes to CPath::GetPathTrab: the members' types are chosen as that function's record's (EFlashOrigem, EUrnaTurno),
// and their names too. The constructor (thunk 5812 of fn 3897, binaryen's merge of the three classes' constructors)
// stores the turn, the origin and the vptr, and when the turn is 51 (TURNO_ATUAL) takes the turn from the state fn 3791
// (Carrega) reads through a named CServicoEstadoGeral (fn 1941): a temporary gives another frame
// (src/units/206-uenux2-app-comum-appinfo-servicos.mk). Its parameter types are those of the members it stores. This
// header's path is chosen.
class CServicoEstadoGeralGap : public IServicoEstado<md::estadoaplicacao::CEstadoGeralGap, asn::CConversorEstadoGeralGap> {
public:
    CServicoEstadoGeralGap(EFlashOrigem origem, EUrnaTurno turno);

    std::filesystem::path GetPathArquivo() override;

private:
    EFlashOrigem m_origem;
    EUrnaTurno m_turno;
};

} // namespace comum
