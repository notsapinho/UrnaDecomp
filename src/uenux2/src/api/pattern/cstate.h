#pragma once

// api::CState: the base of comum::CAppState (RTTI: a class with no base, ledger/classes.json), the only class derived
// from it; api::CStateContext<comum::CAppState> is the machine that runs such states. It is polymorphic: CAppState's
// typeinfo is a __si_class_type_info, which the C++ ABI gives a class whose one base is dynamic too. It has no vtable
// in the target, and its typeinfo is emitted beside CAppState's (@1551296, right after @1551284), so no virtual member
// of its own is out of line: the destructor is inline. Nothing else it declares is recovered: CAppState's nine slots
// (app/comum/cappstate.h) fit this class declaring only the destructor or any of them first. No record, symbol or
// caller names this header: its directory is chosen, beside api's other pattern templates (cpolysingletonlist.h).

namespace api {

class CState {
public:
    virtual ~CState() = default;
};

} // namespace api
