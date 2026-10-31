#include "app/comum/dados/chv.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/pattern/singleton.hpp"
namespace comum {

// (original lines 9-26: content not recovered)
#line 27
SINGLETON_IMPL_GET_INST(CHV, s_mutex, s_instancia)

// (original lines 29-69: content not recovered)
#line 70
std::unique_ptr<CHV> CHV::s_instancia;
std::mutex CHV::s_mutex;

// (original lines 73-105: content not recovered)
#line 106
const md::CHorarioVerao& CHV::GetHorarioVerao() const
{
    VerificaEntraEmHorarioVerao("GetHorarioVerao");
    return m_horarioVerao.GetHorarioVerao();
}

// (original lines 112-113: content not recovered)
#line 114
void CHV::VerificaEntraEmHorarioVerao(const std::string& funcao) const
{
    if (!m_horarioVerao.TemHorarioVerao()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7870, std::format("{} - não entra em horário de verão", funcao));
    }
}

} // namespace comum
