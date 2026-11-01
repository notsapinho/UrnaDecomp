#include "app/comum/dados/crdvvota.h"

#include <algorithm>
#include <string>

#include "ecourna/api/pattern/singleton.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

using ecourna::api::util::CStringUtils;

size_t CRdvPosicionadorVota::Posicao(const std::vector<md::CVoto>& votos, const md::CVoto& voto) const
{
    return std::upper_bound(votos.begin(), votos.end(), voto) - votos.begin();
}

md::TQtdVoto CRdvVota::Candidato(md::TCargoID cargo, uedword numero, uebyte digitos) const
{
    const std::string numeroCandidato = CStringUtils::PreencheAEsquerda(std::to_string(numero), '0', digitos);
    return m_votos.Candidato(cargo, numeroCandidato);
}

// (original lines 24-86: content not recovered)
#line 87
SINGLETON_IMPL_GET_INST(CRdvVota, s_mutex, s_instancia)

// (original lines 89-93: content not recovered)
#line 94
std::unique_ptr<CRdvVota> CRdvVota::s_instancia;
std::mutex CRdvVota::s_mutex;

CRdvVota::~CRdvVota() = default;

CRdv::TVotosCargo CRdvVota::GetVotos() const
{
    TVotosCargo votos;
    for (const auto& [eleicao, votosCargos] : m_votos.GetMapa()) {
        for (const auto& [info, votosCargo] : votosCargos.GetMapa()) {
            votos.emplace(info.cargo, votosCargo.GetVotos());
        }
    }
    return votos;
}

md::TQtdVoto CRdvVota::Comparecimento(md::TEleicaoID eleicao) const
{
    return m_votos.Comparecimento(eleicao);
}

CRdv::TVotosCargo CRdvVota::GetVotos(md::TEleicaoID eleicao) const
{
    TVotosCargo votos;
    for (const auto& [info, votosCargo] : m_votos.GetVotos(eleicao).GetMapa()) {
        votos.emplace(info.cargo, votosCargo.GetVotos());
    }
    return votos;
}

md::TQtdVoto CRdvVota::Legenda(md::TCargoID cargo, int numero) const
{
    const std::string numeroLegenda = CStringUtils::PreencheAEsquerda(std::to_string(numero), '0', m_digitosPartido);
    return m_votos.Legenda(cargo, numeroLegenda);
}

md::TQtdVoto CRdvVota::Partido(md::TCargoID cargo, int numero) const
{
    const std::string numeroPartido = CStringUtils::PreencheAEsquerda(std::to_string(numero), '0', m_digitosPartido);
    return m_votos.Partido(cargo, numeroPartido);
}

md::TQtdVoto CRdvVota::Nominais(md::TCargoID cargo) const
{
    return m_votos.Nominais(cargo);
}

md::TQtdVoto CRdvVota::Legendas(md::TCargoID cargo) const
{
    return m_votos.Legendas(cargo);
}

md::TQtdVoto CRdvVota::Nulos(md::TCargoID cargo) const
{
    return m_votos.Nulos(cargo);
}

md::TQtdVoto CRdvVota::Brancos(md::TCargoID cargo) const
{
    return m_votos.Brancos(cargo);
}

md::TQtdVoto CRdvVota::Cargo(md::TCargoID cargo) const
{
    return m_votos.Cargo(cargo);
}

} // namespace comum
