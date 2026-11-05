// Reconstruction's note, not TSE's text: comum's four menu items' slot 2 (target fns 11669, 11668, 11667, 11666), the
// classes' key function, so their vtables are emitted here. No record names this file: the four vtables (@1550780 to
// @1550888) lie after app/comum/informacao/cinformacaoeleicao.cpp's record (@1550764) and before comum::CMenuBase's
// vtable (@1550924): so informacao/, beside citemmenu.h, a choice, and the file name is the header's, chosen.
// cinformacaoeleicao.cpp itself or a cmenubase.cpp fit the data as well. Each body reads the count first and then calls
// slot 3 (measured: `return Slot3() < informacao.GetNumVias...();` calls slot 3 first). CItemImprimeListaEleitores's
// tests the load's urna type first (fn 11668: GetTipoUrna minus 49 in {0, 2, 3}, which are eUrnaVota,
// eUrnaContingenciaVota and eUrnaContingenciaVotaRecupera); the three comparisons are a chosen spelling of that set.
// The locals' names are chosen.
// Each class's two constructors follow the slots: binaryen inlined both into fn 6599 (no index of their own;
// citemmenu.h has their evidence). The 16-byte one is a function of its own when binaryen runs, and clang inlines a
// constructor that small into a caller in its own TU (a reading), so it is out of line in another TU than
// vota::CMenuMaisInformacoesVota's constructor; this file and the place after the slots are choices. With that
// constructor then in ctelasvota.cpp, each formatting constructor above the other gave the same wasm (sha256 equal),
// and the four classes in the order it calls them (Versoes before Parametros) another wasm with the same score for
// 6599.
#include "app/comum/informacao/citemmenu.h"

#include <format>

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

CItemImprimeEstadoUrna::CItemImprimeEstadoUrna(uebyte numViasImpressas)
    : CItemImprimeEstadoUrna(numViasImpressas, api::SPoint(100, 155))
{
}

CItemImprimeEstadoUrna::CItemImprimeEstadoUrna(uebyte numViasImpressas, const api::SPoint& posicao)
    : CItemMenu(1,
                std::format(
                    "Estado da urna ({}/{})", numViasImpressas,
                    CInformacaoEleicao(CConfiguracaoEleicao::GetInst().GetParametrosUrna()).GetNumViasEstadoUrna()),
                posicao)
{
}

CItemImprimeListaEleitores::CItemImprimeListaEleitores(uebyte numViasImpressas)
    : CItemImprimeListaEleitores(numViasImpressas, api::SPoint(100, 180))
{
}

CItemImprimeListaEleitores::CItemImprimeListaEleitores(uebyte numViasImpressas, const api::SPoint& posicao)
    : CItemMenu(2,
                std::format(
                    "Lista de eleitores ({}/{})", numViasImpressas,
                    CInformacaoEleicao(CConfiguracaoEleicao::GetInst().GetParametrosUrna()).GetNumViasEleitores()),
                posicao)
{
}

CItemParametrosUrna::CItemParametrosUrna(uebyte numViasImpressas)
    : CItemParametrosUrna(numViasImpressas, api::SPoint(100, 230))
{
}

CItemParametrosUrna::CItemParametrosUrna(uebyte numViasImpressas, const api::SPoint& posicao)
    : CItemMenu(4,
                std::format(
                    "Parâmetros de urna ({}/{})", numViasImpressas,
                    CInformacaoEleicao(CConfiguracaoEleicao::GetInst().GetParametrosUrna()).GetNumViasPU()),
                posicao)
{
}

CItemVersoesPacotes::CItemVersoesPacotes(uebyte numViasImpressas)
    : CItemVersoesPacotes(numViasImpressas, api::SPoint(100, 205))
{
}

CItemVersoesPacotes::CItemVersoesPacotes(uebyte numViasImpressas, const api::SPoint& posicao)
    : CItemMenu(3,
                std::format(
                    "Versões de pacotes ({}/{})", numViasImpressas,
                    CInformacaoEleicao(CConfiguracaoEleicao::GetInst().GetParametrosUrna()).GetNumViasVersoesDados()),
                posicao)
{
}

} // namespace comum
