#pragma once

// comum::CInformacaoEleicao: a view over the election's data that answers differently in demonstration mode. The record
// cinformacaoeleicao.cpp:40 names the class and EhModoDemonstracao; clang inlined that member into seven others of the
// file. Fn 603 is the constructor: it stores its argument at +0 and returns this, and its 22 callers each pass
// `fn 187's result + 88` and call these members on the object, which lives in the caller's frame. So +0 is a reference
// (fn 2286 and the others load it and read through it).
// No record names the seven members or the constructor's type. Their names are chosen from their callers:
// - 3847 and 5914 (+12, +16): vota::CVerificaQtdBUsAdicionais adds them and compares a count of copies of the BU;
// - 2865, 5917, 5916, 5915 (+56, +60, +64, +68): the menu items vota::CItemImprimeEstadoUrnaVota, CItemImprimeListaEleitoresVota,
//   CItemVersoesPacotesVota and CItemParametrosUrnaVota each compare one with the copies printed, the four reports of
//   md::estadoaplicacao::CNumViasImpressasRelatorios in that class's order;
// - 1950 (the byte at +400): tested before vota::CImprimirBJust prints, false in demonstration mode.
// Each of the six counts is 1 in demonstration mode. They read 32 bits and their sums compare signed (fn 12023), so they
// are `int`, a choice as far as the bodies go.
// SDadosInformacaoEleicao: the layout alone, the offsets these bodies read. Its name and its members' are chosen; which
// class the object at +88 of fn 187's result is, is not recovered here.

#include "ecourna/api/uetypes.hpp"

namespace comum {

struct SDadosInformacaoEleicao {
    char m_inicio[12];
    int m_numViasBU;
    int m_numViasBUAdicionais;
    char m_meio1[36];
    int m_numViasEstadoUrna;
    int m_numViasEleitores;
    int m_numViasVersoesDados;
    int m_numViasPU;
    char m_meio2[328];
    bool m_imprimeBJust;
};

class CInformacaoEleicao {
public:
    explicit CInformacaoEleicao(const SDadosInformacaoEleicao& dados);

    bool EhModoDemonstracao() const;
    bool ImprimeBJust() const;
    int GetNumViasBU() const;
    int GetNumViasBUAdicionais() const;
    int GetNumViasEstadoUrna() const;
    int GetNumViasEleitores() const;
    int GetNumViasVersoesDados() const;
    int GetNumViasPU() const;

private:
    const SDadosInformacaoEleicao& m_dados;
};

} // namespace comum
