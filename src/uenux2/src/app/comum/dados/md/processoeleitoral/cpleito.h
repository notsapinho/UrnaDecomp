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

    const CEleicaoPE& GetEleicao(const TEleicaoID id) const;
    const CSituacoesEleicoes& GetSituacoesEleicoes(const TEleicaoID id) const;

private:
    TPleitoID m_id;
    std::string m_nome;
    api::CDate m_data;
    TVectorEleicaoPE m_eleicoes;
    TMapVersaoPacoteEleicao m_versoesPacote;
    std::vector<CSituacoesEleicoes> m_situacoes;
};

} // namespace comum::md
