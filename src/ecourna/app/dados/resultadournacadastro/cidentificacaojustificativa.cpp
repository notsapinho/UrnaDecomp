#include "ecourna/app/dados/resultadournacadastro/cidentificacaojustificativa.hpp"

namespace ecourna::app::dados {

CIdentificacaoJustificativa::CIdentificacaoJustificativa(const CRegistroIdentificacaoEleitor& identificacaoEleitor,
                                                         TAno anoNascimentoEleitor)
    : m_identificacaoEleitor(identificacaoEleitor), m_anoNascimentoEleitor(anoNascimentoEleitor)
{
}

} // namespace ecourna::app::dados
