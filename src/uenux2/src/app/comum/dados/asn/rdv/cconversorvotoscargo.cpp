#include "app/comum/dados/asn/rdv/cconversorvotoscargo.h"

#include <format>
#include <vector>

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/app/dados/asn/cconversorcargoid.hpp"

namespace comum::asn {

// (original lines 11-18: content not recovered)
#line 19
CConversorVotosCargo::CConversorVotosCargo(const md::CVotosCargos::SCargoInfo& cargoInfo) : m_cargoInfo(cargoInfo)
{
}

// (original lines 23-24: content not recovered)
#line 25
ModuloRegistroDigitalVoto::VotosCargo CConversorVotosCargo::DoConverte(const TDado& dado) const
{
    if (dado.first.cargo != m_cargoInfo.cargo) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7976, "Cargo info incompatível");
    }

    const ecourna::app::dados::asn::CConversorCargoID conversorCargo;
    TEntidade entidade;
    entidade.set_idCargo() = conversorCargo.Converte(ecourna::app::dados::TCargoID(m_cargoInfo.cargo));
    entidade.set_quantidadeEscolhas(m_cargoInfo.quantidadeEscolhas);
    for (const md::CVoto& voto : dado.second.GetVotos()) {
        const ModuloRegistroDigitalVoto::Voto entidadeVoto = m_conversorVoto.Converte(voto);
        entidade.set_votos().push_back(entidadeVoto);
    }
    return entidade;
}


std::pair<md::CVotosCargos::SCargoInfo, md::CVotos> CConversorVotosCargo::DoDesconverte(const TEntidade& entidade) const
{
    const ecourna::app::dados::asn::CConversorCargoID conversorCargo;
    const ecourna::app::dados::TCargoID cargo = conversorCargo.Deconverte(entidade.get_idCargo());


    if (cargo != m_cargoInfo.cargo) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7977, std::format("Cargo {} difere do esperado: {}", cargo.Get(), m_cargoInfo.cargo));
    }

    const uebyte quantidadeEscolhas = entidade.get_quantidadeEscolhas().getValue();
    if (quantidadeEscolhas != m_cargoInfo.quantidadeEscolhas) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7978, std::format("Quantidade de escolhas difere do esperado: {}/{}",
            quantidadeEscolhas, m_cargoInfo.quantidadeEscolhas));
    }

    std::vector<md::CVoto> votos;
    for (const auto& entidadeVoto : entidade.get_votos()) {
        const md::CVoto voto = m_conversorVoto.Desconverte(entidadeVoto);
        votos.push_back(voto);
    }
    return TDado(m_cargoInfo, md::CVotos(votos));
}

} // namespace comum::asn
