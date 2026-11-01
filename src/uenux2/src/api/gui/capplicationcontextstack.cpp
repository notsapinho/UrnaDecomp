// Reconstruction's note, not TSE's text: api::CApplicationContextGuard, CApplicationContextStack and the two factories
// that build an api::CApplicationContext (/home/rubio/tse/uenux2/src/api/gui/capplicationcontextstack.cpp). The record
// fixes line 45 (the guard's constructor from a stack and a context, inlined into target fn 676), and the target's use
// band puts CriaContextoPadrao ahead of the guard's constructor; every other line, CriaContextoAplicacao's place
// included, and the include order are chosen; src/units/193-uenux2-capplicationcontextstack.mk has the rest.
#include "api/gui/capplicationcontextstack.h"

#include <algorithm>
#include <exception>
#include <iterator>

#include "api/gui/capplication.h"
#include "api/gui/eueguierror.h"

namespace api {

CApplicationContext CriaContextoAplicacao(int tipo, std::string titulo, std::string descricao, std::string detalhe)
{
    return CApplicationContext(std::move(titulo), std::move(descricao), std::move(detalhe), Actions(tipo), 0);
}

CApplicationContext CriaContextoPadrao(std::string titulo, std::string descricao)
{
    return CApplicationContext(std::move(titulo), std::move(descricao),
                               "Tire uma foto dessa tela em que apareça o QR Code ao lado e envie para a equipe de "
                               "suporte para receber auxílio para resolução do problema.",
                               Actions(1), 1);
}

// (original lines 30-40: content not recovered)
#line 41
CApplicationContextGuard::CApplicationContextGuard(CApplicationContextStack& stack, CApplicationContext context)
    : m_stack(stack), m_context(std::move(context))
{
    if (!m_stack.Push(m_context)) {
        throw CUeGuiError(EUE_GUI_APPLICATIONCONTEXTGUARD_CONTEXTO_NAO_CRIADO, "O contexto não pôde ser criado");
    }
}

bool CApplicationContextStack::Push(CApplicationContext context)
{
    if (context.m_padrao && !m_contextos.empty() && !m_contextos.back().m_padrao) {
        return false;
    }
    m_contextos.push_back(std::move(context));
    return true;
}

void CApplicationContextStack::Pop(const CApplicationContext& context)
{
    auto it = std::find(m_contextos.rbegin(), m_contextos.rend(), context);
    if (it != m_contextos.rend()) {
        m_contextos.erase(std::prev(it.base()), m_contextos.end());
    }
}

CApplicationContextGuard::~CApplicationContextGuard()
{
    if (!std::uncaught_exceptions()) {
        m_stack.Pop(m_context);
    }
}

} // namespace api
