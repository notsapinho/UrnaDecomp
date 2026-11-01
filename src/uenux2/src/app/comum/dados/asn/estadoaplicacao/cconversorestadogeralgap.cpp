// Reconstruction: comum::asn::CConversorEstadoGeralGap (target fns 11395, 11394, 5690 and 5689; the records at lines 150,
// 154, 194 and 198) and two helpers no record names, which 93-uenux2-estadoaplicacao.mk describes. No record names the
// lines above 115: where each function starts is a choice.
#include "app/comum/dados/asn/estadoaplicacao/cconversorestadogeralgap.h"

#include <algorithm>
#include <format>
#include <iterator>

#include "app/comum/asn/util.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversordadocorrespondencia.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversornumviasimpressasrelatorios.h"
#include "app/comum/dados/asn/estadoaplicacao/enumeradoasn.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralgap.h"

namespace comum::asn {

using TCorrespondenciasASN =
    ASN1::SEQUENCE_OF<ModuloEstadoGeralUrna::DadoCorrespondencia, ASN1::SizeConstraint<ASN1::FixedConstraint, 0, 10>>;

static TCorrespondenciasASN ConverteCorrespondencias(
    const std::vector<md::estadoaplicacao::CDadoCorrespondencia>& correspondencias)
{
    TCorrespondenciasASN lista;
    const CConversorDadoCorrespondencia conversor;
    std::transform(correspondencias.begin(), correspondencias.end(), std::back_inserter(lista),
                   [&](const md::estadoaplicacao::CDadoCorrespondencia& correspondencia) {
                       return conversor.Converte(correspondencia);
                   });
    return lista;
}

std::vector<md::estadoaplicacao::CDadoCorrespondencia> DesconverteCorrespondencias(const TCorrespondenciasASN& lista);

CConversorEstadoGeralGap::TDado CConversorEstadoGeralGap::DoDesconverte(const TEntidade& entidade) const
{
    const std::vector<md::estadoaplicacao::CDadoCorrespondencia> correspondencias =
        DesconverteCorrespondencias(entidade.get_correspondencias());
    const EUrnaAplicativo appId = DesconverteUrnaAplicativo(entidade.get_appId());
    const EUrnaAplicativo appAnteriorId = DesconverteUrnaAplicativo(entidade.get_appAnteriorId());
    const bool executadoRED = entidade.get_executadoRED();
    const bool identificadoATUE = entidade.get_identificadoATUE();
    const bool audio = entidade.get_audio();
    const bool data2T = entidade.get_data2T();
    const CConversorNumViasImpressasRelatorios conversorNumVias;
    const md::estadoaplicacao::CNumViasImpressasRelatorios numVias1T =
        conversorNumVias.Desconverte(entidade.get_numViasImpressasRelatorios1T());
    const md::estadoaplicacao::CNumViasImpressasRelatorios numVias2T =
        conversorNumVias.Desconverte(entidade.get_numViasImpressasRelatorios2T());
    std::optional<api::CDate> dataSegundoTurno;
    if (entidade.dataSegundoTurno_isPresent()) {
        dataSegundoTurno = Utils::DesconverteDataJE(entidade.get_dataSegundoTurno());
    }
    return TDado(correspondencias, appId, appAnteriorId, executadoRED, identificadoATUE, audio, data2T, numVias1T,
                 numVias2T, dataSegundoTurno);
}

std::vector<md::estadoaplicacao::CDadoCorrespondencia> DesconverteCorrespondencias(const TCorrespondenciasASN& lista)
{
    std::vector<md::estadoaplicacao::CDadoCorrespondencia> correspondencias;
    const CConversorDadoCorrespondencia conversor;
    for (std::size_t i = 0; i < lista.size(); ++i) {
        const md::estadoaplicacao::CDadoCorrespondencia correspondencia = conversor.Desconverte(lista[i]);
        correspondencias.push_back(correspondencia);
    }
    return correspondencias;
}

CConversorEstadoGeralGap::TEntidade CConversorEstadoGeralGap::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    static_cast<TCorrespondenciasASN&>(entidade.set_correspondencias()) =
        ConverteCorrespondencias(dado.GetCorrespondencias());
    entidade.set_appId(ConverteUrnaAplicativo(dado.GetAppId()));
    entidade.set_appAnteriorId(ConverteUrnaAplicativo(dado.GetAppAnteriorId()));
    entidade.set_executadoRED(dado.GetExecutadoRED());
    entidade.set_identificadoATUE(dado.GetIdentificadoATUE());
    entidade.set_audio(dado.GetAudio());
    entidade.set_data2T(dado.GetData2T());
    const CConversorNumViasImpressasRelatorios conversorNumVias;
    entidade.set_numViasImpressasRelatorios1T() = conversorNumVias.Converte(dado.GetNumViasImpressasRelatorios1T());
    entidade.set_numViasImpressasRelatorios2T() = conversorNumVias.Converte(dado.GetNumViasImpressasRelatorios2T());
    if (dado.GetDataSegundoTurno()) {
        entidade.set_dataSegundoTurno() = Utils::ConverteDataJE(*dado.GetDataSegundoTurno());
    } else {
        entidade.omit_dataSegundoTurno();
    }
    return entidade;
}

