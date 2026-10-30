#include "app/comum/dados/md/municipiozona/ccomplementomunicipio.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

CComplementoMunicipio::CComplementoMunicipio(uedword codigo, short fusoHorario, const CHorarioVerao& horarioVerao)
    : m_codigo(codigo), m_fusoHorario(fusoHorario), m_horarioVerao(horarioVerao)
{
    ValidaCriacao();
}

CComplementoMunicipio::CComplementoMunicipio(uedword codigo, short fusoHorario)
    : m_codigo(codigo), m_fusoHorario(fusoHorario)
{
    ValidaCriacao();
}

// (original lines 19-33: content not recovered)
#line 34
const CHorarioVerao& CComplementoMunicipio::GetHorarioVerao() const
{
    if (!m_horarioVerao.has_value()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8112, "Não há informação de horário de verão.");
    }
    return *m_horarioVerao;
}

// (original lines 42-43: content not recovered)
#line 44
void CComplementoMunicipio::ValidaCriacao() const
{
    if (m_codigo >= 100000) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8113, "Código de município inválido.");
    }


    if (m_fusoHorario < -720 || m_fusoHorario > 720) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8114, "Fuso-horário inválido.");
    }
}

} // namespace comum::md
