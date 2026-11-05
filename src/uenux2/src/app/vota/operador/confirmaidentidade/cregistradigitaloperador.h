#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace comum::md {
class CEleitorIdentidade;
} // namespace comum::md

namespace vota {

// vota::CRegistraDigitalOperador (RTTI: si_class of comum::CAppState; vtable @1592424 [1537, 3629, 10454, 7480, 1661,
// 10453, 425, 10452, 10451]): the operator's screen that captures the mesario's finger before a manual habilitation. It
// overrides StartState (slot 2, fn 10454, records cregistradigitaloperador.cpp:95 and :98), FinishState (slot 5, fn
// 10453, records :104 and :105, a thunk into binaryen's fn 6012, the body it shares with
// comum::CPedeDigitalMesario::FinishState), ProcessInput (slot 7, fn 10452), which cancels the habilitation on CORRIGE
// and goes back to vota::CPedeIdentidade, and ProcessTick (slot 8, fn 10451, records :143 to :145), matched
// (src/units/221-uenux2-app-comum-constructors.mk has the forms and the order of objects it needs). The destructor is
// out of line, the body comum::CPedeDigitalMesario and vota::CPedeIdentidade share (fns 1537 and 3629), which releases
// the std::shared_ptr at +24 and then the one at +16.
//
// The layout is what the constructor stores, which GetInst (fn 5396) holds inlined by binaryen: CAppState's with
// EVENTO_ENTRADA | EVENTO_TICK (6); +11 and +12 the bytes vota::CThreadOperador's AddStoppedTick (fn 807) returns for
// 15000 and 50, the ticks StartState starts and ProcessInput stops; +16 the form StartState shows and ProcessInput
// reads, and +24 a second form, "Digital capturada"; +32 a byte the constructor sets to 3, which ProcessTick decrements
// and sets back to 3 or to 0 (i32.load8_u, i32.store8). A singleton: GetInst creates the 36-byte object under a static
// std::mutex (@1909124, destroyed at exit by fn 10456) and keeps it in a static std::unique_ptr (@1909148, by fn 10457,
// a thunk into binaryen's fn 3886, the body of the three statics' ~unique_ptr of the classes that share fn 1537). The
// members' names are chosen. src/units/221-uenux2-app-comum-constructors.mk says which of this is evidence and which
// is chosen.
class CRegistraDigitalOperador final : public comum::CAppState {
public:
    virtual ~CRegistraDigitalOperador() override;

    static CRegistraDigitalOperador& GetInst();

    virtual void StartState() override;

    virtual void FinishState() override;

    virtual void ProcessInput() override;

    virtual void ProcessTick(uebyte id) override;

private:
    CRegistraDigitalOperador();

    // What ProcessTick (fn 10451) holds behind frames of their own once it has stored the captured digital, functions
    // clang kept out of line and binaryen inlined (docs/reference/facts/reading.md R10): IdentificaMesario's 16-byte
    // frame holds the three searches, each behind a 16-byte frame of its own over one of comum::CRegistradorMesario's
    // maps of mesarios, and the search of the digital among the files of the non-registered ones. Their names, their
    // being members (dead-argument elimination dropped the `this` none of them reads) and the split into three
    // searches of one shape are chosen; that each is a function of its own is what the frames show.
    void IdentificaMesario();
    bool BuscaMesarioSecaoComBiometria();
    bool BuscaMesarioSecaoSemBiometria();
    bool BuscaMesarioForaSecao();
    // Fn 3614, with no record of its own: its body opens with BiometriaMesarioPresenteNosEleitores's code (records
    // cregistradigitaloperador.cpp:328 and :371) behind a 96-byte frame inside its own 416-byte one, binaryen's
    // inlining, and then looks for the mesario's registered digital file. Its wasm type is `(i32 i32)->(i32)`, and the
    // three searches pass it the map node's identity and the comparecimento's id_arquivo, or 999999 when it has none (a
    // `select`): those are its parameters. Its name and its being a member of this class are chosen; the member it
    // calls takes both from its records (328, 371: CRegistraDigitalOperador::BiometriaMesarioPresenteNosEleitores).
    bool BiometriaMesarioPresente(const comum::md::CEleitorIdentidade& mesario, int idArquivo);
    bool BiometriaMesarioPresenteNosEleitores(const comum::md::CEleitorIdentidade& mesario);

    static std::unique_ptr<CRegistraDigitalOperador> s_inst;
    static std::mutex s_mutex;

    uebyte m_tickCaptura;
    uebyte m_tickEspera;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_formCapturada;
    uebyte m_tentativasRestantes;
};

// The operator's two forms of this state, which the constructor builds in place. GetInst (fn 5396) holds them inlined
// by binaryen, behind a 64-byte and a 48-byte frame: the first asks the mesario for a finger, the second says "Digital
// capturada" and "Por favor aguarde". Their names and their being free functions of vota with external linkage are
// chosen (src/units/221-uenux2-app-comum-constructors.mk).
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaRegistraDigitalOperador();
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaDigitalCapturadaOperador();

} // namespace vota