// (original lines 92-114: content not recovered)
#line 115
EUrnaAplicativo CConversorEstadoGeralGap::DesconverteUrnaAplicativo(const ModuloEstadoGeralGap::UrnaAplicativo& aplicativo) const
{
    switch (aplicativo) {
        case ModuloEstadoGeralGap::UrnaAplicativo::apvotatreinaeleitor1:
            return eApVotaTreinaEleitor1;
        case ModuloEstadoGeralGap::UrnaAplicativo::apvotatreinaeleitor2:
            return eApVotaTreinaEleitor2;
        case ModuloEstadoGeralGap::UrnaAplicativo::apvotatreinamesario1:
            return eApVotaTreinaMesario1;
        case ModuloEstadoGeralGap::UrnaAplicativo::apvotatreinamesario2:
            return eApVotaTreinaMesario2;
        case ModuloEstadoGeralGap::UrnaAplicativo::apvotasimula1:
            return eApVotaSimula1;
        case ModuloEstadoGeralGap::UrnaAplicativo::apvotasimula2:
            return eApVotaSimula2;
        case ModuloEstadoGeralGap::UrnaAplicativo::apvotaoficial1:
            return eApVotaOficial1;
        case ModuloEstadoGeralGap::UrnaAplicativo::apvotaoficial2:
            return eApVotaOficial2;
        case ModuloEstadoGeralGap::UrnaAplicativo::apapuracaotreina1:
            return eApApuracaoTreina1;
        case ModuloEstadoGeralGap::UrnaAplicativo::apapuracaotreina2:
            return eApApuracaoTreina2;
        case ModuloEstadoGeralGap::UrnaAplicativo::apapuracaosimula1:
            return eApApuracaoSimula1;
        case ModuloEstadoGeralGap::UrnaAplicativo::apapuracaosimula2:
            return eApApuracaoSimula2;
        case ModuloEstadoGeralGap::UrnaAplicativo::apapuracaooficial1:
            return eApApuracaoOficial1;
        case ModuloEstadoGeralGap::UrnaAplicativo::apapuracaooficial2:
            return eApApuracaoOficial2;
        case ModuloEstadoGeralGap::UrnaAplicativo::apsemaplicativo:
            return eApSemAplicativo;
        case ModuloEstadoGeralGap::UrnaAplicativo::unknownEnumeration_:
        case ModuloEstadoGeralGap::UrnaAplicativo::apultimoid:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7921,
                                     std::format("Valor inválido para UrnaAplicativo: {}", aplicativo));
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7922,
                             std::format("Valor inválido para UrnaAplicativo: {}", aplicativo));
}

// (original lines 158-159: content not recovered)
#line 160
ModuloEstadoGeralGap::UrnaAplicativo CConversorEstadoGeralGap::ConverteUrnaAplicativo(const EUrnaAplicativo aplicativo) const
{
    switch (aplicativo) {
        case eApVotaTreinaEleitor1:
            return ModuloEstadoGeralGap::UrnaAplicativo::apvotatreinaeleitor1;
        case eApVotaTreinaEleitor2:
            return ModuloEstadoGeralGap::UrnaAplicativo::apvotatreinaeleitor2;
        case eApVotaTreinaMesario1:
            return ModuloEstadoGeralGap::UrnaAplicativo::apvotatreinamesario1;
        case eApVotaTreinaMesario2:
            return ModuloEstadoGeralGap::UrnaAplicativo::apvotatreinamesario2;
        case eApVotaSimula1:
            return ModuloEstadoGeralGap::UrnaAplicativo::apvotasimula1;
        case eApVotaSimula2:
            return ModuloEstadoGeralGap::UrnaAplicativo::apvotasimula2;
        case eApVotaOficial1:
            return ModuloEstadoGeralGap::UrnaAplicativo::apvotaoficial1;
        case eApVotaOficial2:
            return ModuloEstadoGeralGap::UrnaAplicativo::apvotaoficial2;
        case eApApuracaoTreina1:
            return ModuloEstadoGeralGap::UrnaAplicativo::apapuracaotreina1;
        case eApApuracaoTreina2:
            return ModuloEstadoGeralGap::UrnaAplicativo::apapuracaotreina2;
        case eApApuracaoSimula1:
            return ModuloEstadoGeralGap::UrnaAplicativo::apapuracaosimula1;
        case eApApuracaoSimula2:
            return ModuloEstadoGeralGap::UrnaAplicativo::apapuracaosimula2;
        case eApApuracaoOficial1:
            return ModuloEstadoGeralGap::UrnaAplicativo::apapuracaooficial1;
        case eApApuracaoOficial2:
            return ModuloEstadoGeralGap::UrnaAplicativo::apapuracaooficial2;
        case eApSemAplicativo:
            return ModuloEstadoGeralGap::UrnaAplicativo::apsemaplicativo;
        case eApUltimoID:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7923,
                                     std::format("Valor inválido para EUrnaAplicativo: {}", aplicativo));
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7924,
                             std::format("Valor inválido para EUrnaAplicativo: {}", aplicativo));
}

} // namespace comum::asn

// <stubs>
// f10112 · 20 B · unmatched · placement: link order · name unknown
// void f10112(i32, i32) { ... }
// </stubs>
