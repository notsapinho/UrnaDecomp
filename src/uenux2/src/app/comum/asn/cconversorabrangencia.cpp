// Reconstruction: comum::asn::CConversorAbrangencia (target fns 11462, 11461). The record's line (45) places the throw.
#include "app/comum/asn/cconversorabrangencia.h"

#include <format>

#include "app/comum/asn/euecomumasnerror.h"
#include "app/comum/asn/util.h"

namespace comum::asn {

// (original lines 11-19: content not recovered)
#line 20
CConversorAbrangencia::TEntidade CConversorAbrangencia::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_tipo(Utils::ConverteAbrangencia(dado.GetTipo()));
    switch (dado.GetTipo()) {
        case md::ABRANGENCIA_MUNICIPAL: {
            ModuloTiposEleitorais::IdentificacaoAbrangencia identificacao;
            identificacao.set_siglaUF(dado.GetUF());
            identificacao.set_codigoMunicipio(dado.GetMunicipio());
            entidade.set_id() = identificacao;
            return entidade;
        }
        case md::ABRANGENCIA_ESTADUAL: {
            ModuloTiposEleitorais::IdentificacaoAbrangencia identificacao;
            identificacao.set_siglaUF(dado.GetUF());
            identificacao.omit_codigoMunicipio();
            entidade.set_id() = identificacao;
            return entidade;
        }
        case md::ABRANGENCIA_FEDERAL:
            entidade.omit_id();
            return entidade;
        default:
            break;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_TIPO_ABRANGENCIA_INVALIDO, std::format("Tipo inválido [{}]", static_cast<int>(dado.GetTipo())));
}

CConversorAbrangencia::TDado CConversorAbrangencia::DoDesconverte(const TEntidade& entidade) const
{
    const md::ETipoAbrangencia tipo = Utils::DesconverteAbrangencia(entidade.get_tipo());
    if (!entidade.id_isPresent()) {
        return TDado(tipo, "", 0);
    }
    if (!entidade.get_id().codigoMunicipio_isPresent()) {
        return TDado(tipo, entidade.get_id().get_siglaUF().c_str(), 0);
    }
    return TDado(tipo, entidade.get_id().get_siglaUF().c_str(), entidade.get_id().get_codigoMunicipio().getValue());
}

} // namespace comum::asn
