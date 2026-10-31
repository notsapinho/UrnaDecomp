#pragma once

#include <map>
#include <memory>
#include <mutex>

#include "app/vota/eleitor/comum/ctelascargo.h"

namespace vota {

// Recovered: the layout, from the destructor (fn 6548): a map at +0 whose nodes hold a CTelasCargo at +20, and so another
// map at +24 (fn 4137), and over it a map whose nodes hold a shared_ptr at +20 (fn 1314); then 30 shared_ptrs from +12 to
// +251, released last to first. Record 1536832, CFormInterativoTelaVota vota::CTelasVota::GetTelaCargo(const
// comum::TCargoID, const ETelaVotacao), held by fn 4135, gives the map's types: 4135 walks the map at +0 comparing a
// one-byte key at node+16 with its first argument, and it holds record 1536624 too, CTelasCargo::GetTela, with its `this`
// at node+20, so that is the element. The members' names are chosen, and so is the 30 members' type: only their
// destruction shows, which any std::shared_ptr gives.
class CTelasVota {
public:
    ~CTelasVota();

    static CTelasVota& GetInst();

    // vota::CImprimindoBU's constructor (inlined into fn 5986) copies the member at +100: the getter's name, and that it
    // is a getter, are chosen.
    const CFormInterativoTelaVota& GetTelaImprimindoBU() const { return m_tela12; }

private:
    std::map<comum::TCargoID, CTelasCargo> m_mapaTelas;
    CFormInterativoTelaVota m_tela1, m_tela2, m_tela3, m_tela4, m_tela5, m_tela6, m_tela7, m_tela8, m_tela9, m_tela10;
    CFormInterativoTelaVota m_tela11, m_tela12, m_tela13, m_tela14, m_tela15, m_tela16, m_tela17, m_tela18, m_tela19, m_tela20;
    CFormInterativoTelaVota m_tela21, m_tela22, m_tela23, m_tela24, m_tela25, m_tela26, m_tela27, m_tela28, m_tela29, m_tela30;

    static std::mutex s_mutex;
    static std::unique_ptr<CTelasVota> s_instancia;
};

} // namespace vota
