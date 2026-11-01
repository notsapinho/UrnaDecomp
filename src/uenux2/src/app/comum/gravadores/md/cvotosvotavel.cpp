// comum::md::CIdentificacaoVotavel and comum::md::CVotosVotavel (this file's name and path are the reconstruction's
// choice: no record names either class's file; cvotosvotavel.h says what is recovered). It holds the three
// constructors, target fns 5864, 2856 and 5863, none of which has a record: their lines are a choice, and 5864 comes
// before 5863, as their order in their use band gives.

#include "app/comum/gravadores/md/cvotosvotavel.h"

namespace comum::md {

CIdentificacaoVotavel::CIdentificacaoVotavel(TCandidatoID codigo, TPartidoID partido)
    : m_codigo(codigo), m_partido(partido)
{
}

CVotosVotavel::CVotosVotavel(CVoto::ETipo tipo, TCandidatoID candidato, ueword quantidade)
    : m_tipo(tipo), m_candidato(candidato), m_quantidade(quantidade)
{
}

CVotosVotavel::CVotosVotavel(CVoto::ETipo tipo, TCandidatoID candidato, ueword quantidade,
    const CIdentificacaoVotavel& identificacao)
    : m_tipo(tipo), m_candidato(candidato), m_quantidade(quantidade), m_identificacao(identificacao)
{
}

} // namespace comum::md
