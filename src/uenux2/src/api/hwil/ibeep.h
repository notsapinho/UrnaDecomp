#pragma once

#include <utility>
#include <vector>

namespace api {

// Recovered: RTTI names api::IBeep (typeinfo 1531756), a polymorphic class with no base, and its one implementer
// simulador::CWasmBeep (vtable @1530304), which the wasm build registers as the CPolySingleton<api::IBeep> (records
// of api/pattern/cpolysingleton.h and cpolysingletonlist.h). The target has its typeinfo and no vtable of its own.
// Its nine slots are seven members and the destructor's two, which come last (slots 7 and 8). CWasmBeep's bodies and
// the callers give the members' roles: slot 0 sets the volume (js_wasm_beep_set_volume), slot 1 queues one tone of a
// frequency for a duration in tens of milliseconds (js_wasm_beep_queue(frequency, duration * 10)), and slots 2 to 6
// play fixed tone sequences through slot 1. Slot 2 takes a repeat count (vota::CFimVotoEleitor::StartState passes 4,
// CEleitorVotando::NeedChangeState 1), slot 3 is called by CVerificaEleicaoPassou::StartState, slot 4 by
// CInformacaoZeresimaTardia::ProcessInput and CThreadMonitor::SaiPorVotacaoSuspensa, slot 5 by
// CEleitorVotando::DescartaVotos, slot 6 by CVotacaoStateAudio::PlayKey and the menu fields' input.
// The sequences are built outside the TU that plays them (ibeep.cpp): CWasmBeep's members keep the vector in their
// frame and load its begin and end again after it is built and on every pass, which they do only when the function
// that fills it is one clang cannot see into; binaryen then inlined each into its one caller, so none has a target
// function of its own. No record, symbol or string names any member or this file: the names SetVolume, Beep,
// BeepConfirm, BeepError, BeepAlert, BeepDiscard and BeepKey, the sequence functions' names, their being static
// members, and the path, beside the hardware interfaces whose records name api/hwil/ (iinput.h, ipower.h,
// iimpressora.h), are chosen.
class IBeep {
public:
    virtual void SetVolume(int volume) = 0;
    virtual void Beep(int frequency, int duration) = 0;
    virtual void BeepConfirm(int times) = 0;
    virtual void BeepError() = 0;
    virtual void BeepAlert() = 0;
    virtual void BeepDiscard() = 0;
    virtual void BeepKey() = 0;

    virtual ~IBeep() = default;

protected:
    // a tone sequence: each tone's frequency (Hz) and duration (tens of milliseconds), as Beep takes them
    static std::vector<std::pair<int, int>> ConfirmTones();
    static std::vector<std::pair<int, int>> ErrorTones();
    static std::vector<std::pair<int, int>> AlertTones();
    static std::vector<std::pair<int, int>> DiscardTones();
};

} // namespace api
