// Reconstruction: comum::asn::CConversorEstadoGeralGap::DesconverteUrnaAplicativo and ConverteUrnaAplicativo (target fns
// 5690, 5689, the records at lines 150, 154, 194 and 198). DoConverte and DoDesconverte (fns 11394, 11395) are not
// reconstructed.
#include "app/comum/dados/asn/estadoaplicacao/cconversorestadogeralgap.h"

#include <format>

#include "app/comum/dados/asn/estadoaplicacao/enumeradoasn.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 13-114: content not recovered)
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
