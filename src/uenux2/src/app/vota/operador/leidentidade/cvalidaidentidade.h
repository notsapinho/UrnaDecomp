#pragma once

#include <map>
#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CValidaIdentidade (RTTI: si_class of comum::CAppState; vtable @1589064 [2749, 10628, 10627, 7480, 1661, 218,
// 425, 10626, 425]): the state that validates the identifier the operator typed. It overrides StartState (slot 2, fn
// 10627, 3842 B), which is pending (src/units/278-uenux2-cvalidaidentidade-pending.cpp says what it waits
// for), and ProcessInput (slot 7, fn 10626). The destructor is out of line:
// the deleting one (fn 10628) calls it (fn 2749) and frees `this`, and it stores no vptr, as a final class's
// (docs/reference/facts/reading.md R4, R5). It destroys the std::map at +20 through its tree's destroy (fn 1906), then
// releases the std::shared_ptr at +12. A singleton: vota::CPedeIdentidade::ProcessInput (fn 10677) holds GetInst and
// the constructor inlined: the 32-byte object under a static std::mutex (@1905648, destroyed at exit by fn 10629) kept
// in a static std::unique_ptr (@1905672, by fn 10630, which calls fn 2749); the constructor passes
// comum::CAppState::EVENTO_ENTRADA (2) to the base's and leaves the form and the map empty. The map's key is an int and
// its value 16 bytes, a std::string and a word at +12 that ProcessInput passes to vota::SetTipoIdentidadeDigitada (fn
// 3619): md::CEleitorIdentidade's layout, a choice of type. The members' names are chosen.
// src/units/278-uenux2-cvalidaidentidade.mk says which of this is evidence and which is chosen.
class CValidaIdentidade final : public comum::CAppState {
public:
    virtual ~CValidaIdentidade() override;

    static CValidaIdentidade& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CValidaIdentidade();

    // Held inlined by binaryen in ProcessInput (fn 10626), behind a 400-byte frame of its own that reads the form at
    // +12 and the map at +20: the one-digit option typed, its identifier logged and its type made the typed one, and
    // the next state, or none. Its name, its result type and its being a member are chosen
    // (src/units/278-uenux2-cvalidaidentidade.mk).
    comum::CAppState* ProximoEstadoOpcaoDigitada();

    static std::unique_ptr<CValidaIdentidade> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::map<int, comum::md::CEleitorIdentidade> m_identidades;
};

} // namespace vota
