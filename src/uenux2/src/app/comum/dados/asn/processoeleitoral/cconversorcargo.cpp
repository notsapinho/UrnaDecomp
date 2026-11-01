// Reconstruction: comum::asn::CConversorCargo::DoDesconverte (target fn 11373) and DesconverteTipoCargo, which binaryen
// inlines into it (its frame opens inside 11373's). Their throws sit on their records' lines (69 and 83); where each
// function starts is a choice, and so are the blank lines above them. 191-uenux2-cconversorcargo.mk has the rest.
#include "app/comum/dados/asn/processoeleitoral/cconversorcargo.h"

#include <format>

#include "app/comum/asn/cconversorcodigocargoconsulta.h"
#include "app/comum/dados/asn/processoeleitoral/cconversordetalhecandidato.h"
#include "app/comum/dados/asn/processoeleitoral/cconversordetalheconsulta.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 15-44: content not recovered)
#line 45
md::CCargo CConversorCargo::DoDesconverte(const TEntidade& entidade) const
{
    const CConversorCodigoCargoConsulta conversorCodigo;
    const md::TCargoID id = conversorCodigo.Desconverte(entidade.get_codigo());
    const md::CCargo::ETipo tipo = DesconverteTipoCargo(entidade.get_tipo());
    const uebyte numeroDigitos = entidade.get_numeroDigitos().getValue();
    const md::TQtdEscolha qtdeEscolhas = entidade.get_qtdeEscolhas().getValue();
    const bool podeRepetir = entidade.get_podeRepetir();
    const uebyte ordemAquisicao = entidade.get_ordemAquisicao().getValue();
    const uebyte ordemImpressao = entidade.get_ordemImpressao().getValue();
    const uebyte ordemApuracao = entidade.get_ordemApuracao().getValue();
    const uebyte paginaImpressaoVoto = entidade.get_paginaImpressaoVoto().getValue();
    const TEntidade::detalhe::value_type& detalhe = entidade.get_detalhe();
    if (detalhe.cargo_isSelected()) {
        const CConversorDetalheCandidato conversorDetalhe;
        const md::CDetalheCandidato detalheCandidato = conversorDetalhe.Desconverte(detalhe.get_cargo());
        return md::CCargo(id, tipo, m_abrangencia, numeroDigitos, qtdeEscolhas, podeRepetir, ordemAquisicao,
                          ordemImpressao, ordemApuracao, paginaImpressaoVoto, detalheCandidato);
    } else if (detalhe.pergunta_isSelected()) {
        const CConversorDetalheConsulta conversorDetalhe;
        const md::CDetalheConsulta detalheConsulta = conversorDetalhe.Desconverte(detalhe.get_pergunta());
        return md::CCargo(id, tipo, m_abrangencia, numeroDigitos, qtdeEscolhas, podeRepetir, ordemAquisicao,
                          ordemImpressao, ordemApuracao, paginaImpressaoVoto, detalheConsulta);
    } else {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7948, "Opção de Detalhe Inválida.");
    }
}

md::CCargo::ETipo CConversorCargo::DesconverteTipoCargo(ModuloTiposEleitorais::TipoCargoConsulta::NamedNumber tipo)
{
    switch (tipo) {
        case ModuloTiposEleitorais::TipoCargoConsulta::majoritario:
            return md::CCargo::MAJORITARIO;
        case ModuloTiposEleitorais::TipoCargoConsulta::proporcional:
            return md::CCargo::PROPORCIONAL;
        case ModuloTiposEleitorais::TipoCargoConsulta::consulta:
            return md::CCargo::CONSULTA;
        default:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7949, std::format("Tipo inválido: {}", tipo));
    }
}

} // namespace comum::asn
