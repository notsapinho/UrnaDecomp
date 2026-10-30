#pragma once

// Reconstruction's note, not TSE's text. This file's records are the only recovered lines: line 61 is the throw of
// `std::string api::KeyName(char)` (fn 744) and line 86 the throw of `char api::IInput::GetKey()`, held inlined by fns
// 6319, 10426, 11024 and 11804. Neither is written, so both lines stay blank and the classes follow them: their lines
// are a choice, and so is having IInputKbd and IInputMT in this file. Their names and bases are RTTI's: IInput
// (typeinfo 1530852, a polymorphic class with no base), IInputKbd (1530840) and IInputMT (1530860), si_classes of
// IInput, implemented by simulador::CWasmInputKbd and simulador::CWasmInputMT (vtables @1530084 and @1530136).
// What the target shows of IInput:
// - slots 0 and 1 are the destructor: both implementers hold the shared empty bodies 174 and 144 there. A defaulted
//   destructor in the class is the chosen form.
// - GetKey is not a slot, and its body, read in fn 6319, gives slots 2 and 3 and the int at +4: it throws "IInput - Nao
//   havia um caractere disponivel" unless slot 3 returns true, then calls slot 2 and adds 1 to +4.
// - both implementers' objects are 8 bytes and fn 8302 stores 0 at +4 of each right after the vptr, so the counter is
//   this class's member. Its type and its default initializer are chosen.
// - slot 4 takes nothing and returns nothing: fns 10835, 11075, 11077, 11791 and 13564 call it on the keyboard they get
//   from fn 455, and CWasmInputKbd's body empties the browser's key queue.
// IInputKbd adds slots 5 to 7, which CWasmInputKbd's vtable holds and CWasmInputMT's lacks. All three hold 218, the
// shared empty (i32)->() body, so each takes nothing and returns nothing. fn 7377 (slot 2 of vota::CEleitorVotando) calls
// slot 7 on the keyboard. A look at what fn 455's callers do with its result found no call of slots 5 and 6. Whether
// the empty bodies are IInputKbd's defaults or CWasmInputKbd's overrides is not determined: they are pure here and
// the implementer holds them, a choice (units/81-uenux2-simulador-wasm-devices.mk lists the other).
// The names ReadKey, HasKey, Clear, Slot5, Slot6, Slot7 and m_lidas are chosen: the first three from the imports the
// implementers call (wasm_input_get_key, wasm_input_has_key, wasm_input_clear), the SlotN after their slots, as no
// evidence gives them a role.

// (original lines 27-57: content not recovered)
#line 58
// <stubs>
// f744 · 625 B · unmatched · name unknown
// void f744(i32, i32) { ... }
// </stubs>

// (original lines 63-78: content not recovered)
#line 79
// <stubs>
// f11024 · 673 B · unmatched · name unknown
// ? f11024(i32, i32) { ... }

// f6319 · 673 B · unmatched · name unknown
// ? f6319(i32, i32) { ... }
// </stubs>

namespace api {

class IInput {
public:
    virtual ~IInput() = default;

    virtual char ReadKey() = 0;
    virtual bool HasKey() = 0;
    virtual void Clear() = 0;

protected:
    int m_lidas = 0;
};

class IInputKbd : public IInput {
public:
    virtual void Slot5() = 0;
    virtual void Slot6() = 0;
    virtual void Slot7() = 0;
};

class IInputMT : public IInput {};

} // namespace api
