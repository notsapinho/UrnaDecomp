// The reconstruction's note, not TSE's text: comum::servico::CJustificadorServico's constructor, which no target function
// holds (fn 3742 inlines it), and its destructor (fns 3740 and 11464). No record names a line: their order is chosen.
// RecuperarTodos is fn 5723 (src/units/386-uenux2-carregaeleitores.mk).
#include "app/comum/justificativa/servico/cjustificadorservico.h"

#include "api/persistencia/cdaorepositorio.hpp"

namespace comum::servico {

CJustificadorServico::CJustificadorServico()
    : m_dao(api::persistencia::CDAORepositorio::Entregar<dao::IJustificadorDAO>())
{
}

CJustificadorServico::~CJustificadorServico() = default;

std::vector<ecourna::app::dados::CIdentificacaoJustificativa> CJustificadorServico::RecuperarTodos() const
{
    return m_dao->RecuperarTodos();
}

} // namespace comum::servico
