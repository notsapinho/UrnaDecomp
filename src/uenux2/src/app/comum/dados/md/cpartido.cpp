// Reconstruction: comum::md::CPartido's constructor and ValidaCriacao. Both are out of line, and binaryen inlines them
// into comum::asn::CConversorPartido::DoDesconverte (target fn 11459), the one caller in the target: the second
// stack-pointer prologue in that body. The records (lines 30, 33, 36) place the throws; the constructor's line is chosen.
#include "app/comum/dados/md/cpartido.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

CPartido::CPartido(ueword numero, const std::string& sigla, const std::string& nome)
    : m_numero(numero), m_sigla(sigla), m_nome(nome)
{
    ValidaCriacao();
}

// (original lines 16-26: content not recovered)
#line 27
void CPartido::ValidaCriacao() const
{
    if (m_numero >= 100) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8050, "Número do partido inválido");
    }
    if (m_sigla.size() >= 25) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8051, "Sigla do partido inválida");
    }
    if (m_nome.size() >= 56) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8052, "Nome do partido inválido");
    }
}

} // namespace comum::md
