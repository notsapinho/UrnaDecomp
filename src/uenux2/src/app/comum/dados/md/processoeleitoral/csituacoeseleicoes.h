#pragma once

#include "app/comum/dados/md/rdv/cvotoscargos.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// The orders of one active election of the pleito: comum::asn::CConversorSituacoesEleicoes::DoDesconverte (target fn
// 11361) builds one from each ModuloSituacoesEleicoes::SituacaoEleicao whose tipo is ativa, the election id as a
// 4-byte word at +0 and the three orders as bytes 4-6, in the order of SituacaoEleicao's fields; the member names
// follow those fields. CPleito keeps them in a std::vector and finds one by the election id (CPleito's records in
// md/processoeleitoral/cpleito.cpp: GetSituacoesEleicoes(const TEleicaoID)). The constructor is out of line
// (csituacoeseleicoes.cpp): DoDesconverte passes it the orders zero-extended, as a call's uebyte arguments are, and
// wasm-opt inlines it there. The class stays trivially copyable, 8 bytes: the target's std::vector push_back of it is
// fn 760, one body with every other 8-byte element's.
// TEleicaoID: the records put it in namespace comum (CCargos::GetCurrentEleicaoID), a header not recovered; the
// project declares it as md::TEleicaoID in md/rdv/cvotoscargos.h.
class CSituacoesEleicoes {
public:
    CSituacoesEleicoes(TEleicaoID idEleicao, uebyte ordemAquisicao, uebyte ordemImpressao, uebyte ordemApuracao);

    TEleicaoID GetIdEleicao() const { return m_idEleicao; }
    uebyte GetOrdemAquisicao() const { return m_ordemAquisicao; }
    uebyte GetOrdemImpressao() const { return m_ordemImpressao; }
    uebyte GetOrdemApuracao() const { return m_ordemApuracao; }

private:
    TEleicaoID m_idEleicao;
    uebyte m_ordemAquisicao;
    uebyte m_ordemImpressao;
    uebyte m_ordemApuracao;
};

} // namespace comum::md
