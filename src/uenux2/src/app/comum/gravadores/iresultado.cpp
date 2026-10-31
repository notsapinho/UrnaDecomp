// comum::IResultado and comum::IGravador's constructors (/home/rubio/tse/uenux2/src/app/comum/gravadores/iresultado.cpp),
// one target function, fn 1396: binaryen inlined IResultado's into IGravador's, its one caller. IResultado's throw is a
// record of the target (line 40, column 15); IGravador's constructor has no record, so its line is a choice, after the
// constructor it calls.

#include "app/comum/gravadores/iresultado.h"

#include <format>

#include "app/comum/gravadores/cgravadorutil.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"
#include "app/comum/gravadores/igravador.h"

namespace comum {

// (original lines 16-32: content not recovered)
#line 33
IResultado::IResultado(TMunicipioID municipio, TZonaID zona, TLocalID local, TSecaoID secao, char fase,
    EExtensaoArquivoResultado extensao, ESavdArquivoUE arquivoSavd)
    : m_municipio(municipio), m_zona(zona), m_local(local), m_secao(secao), m_fase(fase),
      m_nomeArquivo(CGravadorUtil::DeterminaNomeArquivo(municipio, zona, secao, fase, extensao)), m_extensao(extensao),
      m_arquivoSavd(arquivoSavd)
{
    if (fase != 'o' && fase != 's' && fase != 't') {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8657, std::format("Fase inválida: {}", fase));
    }
}

IGravador::IGravador(TMunicipioID municipio, TZonaID zona, TLocalID local, TSecaoID secao, char fase,
    EExtensaoArquivoResultado extensao, ESavdArquivoUE arquivoSavd)
    : IResultado(municipio, zona, local, secao, fase, extensao, arquivoSavd)
{
}

} // namespace comum

// <stubs>
// f6043 · 55 B · unmatched · placement: link order · name unknown
// ? f6043(i32, i32, i32) { ... }
// </stubs>
