#include "app/comum/dados/ccandidaturas.h"

#include <format>
#include <mutex>

#include "app/comum/dados/ccandidaturasds.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum {

CCandidaturas& CCandidaturas::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst = std::make_unique<CCandidaturas>();
    }
    return *s_inst;
}

std::unique_ptr<CCandidaturas> CCandidaturas::s_inst;
std::mutex CCandidaturas::s_mutex;

CCandidaturas::CCandidaturas() : CDataMap("CCandidaturas"), m_carregado(true) {}

CCandidaturas::~CCandidaturas() = default;

// (original lines 27-84: content not recovered)
#line 85
const std::string CCandidaturas::RecuperaVersaoPacote(TCargoID cargo) const
{
    const auto versao = m_versoesPacote.find(cargo);
    if (versao == m_versoesPacote.end()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7801, std::format("Versão de pacote não encontrada para o cargo {}", cargo));
    }
    return versao->second;
}


std::vector<TCandidatoID> CCandidaturas::GetCandidatosPartido(TCargoID cargo, TPartidoID partido) const
{
    std::vector<TCandidatoID> candidatos;
    for (const auto& [chave, candidatura] : m_registros) {
        if (candidatura.GetCargoID() == cargo && candidatura.GetTitular().GetSituacao() == 0 &&
            (partido == 0 || candidatura.GetPartidoID() == partido)) {
            candidatos.push_back(candidatura.GetCandidatoID());
        }
    }
    return candidatos;
}

bool CCandidaturas::ExisteCandidato(TCargoID cargo) const
{
    for (const auto& [chave, candidatura] : m_registros) {
        if (candidatura.GetTitular().GetSituacao() == 0 && candidatura.GetCargoID() == cargo) {
            return true;
        }
    }
    return false;
}

std::vector<TCandidatoID> CCandidaturas::GetCandidatos(TCargoID cargo) const
{
    std::vector<TCandidatoID> candidatos;
    for (const auto& [chave, candidatura] : m_registros) {
        if (candidatura.GetCargoID() == cargo && candidatura.GetTitular().GetSituacao() == 0) {
            candidatos.push_back(candidatura.GetCandidatoID());
        }
    }
    return candidatos;
}

md::CCandidatura* CCandidaturas::Busca(TCargoID cargo, TCandidatoID candidato)
{
    return Find(cargo * 1000000 + candidato);
}

// (original lines 133-256: content not recovered)
#line 257
const md::CCandidatura& GetCandidaturaAtual(const std::string& funcao)
{
    const md::CCandidatura* candidatura = CCandidaturas::GetInst().GetCurrent();
    if (candidatura == nullptr) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7805, std::format("{} - não posicionado no candidato corretamente", funcao));
    }
    return *candidatura;
}

namespace {

const md::CDadosCandidato& GetCandidatoAtual(const std::string& funcao, uebyte suplente)
{
    const md::CCandidatura& candidatura = GetCandidaturaAtual(funcao);
    return suplente == 0 ? candidatura.GetTitular() : candidatura.GetSuplente(suplente);
}

} // namespace

std::string CCandidaturasDSNome::operator()() const
{
    const md::CDadosCandidato& candidato = GetCandidatoAtual("CCandidaturasDSNome", m_suplente);
    return candidato.GetNomeUrna();
}

md::CSexo::ESexo CCandidaturasDSSexo::operator()() const
{
    const md::CDadosCandidato& candidato = GetCandidatoAtual("CCandidaturasDSSexo", m_suplente);
    return candidato.GetSexo();
}

} // namespace comum
