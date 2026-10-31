// Reconstruction's note, not TSE's text: comum's four menu items' slot 2 (target fns 11669, 11668, 11667, 11666), the
// classes' key function, so their vtables are emitted here. No record names this file: the four vtables (@1550780 to
// @1550888) lie after app/comum/informacao/cinformacaoeleicao.cpp's record (@1550764) and before comum::CMenuBase's
// vtable (@1550924): so informacao/, beside citemmenu.h, a choice, and the file name is the header's, chosen.
// cinformacaoeleicao.cpp itself or a cmenubase.cpp fit the data as well. Each body reads the count first and then calls
// slot 3 (measured: `return Slot3() < informacao.GetNumVias...();` calls slot 3 first). CItemImprimeListaEleitores's
// tests the load's urna type first (fn 11668: GetTipoUrna minus 49 in {0, 2, 3}, which are eUrnaVota,
// eUrnaContingenciaVota and eUrnaContingenciaVotaRecupera); the three comparisons are a chosen spelling of that set.
// The locals' names are chosen.
#include "app/comum/informacao/citemmenu.h"

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/informacao/cinformacaoeleicao.h"

namespace comum {

bool CItemImprimeEstadoUrna::Slot2()
{
    CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    const int vias = informacao.GetNumViasEstadoUrna();
    return Slot3() < vias;
}

bool CItemImprimeListaEleitores::Slot2()
{
    const EUrnaTipo tipo = CAppInfo::GetInst().GetGeral().GetDadoCarga().GetTipoUrna();
    if (tipo != eUrnaVota && tipo != eUrnaContingenciaVota && tipo != eUrnaContingenciaVotaRecupera) {
        return false;
    }
    CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    const int vias = informacao.GetNumViasEleitores();
    return Slot3() < vias;
}

bool CItemParametrosUrna::Slot2()
{
    CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    const int vias = informacao.GetNumViasPU();
    return Slot3() < vias;
}

bool CItemVersoesPacotes::Slot2()
{
    CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    const int vias = informacao.GetNumViasVersoesDados();
    return Slot3() < vias;
}

} // namespace comum
