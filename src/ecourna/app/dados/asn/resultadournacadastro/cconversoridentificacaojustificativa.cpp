#include "ecourna/app/dados/asn/resultadournacadastro/cconversoridentificacaojustificativa.hpp"

#include "ecourna/app/dados/asn/cconversorregistroidentificacaoeleitor.hpp"

namespace ecourna::app::dados::asn {

CConversorIdentificacaoJustificativa::TEntidade CConversorIdentificacaoJustificativa::DoConverte(const TDado& dado) const
{
    CConversorRegistroIdentificacaoEleitor conversorRegistro;
    TEntidade entidade;
    entidade.set_identificacaoEleitor() = conversorRegistro.Converte(dado.GetIdentificacaoEleitor());
    entidade.set_anoNascimentoEleitor(dado.GetAnoNascimentoEleitor());
    return entidade;
}

CConversorIdentificacaoJustificativa::TDado CConversorIdentificacaoJustificativa::DoDeconverte(const TEntidade& entidade) const
{
    CConversorRegistroIdentificacaoEleitor conversorRegistro;
    return TDado(conversorRegistro.Deconverte(entidade.get_identificacaoEleitor()),
                 entidade.get_anoNascimentoEleitor().getValue());
}

} // namespace ecourna::app::dados::asn
