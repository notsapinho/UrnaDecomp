// Reconstruction notes: comum::md::CPleito's GetEleicao and GetSituacoesEleicoes (target fns 5651 and 5648), on their
// records' lines 139 and 175, at the four-space indent each record's column 11 gives; ExisteEleicao (no record, no index:
// fn 3775 holds it inlined), its line a choice. The constructor (fn 5652, records at 64, 67 and 70) and
// GetVersaoPacoteEleicao (inlined into fn 5604, record at 158) are not written; unit 88's fragment says why.
#include "app/comum/dados/md/processoeleitoral/cpleito.h"

#include <algorithm>
#include <format>
#include <set>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 15-53: content not recovered)
#line 54
CPleito::CPleito(const TPleitoID id, const std::string& nome, const api::CDate& data, const TVectorEleicaoPE& eleicoes,
                 const TMapVersaoPacoteEleicao& versoesPacote, const std::vector<CSituacoesEleicoes>& situacoes)
    : m_id(id), m_nome(nome), m_data(data), m_eleicoes(eleicoes), m_versoesPacote(versoesPacote), m_situacoes(situacoes)
{
    std::set<TEleicaoID> ids;
    for (const CEleicaoPE& eleicao : m_eleicoes) {
        ids.insert(eleicao.GetID());
    }

    if (ids.size() != m_eleicoes.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8159, "Há eleições com identificadores repetidos.");
    }
    if (ids.size() > m_versoesPacote.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8160, "Há eleições sem versão de pacotes.");
    }
    if (ids.size() != m_situacoes.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8161, "Há eleições com situações inválidas.");
    }
}

// (original lines 74-131: content not recovered)
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


bool CPleito::ExisteEleicao(const TEleicaoID id) const
{
    return std::any_of(m_eleicoes.begin(), m_eleicoes.end(),
                       [id](const CEleicaoPE& eleicao) { return eleicao.GetID() == id; });
}

// (original lines 149-167: content not recovered)
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
