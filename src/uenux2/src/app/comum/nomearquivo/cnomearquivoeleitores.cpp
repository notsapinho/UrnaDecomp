// The reconstruction's note, not TSE's text: comum::NomeArquivoEleitores and NomeArquivoEleitoresTTE (target fns 3745
// and 5727), declared in cnomearquivo.h, which says what they rest on. No record names this file: its name and path,
// and the order of the two, are chosen. That it is not cnomearquivo.cpp is measured
// (src/units/279-uenux2-nomearquivoeleitores-cmesarioregistrado.mk). comum::NomesArquivosEleicao (fn 3744) follows
// them, as use band 3 orders 3745 and 3744; src/units/388-uenux2-nomesarquivos.mk says what places it here.
#include "app/comum/nomearquivo/cnomearquivo.h"

namespace comum {

std::string NomeArquivoEleitores(const SIdentificacaoArquivo& identificacao, uedword municipio, ueword zona,
    ueword secao)
{
    return CNomeArquivo::NomeArquivoSecao(identificacao.fase, identificacao.idPE, identificacao.uf, municipio, zona,
        secao, "el", "dat");
}

std::string NomeArquivoEleitoresTTE(const SIdentificacaoArquivo& identificacao, uedword municipio, ueword zona,
    ueword secao)
{
    return CNomeArquivo::NomeArquivoSecao(identificacao.fase, identificacao.idPE, identificacao.uf, municipio, zona,
        secao, "tte", "dat");
}

std::map<md::ETipoAbrangencia, std::string> NomesArquivosEleicao(const SIdentificacaoArquivo& identificacao,
    const md::CPleito& pleito, TMunicipioID municipio, md::TEleicaoID idEleicao, const std::string& tipo,
    const std::string& extensao)
{
    std::map<md::ETipoAbrangencia, std::string> nomes;
    const md::CEleicaoPE eleicao = pleito.GetEleicao(idEleicao);
    if (eleicao.PossuiCargoCandidato()) {
        nomes.insert({eleicao.GetAbrangencia(), CNomeArquivo::NomeArquivoAbrangencia(identificacao.fase, idEleicao,
            identificacao.uf, municipio, eleicao.GetAbrangencia(), tipo, extensao)});
    }
    return nomes;
}


} // namespace comum
