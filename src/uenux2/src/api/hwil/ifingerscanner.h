#pragma once

// api::IFingerScanner: the head alone. The name is the one api::CPolySingleton<api::IFingerScanner>::instance (fn 816, a
// thunk into binaryen's fn 6013) gives in its records (cpolysingleton.h:78, cpolysingletonlist.h:99 and :105) and its
// typeid name, "N3api14IFingerScannerE" @539532; no record names a file of this class, and the path is chosen, beside the
// hardware interfaces. No class of the target derives from it (ledger/classes.json), so no vtable gives its slots: they
// are the ones its callers reach. comum::CPedeDigitalMesario::StartState (fn 10318) calls slot 7 with 2 and then slot 3,
// the FinishState body fn 6012 slot 7 with 0 and then slot 6, and CPedeDigitalMesario::ProcessTick (fn 10316) slot 7 with
// 1, slot 4 (it returns an object through a result pointer) and slot 0, whose int it compares with a vector's size: so
// slot 0 is no destructor. The names are chosen after the slots; the types of slots 0, 3, 6 and 7 are the calls' widths,
// and slots 1, 2, 4 and 5 are declared only to keep the others at their places, with no type recovered.

namespace api {

class IFingerScanner {
public:
    virtual int Slot0() = 0;
    virtual void Slot1() = 0;
    virtual void Slot2() = 0;
    virtual void Slot3() = 0;
    virtual void Slot4() = 0;
    virtual void Slot5() = 0;
    virtual void Slot6() = 0;
    virtual void Slot7(int modo) = 0;
};

} // namespace api
