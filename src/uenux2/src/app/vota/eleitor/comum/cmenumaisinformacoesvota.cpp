// Reconstruction's note, not TSE's text: vota::CMenuMaisInformacoesVota's constructor (citensmenuvota.h has the class
// and what the constructor builds). No record names this file. Its TU is neither 6599's nor the items' destructor's,
// both measured in the whole link (src/units/110-uenux2-singletons.mk has the scores): in ctelasvota.cpp, 6599 drops
// the constructor's returned `this` and folds the menu's frame address into its loads where the target keeps that
// pointer in a local (nine rows); in citensmenuvota.cpp, which defines ~CItemVisualizarCandidatosVota, the fifth item's
// control block slot 2 (12172) leaves match: the target's frees what the D2 returns, the shape how-to step 5 gives a
// block built outside the destructor's TU. Its object links right after citensmenuvota.cpp's, after ctelasvota.cpp's,
// as the target's data hold the menu's vtable and the five blocks it builds (@1539812 to @1540032, after the items'
// vtables and before fimvotacao's CCopiaResultadoParaMR): unit 110's list. The path, app/vota/eleitor/comum/ beside
// that run, and the name, the class's in lower case, are chosen; the name sorts before ctelasvota.cpp, where the data
// put the object after it.
#include "app/vota/operador/outrasopcoes/citensmenuvota.h"

#include <memory>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"

namespace vota {

CMenuMaisInformacoesVota::CMenuMaisInformacoesVota(api::CFormBuilder& form)
    : comum::CMenuBase(form)
{
    comum::md::estadoaplicacao::CEstadoGeralVota& vota = comum::CAppInfo::GetInst().GetVota();
    AdicionaItem(std::shared_ptr<comum::CItemMenu>(
        new CItemImprimeEstadoUrnaVota(vota.GetNumViasImpressasRelatorios().GetNumViasEstadoUrna())));
    AdicionaItem(std::shared_ptr<comum::CItemMenu>(
        new CItemImprimeListaEleitoresVota(vota.GetNumViasImpressasRelatorios().GetNumViasEleitores())));
    AdicionaItem(std::shared_ptr<comum::CItemMenu>(
        new CItemVersoesPacotesVota(vota.GetNumViasImpressasRelatorios().GetNumViasVersoesDados())));
    AdicionaItem(std::shared_ptr<comum::CItemMenu>(
        new CItemParametrosUrnaVota(vota.GetNumViasImpressasRelatorios().GetNumViasPU())));
    AdicionaItem(std::shared_ptr<comum::CItemMenu>(new CItemVisualizarCandidatosVota()));
}

} // namespace vota
