// Reconstruction: comum::asn::CConversorCabecalhoEntidade's two slots, DoConverte and DoDesconverte (target fns 11589
// and 11588). Each throw sits on its record's line (35 and 56); the lines between are blank where the original is not
// recovered, and where each function begins is chosen. src/units/172-uenux2-comum-datahora-converters.mk has the choices.
#include "app/comum/asn/cconversorcabecalhoentidade.h"

#include <format>

#include "app/comum/asn/euecomumasnerror.h"
#include "app/comum/asn/util.h"

namespace comum::asn {

// (original lines 13-19: content not recovered)
#line 20
CConversorCabecalhoEntidade::TEntidade CConversorCabecalhoEntidade::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_dataGeracao() = Utils::ConverteDataHoraJE(dado.GetDataGeracao());
    switch (dado.GetTipo()) {
        case md::TIPO_CABECALHO_PROCESSO_ELEITORAL:
            entidade.set_idEleitoral().select_idProcessoEleitoral() = dado.GetCodigo();
            break;
        case md::TIPO_CABECALHO_PLEITO:
            entidade.set_idEleitoral().select_idPleito() = dado.GetCodigo();
            break;
        case md::TIPO_CABECALHO_ELEICAO:
            entidade.set_idEleitoral().select_idEleicao() = dado.GetCodigo();
            break;
        default:
            throw CUeComumAsnError(EUE_COMUM_ASN_TIPO_CABECALHO_INVALIDO,
                                   std::format("Tipo inválido [{}]", static_cast<int>(dado.GetTipo())));
    }
    return entidade;
}

// (original lines 41-49: content not recovered)
#line 50
md::CCabecalhoEntidade CConversorCabecalhoEntidade::DoDesconverte(const TEntidade& entidade) const
{
    const ModuloTiposEleitorais::IDEleitoral& idEleitoral = entidade.get_idEleitoral();
    const int tipo = idEleitoral.currentSelection();
    if (tipo < ModuloTiposEleitorais::IDEleitoral::idProcessoEleitoral0 ||
        tipo > ModuloTiposEleitorais::IDEleitoral::idEleicao2) {
        throw CUeComumAsnError(EUE_COMUM_ASN_TIPO_ID_CABECALHO_INVALIDO, "Tipo de id de cabeçalho inválido");
    }
    const uedword codigo = static_cast<const ASN1::INTEGER*>(idEleitoral.getSelection())->getValue();
    return md::CCabecalhoEntidade(Utils::DesconverteDataHoraJE(entidade.get_dataGeracao()), codigo,
                                  static_cast<md::ETipoCabecalho>(tipo));
}

} // namespace comum::asn
