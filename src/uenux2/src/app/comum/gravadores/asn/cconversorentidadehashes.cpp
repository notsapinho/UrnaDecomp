// Reconstruction: CConversorEntidadeHashes::DoConverte (target fn 10266) and comum::asn::GravaArquivo for the hashes'
// entity (target fn 5367). No record names the file or its lines: the file is the converter's, chosen as its header's
// notes say, and so are the lines and the two functions' order. DoConverte's records are its inlined callees'
// (iconversorasn.h:56, CConversorHashArquivo's Converte, binaryen's: its 640-byte frame opens in the loop). What the
// target's 10266 shows, and the source gives: the entity constructed first, the header's converter a named local (its
// vptr stored before the call) and its result a temporary (destroyed right after the assignment), the phase copied for
// ConverteFase, siglaUF and versaoUENUX set before identificacaoUrna (fields 2, 4, then 3), the identification from the
// section, else the contingency, else omitted, the hashes' converter a named local declared after it (its vptr store
// follows the identification's code), and each hash pushed through set_hashesArquivos(), the field's holder loaded
// before the conversion, whose result is cloned through the vtable. As first written it is 46 over 577 rows by pnpm
// wasm score in the whole link, every row an operand row (calls, data addresses, the std::format pieces' packed
// addresses and table slots). The local names are chosen.

#include "app/comum/gravadores/asn/cconversorentidadehashes.h"

#include "api/io/asn/cfileasn.h"
#include "app/comum/asn/cconversorcabecalhoentidade.h"
#include "app/comum/asn/util.h"
#include "app/comum/gravadores/asn/cconversorhasharquivo.h"

namespace comum::asn {

CConversorEntidadeHashes::TEntidade CConversorEntidadeHashes::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    const CConversorCabecalhoEntidade conversorCabecalho;
    entidade.set_cabecalho() = conversorCabecalho.Converte(dado.GetCabecalho());
    entidade.set_fase() = Utils::ConverteFase(dado.GetFase());
    entidade.set_siglaUF(dado.GetSiglaUF());
    entidade.set_versaoUENUX(dado.GetVersaoUENUX());
    if (dado.TemIdentificacaoSecao()) {
        const md::CIdentificacaoSecao& identificacao = dado.GetIdentificacaoSecao();
        ModuloTiposEleitorais::IdentificacaoSecaoEleitoral secao;
        secao.set_municipioZona().set_municipio(identificacao.GetMunicipio());
        secao.set_municipioZona().set_zona(identificacao.GetZona());
        secao.set_local(identificacao.GetLocal());
        secao.set_secao(identificacao.GetSecao());
        entidade.set_identificacaoUrna().select_identificacaoSecaoEleitoral() = secao;
    } else if (dado.TemIdentificacaoContingencia()) {
        const md::CIdentificacaoUrnaContingencia& identificacao = dado.GetIdentificacaoContingencia();
        ModuloTiposEleitorais::IdentificacaoContingencia contingencia;
        contingencia.set_municipioZona().set_municipio(identificacao.GetMunicipio());
        contingencia.set_municipioZona().set_zona(identificacao.GetZona());
        entidade.set_identificacaoUrna().select_identificacaoContingencia() = contingencia;
    } else {
        entidade.omit_identificacaoUrna();
    }
    const CConversorHashArquivo conversorHash;
    for (const api::hash::CHashArquivo& hash : dado.GetHashesArquivos()) {
        entidade.set_hashesArquivos().push_back(conversorHash.Converte(hash));
    }
    return entidade;
}

void GravaArquivo(const api::CFile& arquivo, const md::CEntidadeHashes& hashes)
{
    const CConversorEntidadeHashes conversor;
    api::CFileASN::WriteToFile(arquivo, conversor.Converte(hashes));
}

} // namespace comum::asn
