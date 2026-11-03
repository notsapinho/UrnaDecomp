// The reconstruction's note, not TSE's text: comum::NomeArquivoEleitores and NomeArquivoEleitoresTTE (target fns 3745
// and 5727), declared in cnomearquivo.h, which says what they rest on. No record names this file: its name and path,
// and the order of the two, are chosen. That it is not cnomearquivo.cpp is measured
// (src/units/279-uenux2-nomearquivoeleitores-cmesarioregistrado.mk).
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

} // namespace comum
