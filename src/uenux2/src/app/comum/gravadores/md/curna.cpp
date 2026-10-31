// Reconstruction: comum::md::CUrna's constructors (target fns 2854 and 2855) and ValidaCriacao (fn 5862), which both
// call. ValidaCriacao's throws are records of the target (lines 58 to 69, column 15); the constructors have none, so
// their lines are a choice, above the member they call.

#include "app/comum/gravadores/md/curna.h"

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::md {

CUrna::CUrna(EUrnaTipo tipoUrna, const std::string& versaoVotacao, const CCorrespondenciaResultado& correspondencia,
    ETipoArquivo tipoArquivo, const std::string& numeroSerieFV)
    : m_tipoUrna(tipoUrna), m_versaoVotacao(versaoVotacao), m_correspondencia(correspondencia),
      m_tipoArquivo(tipoArquivo), m_flag(true), m_numeroSerieFV(numeroSerieFV)
{
    ValidaCriacao();
}

CUrna::CUrna(EUrnaTipo tipoUrna, const std::string& versaoVotacao, const CCorrespondenciaResultado& correspondencia,
    ETipoArquivo tipoArquivo, const std::string& numeroSerieFV, const CTipoApuracaoSA& tipoApuracao)
    : m_tipoUrna(tipoUrna), m_versaoVotacao(versaoVotacao), m_correspondencia(correspondencia),
      m_tipoArquivo(tipoArquivo), m_flag(true), m_numeroSerieFV(numeroSerieFV), m_tipoApuracao(tipoApuracao)
{
    ValidaCriacao();
}

// (original lines 27-54: content not recovered)
#line 55
void CUrna::ValidaCriacao() const
{
    if (m_tipoUrna == eUrnaSemTipo) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8689, "Tipo de urna inválido");
    }
    if (m_tipoArquivo == TIPO_ARQUIVO_SEM_TIPO) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8690, "Tipo de arquivo inválido");
    }
    if (m_numeroSerieFV.size() != 8) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8691, "Serial da MV inválido [" + m_numeroSerieFV + "]");
    }


    if (m_numeroSerieFV.find_first_not_of("0123456789ABCDEFabcdef") != std::string::npos) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8692, "Serial da MV inválido [" + m_numeroSerieFV + "]");
    }
}

} // namespace comum::md
