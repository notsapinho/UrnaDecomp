#pragma once

// comum::CInformacaoEleicao: a view over the election's data that answers differently in demonstration mode. The record
// cinformacaoeleicao.cpp:40 names the class and EhModoDemonstracao; clang inlined that member into seven others of the
// file. Fn 603 is the constructor: it stores its argument at +0 and returns this, and its 22 callers each pass
// `fn 187's result + 88` and call these members on the object, which lives in the caller's frame. So +0 is a reference
// (fn 2286 and the others load it and read through it).
// No record names those seven members, the eighth below or the constructor's type. Their names are chosen from their
// callers:
// - 3847 and 5914 (+12, +16): vota::CVerificaQtdBUsAdicionais adds them and compares a count of copies of the BU;
// - 2865, 5917, 5916, 5915 (+56, +60, +64, +68): the menu items vota::CItemImprimeEstadoUrnaVota, CItemImprimeListaEleitoresVota,
//   CItemVersoesPacotesVota and CItemParametrosUrnaVota each compare one with the copies printed, the four reports of
//   md::estadoaplicacao::CNumViasImpressasRelatorios in that class's order;
// - 1950 (the byte at +400): tested before vota::CImprimirBJust prints, false in demonstration mode;
// - 5918 (the byte at +394, the field that header calls aceitarJustificativa): fn 4578 returns its negation on an object
//   it builds as the others do, and fn 12065 tests it; it reads no demonstration mode. Its band (uses 2) puts it ahead of
//   5917 in the link, so it is defined above GetNumViasEleitores; after ImprimeBJust is a choice.
// Each of the six counts is 1 in demonstration mode. They read 32 bits and their sums compare signed (fn 12023), so they
// are `int`, a choice as far as the bodies go.
// Fn 187 has a record, static CConfiguracaoEleicao &comum::CConfiguracaoEleicao::GetInst() at cconfiguracaoeleicao.cpp:36,
// so the object is a member of that class, at +88: the urna's parameters, ecourna::app::dados::CParametrosUrna
// (cconfiguracaoeleicao.h), whose fields at those offsets are the counts of copies numBUVotaObrigatorios,
// numBUVotaAdicionais, numRelatorioEstado, numRelatorioEleitores, numRelatorioVersoesDados and numRelatorioPU, and
// at +400 the flag that header calls registrarMesarios. The constructor's parameter type is that class: the slots
// of comum::CRelatorioTesteImpressora (fn 11193) and CRelUtil::GetSeparadorFase (fn 1919) hand it
// CConfiguracaoEleicao::GetParametrosUrna().

#include "ecourna/app/dados/parametrizacaourna/cparametrosurna.hpp"

namespace comum {

class CInformacaoEleicao {
public:
    explicit CInformacaoEleicao(const ecourna::app::dados::CParametrosUrna& parametros);

    bool EhModoDemonstracao() const;
    bool ImprimeBJust() const;
    bool AceitaJustificativa() const;
    int GetNumViasBU() const;
    int GetNumViasBUAdicionais() const;
    int GetNumViasEstadoUrna() const;
    int GetNumViasEleitores() const;
    int GetNumViasVersoesDados() const;
    int GetNumViasPU() const;

private:
    const ecourna::app::dados::CParametrosUrna& m_parametros;
};

} // namespace comum
