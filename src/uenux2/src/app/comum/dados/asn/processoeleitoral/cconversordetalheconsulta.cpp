// Reconstruction: comum::asn::CConversorDetalheConsulta::DoDesconverte (target fn 11377), over FormataPergunta, which
// binaryen inlines into it. No record names this file (its header says why the path is chosen); fragment 225 has the
// rest.
#include "app/comum/dados/asn/processoeleitoral/cconversordetalheconsulta.h"

#include <algorithm>
#include <iterator>
#include <numeric>

#include "ecourna/api/util/cstringutils.hpp"

namespace comum::asn {

std::string FormataPergunta(const std::string& texto);

CConversorDetalheConsulta::TDado CConversorDetalheConsulta::DoDesconverte(const TEntidade& entidade) const
{
    const std::string nome = entidade.get_nome();
    const std::string pergunta = FormataPergunta(entidade.get_pergunta());
    md::TVectorRespostaConsulta respostas;
    std::transform(entidade.get_respostas().begin(), entidade.get_respostas().end(), std::back_inserter(respostas),
                   [](const ModuloEleicao::RespostaPergunta& resposta) {
                       const std::string& descricao = resposta.get_resposta();
                       const ASN1::GeneralString textoFonetico =
                           resposta.textoFonetico_isPresent() ? resposta.get_textoFonetico() : ASN1::GeneralString("");
                       return md::CRespostaConsulta(resposta.get_numero().getValue(), descricao, textoFonetico);
                   });
    const std::string textoFonetico =
        entidade.textoFonetico_isPresent() ? entidade.get_textoFonetico() : TEntidade::textoFonetico::value_type("");
    return TDado(nome, pergunta, respostas, textoFonetico);
}

std::string FormataPergunta(const std::string& texto)
{
    std::vector<std::string> partes = ecourna::api::util::CStringUtils::Split(texto, '|');
    std::transform(partes.begin(), partes.end(), partes.begin(),
                   [](const std::string& parte) { return ecourna::api::util::CStringUtils::Trim(parte); });
    return std::accumulate(partes.begin() + 1, partes.end(), partes.front(),
                           [](const std::string& texto, const std::string& parte) { return texto + '|' + parte; });
}

} // namespace comum::asn
