#include "app/comum/dados/asn/rdv/cconversoreleicoesvota.h"

#include <string>
#include <utility>

#include "app/comum/dados/asn/rdv/cconversorvotoscargo.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 11-29: content not recovered)
#line 30
ModuloRegistroDigitalVoto::Eleicoes CConversorEleicoesVota::DoConverte(const TDado& dado) const
{
    const md::CVotosEleicoesVota::TMapa& votosEleicoes = dado.GetMapa();
    if (votosEleicoes.size() != m_cargos.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7965, "Eleições incompatíveis");
    }

    TEntidade entidade;
    TEntidade::eleicoesVota::reference eleicoesVota = entidade.select_eleicoesVota();
    for (const auto& [eleicao, votosCargos] : votosEleicoes) {
        ModuloRegistroDigitalVoto::EleicaoVota eleicaoVota;
        eleicaoVota.set_idEleicao(ModuloRegistroDigitalVoto::EleicaoVota::idEleicao::value_type(eleicao));

        const auto cargos = m_cargos.find(eleicao);
        if (cargos == m_cargos.end()) {

            throw CUeComumDadosError(EUE_COMUM_DADOS_7966, "Eleição " + std::to_string(eleicao) + " não encontrada");
        }
        for (const md::CCargo& cargo : cargos->second) {
            const md::CVotosCargos::SCargoInfo info{cargo.GetID(), cargo.GetTipo(), cargo.GetNumeroDigitos(), cargo.GetQtdeEscolhas()};
            const CConversorVotosCargo conversor(info);
            const md::CVotos& votos = votosCargos.GetVotos(cargo.GetID());
            eleicaoVota.set_votosCargos().push_back(conversor.Converte(std::make_pair(info, votos)));
        }
        eleicoesVota.push_back(eleicaoVota);
    }
    return entidade;
}

// (original lines 59-62: content not recovered)
#line 63
} // namespace comum::asn
