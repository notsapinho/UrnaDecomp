#include "app/comum/dados/md/chorarioveraomunicipio.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

CHorarioVeraoMunicipio::CHorarioVeraoMunicipio(uedword codigo) : m_codigo(codigo)
{
    ValidaCriacao();
}

CHorarioVeraoMunicipio::CHorarioVeraoMunicipio(uedword codigo, const CHorarioVerao& horarioVerao)
    : m_codigo(codigo), m_horarioVerao(horarioVerao)
{
    ValidaCriacao();
}

// (original lines 20-33: content not recovered)
#line 34
const CHorarioVerao& CHorarioVeraoMunicipio::GetHorarioVerao() const
{
    if (!m_horarioVerao.has_value()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8005, "Não há informação de horário de verão.");
    }
    return *m_horarioVerao;
}

// (original lines 42-43: content not recovered)
#line 44
void CHorarioVeraoMunicipio::ValidaCriacao() const
{
    if (m_codigo >= 100000) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8006, std::format("Código de município inválido: {}", m_codigo));
    }
}

} // namespace comum::md
