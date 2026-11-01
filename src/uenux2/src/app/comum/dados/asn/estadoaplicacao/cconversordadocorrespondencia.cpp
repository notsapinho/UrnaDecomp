// Reconstruction: comum::asn::CConversorDadoCorrespondencia's two slots, DoConverte and DoDesconverte (target fns 11399
// and 11400). No record names this file or a line in it: the path is the header's (cconversordadocorrespondencia.h),
// and the functions' order is chosen. src/units/172-uenux2-comum-datahora-converters.mk has the choices.
#include "app/comum/dados/asn/estadoaplicacao/cconversordadocorrespondencia.h"

#include "app/comum/asn/util.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversorlocalidadeeleitoral.h"
#include "app/comum/gravadores/asn/util.h"
#include "ecourna/app/dados/asn/cconversoridentificadorgeradormidia.hpp"

namespace comum::asn {

CConversorDadoCorrespondencia::TEntidade CConversorDadoCorrespondencia::DoConverte(const TDado& dado) const
{
    const ecourna::app::dados::asn::CConversorIdentificadorGeradorMidia conversorIdentificador;
    TEntidade entidade;
    entidade.set_carga().set_numeroInternoUrna(dado.GetNumeroInternoUrna());
    entidade.set_carga().set_codigoCarga(dado.GetCodigoCarga());
    entidade.set_carga().set_numeroSerieFC(ConverteSerialFlash(dado.GetNumeroSerieFC()));
    entidade.set_carga().set_dataHoraCarga(Utils::ConverteDataHoraJE(dado.GetDataHoraCarga()));
    entidade.set_carga().set_identificadorGeradorMidia(
        conversorIdentificador.Converte(dado.GetIdentificadorGeradorMidia()));
    const CConversorLocalidadeEleitoral conversorLocalidade;
    entidade.set_secaoCarga() = conversorLocalidade.Converte(dado.GetSecaoCarga());
    TEntidade::assinatura::reference assinatura = entidade.set_assinatura();
    assinatura.insert(assinatura.begin(), dado.GetAssinatura().begin(), dado.GetAssinatura().end());
    return entidade;
}

CConversorDadoCorrespondencia::TDado CConversorDadoCorrespondencia::DoDesconverte(const TEntidade& entidade) const
{
    const ecourna::app::dados::asn::CConversorIdentificadorGeradorMidia conversorIdentificador;
    const uedword numeroInternoUrna = entidade.get_carga().get_numeroInternoUrna().getValue();
    const std::string numeroSerieFC = DesconverteSerialFlash(entidade.get_carga().get_numeroSerieFC());
    const api::CDateTime dataHoraCarga = Utils::DesconverteDataHoraJE(entidade.get_carga().get_dataHoraCarga());
    const std::string codigoCarga = entidade.get_carga().get_codigoCarga();
    const CConversorLocalidadeEleitoral conversorLocalidade;
    const md::estadoaplicacao::CLocalidadeEleitoral secaoCarga =
        conversorLocalidade.Desconverte(entidade.get_secaoCarga());
    const std::vector<uebyte> assinatura(entidade.get_assinatura().begin(), entidade.get_assinatura().end());
    const ecourna::app::dados::CIdentificadorGeradorMidia identificadorGeradorMidia =
        conversorIdentificador.Deconverte(entidade.get_carga().get_identificadorGeradorMidia());
    return TDado(numeroInternoUrna, numeroSerieFC, dataHoraCarga, codigoCarga, secaoCarga, assinatura,
                 identificadorGeradorMidia);
}

} // namespace comum::asn
