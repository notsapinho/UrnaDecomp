#include "app/comum/comparecimentomesario/cregistradormesario.h"

#include <algorithm>
#include <iterator>
#include <ranges>
#include <utility>

#include "app/comum/comparecimentomesario/euecomumcomparecimentomesarioerror.h"

namespace comum {

CRegistradorMesario::~CRegistradorMesario() = default;

void CRegistradorMesario::AtualizaMesarioSecao(const md::CComparecimentoMesario& comparecimento)
{
    const auto it = m_mesariosSecao.find(comparecimento.GetMesario());
    if (it != m_mesariosSecao.end()) {
        it->second = comparecimento;
    } else {
        m_mesariosSecao.insert({comparecimento.GetMesario(), comparecimento});
    }
}

void CRegistradorMesario::Registra(const md::CComparecimentoMesario& comparecimento)
{
    if (comparecimento.PertenceSecao()) {
        AtualizaMesarioSecao(comparecimento);
    }

    if (Find(comparecimento) != nullptr) {
        Update(comparecimento, comparecimento);
    } else {
        Add(comparecimento, comparecimento);
    }
}

std::size_t CRegistradorMesario::QuantidadeMesariosInicio() const
{
    return std::count_if(m_registros.begin(), m_registros.end(),
        [](const auto& registro) { return registro.first.GetPeriodoPresente() == 1; });
}

std::size_t CRegistradorMesario::QuantidadeMesariosFim() const
{
    return std::count_if(m_registros.begin(), m_registros.end(),
        [](const auto& registro) { return registro.first.GetPeriodoPresente() == 2; });
}

CRegistradorMesario& CRegistradorMesario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CRegistradorMesario());
    }
    return *s_inst;
}

bool CRegistradorMesario::HasInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    return s_inst != nullptr;
}

std::unique_ptr<CRegistradorMesario> CRegistradorMesario::s_inst;
std::mutex CRegistradorMesario::s_mutex;

// (original lines 67-81: content not recovered)
#line 82
void CRegistradorMesario::SaveCurrentInternal()
{
    if (m_registros.empty()) {
        throw CUeComumComparecimentoMesarioError(EUE_COMUM_COMPARECIMENTO_MESARIO_CONTAINER_VAZIO, "O contêiner estava vazio");
    }
    m_servico.Inserir(m_corrente->second);
}

std::map<md::CEleitorIdentidade, md::CComparecimentoMesario> CRegistradorMesario::GetMesariosSecaoComBiometria() const
{
    std::map<md::CEleitorIdentidade, md::CComparecimentoMesario> mesarios;
    std::ranges::copy(m_mesariosSecao | std::views::filter([](const auto& mesario) {
                          return mesario.second.GetDedoHabilitacao() != 0;
                      }),
                      std::inserter(mesarios, mesarios.end()));
    return mesarios;
}

std::map<md::CEleitorIdentidade, md::CComparecimentoMesario> CRegistradorMesario::GetMesariosSecaoSemBiometria() const
{
    std::map<md::CEleitorIdentidade, md::CComparecimentoMesario> mesarios;
    std::ranges::copy(m_mesariosSecao | std::views::filter([](const auto& mesario) {
                          return mesario.second.GetDedoHabilitacao() == 0;
                      }),
                      std::inserter(mesarios, mesarios.end()));
    return mesarios;
}

std::map<md::CEleitorIdentidade, md::CComparecimentoMesario> CRegistradorMesario::GetMesariosForaSecao() const
{
    std::map<md::CEleitorIdentidade, md::CComparecimentoMesario> mesarios;
    std::ranges::copy(m_registros |
                          std::views::filter([](const auto& registro) { return !registro.second.PertenceSecao(); }) |
                          std::views::transform([](const auto& registro) {
                              return std::make_pair(registro.second.GetMesario(), registro.second);
                          }),
                      std::inserter(mesarios, mesarios.end()));
    return mesarios;
}

void CRegistradorMesario::Carrega()
{
    m_registros.clear();
    m_corrente = m_registros.end();
    const std::vector<md::CComparecimentoMesario> comparecimentos = m_servico.RecuperarTodos();
    std::for_each(comparecimentos.begin(), comparecimentos.end(), [this](const md::CComparecimentoMesario& comparecimento) {
        Add(comparecimento, comparecimento);
        if (comparecimento.PertenceSecao()) {
            m_mesariosSecao.insert({comparecimento.GetMesario(), comparecimento});
        }
    });
    Reset();
}

} // namespace comum
