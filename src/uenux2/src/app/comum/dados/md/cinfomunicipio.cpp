#include "app/comum/dados/md/cinfomunicipio.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

CInfoMunicipio::CInfoMunicipio(uedword codigo, const std::string& nome, short fusoHorario, bool urnaBiometrica)
    : m_codigo(codigo), m_nome(nome), m_fusoHorario(fusoHorario), m_urnaBiometrica(urnaBiometrica)
{
    ValidaCriacao();
}

CInfoMunicipio::CInfoMunicipio(uedword codigo, const std::string& nome, short fusoHorario, bool urnaBiometrica,
    const CHorarioVerao& horarioVerao)
    : m_codigo(codigo), m_nome(nome), m_fusoHorario(fusoHorario), m_urnaBiometrica(urnaBiometrica),
      m_horarioVerao(horarioVerao)
{
    ValidaCriacao();
}

// (original lines 23-47: content not recovered)
#line 48
const CHorarioVerao& CInfoMunicipio::GetHorarioVerao() const
{
    if (!m_horarioVerao.has_value()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8008, "Não há informação de horário de verão.");
    }
    return *m_horarioVerao;
}

// (original lines 56-57: content not recovered)
#line 58
void CInfoMunicipio::ValidaCriacao() const
{
    if (m_codigo >= 100000) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8009, std::format("Código de município inválido: {}", m_codigo));
    }


    if (m_nome.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8010, "Nome vazio.");
    }
    if (m_fusoHorario < -720 || m_fusoHorario > 720) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8011, std::format("Fuso-horário inválido: {}", m_fusoHorario));
    }
}

} // namespace comum::md
