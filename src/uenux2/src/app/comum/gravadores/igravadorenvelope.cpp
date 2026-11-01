// comum::IGravadorEnvelope's constructor (this file's name and path are the reconstruction's choice: no record names
// the class's file; app/comum/gravadores/igravadorenvelope.h says what is recovered). The constructor has no target
// index of its own: binaryen inlines it into its one caller, CGravadorEnvelopeArquivo's constructor (target fn 5856).

#include "app/comum/gravadores/igravadorenvelope.h"

#include "app/comum/gravadores/cgravadorutil.h"

namespace comum {

IGravadorEnvelope::IGravadorEnvelope(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona,
    TLocalID local, TSecaoID secao, char fase, EExtensaoArquivoResultado extensao, ESavdArquivoUE arquivoSavd,
    md::CEnvelopeGenerico::Tipo tipoEnvelope, const md::estadoaplicacao::CDadoCorrespondencia& correspondencia)
    : IGravador(municipio, zona, local, secao, fase, extensao, arquivoSavd),
      m_dataHora(dataHora),
      m_faseUrna(CGravadorUtil::ConverteFase(fase)),
      m_tipoUrna(eUrnaVota),
      m_tipoEnvelope(tipoEnvelope),
      m_correspondencia(correspondencia)
{
}

} // namespace comum
