#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <utility>

namespace vota {

// Recovered: the layout, from the destructor (fn 6548): a map at +0 whose nodes hold another map at +24 (fn 4137), and
// over it a map whose nodes hold a shared_ptr at +20 (fn 1314); then 30 shared_ptrs from +12 to +251, released last to
// first. The element types, the keys and the members' names are chosen: only the destruction order is recovered.
class CTelasVota {
public:
    ~CTelasVota();

    static CTelasVota& GetInst();

private:
    struct CTela;
    using TTelaPtr = std::shared_ptr<CTela>;
    using TMapaTelas = std::map<int, TTelaPtr>;

    std::map<std::pair<int, int>, TMapaTelas> m_mapaTelas;
    TTelaPtr m_tela1, m_tela2, m_tela3, m_tela4, m_tela5, m_tela6, m_tela7, m_tela8, m_tela9, m_tela10;
    TTelaPtr m_tela11, m_tela12, m_tela13, m_tela14, m_tela15, m_tela16, m_tela17, m_tela18, m_tela19, m_tela20;
    TTelaPtr m_tela21, m_tela22, m_tela23, m_tela24, m_tela25, m_tela26, m_tela27, m_tela28, m_tela29, m_tela30;

    static std::mutex s_mutex;
    static std::unique_ptr<CTelasVota> s_instancia;
};

} // namespace vota
