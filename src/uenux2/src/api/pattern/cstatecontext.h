#pragma once

// api::CStateContext<STATE>: the base of comum::CAppStateContext, whose typeinfo is a __si_class_type_info naming
// api::CStateContext<comum::CAppState> (typeinfo @1551332, a class with no base: ledger/classes.json). That kind is for
// a derived class that is dynamic exactly when its base is, and CAppStateContext has a vtable, so the base is
// polymorphic too. It has no vtable in the target and its typeinfo lies right after CAppStateContext's (@1551320), so
// no virtual member of its own is out of line: the destructor is inline. Nothing else it declares is recovered: which
// of the context's members (comum::CAppStateContext's state at +4 among them) it holds is not in the target. The head
// alone; this path and the template parameter's name are chosen, beside api/pattern/cstate.h, whose api::CState is the
// base of the states such a context runs.

namespace api {

template <typename STATE>
class CStateContext {
public:
    virtual ~CStateContext() = default;
};

} // namespace api
