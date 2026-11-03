// comum::asn::CConversorDetalheCandidato::DoDesconverte (target fn 11375). The reconstruction's own note: its three
// throws sit on their records' lines (29, 34 and 39); the blank lines stand for text not recovered, and where the
// function starts and how its conditions are spread over lines are a choice
// (src/units/299-uenux2-cqrcodeds-processoeleitoral.mk says what the bytes decide).
#include "app/comum/dados/asn/processoeleitoral/cconversordetalhecandidato.h"

#include "app/comum/dados/asn/processoeleitoral/cconversornomescargo.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorsuplencia.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 13-21: content not recovered)
#line 22
md::CDetalheCandidato CConversorDetalheCandidato::DoDesconverte(const TEntidade& entidade) const
{
    const CConversorNomesCargo conversorNomes;
    const unsigned int quantidade = entidade.get_qtdeSuplentes().getValue();

    if (quantidade == 0 && entidade.hasOptionalField(TEntidade::e_suplencias) &&
        entidade.get_suplencias().size() != 0) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7950,
                                 "Quantidade de suplências incompatível com sequência de suplências.");
    }

    if (quantidade != 0 && !entidade.hasOptionalField(TEntidade::e_suplencias)) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7951, "Quantidade não nula e sem suplências.");
    }

    if (entidade.hasOptionalField(TEntidade::e_suplencias) &&
        quantidade != entidade.get_suplencias().size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7952, "Quantidade de suplências incompatível.");
    }

    const bool temFoto = entidade.get_temFoto();
    const md::CNomesCargo nomes = conversorNomes.Desconverte(entidade.get_nomes());
    md::TVectorSuplencia suplencias;
    for (unsigned int i = 0; i < quantidade; ++i) {
        const CConversorSuplencia conversorSuplencia;
        md::CSuplencia suplencia = conversorSuplencia.Desconverte(entidade.get_suplencias().at(i));
        suplencias.emplace_back(suplencia);
    }
    return md::CDetalheCandidato(temFoto, nomes, suplencias);
}

} // namespace comum::asn
