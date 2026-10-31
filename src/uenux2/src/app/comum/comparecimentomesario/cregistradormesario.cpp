#include "app/comum/comparecimentomesario/cregistradormesario.h"

namespace comum {

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

} // namespace comum

// <stubs>
// f10337 · 1733 B · unmatched · name unknown
// void f10337(i32) { ... }
// </stubs>
