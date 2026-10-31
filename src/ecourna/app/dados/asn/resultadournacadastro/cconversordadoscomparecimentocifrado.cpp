#include "ecourna/app/dados/asn/resultadournacadastro/cconversordadoscomparecimentocifrado.hpp"

#include "ecourna/app/dados/asn/octetstringasn.hpp"
#include "ecourna/app/dados/asn/resultadournacadastro/cconversordadoscifracao.hpp"

namespace ecourna::app::dados::asn {

CConversorDadosComparecimentoCifrado::TEntidade CConversorDadosComparecimentoCifrado::DoConverte(const TDado& dado) const
{
    CConversorDadosCifracao conversorDadosCifracao;
    TEntidade entidade;
    entidade.set_dadosCifracao() = conversorDadosCifracao.Converte(dado.GetDadosCifracao());
    entidade.set_conteudo() = ConverteOctetos(dado.GetConteudo());
    return entidade;
}

CConversorDadosComparecimentoCifrado::TDado CConversorDadosComparecimentoCifrado::DoDeconverte(const TEntidade& entidade) const
{
    CConversorDadosCifracao conversorDadosCifracao;
    const CDadosCifracao dadosCifracao = conversorDadosCifracao.Deconverte(entidade.get_dadosCifracao());
    const std::vector<uebyte> conteudo = DeconverteOctetos(entidade.get_conteudo());
    return TDado(dadosCifracao, conteudo);
}

} // namespace ecourna::app::dados::asn
