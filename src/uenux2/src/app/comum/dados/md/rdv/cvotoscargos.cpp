#include "app/comum/dados/md/rdv/cvotoscargos.h"
#include "app/comum/dados/euerdverror.h"
namespace comum::md {

// (original lines 5-46: content not recovered)
#line 47
CVotosCargos::CVotosCargos(TMapa mapa) : m_mapa(std::move(mapa))
{
    if (m_mapa.empty()) {
        throw api::CUeRdvError(api::EUE_RDV_MAPA_VOTOS_VAZIO, "Mapa de votos vazio");
    }

    const TQtdVoto comparecimento = Comparecimento();
    for (const auto& [info, votos] : m_mapa) {
        const TCargoID cargo = info.cargo;
        const TQtdVoto total = votos.Total();
        if (total % info.quantidadeEscolhas != 0) {
            throw api::CUeRdvError(api::EUE_RDV_VOTOS_NAO_MULTIPLO_ESCOLHAS,
                                   "Numero de votos (" + std::to_string(total) + ") do cargo " + std::to_string(cargo) +
                                       " nao eh multiplo da quantidade de escolhas (" +
                                       std::to_string(info.quantidadeEscolhas) + ")");
        }

        const TQtdVoto esperado = comparecimento * info.quantidadeEscolhas;
        if (total != esperado) {
            throw api::CUeRdvError(api::EUE_RDV_VOTOS_DIFERENTE_ESPERADO,
                                   "Numero de votos (" + std::to_string(total) + ") do cargo " + std::to_string(cargo) +
                                       " diferente do esperado (" + std::to_string(esperado) + ")");
        }
    }
}

uebyte CVotosCargos::QuantidadeEscolhas() const
{
    uebyte quantidade = 0;
    for (const auto [info, votos] : m_mapa) {
        quantidade += info.quantidadeEscolhas;
    }
    return quantidade;
}

// (original lines 82-85: content not recovered)
#line 86
const CVotos& CVotosCargos::GetVotos(TCargoID cargo) const
{
    const auto it = m_mapa.find(SCargoInfo{cargo});
    if (it == m_mapa.end()) {
        const std::string mensagem = "Cargo " + std::to_string(cargo) + " nao encontrado";
        throw api::CUeRdvError(api::EUE_RDV_CARGO_NAO_ENCONTRADO, mensagem);
    }
    return it->second;
}

TQtdVoto CVotosCargos::Candidato(TCargoID cargo, std::string numero) const
{
    const auto it = m_mapa.find(SCargoInfo{cargo});
    return it == m_mapa.end() ? 0 : it->second.Candidato(numero);
}

TQtdVoto CVotosCargos::Legenda(TCargoID cargo, std::string numero) const
{
    const auto it = m_mapa.find(SCargoInfo{cargo});
    return it == m_mapa.end() ? 0 : it->second.Legenda(numero);
}

TQtdVoto CVotosCargos::Partido(TCargoID cargo, std::string numero) const
{
    const auto it = m_mapa.find(SCargoInfo{cargo});
    return it == m_mapa.end() ? 0 : it->second.Partido(numero);
}

TQtdVoto CVotosCargos::Nominais(TCargoID cargo) const
{
    const auto it = m_mapa.find(SCargoInfo{cargo});
    return it == m_mapa.end() ? 0 : it->second.TotalQue(&CVoto::EhNominal);
}

TQtdVoto CVotosCargos::Legendas(TCargoID cargo) const
{
    const auto it = m_mapa.find(SCargoInfo{cargo});
    return it == m_mapa.end() ? 0 : it->second.TotalQue(&CVoto::EhLegenda);
}

TQtdVoto CVotosCargos::Nulos(TCargoID cargo) const
{
    const auto it = m_mapa.find(SCargoInfo{cargo});
    return it == m_mapa.end() ? 0 : it->second.TotalQue(&CVoto::EhNulo);
}

TQtdVoto CVotosCargos::Brancos(TCargoID cargo) const
{
    const auto it = m_mapa.find(SCargoInfo{cargo});
    return it == m_mapa.end() ? 0 : it->second.TotalQue(&CVoto::EhBranco);
}

TQtdVoto CVotosCargos::Cargo(TCargoID cargo) const
{
    const auto it = m_mapa.find(SCargoInfo{cargo});
    return it == m_mapa.end() ? 0 : it->second.Total();
}

bool CVotosCargos::Compativel(const CVotosCargos& outro) const
{
    if (m_mapa.size() != outro.m_mapa.size()) {
        return false;
    }
    for (const auto& [info, votos] : outro.m_mapa) {
        const auto it = m_mapa.find(info);
        if (it == m_mapa.end() || info.tipo != it->first.tipo || info.numeroDigitos != it->first.numeroDigitos ||
            info.quantidadeEscolhas != it->first.quantidadeEscolhas) {
            return false;
        }
    }
    return true;
}

} // namespace comum::md

// <stubs>
// f4454 · 5617 B · unmatched · name unknown
// void f4454(i32) { ... }
// </stubs>
