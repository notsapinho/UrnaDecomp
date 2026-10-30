#pragma once

#include <memory>
#include <string>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CEleitorVotouNaoVotou (RTTI: si_class of comum::CAppState; vtable @1592928 [1284, 2884, 10431, 7480, 1661, 218,
// 425, 10430, 425]): the operator's screen that says whether the voter voted. It overrides the destructors, StartState
// (slot 2, fn 10431) and ProcessInput (slot 7, fn 10430, pending); slot 2's name is comum::CAppState's. A singleton: fn
// 1901 creates the one 36-byte object on first use, unlocks a static std::mutex (@1909264, destroyed at exit by fn
// 10433) and keeps the object in a static std::unique_ptr (@1909288, destroyed at exit by fn 10434); the table holds
// fns 10434 and 10433 right before this vtable's slots (elem 4215-4220). The constructor, inlined there, passes
// comum::CAppState::EVENTO_ENTRADA (2) to the base constructor (fn 224) and stores what the layout below holds.
// Recovered: the layout, StartState and the destructor. It is out of line, as the deleting one shows (fn 2884,
// f1284(p0); f136(p0)); it stores no vptr, which clang leaves out only when the class or the destructor is final. fns
// 1284 and 2884 fill the same slots of vota::CRetirarMR, CDigitalNaoReconhecida and CEleitorDemorando: binaryen merged
// those classes' destructors. Declared first, it is the key function and celeitorvotounaovotou.cpp emits the vtable: a
// choice, as a key function StartState gives the same objects' code. Not recovered: the constructor and GetInst (fn
// 1901; its name follows the project's other singletons).
//
// The layout: +11 whether the voter voted: fn 1901 clears it, and the code that goes to this state sets it first, to 0
// in CMostraEleitorVotando's and CPerguntaCodigoSuspensao's slot 6 (fns 10425, 10419) and to 1 in
// CSincronismoOperador's (fn 10209); StartState says "VOTOU" when it is not 0. bool is a choice: a uebyte gives a
// cmp-identical module. private with no setter is a choice too: those three classes write it. +12 and +20 two
// std::shared_ptr<std::string>: fn 1901 builds each with std::make_shared (control block vptr 1588328,
// __shared_ptr_emplace<std::string>), the first from "pode/nao pode entregar comp", the second empty, and hands each to
// a field of the form (fn 1152). +28 the form: fn 1901 takes it from fn 301, whose control block is
// __shared_ptr_pointer<api::CInteractiveForm<api::IScreenMT, api::IInputMT>*, ...> (vptr 1580416), and fn 10430 reads
// it through that class's Read() (record cinteractiveform.h:57 @1592984). The member names are not in the target.
class CEleitorVotouNaoVotou final : public comum::CAppState {
public:
    virtual ~CEleitorVotouNaoVotou() override;

    static CEleitorVotouNaoVotou& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CEleitorVotouNaoVotou();

    bool m_bVotou;
    std::shared_ptr<std::string> m_situacao;
    std::shared_ptr<std::string> m_complemento;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
