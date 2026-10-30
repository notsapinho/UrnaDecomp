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
// The target shows that each sequence of slots 2 to 5 is built in another TU and returned by value: CWasmBeep's members
// keep the vector in their frame and load its begin and end right after the code that stored them, with no call
// between, which a function boundary alone gives (clang forwards such a store, binaryen does not), and fn 8523 zeroes
// the vector after a second stack prologue, so the callee builds it. Each was inlined by binaryen into its one caller,
// so none has a target function of its own. That they are free functions of namespace api, in ibeep.cpp, is a choice:
// they read no state, and no evidence names the file. No record, symbol or string names any member, sequence or this
// file: the names SetVolume, Beep, BeepConfirm, BeepError, BeepAlert, BeepDiscard, BeepKey, ConfirmTones, ErrorTones,
// AlertTones and DiscardTones are chosen from those roles, and the path, beside the hardware interfaces whose records
// name api/hwil/ (iinput.h, ipower.h, iimpressora.h), is chosen.
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
};

// the tone sequences of slots 2 to 5: each tone's frequency (Hz) and duration (tens of milliseconds), as IBeep::Beep
// takes them
std::vector<std::pair<int, int>> ConfirmTones();
std::vector<std::pair<int, int>> ErrorTones();
std::vector<std::pair<int, int>> AlertTones();
std::vector<std::pair<int, int>> DiscardTones();

} // namespace api
