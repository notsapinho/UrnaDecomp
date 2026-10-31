// comum::md::CVersoesArquivos (/home/rubio/tse/uenux2/src/app/comum/gravadores/md/cversoesarquivos.cpp): the
// constructor, target fn 5867, with ValidaCriacao inlined by binaryen (its second stack frame). ValidaCriacao's throws
// are records of the target (lines 28 and 33, column 15); the constructor has none, so its line is a choice, above the
// member it calls.

#include "app/comum/gravadores/md/cversoesarquivos.h"

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::md {

// (original lines 12-13: content not recovered)
#line 14
CVersoesArquivos::CVersoesArquivos(const std::string& versaoTag, const TMapVersoes& versoes)
    : m_versaoTag(versaoTag), m_versoes(versoes)
{
    ValidaCriacao();
}

// (original lines 20-24: content not recovered)
#line 25
void CVersoesArquivos::ValidaCriacao() const
{
    if (m_versaoTag.empty()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8694, "Versão da TAG inválida");
    }


    if (m_versoes.empty()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8695, "Versões de arquivos inválida");
    }
}

} // namespace comum::md
