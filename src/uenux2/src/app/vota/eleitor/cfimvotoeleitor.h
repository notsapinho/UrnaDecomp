#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CFimVotoEleitor (RTTI: si_class of comum::CAppState; vtable @1534004 [174, 144, 7198, 7480, 1661, 218, 425,
// 218, 425]): it overrides StartState alone (slot 2, fn 7198, record cfimvotoeleitor.cpp:42; pending:
// src/units/241-uenux2-app-vota-eleitor-pending.cpp says what it waits for). Its singleton lives in fn 7181
// (vota::CSincronismoEleitor::ProcessKey), which holds GetInst and the constructor inlined: it allocates 12 bytes,
// passes 0 to the base's constructor and stores only the vptr, keeps the object in a static std::unique_ptr (@1833132)
// under a static std::mutex (@1833108), and frees an old object with no call through the vtable, as for a final class
// (the states of src/units/104-uenux2-app-vota-estados.mk have the same shape and its fragment the evidence for each
// part).
//
// The constructor is out of line in cfimvotoeleitor.cpp: 7181 keeps what operator new returned as the object and takes
// the vptr store's address from the base constructor's result, the shape that fragment gives an out-of-line constructor
// binaryen inlines. Measured in the whole link (pnpm wasm score of 7181 against ProcessKey): defined in the class, 101
// over 858 rows (99 replaced, 98 of them operand-only, 1 inserted, 1 deleted), the base constructor's result kept as
// the object where the target keeps operator new's; out of line, 7181 matches. GetInst and the statics are in
// cfimvotoeleitor.cpp too; the target has no function of GetInst's own, and
// whether clang or binaryen inlined it into 7181 is not decided: its place is a choice. The statics are members defined
// below GetInst, the pointer first: the mutex lies lower in .bss and the pointer's exit destructor (fn 7212) links
// before the mutex's (fn 7202), both before StartState's 7198 in use band 1. The destructors are the bodies 174 and 144
// the class shares with the base, an implicit destructor. The enumerator EVENTO_NENHUM for the 0 is the base header's;
// the path of this header is chosen, beside cfimvotoeleitor.cpp, the file StartState's record names.

class CFimVotoEleitor final : public comum::CAppState {
public:
    static CFimVotoEleitor& GetInst();

    virtual void StartState() override;

private:
    CFimVotoEleitor();

    static std::unique_ptr<CFimVotoEleitor> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
