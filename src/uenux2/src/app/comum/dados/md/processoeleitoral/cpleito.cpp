// Reconstruction notes: comum::md::CPleito's GetEleicao and GetSituacoesEleicoes (target fns 5651 and 5648), on their
// records' lines 139 and 175, at the four-space indent each record's column 11 gives; ExisteEleicao (no record, no index:
// fn 3775 holds it inlined), its line a choice; GetVersaoPacoteEleicao (record at 158, no index: binaryen inlines it
// into fn 5604, unit 155's); GetEleicoesMunicipio and FiltraMunicipio (fns 5649 and 3713, no record, lines chosen:
// src/units/388-uenux2-nomesarquivos.mk). The constructor (fn 5652) has its records on lines 64, 67 and 70;
// ObtemIDsEleicoes, which it calls and clang inlines (no record, no index), has internal linkage, which the target's
// code shows; its name, its namespace and both functions' first lines are chosen (fragment 88 says what bytes decide).
#include "app/comum/dados/md/processoeleitoral/cpleito.h"

#include <algorithm>
#include <format>
#include <set>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 18-43: content not recovered)
#line 44
namespace {

std::set<TEleicaoID> ObtemIDsEleicoes(const TVectorEleicaoPE& eleicoes)
{
    std::set<TEleicaoID> ids;
    for (const CEleicaoPE& eleicao : eleicoes) {
        ids.insert(eleicao.GetID());
    }
    return ids;
}

} // namespace

CPleito::CPleito(const TPleitoID id, const std::string& nome, const api::CDate& data, const TVectorEleicaoPE& eleicoes,
                 const TMapVersaoPacoteEleicao& versoesPacote, const std::vector<CSituacoesEleicoes>& situacoes)
    : m_id(id), m_nome(nome), m_data(data), m_eleicoes(eleicoes), m_versoesPacote(versoesPacote), m_situacoes(situacoes)
{
    const std::set<TEleicaoID> ids = ObtemIDsEleicoes(m_eleicoes);

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

// (original lines 74-124: content not recovered)
#line 125
bool CPleito::ExisteEleicao(const TEleicaoID id) const
{
    return std::any_of(m_eleicoes.begin(), m_eleicoes.end(),
                       [id](const CEleicaoPE& eleicao) { return eleicao.GetID() == id; });
}


const CEleicaoPE& CPleito::GetEleicao(const TEleicaoID id) const
{
    const auto it = std::find_if(m_eleicoes.begin(), m_eleicoes.end(),
                                 [id](const CEleicaoPE& eleicao) { return eleicao.GetID() == id; });
    if (it != m_eleicoes.end()) {
        return *it;
    }
    throw CUeComumDadosError(EUE_COMUM_DADOS_8162, std::format("Eleição não encontrada: {}", id));
}

TVectorEleicaoPE CPleito::GetEleicoesMunicipio(const uedword municipio) const
{
    if (municipio == 0) {
        return m_eleicoes;
    }
    TVectorEleicaoPE eleicoes;
    std::copy_if(m_eleicoes.begin(), m_eleicoes.end(), std::back_inserter(eleicoes),
                 [municipio](const CEleicaoPE& eleicao) { return eleicao.PossuiMunicipio(municipio); });
    return eleicoes;
}


const std::string& CPleito::GetVersaoPacoteEleicao(const TEleicaoID id) const
{
    const auto it = m_versoesPacote.find(id);
    if (it == m_versoesPacote.end()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8163, "Versão de pacote não encontrada");
    }
    return it->second;
}

// (original lines 163-167: content not recovered)
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

std::vector<CSituacoesEleicoes> CPleito::GetSituacoesMunicipio(const uedword municipio) const
{
    if (municipio == 0) {
        return m_situacoes;
    }
    std::vector<CSituacoesEleicoes> situacoes;
    for (const CEleicaoPE& eleicao : m_eleicoes) {
        if (eleicao.PossuiMunicipio(municipio)) {
            situacoes.push_back(GetSituacoesEleicoes(eleicao.GetID()));
        }
    }
    return situacoes;
}

CPleito CPleito::FiltraMunicipio(const uedword municipio) const
{
    return CPleito(m_id, m_nome, m_data, GetEleicoesMunicipio(municipio), m_versoesPacote,
                   GetSituacoesMunicipio(municipio));
}

} // namespace comum::md
