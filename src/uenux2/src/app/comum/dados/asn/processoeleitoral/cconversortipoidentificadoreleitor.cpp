#include "app/comum/dados/asn/processoeleitoral/cconversortipoidentificadoreleitor.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

using ModuloTiposEleitorais::TipoIdentificadorEleitor;
using namespace ecourna::app::dados;

namespace {

// 8184 reaches the target through fn 6030, not fn 170 directly, so the shared enum header does not list it.
constexpr auto EUE_COMUM_DADOS_8184 = static_cast<EUeComumDadosError>(8184);

} // namespace

// (original lines 17-19: content not recovered)
#line 20
ModuloTiposEleitorais::TipoIdentificadorEleitor
CConversorTipoIdentificadorEleitor::DoConverte(const TDado& tipo) const
{
    switch (tipo) {
        case TipoIDInscricaoEleitoral:
            return TipoIdentificadorEleitor::numeroInscricaoEleitoral;
        case TipoIDCPF:
            return TipoIdentificadorEleitor::numeroCPF;
        case TipoIDNumeroLivre:
            return TipoIdentificadorEleitor::numeroLivre;
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_8183, "Tipo de identificador de eleitor inválido");
}

// (original lines 35-36: content not recovered)
#line 37
ecourna::app::dados::ETipoIdentificadorEleitor
CConversorTipoIdentificadorEleitor::DoDesconverte(const TEntidade& entidade) const
{
    switch (entidade) {
        case TipoIdentificadorEleitor::numeroInscricaoEleitoral:
            return TipoIDInscricaoEleitoral;
        case TipoIdentificadorEleitor::numeroCPF:
            return TipoIDCPF;
        case TipoIdentificadorEleitor::numeroLivre:
            return TipoIDNumeroLivre;
        default:
            break;
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_8184, "Tipo de identificador de eleitor inválido");
}

} // namespace comum::asn
