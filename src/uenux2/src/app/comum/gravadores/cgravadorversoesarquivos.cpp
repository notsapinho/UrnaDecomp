// The reconstruction's note, not TSE's text: comum::CGravadorVersoesArquivos's constructor, which fn 12098 holds inlined
// (no index; unrooted), and GravaResultado (target fn 11582), the class's key function, so this object emits its vtable
// and implicit destructors (fns 11581, 11580). No record names this file: its directory is a reading of the data, where
// its vtable (@1557240) lies between cgravadorutil.cpp's records and cgravadorwsq.cpp's, and its name the class's,
// chosen (src/units/122-uenux2-app-comum-gravadores.mk).
#include "app/comum/gravadores/cgravadorversoesarquivos.h"

#include "app/comum/carquivosresultado.h"
#include "app/comum/gravadores/asn/cconversorversoesarquivos.h"

namespace comum {

CGravadorVersoesArquivos::CGravadorVersoesArquivos(TMunicipioID municipio, TZonaID zona, TLocalID local,
    TSecaoID secao, char fase, const md::CVersoesArquivos& versoesArquivos)
    : IGravador(municipio, zona, local, secao, fase, EXTENSAO_MR_VER, static_cast<ESavdArquivoUE>(70)),
      m_versoesArquivos(versoesArquivos)
{
}

void CGravadorVersoesArquivos::GravaResultado(api::CFile& arquivo) const
{
    asn::GravaArquivo(arquivo, m_versoesArquivos);
}

} // namespace comum
