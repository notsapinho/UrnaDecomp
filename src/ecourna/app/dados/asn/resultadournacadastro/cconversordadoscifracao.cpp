#include "ecourna/app/dados/asn/resultadournacadastro/cconversordadoscifracao.hpp"

#include "ecourna/app/dados/asn/octetstringasn.hpp"

namespace ecourna::app::dados::asn {

CConversorDadosCifracao::TEntidade CConversorDadosCifracao::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_chave() = ConverteOctetos(dado.GetChave());
    entidade.set_salt() = ConverteOctetos(dado.GetSalt());
    entidade.set_informacaoAdicional() = ConverteOctetos(dado.GetInformacaoAdicional());
    return entidade;
}

CConversorDadosCifracao::TDado CConversorDadosCifracao::DoDeconverte(const TEntidade& entidade) const
{
    const std::vector<uebyte> chave = DeconverteOctetos(entidade.get_chave());
    const std::vector<uebyte> salt = DeconverteOctetos(entidade.get_salt());
    const std::vector<uebyte> informacaoAdicional = DeconverteOctetos(entidade.get_informacaoAdicional());
    return TDado(chave, salt, informacaoAdicional);
}

} // namespace ecourna::app::dados::asn
