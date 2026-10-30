// Reconstruction notes: comum::md::CPleito's GetEleicao and GetSituacoesEleicoes (target fns 5651 and 5648), on their
// records' lines 139 and 175, at the four-space indent each record's column 11 gives. The constructor (fn 5652, records
// at 64, 67 and 70) and GetVersaoPacoteEleicao (inlined into fn 5604, record at 158) are not written; the fragment says
// what the constructor waits for.
#include "app/comum/dados/md/processoeleitoral/cpleito.h"

#include <algorithm>
#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 14-60: content not recovered)
#line 61
// <stubs>
// f5652 · 844 B · unmatched · name unknown
// void f5652(i32, i32, i32, i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 66-131: content not recovered)
#line 132
const CEleicaoPE& CPleito::GetEleicao(const TEleicaoID id) const
{
    const auto it = std::find_if(m_eleicoes.begin(), m_eleicoes.end(),
                                 [id](const CEleicaoPE& eleicao) { return eleicao.GetID() == id; });
    if (it != m_eleicoes.end()) {
        return *it;
    }
    throw CUeComumDadosError(EUE_COMUM_DADOS_8162, std::format("Eleição não encontrada: {}", id));
}

// (original lines 142-167: content not recovered)
#line 168
const CSituacoesEleicoes& CPleito::GetSituacoesEleicoes(const TEleicaoID id) const
{
    const auto it = std::find_if(m_situacoes.begin(), m_situacoes.end(),
                                 [id](const CSituacoesEleicoes& situacoes) { return situacoes.GetIdEleicao() == id; });
    if (it != m_situacoes.end()) {
        return *it;
    }
    throw CUeComumDadosError(EUE_COMUM_DADOS_8164, std::format("Situação eleição não encontrada: {}", id));
}

} // namespace comum::md
