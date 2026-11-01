#pragma once

#include <memory>
#include <mutex>
#include <optional>
#include <vector>

#include "app/comum/cappstate.h"
#include "app/comum/dados/md/candidatura/ccandidatura.h"

namespace vota {

// vota::CVisualizarCandidatos (RTTI: si_class of comum::CAppState; vtable @1545664 [2871, 11877, 11876, 7480, 1661,
// 218, 425, 218, 425]): it overrides StartState (slot 2, fn 11876, records cvisualizarcandidatos.cpp:132 and :140,
// pending: src/units/150-uenux2-eleitor-estados-pending.cpp) and the destructors. The destructor is out of line: the
// deleting one (fn 11877) calls it and frees `this`; fn 2871 stores no vptr, as a final class's
// (docs/reference/facts/reading.md R4). Fn 2871 destroys a std::vector of 72-byte elements at +12, each one's members
// where comum::md::CCandidatura has them (ccandidatura.h): the substitutes' vector at +60 through fn 1719, then the
// holder's optional string and two strings at +32, +20 and +8. A singleton: GetInst (fn 1279) keeps the object (40 B) in
// a static std::unique_ptr (@1834660) under a static std::mutex (@1834636); the constructor passes 2 to the base's and
// zeroes +12 to +25 (two overlapping 8-byte stores) and the bytes at +28, +32, +36 and +38, which is what three
// std::optional give, over one byte at +24, four bytes at +28 and two at +36, each with its null state and its flag
// zeroed. Their types are chosen from those widths, as comum::md::TCargoID, comum::TCandidatoID and
// comum::TPartidoID; every member name, GetInst's, and this header's path beside cvisualizarcandidatos.cpp are chosen.
class CVisualizarCandidatos final : public comum::CAppState {
public:
    virtual ~CVisualizarCandidatos() override;

    static CVisualizarCandidatos& GetInst();

    virtual void StartState() override;

    // Fn 5951: the byte at +24 when +25 is set, else 0, so m_cargo's value or 0. Out of line, in this class's .cpp:
    // vota::CMenuFiltrarCandidatosPorNumero's two slots (fns 11891 and 11892, another file) call it on GetInst()'s
    // result. No record names it; the name is chosen from what it returns.
    comum::md::TCargoID GetCargo() const;

private:
    CVisualizarCandidatos();

    static std::mutex s_mutex;
    static std::unique_ptr<CVisualizarCandidatos> s_inst;

    std::vector<comum::md::CCandidatura> m_candidaturas;
    std::optional<comum::md::TCargoID> m_cargo;
    std::optional<comum::TCandidatoID> m_candidato;
    std::optional<comum::TPartidoID> m_partido;
};

} // namespace vota
