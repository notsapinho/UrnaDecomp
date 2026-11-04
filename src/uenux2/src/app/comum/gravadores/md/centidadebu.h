#pragma once

#include "app/comum/eurnafase.h"
#include "app/comum/gravadores/md/curna.h"
#include "app/comum/md/ccabecalhoentidade.h"

namespace comum::md {

// The BU's data, the DADO of comum::asn::CConversorEntidadeBU (its RTTI's base names the class). Its records are
// centidadebu.cpp's (ValidaCriacao, lines 159 to 177, held by target fn 11629; GetDadosVota, GetDadosSA and
// GetDetalhamentoComparecimento, lines 186, 196 and 206, held by fn 10273), and none of those functions is written.
// Recovered: the head of the layout, from the converter's DoConverte (fn 10273), which hands +0 to the entity header's
// converter (fn 2275, IConversorASN<ModuloTiposEleitorais::CabecalhoEntidade, md::CCabecalhoEntidade>::Converte), +20
// to comum::asn::Utils::ConverteFase (fn 1712, const EUrnaFase &) and +24 to the urna's converter (fn 3799,
// IConversorASN<ModuloTiposResultadosEcoUrna::Urna, md::CUrna>::Converte); CUrna's 136 bytes end at +160. The members
// follow ModuloBoletimUrna::EntidadeBoletimUrna's first fields (cabecalho, fase, urna); their names are chosen. The
// members from +160 on (fn 10273 reads further up to +286) and the constructor are not recovered, so nothing may
// construct the class.
class CEntidadeBU {
private:
    CCabecalhoEntidade m_cabecalho;
    EUrnaFase m_fase;
    CUrna m_urna;
};

} // namespace comum::md
