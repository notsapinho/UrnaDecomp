// comum::CGravadorWSQ (/home/rubio/tse/uenux2/src/app/comum/gravadores/cgravadorwsq.cpp): the constructor, target fn
// 3796, with ValidaTipoBiometria inlined by clang (one stack frame, set up before IGravador's constructor is called).
// ValidaTipoBiometria's throw is a record of the target (line 73, column 15); the constructor has none, so its line is
// a choice, above the member it calls. The slots and fn 5821 (records at lines 175 and 192) are not written.

#include "app/comum/gravadores/cgravadorwsq.h"

#include "app/comum/gravadores/cgravadorutil.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum {

// (original lines 13-55: content not recovered)
#line 56
CGravadorWSQ::CGravadorWSQ(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona, TLocalID local,
    TSecaoID secao, char fase, EExtensaoArquivoResultado extensao, ESavdArquivoUE arquivoSavd, unsigned int tipoBiometria,
    bool gravaMidiaExterna)
    : IGravador(municipio, zona, local, secao, fase, extensao, arquivoSavd), m_dataHora(dataHora),
      m_faseUrna(CGravadorUtil::ConverteFase(fase)), m_arquivoChave("wsq.pk1"), m_tipoBiometria(tipoBiometria),
      m_versao("10.23.0.1 - DESENVOLVIMENTO"), m_gravaMidiaExterna(gravaMidiaExterna)
{
    ValidaTipoBiometria();
}

// (original lines 66-69: content not recovered)
#line 70
void CGravadorWSQ::ValidaTipoBiometria() const
{
    if (m_tipoBiometria >= 3) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8651, "Argumento tipo de biometria inválido.");
    }
}

} // namespace comum

// <stubs>
// f5821 · 8686 B · unmatched · name unknown
// void f5821(i32, i32, i32) { ... }
// </stubs>
