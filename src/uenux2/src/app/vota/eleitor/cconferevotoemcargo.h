#pragma once

#include <memory>
#include <mutex>
#include <optional>

#include "app/vota/eleitor/comum/ctelascargo.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::IConfereVotoEmCargo (RTTI: si_class of vota::CVotacaoStateAudio; vtable @1547576 [1717, 325, 7028, 7480, 1661,
// 7022, 425, 7029, 7010, 11791, 11793, 11792, 11790, 3139, 6999, 11789, 12143]): the base of the CConfereVotoEmCargo<T,
// ETelaVotacao> states (RTTI), abstract (slot 1 is the trap 325, slot 16 pure). Records of cconferevotoemcargo.cpp name
// slot 9 (ProcessInputAudio, :80) and a member slot 12 calls, ExecutarAposAudioAtual (:95, fn 3851); slot 10 holds the
// record :41 of an anonymous-namespace GetCargoID. Slots 9, 10 and 12 are pending
// (src/units/97-uenux2-cvotacaostateaudio-pending.cpp); slot 11 (fn 11792) cancels the wait at +32, slot 15 (fn 11789)
// returns its message. fn 1717, the D2, cancels the +32 wait as slot 11 does, then releases it and calls
// CVotacaoStateAudio's D2. The destructor is out of line: fn 1278, the D0 of every CConfereVotoEmCargo instance, calls fn
// 1717 and frees what it returns, a destructor not out of line in a class that adds no member over an out-of-line base D2
// (docs/reference/facts/reading.md R5); defined in the class, the destructor is inlined there at the tree's -O3 (measured
// in the whole link: 63 rows inserted against 1278, and operand rows only out of line). Declared first, it is the key
// function, a choice. The layout is what the constructor (fn 1165) stores: +28 a tick id it creates stopped and +29 a
// byte, 1 when it created one and 0 with the id 0 otherwise, +30 its argument's byte, +32 a std::shared_ptr. The tick's
// time is read at +176 of comum::CConfiguracaoEleicao::GetInst(), +88 of the CParametrosUrna at +88 there, which is
// tempoConfirmacaoVoto in that class's layout, and compared with 0 as a signed int. The argument is the ETelaVotacao each
// CConfereVotoEmCargo instance passes, its second template argument (fn 11744 passes 14 and 7 for the instances over
// (ETelaVotacao)14 and 7, fn 11724 10, 12, 14 and 2). The widths are evidence. A std::optional<uebyte> for +28 and +29 is
// chosen: its null state stores the 0 at +28 too, and the constructor's rows are the target's with it (whole link,
// operand rows only); the +32 pointee is chosen as CVotacaoStateAudio's wait type, whose member takes the same call of
// slot 2 and reset; the member names, the helpers' (CancelaEsperaConfere and the constructor's CriaTickConfere) and the
// slot-16 name are chosen. This header's path is chosen, beside cconferevotoemcargo.cpp.
class IConfereVotoEmCargo : public CVotacaoStateAudio {
public:
    virtual ~IConfereVotoEmCargo() override;

    virtual void ProcessInputAudio() override;

    virtual void StartStateAudio() override;

    virtual void FinishStateAudio() override;

    virtual void ProcessTickAudio(uebyte tick) override;

    virtual std::string GetMensagem() const override;

    virtual comum::CAppState* GetProximoEstado() const = 0;

protected:
    explicit IConfereVotoEmCargo(ETelaVotacao tela);

private:
    void CancelaEsperaConfere()
    {
        if (m_esperaConfere) {
            m_esperaConfere->Cancela();
            m_esperaConfere.reset();
        }
    }

    std::optional<uebyte> m_tickConfere;
    ETelaVotacao m_tela;
    std::shared_ptr<api::IEsperaAudio> m_esperaConfere;
};

// vota::CConfereVotoEmCargo<ESTADO, TELA> (RTTI: si_class of IConfereVotoEmCargo, ten instances, vtables @1548628 to
// @1550676): the state that asks to confirm the vote ESTADO gives, on the screen TELA. Each instance's vtable is the
// base's but for slot 1, fn 1278, the D0 binaryen keeps once for all ten, and slot 16, GetProximoEstado: a thunk that
// passes ESTADO's statics, vptr and constructor arguments to fn 1961 (the six CConfirmaProporcional states) or fn 2901
// (the four CConfirmaMajoritario ones), the bodies binaryen shares for ESTADO::GetInst() inlined there. Slot 0 is the
// base's D2 (fn 1717): the destructor is not out of line; implicit is a choice (an in-class `= default` or `{}` gives a
// cmp-identical object). A singleton: fns 11683, 11711, 11724 and 11744 hold GetInst inlined,
// in unit 104's form: a lock of the class's std::mutex, the std::unique_ptr built on first use with a 40-B object whose
// constructor calls fn 1165 with TELA and stores the vptr, the old object deleted through a direct call of fn 1717 and a
// free, so the class is final. The statics are a class template's: for the instance over CCandidatoInapto the mutex is
// @1837792 and the unique_ptr @1837820, each followed by a byte that __wasm_call_ctors tests and sets (@1837816,
// @1837824), read as their guards; fn 11742 passes that unique_ptr to fn 1286, which deletes the object, and fn 11743
// passes the mutex to fn 150. The template's name and arguments are the RTTI's; its parameter names, this header and the
// order of the statics' definitions are chosen.
template <typename ESTADO, ETelaVotacao TELA>
class CConfereVotoEmCargo final : public IConfereVotoEmCargo {
public:
    static CConfereVotoEmCargo& GetInst()
    {
        std::lock_guard<std::mutex> trava(s_mutex);
        if (!s_inst) {
            s_inst.reset(new CConfereVotoEmCargo());
        }
        return *s_inst;
    }

    virtual comum::CAppState* GetProximoEstado() const override { return &ESTADO::GetInst(); }

private:
    CConfereVotoEmCargo()
        : IConfereVotoEmCargo(TELA)
    {
    }

    static std::mutex s_mutex;
    static std::unique_ptr<CConfereVotoEmCargo> s_inst;
};

template <typename ESTADO, ETelaVotacao TELA>
std::mutex CConfereVotoEmCargo<ESTADO, TELA>::s_mutex;

template <typename ESTADO, ETelaVotacao TELA>
std::unique_ptr<CConfereVotoEmCargo<ESTADO, TELA>> CConfereVotoEmCargo<ESTADO, TELA>::s_inst;

} // namespace vota
