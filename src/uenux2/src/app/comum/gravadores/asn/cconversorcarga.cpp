// Reconstruction: comum::asn::CConversorCarga's two slots, DoConverte and DoDesconverte (target fns 10291 and 10290).
// No record names this file or a line in it: the path is the class name's (cconversorcarga.h), DoConverte comes first
// by the link order (10291 links ahead of 10290 in their use band) and the lines are chosen.
// src/units/172-uenux2-comum-datahora-converters.mk has the choices.
#include "app/comum/gravadores/asn/cconversorcarga.h"

#include "app/comum/asn/util.h"
#include "app/comum/gravadores/asn/util.h"
#include "ecourna/app/dados/asn/cconversoridentificadorgeradormidia.hpp"

namespace comum::asn {

CConversorCarga::TEntidade CConversorCarga::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    const ecourna::app::dados::asn::CConversorIdentificadorGeradorMidia conversorIdentificador;
    entidade.set_numeroInternoUrna(dado.GetNumeroInternoUrna());
    const std::vector<char> numeroSerieFC = ConverteSerialFlash(dado.GetNumeroSerieFC());
    entidade.set_numeroSerieFC().assign(numeroSerieFC.begin(), numeroSerieFC.end());
    entidade.set_dataHoraCarga() = Utils::ConverteDataHoraJE(dado.GetDataHoraCarga());
    entidade.set_codigoCarga(dado.GetCodigoCarga());
    entidade.set_identificadorGeradorMidia() = conversorIdentificador.Converte(dado.GetIdentificadorGeradorMidia());
    return entidade;
}

CConversorCarga::TDado CConversorCarga::DoDesconverte(const TEntidade& entidade) const
{
    const ecourna::app::dados::asn::CConversorIdentificadorGeradorMidia conversorIdentificador;
    const uedword numeroInternoUrna = entidade.get_numeroInternoUrna().getValue();
    const std::string numeroSerieFC = DesconverteSerialFlash(entidade.get_numeroSerieFC());
    const api::CDateTime dataHoraCarga = Utils::DesconverteDataHoraJE(entidade.get_dataHoraCarga());
    const std::string codigoCarga = entidade.get_codigoCarga();
    const ecourna::app::dados::CIdentificadorGeradorMidia identificadorGeradorMidia =
        conversorIdentificador.Deconverte(entidade.get_identificadorGeradorMidia());
    return TDado(numeroInternoUrna, numeroSerieFC, dataHoraCarga, codigoCarga, identificadorGeradorMidia);
}

} // namespace comum::asn
