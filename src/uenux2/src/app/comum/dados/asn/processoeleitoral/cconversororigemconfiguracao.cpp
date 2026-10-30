#include "app/comum/dados/asn/processoeleitoral/cconversororigemconfiguracao.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

namespace {

// 7953 reaches the target through fn 6030, not fn 170 directly, so the shared enum header does not list it.
constexpr auto EUE_COMUM_DADOS_7953 = static_cast<EUeComumDadosError>(7953);

} // namespace

// (original lines 14-26: content not recovered)
#line 27
md::EOrigemConfiguracao CConversorOrigemConfiguracao::DoDesconverte(const TEntidade& entidade) const
{
    switch (entidade) {
        case TEntidade::oficial:
            return md::ORIGEM_OFICIAL;
        case TEntidade::comunitaria:
            return md::ORIGEM_COMUNITARIA;
        default:
            break;
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7953, "Origem configuração inválida");
}





CConversorOrigemConfiguracao::TEntidade CConversorOrigemConfiguracao::DoConverte(const TDado& origem) const
{
    return origem == md::ORIGEM_COMUNITARIA ? TEntidade::comunitaria : TEntidade::oficial;
}

} // namespace comum::asn
