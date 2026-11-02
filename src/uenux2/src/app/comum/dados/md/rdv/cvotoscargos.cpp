#include "app/comum/dados/md/rdv/cvotoscargos.h"

#include <algorithm>
#include <map>

#include "app/comum/dados/euerdverror.h"
#include "app/comum/dados/md/rdv/ccedula.h"
#include "app/comum/dados/md/rdv/crdvposicionador.h"
namespace comum::md {

// (original lines 11-46: content not recovered)
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

// (original lines 159-190: content not recovered)
#line 191
void CVotosCargos::InsereCedula(const CRdvPosicionador& posicionador, const CCedula& cedula)
{
    ConfereCedula(cedula);
    TMapa mapa(m_mapa);
    for (const auto& [cargo, voto] : cedula.GetVotos()) {
        const auto it = mapa.find(SCargoInfo{cargo});
        if (it == mapa.end()) {
            const std::string mensagem = "Cargo nao encontrado " + std::to_string(cargo);
            throw api::CUeRdvError(api::EUE_RDV_CEDULA_CARGO_NAO_ENCONTRADO, mensagem);
        }
        it->second.Insere(voto, posicionador.Posicao(it->second.GetVotos(), voto));
    }
    m_mapa.swap(mapa);
}

// (original lines 206-242: content not recovered)
#line 243
void CVotosCargos::ConfereCedula(const CCedula& cedula) const
{
    if (cedula.GetVotos().size() != QuantidadeEscolhas()) {
        const std::string mensagem = "Tamanho da cedula (" + std::to_string(cedula.GetVotos().size()) +
                                     ") difere do esperado (" + std::to_string(QuantidadeEscolhas()) + ")";
        throw api::CUeRdvError(api::EUE_RDV_TAMANHO_CEDULA, mensagem);
    }

    std::map<TCargoID, size_t> quantidades;
    for (const auto& [cargo, voto] : cedula.GetVotos()) {
        quantidades[cargo]++;
    }
    for (const auto& [cargo, quantidade] : quantidades) {
        const auto it = m_mapa.find(SCargoInfo{cargo});
        if (it == m_mapa.end()) {
            const std::string mensagem = "Cedula com cargo nao encontrado (" + std::to_string(cargo) + ")";
            throw api::CUeRdvError(api::EUE_RDV_CEDULA_COM_CARGO_NAO_ENCONTRADO, mensagem);
        }
        if (quantidade != it->first.quantidadeEscolhas) {
            const std::string mensagem = "Cedula do cargo " + std::to_string(cargo) + " com numero de votos (" +
                                         std::to_string(quantidade) + ") diferente da quantidade de escolhas (" +
                                         std::to_string(it->first.quantidadeEscolhas) + ")";
            throw api::CUeRdvError(api::EUE_RDV_CEDULA_QUANTIDADE_ESCOLHAS, mensagem);
        }
    }

    for (const auto& [cargo, voto] : cedula.GetVotos()) {
        const SCargoInfo& info = m_mapa.find(SCargoInfo{cargo})->first;
        switch (voto.GetTipo()) {
            case CVoto::NOMINAL:
                if (voto.GetNumero().size() != info.numeroDigitos) {
                    const std::string mensagem = "Voto nominal para o cargo " + std::to_string(cargo) +
                                                 " com tamanho (" + std::to_string(voto.GetNumero().size()) +
                                                 ") diferente do numero de digitos (" +
                                                 std::to_string(info.numeroDigitos) + ")";
                    throw api::CUeRdvError(api::EUE_RDV_CEDULA_TAMANHO_VOTO_NOMINAL, mensagem);
                }
                break;
            case CVoto::NULO_POR_REPETICAO: {
                if (info.quantidadeEscolhas == 1) {
                    const std::string mensagem =
                        "Voto nulo por repeticao para o cargo " + std::to_string(cargo) + " que so tem uma escolha";
                    throw api::CUeRdvError(api::EUE_RDV_CEDULA_NULO_REPETICAO_UMA_ESCOLHA, mensagem);
                }

                const auto& votos = cedula.GetVotos();
                const auto nominal =
                    std::find(votos.begin(), votos.end(), SVotoCargo{cargo, CVoto(CVoto::NOMINAL, voto.GetNumero())});
                if (nominal == votos.end()) {
                    const std::string mensagem = "Voto nulo por repeticao para o cargo " +
                                                 std::to_string(cargo) +
                                                 " sem voto nominal correspondente";
                    throw api::CUeRdvError(api::EUE_RDV_CEDULA_NULO_REPETICAO_SEM_NOMINAL, mensagem);
                }
                break;
            }
            default:
                break;
        }
    }
}

} // namespace comum::md
