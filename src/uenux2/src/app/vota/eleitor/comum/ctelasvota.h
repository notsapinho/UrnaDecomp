#pragma once

#include <map>
#include <memory>
#include <mutex>

#include "app/vota/eleitor/comum/ctelascargo.h"

namespace api {
class CProgressBar;
} // namespace api

namespace vota {

// Recovered: the layout, from the destructor (fn 6548): a map at +0 whose nodes hold a CTelasCargo at +20, and so another
// map at +24 (fn 4137), and over it a map whose nodes hold a shared_ptr at +20 (fn 1314); then 30 shared_ptrs from +12 to
// +251, released last to first. Record 1536832, CFormInterativoTelaVota vota::CTelasVota::GetTelaCargo(const
// comum::TCargoID, const ETelaVotacao), held by fn 4135, gives the map's types: 4135 walks the map at +0 comparing a
// one-byte key at node+16 with its first argument, and it holds record 1536624 too, CTelasCargo::GetTela, with its `this`
// at node+20, so that is the element. The members' names are chosen, and so is the 30 members' type: only their
// destruction shows, which any std::shared_ptr gives. Five constructors copy one member each, through a getter:
// vota::CImprimindoBU's (inlined into fn 5986) the one at +100, vota::CReinicioVotacao's (inlined into fn 5938) the
// one at +148, and the zeresima states' (fns 5965, 11945 and 5957) those at +212, +220 and +228. Four GetInst copy one
// more each, right after CTelasVota::GetInst() (fn 407): vota::CAplicacaoEncerrada's (fn 3877) the one at +36,
// vota::CExibeAlertaDesligamento's (fn 5979) +44, vota::CConfirmaImpressaoZeresima's (fn 5959) +52 and
// vota::CInstrucaoVotacaoAcessibilidade's (fn 4420) +124. vota::CLimiteCopiasBUAtingido's constructor (its GetInst
// inlined into fn 12023) copies the one at +108. The getters' names, and that they are getters, are chosen.
// GetTelaCargo is the record's (1536832, ctelasvota.cpp:3534), defined in ctelasvota.cpp.
// Seven more members are read the same way: the constructors of vota::CVerificaHorarioZeresima (inlined into fn 5947)
// +20, vota::CInicioVotacao (fn 2880) +116, vota::CQuerImprimirBU (inlined into fn 12062) +236 and
// vota::CQuerReimprimirZeresima (fn 5940) +244 copy one each; vota::CVerificaEleicaoPassou::StartState (fn 11914) copies
// +76 into a temporary and calls its slot 2 before the temporary is released: GetTelaEleicaoPassou returns the
// std::shared_ptr by value, a choice, which gives that copy (fn 11914 matches with it; a copy the caller makes is not
// measured); and vota::CSincronismoEleitor::StartState (fn 7178) calls slot 2 of +172 and api::CProgressBar::SetValor
// (fn 3667) on +180 with that bar's +28, with no copy of either. So +180's pointee is an api::CProgressBar, and its
// member's type says so; the other 29 stay the forms' type (ctelasvota.cpp.o compiles to the same object either way,
// cmp).
class CTelasVota {
public:
    ~CTelasVota();

    static CTelasVota& GetInst();

    CFormInterativoTelaVota GetTelaCargo(const comum::TCargoID cargo, const ETelaVotacao tela) const;

    const CFormInterativoTelaVota& GetTelaAplicacaoEncerrada() const { return m_tela4; }
    const CFormInterativoTelaVota& GetTelaAlertaDesligamento() const { return m_tela5; }
    const CFormInterativoTelaVota& GetTelaConfirmaImpressaoZeresima() const { return m_tela6; }
    const CFormInterativoTelaVota& GetTelaImprimindoBU() const { return m_tela12; }
    const CFormInterativoTelaVota& GetTelaInstrucaoVotacaoAcessibilidade() const { return m_tela15; }
    const CFormInterativoTelaVota& GetTelaReinicioVotacao() const { return m_tela18; }
    const CFormInterativoTelaVota& GetTelaGeraZeresima() const { return m_tela26; }
    const CFormInterativoTelaVota& GetTelaGeraResumoZeresima() const { return m_tela27; }
    const CFormInterativoTelaVota& GetTelaQuerImprimirZeresima() const { return m_tela28; }
    const CFormInterativoTelaVota& GetTelaLimiteCopiasBUAtingido() const { return m_tela13; }
    const CFormInterativoTelaVota& GetTelaVerificaHorarioZeresima() const { return m_tela2; }
    CFormInterativoTelaVota GetTelaEleicaoPassou() const { return m_tela9; }
    const CFormInterativoTelaVota& GetTelaInicioVotacao() const { return m_tela14; }
    const CFormInterativoTelaVota& GetTelaSincronismo() const { return m_tela21; }
    const std::shared_ptr<api::CProgressBar>& GetBarraSincronismo() const { return m_barraSincronismo; }
    const CFormInterativoTelaVota& GetTelaQuerImprimirBU() const { return m_tela29; }
    const CFormInterativoTelaVota& GetTelaQuerReimprimirZeresima() const { return m_tela30; }

private:
    std::map<comum::TCargoID, CTelasCargo> m_mapaTelas;
    CFormInterativoTelaVota m_tela1, m_tela2, m_tela3, m_tela4, m_tela5, m_tela6, m_tela7, m_tela8, m_tela9, m_tela10;
    CFormInterativoTelaVota m_tela11, m_tela12, m_tela13, m_tela14, m_tela15, m_tela16, m_tela17, m_tela18, m_tela19, m_tela20;
    CFormInterativoTelaVota m_tela21;
    std::shared_ptr<api::CProgressBar> m_barraSincronismo;
    CFormInterativoTelaVota m_tela23, m_tela24, m_tela25, m_tela26, m_tela27, m_tela28, m_tela29, m_tela30;

    static std::mutex s_mutex;
    static std::unique_ptr<CTelasVota> s_instancia;
};

} // namespace vota
