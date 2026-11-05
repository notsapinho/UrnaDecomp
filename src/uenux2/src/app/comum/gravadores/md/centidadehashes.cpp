// Reconstruction: comum::md::CEntidadeHashes's constructors and ValidaCriacao (target fn 5855). The throws are
// records of the target (lines 59 and 62, column 15); the constructors have none, and their lines are a choice.

#include "app/comum/gravadores/md/centidadehashes.h"

#include <format>

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::md {

CEntidadeHashes::CEntidadeHashes(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, const std::string& siglaUF,
    const CIdentificacaoSecao& identificacaoSecao, const std::string& versaoUENUX,
    const std::vector<api::hash::CHashArquivo>& hashesArquivos)
    : m_cabecalho(cabecalho), m_fase(fase), m_siglaUF(siglaUF), m_identificacaoSecao(identificacaoSecao),
      m_versaoUENUX(versaoUENUX), m_hashesArquivos(hashesArquivos)
{
    ValidaCriacao();
}

CEntidadeHashes::CEntidadeHashes(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, const std::string& siglaUF,
    const CIdentificacaoUrnaContingencia& identificacaoContingencia, const std::string& versaoUENUX,
    const std::vector<api::hash::CHashArquivo>& hashesArquivos)
    : m_cabecalho(cabecalho), m_fase(fase), m_siglaUF(siglaUF), m_identificacaoContingencia(identificacaoContingencia),
      m_versaoUENUX(versaoUENUX), m_hashesArquivos(hashesArquivos)
{
    ValidaCriacao();
}

// (original lines 30-55: content not recovered)
#line 56
void CEntidadeHashes::ValidaCriacao() const
{
    if (m_fase == '0' || m_fase > FASE_TREINAMENTO) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8672, "Fase inválida");
    }
    if (m_siglaUF.size() != 2) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8673, std::format("UF inválida: {}", m_siglaUF));
    }
}

} // namespace comum::md
