#include "ecourna/app/dados/asn/resultadournacadastro/cconversordadoscomparecimento.hpp"

#include "ecourna/app/dados/asn/resultadournacadastro/cconversorcomparecimentomesario.hpp"
#include "ecourna/app/dados/asn/resultadournacadastro/cconversorcomparecimentosecao.hpp"
#include "ecourna/app/dados/asn/resultadournacadastro/cconversoridentificacaojustificativa.hpp"
#include "ecourna/app/dados/asn/sequenciaasn.hpp"

namespace ecourna::app::dados::asn {

CConversorDadosComparecimento::TEntidade CConversorDadosComparecimento::DoConverte(const TDado& dado) const
{
    CConversorIdentificacaoJustificativa conversorJustificativa;
    CConversorComparecimentoSecao conversorSecao;
    CConversorComparecimentoMesario conversorMesario;
    TEntidade entidade;
    entidade.set_identificacaoComparecimento() = conversorSecao.Converte(dado.GetIdentificacaoComparecimento());
    const TVectorIdentificacaoJustificativa justificativas = dado.GetJustificativas();
    entidade.set_justificativas() = ConverteSequencia(justificativas, conversorJustificativa);
    if (dado.HasMesariosAbertura()) {
        const TVectorComparecimentoMesario mesarios = dado.GetMesariosAbertura();
        const auto sequencia = ConverteSequencia(mesarios, conversorMesario);
        TEntidade::mesariosAbertura::reference destino = entidade.set_mesariosAbertura();
        destino.insert(destino.begin(), sequencia.begin(), sequencia.end());
    } else {
        entidade.omit_mesariosAbertura();
    }
    if (dado.HasMesariosEncerramento()) {
        const TVectorComparecimentoMesario mesarios = dado.GetMesariosEncerramento();
        const auto sequencia = ConverteSequencia(mesarios, conversorMesario);
        TEntidade::mesariosEncerramento::reference destino = entidade.set_mesariosEncerramento();
        destino.insert(destino.begin(), sequencia.begin(), sequencia.end());
    } else {
        entidade.omit_mesariosEncerramento();
    }
    return entidade;
}

CConversorDadosComparecimento::TDado CConversorDadosComparecimento::DoDeconverte(const TEntidade& entidade) const
{
    CConversorIdentificacaoJustificativa conversorJustificativa;
    CConversorComparecimentoSecao conversorSecao;
    CConversorComparecimentoMesario conversorMesario;
    auto justificativasAsn = entidade.get_justificativas();
    const TVectorIdentificacaoJustificativa justificativas = DeconverteSequencia(justificativasAsn, conversorJustificativa);
    const CComparecimentoSecao secao = conversorSecao.Deconverte(entidade.get_identificacaoComparecimento());
    std::optional<TVectorComparecimentoMesario> mesariosAbertura;
    std::optional<TVectorComparecimentoMesario> mesariosEncerramento;
    if (entidade.mesariosAbertura_isPresent()) {
        auto mesariosAsn = entidade.get_mesariosAbertura();
        mesariosAbertura = DeconverteSequencia(mesariosAsn, conversorMesario);
    }
    if (entidade.mesariosEncerramento_isPresent()) {
        auto mesariosAsn = entidade.get_mesariosEncerramento();
        mesariosEncerramento = DeconverteSequencia(mesariosAsn, conversorMesario);
    }
    return TDado(justificativas, secao, mesariosAbertura, mesariosEncerramento);
}

} // namespace ecourna::app::dados::asn
