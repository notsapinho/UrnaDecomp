#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "app/comum/cappstate.h"
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// The options StartState offers, by the number the operator types: the type's name and the type. The alias's name is
// chosen.
using TOpcoesIdentidade = std::map<int, std::pair<std::string, ecourna::app::dados::ETipoIdentificadorEleitor>>;

// vota::CValidaIdentidade (RTTI: si_class of comum::CAppState; vtable @1589064 [2749, 10628, 10627, 7480, 1661, 218,
// 425, 10626, 425]): the state that validates the identifier the operator typed. It overrides StartState (slot 2, fn
// 10627) and ProcessInput (slot 7, fn 10626). The destructor is out of line:
// the deleting one (fn 10628) calls it (fn 2749) and frees `this`, and it stores no vptr, as a final class's
// (docs/reference/facts/reading.md R4, R5). It destroys the std::map at +20 through its tree's destroy (fn 1906), then
// releases the std::shared_ptr at +12. A singleton: vota::CPedeIdentidade::ProcessInput (fn 10677) holds GetInst and
// the constructor inlined: the 32-byte object under a static std::mutex (@1905648, destroyed at exit by fn 10629) kept
// in a static std::unique_ptr (@1905672, by fn 10630, which calls fn 2749); the constructor passes
// comum::CAppState::EVENTO_ENTRADA (2) to the base's and leaves the form and the map empty. StartState (slot 2, fn
// 10627) fills both when the identifier typed fits more than one type. The map's key is an int, the option the operator
// types, and its value 16 bytes, the type's name (a std::string) and the type, a word at +12 that ProcessInput passes to
// vota::SetTipoIdentidadeDigitada (fn 3619): MontaOpcoesIdentidade (fn 5420) builds each value from a literal and a
// type with no call of md::CEleitorIdentidade's constructor (fn 566). The std::pair is a choice of type, as are the
// members' names. src/units/278-uenux2-cvalidaidentidade.mk says which of this is evidence and which is chosen.
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
    TOpcoesIdentidade m_identidades;
};

// fn 5420, called twice by StartState (fn 10627), its one caller: the options of the types given, numbered from 1 in
// their order, "Título de eleitor", "CPF" or "Identificador" with the type (a type past the three gets no option and no
// number). The vector is taken by value: the caller copies it for each call. Its name, its being a free function of vota
// and its external linkage are chosen; cvalidaidentidade.cpp, its caller's file, is a choice its band allows: 5420 links
// right after vota::CProcuraEleitor::GetInst (fn 5421, cprocuraeleitor.cpp), whose object's data come just before
// this class's vtable.
TOpcoesIdentidade MontaOpcoesIdentidade(std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> tipos);

// Held inlined by binaryen in StartState (fn 10627), behind a 464-byte frame of its own: the form that lists the
// options and takes the one typed. Its name, its parameter and its being a free function of vota are chosen.
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaOpcoes(const TOpcoesIdentidade& opcoes);

} // namespace vota
