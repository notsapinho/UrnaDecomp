#pragma once

// api::IFingerDetection: the head alone. The name is the one api::CPolySingleton<api::IFingerDetection>::instance (fn
// 3615) gives in its records (cpolysingleton.h:78, cpolysingletonlist.h:99 and :105) and its typeid name,
// "N3api16IFingerDetectionE" @539555; no record names a file of this class, and the path is chosen, beside the other
// hardware interfaces (ifingermatcher.h, ifingerscanner.h). No class of the target derives from it (ledger/classes.json),
// so no vtable gives its slots: fn 10451 calls slot 2 on the instance with one argument and tests the result for zero.
// The name is chosen after the slot, the parameter's and result's types are the call's widths, and slots 0 and 1 are
// declared only to keep slot 2 at its place, with no type recovered. Nothing here calls a slot yet.

namespace api {

class IFingerDetection {
public:
    virtual void Slot0() = 0;
    virtual void Slot1() = 0;
    virtual int Slot2(const void* imagem) = 0;
};

} // namespace api
