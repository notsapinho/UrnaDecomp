#pragma once

#include <map>
#include <memory>
#include <mutex>

#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// One byte: fn 4135 compares it with load8_u. Record 1536832 names the type; its scope and its enumerators are not
// recovered, and that it is a scoped enum is chosen.
enum class ETelaVotacao : unsigned char;

// Recovered: the layout, from the destructor (fn 6548): a map at +0 whose nodes hold another map at +24 (fn 4137), and
// over it a map whose nodes hold a shared_ptr at +20 (fn 1314); then 30 shared_ptrs from +12 to +251, released last to
// first. Record 1536832, CFormInterativoTelaVota vota::CTelasVota::GetTelaCargo(const comum::TCargoID, const ETelaVotacao),
// held by fn 4135, gives the rest of the maps: 4135 walks the map at +0 comparing a one-byte key at node+16 with its
// first argument, then the map at node+24 comparing a one-byte key with its second. So the outer key is a TCargoID, the
// inner key an ETelaVotacao and the inner element a CFormInterativoTelaVota, and a word sits at node+20 that the bodies
// here do not read. STelasCargo, that word's type and the members' names are chosen, and so is the 30 members' type:
// only their destruction shows, which any std::shared_ptr gives.
class CTelasVota {
public:
    ~CTelasVota();

    static CTelasVota& GetInst();

private:
    using TMapaTelas = std::map<ETelaVotacao, CFormInterativoTelaVota>;

    struct STelasCargo {
        unsigned m_naoRecuperado;
        TMapaTelas m_telas;
    };

    std::map<comum::TCargoID, STelasCargo> m_mapaTelas;
    CFormInterativoTelaVota m_tela1, m_tela2, m_tela3, m_tela4, m_tela5, m_tela6, m_tela7, m_tela8, m_tela9, m_tela10;
    CFormInterativoTelaVota m_tela11, m_tela12, m_tela13, m_tela14, m_tela15, m_tela16, m_tela17, m_tela18, m_tela19, m_tela20;
    CFormInterativoTelaVota m_tela21, m_tela22, m_tela23, m_tela24, m_tela25, m_tela26, m_tela27, m_tela28, m_tela29, m_tela30;

    static std::mutex s_mutex;
    static std::unique_ptr<CTelasVota> s_instancia;
};

} // namespace vota
