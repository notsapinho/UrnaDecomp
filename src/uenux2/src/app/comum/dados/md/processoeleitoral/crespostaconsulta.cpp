// Reconstruction notes: comum::md::CRespostaConsulta's constructor, which binaryen inlines into its one caller,
// comum::asn::CConversorDetalheConsulta::DoDesconverte (target fn 11377). Fragment 225 has the rest.
#include "app/comum/dados/md/processoeleitoral/crespostaconsulta.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 9-22: content not recovered)
#line 23
CRespostaConsulta::CRespostaConsulta(TCandidatoID numero, const std::string& resposta, const std::string& textoFonetico)
    : m_numero(numero),
      m_resposta(resposta),
      m_textoFonetico(textoFonetico)
{
    if (numero > 99999) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8167, "Número de votável inválido.");
    }
    if (m_resposta.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8168, "Resposta inválida.");
    }
}

} // namespace comum::md
