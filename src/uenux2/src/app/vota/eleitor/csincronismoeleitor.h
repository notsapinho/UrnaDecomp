#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CSincronismoEleitor (RTTI: si_class of comum::CAppState; vtable @1534076 [174, 144, 7178, 7480, 1661, 218, 7181,
// 218, 425]): it overrides StartState (slot 2, fn 7178) and ProcessKey (slot 6, fn 7181). Its singleton lives in fn 4454,
// which holds GetInst and the constructor inlined: it allocates 12 bytes, passes comum::CAppState::EVENTO_TECLA (1) to
// the base's constructor and stores only the vptr, keeps the object in a static std::unique_ptr (@1833160) under a static
// std::mutex (@1833136), and frees an old object with no call through the vtable, as for a final class. GetInst, the
// statics and the constructor are in csincronismoeleitor.cpp: the target has no function of GetInst's own, and
// whether clang or binaryen inlined it into 4454 (vota::CEleitorVotando::FinalizaEleitor, written and not matched) is
// not decided, a choice. The constructor is out of line, above GetInst (its place a choice): 4454 stores the vptr
// through the base constructor's returned `this` and sets s_inst from operator new's pointer, as a call of the complete
// constructor that binaryen inlines gives (at -fPIC it stays a call in its TU, docs/reference/facts/codegen.md C6);
// defined in the class, clang inlines it into GetInst and uses the returned `this` for both (unit 197's fragment has
// 4454's scores). The statics' exit destructors are fns 7195 (s_inst) and 7187 (s_mutex), in that order in use band 1,
// so s_inst is defined first. The destructors are the bodies 174 and 144 the class shares with the base, an implicit
// destructor.
//
// No record names the class: the path is chosen. Its vtable and typeinfo lie in the data between
// app/vota/eleitor/cfimvotoeleitor.cpp's record (1534048) and app/vota/eleitor/csincronismovotoeleitor.cpp's (1534132),
// where csincronismoeleitor.cpp, the class's name in lower case, sorts in that directory's name order; a place at the end
// of either neighbour's object fits the data too.
class CSincronismoEleitor final : public comum::CAppState {
public:
    static CSincronismoEleitor& GetInst();

    virtual void StartState() override;

    virtual void ProcessKey(uebyte tecla) override;

private:
    CSincronismoEleitor();

    static std::unique_ptr<CSincronismoEleitor> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
