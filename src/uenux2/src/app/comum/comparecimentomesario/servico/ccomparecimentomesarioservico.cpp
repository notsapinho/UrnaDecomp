// The reconstruction's note, not TSE's text: comum::servico::CComparecimentoMesarioServico's constructor, which no target
// function holds (fn 815 inlines it), and its destructor (fns 3607 and 10312). No record names a line: their order is
// chosen.
#include "app/comum/comparecimentomesario/servico/ccomparecimentomesarioservico.h"

#include "api/persistencia/cdaorepositorio.hpp"

namespace comum::servico {

CComparecimentoMesarioServico::CComparecimentoMesarioServico()
    : m_dao(api::persistencia::CDAORepositorio::Entregar<dao::IComparecimentoMesarioDAO>())
{
}

CComparecimentoMesarioServico::~CComparecimentoMesarioServico() = default;

} // namespace comum::servico
