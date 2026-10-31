// comum::asn::CConversorEstadoGeral (the reconstruction's note, not TSE's text). ConverteEstadoUrna's throws sit on their
// records' lines (106 and 110); DesconverteEstadoUrna's records (87 and 91) and DoDesconverte are not written, so their
// lines stay blank. Where DoConverte starts is a choice. 124-uenux2-app-comum-dados-asn.mk lists what the bytes decide.
#include "app/comum/dados/asn/estadoaplicacao/cconversorestadogeral.h"

#include <format>

#include "app/comum/dados/asn/estadoaplicacao/cconversorajustedatahora.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversordadocarga.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversordadocorrespondencia.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversordadolocal.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 16-59: content not recovered)
#line 60
CConversorEstadoGeral::TEntidade CConversorEstadoGeral::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    CConversorAjusteDataHora conversorAjusteDataHora;
    entidade.set_ajusteDataHora() = conversorAjusteDataHora.Converte(dado.GetAjusteDataHora());
    CConversorDadoCarga conversorDadoCarga;
    entidade.set_dadoCarga() = conversorDadoCarga.Converte(dado.GetDadoCarga());
    CConversorDadoLocal conversorDadoLocal;
    entidade.set_dadoLocal() = conversorDadoLocal.Converte(dado.GetDadoLocal());
    CConversorDadoCorrespondencia conversorCorrespondencia;
    entidade.set_correspondencia() = conversorCorrespondencia.Converte(dado.GetCorrespondencia());
    entidade.set_idPE(dado.GetIdPE());
    entidade.set_estadoUrna(ConverteEstadoUrna(dado.GetEstadoUrna()));
    entidade.set_versao(dado.GetVersao());
    TEntidade::hashVersoesPacotes::reference hash = entidade.set_hashVersoesPacotes();
    hash.insert(hash.begin(), dado.GetHashVersoesPacotes().begin(), dado.GetHashVersoesPacotes().end());
    return entidade;
}

// (original lines 79-95: content not recovered)
#line 96
ModuloEstadoGeralUrna::EstadoUrna CConversorEstadoGeral::ConverteEstadoUrna(const EEstadoUrna estado) const
{
    switch (estado) {
        case eEstadoUrnaCarregada:
            return ModuloEstadoGeralUrna::EstadoUrna::carregada;
        case eEstadoUrnaCarregando:
            return ModuloEstadoGeralUrna::EstadoUrna::carregando;
        case eEstadoUrnaTestada:
            return ModuloEstadoGeralUrna::EstadoUrna::testada;
        case eEstadoUrnaUltimoID:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7919, std::format("Valor inválido para estado da urna: {}", estado));
        default:
            break;
    }
    throw CUeComumDadosError(EUE_COMUM_DADOS_7920, std::format("Valor inválido para estado da urna: {}", estado));
}


} // namespace comum::asn

// <stubs>
// f3592 · 20 B · unmatched · placement: link order · name unknown
// void f3592(i32, i32) { ... }
// </stubs>
