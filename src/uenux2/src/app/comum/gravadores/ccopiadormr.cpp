// comum::CCopiadorMR (this file's name and path are the reconstruction's choice: no record names the class;
// app/comum/gravadores/ccopiadormr.h says what places it here). It holds the constructor, target fn 1276, which has no
// record: its line is a choice. The class's slots 2 and 3 (fns 5874, 5873) are not reconstructed
// (src/units/160-uenux2-comum-gravadores-classes-pending.cpp).

#include "app/comum/gravadores/ccopiadormr.h"

#include "app/comum/gravadores/cgravadorutil.h"

namespace comum {

CCopiadorMR::CCopiadorMR(TMunicipioID municipio, TZonaID zona, TSecaoID secao, char fase,
    EExtensaoArquivoResultado extensao)
    : m_nomeArquivo(CGravadorUtil::DeterminaNomeArquivo(municipio, zona, secao, fase, extensao))
{
}

} // namespace comum
