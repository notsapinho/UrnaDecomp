// Reconstruction: comum::asn::CConversorAjusteDataHora (target fns 11405, 11406). DesconverteTipoAjusteDataHora's records
// are lines 49 and 53, ConverteTipoAjusteDataHora's line 69, and binaryen inlines each into its one caller.
#include "app/comum/dados/asn/estadoaplicacao/cconversorajustedatahora.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

CConversorAjusteDataHora::TEntidade CConversorAjusteDataHora::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_valorAjusteDataHora(dado.GetDeltaT());
    entidade.set_tipoAjusteDataHora(ConverteTipoAjusteDataHora(dado.GetTipoDeltaT()));
    return entidade;
}

CConversorAjusteDataHora::TDado CConversorAjusteDataHora::DoDesconverte(const TEntidade& entidade) const
{
    return TDado(DesconverteTipoAjusteDataHora(entidade.get_tipoAjusteDataHora()),
                 entidade.get_valorAjusteDataHora().getValue());
}

// (original lines 25-38: content not recovered)
#line 39
md::estadoaplicacao::CAjusteDataHora::ETipoDeltaT CConversorAjusteDataHora::DesconverteTipoAjusteDataHora(const ModuloEstadoGeralUrna::TipoAjusteDataHora& tipo) const
{
    switch (tipo) {
        case ModuloEstadoGeralUrna::TipoAjusteDataHora::semAjusteDataHora:
            return md::estadoaplicacao::CAjusteDataHora::eSemAjusteDataHora;
        case ModuloEstadoGeralUrna::TipoAjusteDataHora::alterarDataEleicao:
            return md::estadoaplicacao::CAjusteDataHora::eAlterarDataEleicao;
        case ModuloEstadoGeralUrna::TipoAjusteDataHora::alterarDataSistema:
            return md::estadoaplicacao::CAjusteDataHora::eAlterarDataSistema;
        case ModuloEstadoGeralUrna::TipoAjusteDataHora::unknownEnumeration_:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7906,
                                     std::format("Valor inválido para TipoAjusteDataHora: {}", tipo.asInt()));
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7907,
                             std::format("Valor inválido para TipoAjusteDataHora: {}", tipo.asInt()));
}


ModuloEstadoGeralUrna::TipoAjusteDataHora CConversorAjusteDataHora::ConverteTipoAjusteDataHora(const md::estadoaplicacao::CAjusteDataHora::ETipoDeltaT& tipo) const
{
    switch (tipo) {
        case md::estadoaplicacao::CAjusteDataHora::eSemAjusteDataHora:
            return ModuloEstadoGeralUrna::TipoAjusteDataHora::semAjusteDataHora;
        case md::estadoaplicacao::CAjusteDataHora::eAlterarDataEleicao:
            return ModuloEstadoGeralUrna::TipoAjusteDataHora::alterarDataEleicao;
        case md::estadoaplicacao::CAjusteDataHora::eAlterarDataSistema:
            return ModuloEstadoGeralUrna::TipoAjusteDataHora::alterarDataSistema;
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7908, std::format("Valor inválido para ETipoDeltaT: {}", tipo));
}

} // namespace comum::asn
