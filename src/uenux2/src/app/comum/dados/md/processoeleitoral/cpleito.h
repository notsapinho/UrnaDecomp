#pragma once

#include <map>
#include <string>
#include <vector>

#include "api/util/cdate.h"
#include "app/comum/dados/md/processoeleitoral/celeicaope.h"
#include "app/comum/dados/md/processoeleitoral/csituacoeseleicoes.h"

namespace comum::md {

// Recovered: the layout, 60 bytes, in the order of the constructor's record (cpleito.cpp:64: TPleitoID, a string, a
// CDate, TVectorEleicaoPE, TMapVersaoPacoteEleicao, a std::vector<CSituacoesEleicoes>), with the offsets fn 5652 writes:
// +0, +4, +16, +24, +36 and +48. TPleitoID's width comes from the 32-bit store at +0. The types of the map are chosen:
// its node is in fn 3870, and GetVersaoPacoteEleicao's record returns a string for a
// TEleicaoID. The members' names are chosen.
using TPleitoID = unsigned int;
using TVectorEleicaoPE = std::vector<CEleicaoPE>;
using TMapVersaoPacoteEleicao = std::map<TEleicaoID, std::string>;

class CPleito {
public:
    CPleito(const TPleitoID id, const std::string& nome, const api::CDate& data, const TVectorEleicaoPE& eleicoes,
            const TMapVersaoPacoteEleicao& versoesPacote, const std::vector<CSituacoesEleicoes>& situacoes);

    // The name is chosen: no record names this accessor.
    const TVectorEleicaoPE& GetEleicoes() const { return m_eleicoes; }
    // The name is chosen too: CGravadorUtil::DeterminaNomeArquivoSemLetra formats the word at +0.
    TPleitoID GetID() const { return m_id; }
    // The name is chosen: comum::CRelatorioTesteImpressora's constructor (fn 5586) reads the date at +16 inline.
    const api::CDate& GetData() const { return m_data; }
    // The name is chosen too: comum::CImprimirExtratoCarga::Imprime (fn 5591) prints the string at +4 inline.
    const std::string& GetNome() const { return m_nome; }
    const CEleicaoPE& GetEleicao(const TEleicaoID id) const;
    // Whether the pleito has an election with that id. Out of line: CConfiguracaoEleicao::GetCargos (fn 3775) holds its
    // loop as binaryen inlines a call (a bool built as `if (result i32) ... else 0 end` and tested again; of another
    // TU, the reading how-to step 3 gives), and it has no target index of its own. No record names it: its name, its
    // being a member (it reads m_eleicoes), its file and its form are chosen.
    bool ExisteEleicao(const TEleicaoID id) const;
    const std::string& GetVersaoPacoteEleicao(const TEleicaoID id) const;
    const CSituacoesEleicoes& GetSituacoesEleicoes(const TEleicaoID id) const;
    // fn 5649: a copy of the elections, all of them for the municipality 0, else those whose municipalities hold it or
    // 0 (CEleicaoPE::PossuiMunicipio). fn 3713: a copy of the pleito with those elections and, for each, its situations
    // (all of them for 0). In use band 2, 5649 lies between GetEleicao (5651) and GetSituacoesEleicoes (5648), so in
    // cpleito.cpp, and they read m_eleicoes, m_versoesPacote and m_situacoes. No record names them: their names, their
    // being members and the parameters' type (uedword, as wide as the bodies' 32-bit compares) are chosen.
    TVectorEleicaoPE GetEleicoesMunicipio(const uedword municipio) const;
    CPleito FiltraMunicipio(const uedword municipio) const;

private:
    std::vector<CSituacoesEleicoes> GetSituacoesMunicipio(const uedword municipio) const;

    TPleitoID m_id;
    std::string m_nome;
    api::CDate m_data;
    TVectorEleicaoPE m_eleicoes;
    TMapVersaoPacoteEleicao m_versoesPacote;
    std::vector<CSituacoesEleicoes> m_situacoes;
};

} // namespace comum::md
