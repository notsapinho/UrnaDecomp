#include "app/comum/dados/asn/rdv/cconversoreleicoesvota.h"

#include <algorithm>
#include <format>
#include <string>
#include <utility>

#include "app/comum/dados/asn/rdv/cconversorvotoscargo.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/app/dados/asn/cconversorcargoid.hpp"

namespace comum::asn {

// (original lines 14-29: content not recovered)
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
            const md::CVotos& votos = votosCargos.GetVotos(info.cargo);
            eleicaoVota.set_votosCargos().push_back(conversor.Converte(CConversorVotosCargo::TDado(info, votos)));
        }
        eleicoesVota.push_back(eleicaoVota);
    }
    return entidade;
}

// (original lines 59-63: content not recovered)
#line 64
md::CVotosEleicoesVota CConversorEleicoesVota::DoDesconverte(const TEntidade& entidade) const
{
    if (!entidade.eleicoesVota_isSelected()) {


        throw CUeComumDadosError(EUE_COMUM_DADOS_7967, "Dado não é do Vota");
    }

    const TEntidade::eleicoesVota::value_type& eleicoesVota = entidade.get_eleicoesVota();
    if (eleicoesVota.size() != m_cargos.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7968, "Eleições incompatíveis");
    }

    const ecourna::app::dados::asn::CConversorCargoID conversorCargo;
    md::CVotosEleicoesVota::TMapa votosEleicoes;
    for (const ModuloRegistroDigitalVoto::EleicaoVota& eleicaoVota : eleicoesVota) {
        md::CVotosCargos::TMapa votosCargos;
        const md::TEleicaoID eleicao = eleicaoVota.get_idEleicao().getValue();

        // (original lines 83-90: content not recovered)
#line 91
        const auto cargos = m_cargos.find(eleicao);
        if (cargos == m_cargos.end()) {

            throw CUeComumDadosError(EUE_COMUM_DADOS_7969, std::format("Eleição {} não encontrada", eleicao));
        }
        for (const ModuloRegistroDigitalVoto::VotosCargo& votosCargo : eleicaoVota.get_votosCargos()) {
            const md::TCargoID idCargo = conversorCargo.Deconverte(votosCargo.get_idCargo());
            const auto cargo = std::find_if(cargos->second.begin(), cargos->second.end(),
                                            [idCargo](const md::CCargo& c) { return c.GetID() == idCargo; });

            // (original lines 101-102: content not recovered)
#line 103
            if (cargo == cargos->second.end()) {
                throw CUeComumDadosError(EUE_COMUM_DADOS_7970, std::format("Cargo {} não encontrado para eleição {}", idCargo, eleicao));
            }
            const CConversorVotosCargo conversor({cargo->GetID(), cargo->GetTipo(), cargo->GetNumeroDigitos(), cargo->GetQtdeEscolhas()});

            votosCargos.insert(conversor.Desconverte(votosCargo));
        }
        votosEleicoes.insert(std::make_pair(eleicao, md::CVotosCargos(votosCargos)));
    }
    return md::CVotosEleicoesVota(votosEleicoes);
}

} // namespace comum::asn
