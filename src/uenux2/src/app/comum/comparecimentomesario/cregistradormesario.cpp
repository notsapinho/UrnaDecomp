#include "app/comum/comparecimentomesario/cregistradormesario.h"

#include <algorithm>

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

} // namespace comum
