// Reconstruction notes: comum::md::CDetalheConsulta's constructor, which binaryen inlines into its one caller,
// comum::asn::CConversorDetalheConsulta::DoDesconverte (target fn 11377). Fragment 225 has the rest.
#include "app/comum/dados/md/processoeleitoral/cdetalheconsulta.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 9-20: content not recovered)
#line 21
CDetalheConsulta::CDetalheConsulta(const std::string& nome, const std::string& pergunta,
                                   const TVectorRespostaConsulta& respostas, const std::string& textoFonetico)
    : m_nome(nome),
      m_pergunta(pergunta),
      m_respostas(respostas),
      m_textoFonetico(textoFonetico)
{
    if (m_pergunta.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8146, "Pergunta inválida.");
    }
    if (m_respostas.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8147, "Conjunto de respostas vazio.");
    }
}

} // namespace comum::md
