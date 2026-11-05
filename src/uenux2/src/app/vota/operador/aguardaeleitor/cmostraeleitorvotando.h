#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota {

// vota::CMostraEleitorVotando (RTTI: si_class of comum::CAppState; vtable @1593000 [448, 765, 10427, 7480, 1661, 218,
// 10425, 10426, 425]). It overrides the destructors, StartState (slot 2, fn 10427), ProcessKey (slot 6, fn
// 10425, which holds the private SalvaHabilitacaoEleitor inlined: its records, cmostraeleitorvotando.cpp:127 and 159)
// and ProcessInput (slot 7, fn 10426, record cmostraeleitorvotando.cpp:64). A singleton: fn 1150 creates the 28-byte
// object on first use and keeps it in a static
// std::unique_ptr (@1909316) under a static std::mutex (@1909292), destroyed at exit by fns 10429 and 10428; the
// constructor, inlined there, passes comum::CAppState::EVENTO_TECLA | comum::CAppState::EVENTO_ENTRADA (3) to the base's
// and stores what the layout below holds. The destructor is out of line: the deleting one (fn 765) calls it and frees
// `this`, and it stores no vptr, as a final class's; 19 states share the two bodies, fns 448 and 765. GetInst (fn 1150)
// holds the constructor inlined, which clang gives, and the form's builder, CriaForm, as binaryen inlines a function into
// its one caller: a second stack frame in the middle of fn 1150, entered with a copy of +12's std::shared_ptr made before
// it, so the builder takes the pointer by value. CriaForm's name, its being a static member and its parameter's type are
// chosen; src/units/142-uenux2-app-vota-estados-448.mk says what else is.
//
// The layout: +12 a std::shared_ptr<std::string>, which fn 1150 builds empty with std::make_shared (control block vptr
// 1588328, __shared_ptr_emplace<std::string>) and StartState fills from vota::CThreadOperador's string at +108; +20 the
// form, from api::CMTFormBuilderBase::GetForm (fn 1694). The member names are chosen.
class CMostraEleitorVotando final : public comum::CAppState {
public:
    virtual ~CMostraEleitorVotando() override;

    static CMostraEleitorVotando& GetInst();

    virtual void StartState() override;

    virtual void ProcessKey(uebyte tecla) override;

    virtual void ProcessInput() override;

private:
    CMostraEleitorVotando();

    void SalvaHabilitacaoEleitor();

    static std::shared_ptr<api::IForm<api::IScreenMT>> CriaForm(std::shared_ptr<std::string> nome);

    std::shared_ptr<std::string> m_nome;
    std::shared_ptr<api::IForm<api::IScreenMT>> m_form;

    static std::unique_ptr<CMostraEleitorVotando> s_inst;
    static std::mutex s_mutex;
};

// The voter's WSQ files that SalvaHabilitacaoEleitor writes through
// comum::CControlaArmazenamentoDeImagens::ArmazenaImagem (fn 2725): the voter enabled by its fingerprint, the one
// enabled by the mesario's (its own capture, when there is one) and the mesario's. Each is behind a stack frame of its
// own in fn 10425 (448, 432 and 112 bytes), so out of line, inlined by binaryen into its one caller. They read no state
// of the class: free functions of vota, their names, parameters and file chosen
// (src/units/142-uenux2-app-vota-estados-448.mk).
void ArmazenaImagemHabilitado(const std::vector<uebyte>& wsq, uebyte tentativa, uebyte dedo);
void ArmazenaImagemNaoHabilitado(const std::vector<uebyte>& wsq, uebyte tentativa);
void ArmazenaImagemOperador(const std::vector<uebyte>& wsq);
// The audio word of SalvaHabilitacaoEleitor's comum::CEleitorDadosHabilitacao: 0 in CEstadoAudio's mode 0, else 1 in
// mode 1, else 2. clang inlines it at each of its four calls in cmostraeleitorvotando.cpp; its name, its being a free
// function with external linkage and its line are chosen (unit 142's fragment has the internal form's score).
int TipoAtivacaoAudio();

} // namespace vota
