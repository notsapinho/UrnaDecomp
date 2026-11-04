// comum::asn::CConversorEstadoGeral (the reconstruction's note, not TSE's text). DesconverteEstadoUrna's and
// ConverteEstadoUrna's throws sit on their records' lines (87, 91, 106 and 110); where DoDesconverte and DoConverte
// start is a choice. 124-uenux2-app-comum-dados-asn.mk lists what the bytes decide and the layout of these lines.
#include "app/comum/dados/asn/estadoaplicacao/cconversorestadogeral.h"

#include <format>

#include "app/comum/dados/asn/estadoaplicacao/cconversorajustedatahora.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversordadocarga.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversordadocorrespondencia.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversordadolocal.h"
#include "app/comum/dados/asn/estadoaplicacao/enumeradoasn.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

CConversorEstadoGeral::TDado CConversorEstadoGeral::DoDesconverte(const TEntidade& entidade) const
{
    const uedword idPE = entidade.get_idPE().getValue();
    const EEstadoUrna estadoUrna = DesconverteEstadoUrna(entidade.get_estadoUrna());
    CConversorAjusteDataHora conversorAjusteDataHora;
    const md::estadoaplicacao::CAjusteDataHora ajusteDataHora =
        conversorAjusteDataHora.Desconverte(entidade.get_ajusteDataHora());
    CConversorDadoLocal conversorDadoLocal;
    const md::estadoaplicacao::CDadoLocal dadoLocal = conversorDadoLocal.Desconverte(entidade.get_dadoLocal());
    CConversorDadoCarga conversorDadoCarga;
    const md::estadoaplicacao::CDadoCarga dadoCarga = conversorDadoCarga.Desconverte(entidade.get_dadoCarga());
    CConversorDadoCorrespondencia conversorCorrespondencia;
    const md::estadoaplicacao::CDadoCorrespondencia correspondencia =
        conversorCorrespondencia.Desconverte(entidade.get_correspondencia());
    const std::vector<uebyte> hashVersoesPacotes(entidade.get_hashVersoesPacotes().begin(),
                                                 entidade.get_hashVersoesPacotes().end());
    const std::string versao = entidade.get_versao();
    return TDado(estadoUrna, idPE, dadoLocal, dadoCarga, ajusteDataHora, correspondencia, versao, hashVersoesPacotes);
}

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

// (original lines 56-76: content not recovered)
#line 77
EEstadoUrna CConversorEstadoGeral::DesconverteEstadoUrna(const ModuloEstadoGeralUrna::EstadoUrna& estado) const
{
    switch (estado) {
        case ModuloEstadoGeralUrna::EstadoUrna::carregada:
            return eEstadoUrnaCarregada;
        case ModuloEstadoGeralUrna::EstadoUrna::carregando:
            return eEstadoUrnaCarregando;
        case ModuloEstadoGeralUrna::EstadoUrna::testada:
            return eEstadoUrnaTestada;
        case ModuloEstadoGeralUrna::EstadoUrna::unknownEnumeration_:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7917,
                                     std::format("Valor inválido para estado da urna: {}", estado));
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7918, std::format("Valor inválido para estado da urna: {}", estado));
}

// (original lines 94-95: content not recovered)
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
