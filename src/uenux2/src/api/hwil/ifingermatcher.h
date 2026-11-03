#pragma once

// api::IFingerMatcher: the head alone. The name is the one api::CPolySingleton<api::IFingerMatcher>::instance (fn 1686, a
// thunk into binaryen's fn 6013, which it shares with IFingerScanner's) gives in its records (cpolysingleton.h:78,
// cpolysingletonlist.h:99 and :105) and its typeid name, "N3api14IFingerMatcherE" @539580; no record names a file of
// this class, and the path is chosen, beside the hardware interfaces. No class of the target derives from it
// (ledger/classes.json), so no vtable gives its slots: vota::CDigitalReconhecida::StartState (fn 10482) and fn 5372 read
// an int from slot 4 (10482 formats it after "Score: {}"), and fn 3614 calls slot 2 with three arguments and uses its
// result. The names are chosen after the slots; slot 4's type is the calls' width, and slots 0 to 3 are declared only to
// keep it at its place, with no type recovered. Nothing here calls a slot yet.

namespace api {

class IFingerMatcher {
public:
    virtual void Slot0() = 0;
    virtual void Slot1() = 0;
    virtual void Slot2() = 0;
    virtual void Slot3() = 0;
    virtual int Slot4() = 0;
};

} // namespace api
