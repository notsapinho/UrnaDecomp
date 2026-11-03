// The reconstruction's note, not TSE's text: comum::CGravadorVersoesArquivos::GravaResultado (target fn 11582), the
// class's key function, so this object emits its vtable and implicit destructors (fns 11581, 11580). No record names
// this file: its directory is that of fn 11582's neighbours in its use band (CGravadorWSQ's and CGravadorLog's members),
// and its name the class's, chosen (src/units/122-uenux2-app-comum-gravadores.mk).
#include "app/comum/gravadores/cgravadorversoesarquivos.h"

#include "app/comum/gravadores/asn/cconversorversoesarquivos.h"

namespace comum {

void CGravadorVersoesArquivos::GravaResultado(api::CFile& arquivo) const
{
    asn::GravaArquivo(arquivo, m_versoesArquivos);
}

} // namespace comum
