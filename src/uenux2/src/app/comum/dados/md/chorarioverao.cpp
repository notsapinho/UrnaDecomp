// comum::md::CHorarioVerao. The reconstruction's own note: the blank lines stand for text not recovered. Lines 29 and
// 32 are the records of the constructor, which fn 11384 holds inlined; where it begins, and Contem's line, are chosen.
// Fragments 147 and 172 say what the members rest on.
#include "app/comum/dados/md/chorarioverao.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 10-24: content not recovered)
#line 25
CHorarioVerao::CHorarioVerao(const api::CDate& inicio, const api::CDate& fim, int diferenca)
    : m_inicio(inicio), m_fim(fim), m_diferenca(diferenca)
{
    if (fim <= inicio) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8003, "Período inválido.");
    }
    if (diferenca == 0) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8004, "Diferença de horário nula.");
    }
}

bool CHorarioVerao::Contem(const api::CDate& data) const
{
    return m_inicio <= data && data < m_fim;
}

} // namespace comum::md
