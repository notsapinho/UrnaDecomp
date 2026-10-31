#include "app/comum/gravadores/asn/cconversorversoesarquivos.h"

namespace comum::asn {

ModuloVersaoArquivos::EntidadeVersaoArquivos::arquivos::value_type ConverteArquivos(const md::CVersoesArquivos::TMapVersoes& versoes)
{
    ModuloVersaoArquivos::EntidadeVersaoArquivos::arquivos::value_type arquivos;
    for (const auto& versao : versoes) {
        ModuloTiposEleitorais::ArquivoAssinatura arquivo;
        arquivo.set_nomeArquivo(versao.first);
        arquivo.set_assinatura(versao.second);
        arquivos.push_back(arquivo);
    }
    return arquivos;
}

CConversorVersoesArquivos::TEntidade CConversorVersoesArquivos::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_versaoTag(dado.GetVersaoTag());
    entidade.set_arquivos() = ConverteArquivos(dado.GetVersoes());
    return entidade;
}

CConversorVersoesArquivos::TDado CConversorVersoesArquivos::DoDesconverte(const TEntidade& entidade) const
{
    const std::string versaoTag = entidade.get_versaoTag();
    TDado::TMapVersoes versoes;
    for (const auto& arquivo : entidade.get_arquivos()) {
        const std::pair<std::string, std::string> versao(arquivo.get_nomeArquivo(), arquivo.get_assinatura());
        versoes.insert(versao);
    }
    return TDado(versaoTag, versoes);
}

} // namespace comum::asn
