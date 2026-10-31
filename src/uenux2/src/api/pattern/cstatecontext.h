#pragma once

// api::CStateContext<STATE>: the base of comum::CAppStateContext, whose typeinfo is a __si_class_type_info naming
// api::CStateContext<comum::CAppState> (typeinfo @1551332, a class with no base: ledger/classes.json). The base has no
// vtable in the target. Whether it is polymorphic is not in the bytes: an empty base, with the virtual destructor in
// CAppStateContext alone, gives the same typeinfo kinds and the same code (only one destructor symbol's name differs,
// and the link folds that body into the shared body 174). The inline virtual destructor here is a choice. Nothing
// else it declares is recovered: which
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
