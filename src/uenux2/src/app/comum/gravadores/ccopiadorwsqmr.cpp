// comum::CCopiadorWSQMR (this file's name and path are the reconstruction's choice: no record names the class;
// app/comum/gravadores/ccopiadormr.h, which declares it, says what places it here). It holds the constructor, target fn
// 3827, which has no record: its line is a choice. It is apart from CCopiadorMR's constructor, which it calls: fn 3827
// keeps that call (fn 1276) and takes `this` from its result, where one translation unit inlines it (measured).

#include "app/comum/gravadores/ccopiadormr.h"

namespace comum {

CCopiadorWSQMR::CCopiadorWSQMR(TMunicipioID municipio, TZonaID zona, TSecaoID secao, char fase,
    EExtensaoArquivoResultado extensao)
    : CCopiadorMR(municipio, zona, secao, fase, extensao)
{
}

} // namespace comum
