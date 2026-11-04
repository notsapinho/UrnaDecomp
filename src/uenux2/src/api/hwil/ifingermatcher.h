#pragma once

// api::IFingerMatcher: the head alone. The name is the one api::CPolySingleton<api::IFingerMatcher>::instance (fn 1686, a
// thunk into binaryen's fn 6013, which it shares with IFingerScanner's) gives in its records (cpolysingleton.h:78,
// cpolysingletonlist.h:99 and :105) and its typeid name, "N3api14IFingerMatcherE" @539580; no record names a file of
// this class, and the path is chosen, beside the hardware interfaces. No class of the target derives from it
// (ledger/classes.json), so no vtable gives its slots: vota::CDigitalReconhecida::StartState (fn 10482) and fn 5372 read
// an int from slot 4 (10482 formats it after "Score: {}"), and fn 3614 calls slot 2 with three arguments and uses its
// result. vota::CPedeDigital::ProcessTick (fn 10465) calls slot 2 with a std::vector<uebyte> (the template
// CParametrosImagemDigital::ExtraiTemplate fills), the copy of a comum::md::CDedo's minutiae and 20, and tests the
// result; slot 3 with a bool and 20, dropping an i32 result (`call_indirect (i32 i32 i32)->(i32)` and `drop`); and
// stores slot 4's int as a 16-bit score. The names are chosen after the slots; the types of slots 2 to 4 are the calls'
// widths and what 10465 passes, the parameters' names and the bool and int results are chosen, and slots 0 and 1 are
// declared only to keep the others at their places, with no type recovered.

#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace api {

struct SXYT; // comum::md's cdedo.h defines it

class IFingerMatcher {
public:
    virtual void Slot0() = 0;
    virtual void Slot1() = 0;
    virtual bool Slot2(const std::vector<uebyte>& modelo, const std::vector<SXYT>& minucias, int limiar) = 0;
    virtual int Slot3(bool reconhecido, int limiar) = 0;
    virtual int Slot4() = 0;
};

} // namespace api
