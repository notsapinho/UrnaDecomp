#pragma once

// api::IFingerScanner: the head alone. The name is the one api::CPolySingleton<api::IFingerScanner>::instance (fn 816, a
// thunk into binaryen's fn 6013) gives in its records (cpolysingleton.h:78, cpolysingletonlist.h:99 and :105) and its
// typeid name, "N3api14IFingerScannerE" @539532; no record names a file of this class, and the path is chosen, beside the
// hardware interfaces. No class of the target derives from it (ledger/classes.json), so no vtable gives its slots: they
// are the ones its callers reach. comum::CPedeDigitalMesario::StartState (fn 10318) calls slot 7 with 2 and then slot 3,
// the FinishState body fn 6012 slot 7 with 0 and then slot 6, and CPedeDigitalMesario::ProcessTick (fn 10316) slot 7 with
// 1, slot 4 (it returns an object through a result pointer) and slot 0, whose int it compares with a vector's size: so
// slot 0 is no destructor. vota::CPedeDigital::ProcessTick (fn 10465) calls slots 4, 0, 2 and 1: slot 4's object is a
// TSharedImageVector (below), whose vector's size it compares with slot 0's int, and slots 2 and 1, called in that
// order, give the ints it passes as the second and third arguments of api::CBmpConversor::InvertColors and VerticalFlip
// (records `(unsigned char *, const int, const int)`) and as VerificaDigital's two `const long` (record
// cpededigital.cpp:262). The names are chosen after the slots; the types of slots 0 to 4, 6 and 7 are the calls' widths
// and slot 4's what 10465 reads from it, and slot 5 is declared only to keep the others at their places, with no type
// recovered.

#include <memory>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace api {

// The name is the records' (vota::CPedeDigital::VerificaDigital's, cpededigital.cpp:262, and
// comum::CPedeDigitalMesario::ExecutaBatimentoDigitalMesario's, cpededigitalmesario.cpp:262, print `const
// api::TSharedImageVector &`); the type is what fn 10465 holds under it: a std::shared_ptr whose control block is
// std::make_shared's __shared_ptr_emplace<std::vector<unsigned char>> (vptr 1529416, ledger/vtables.json) and whose
// vector's bytes it reads. Its being an alias and its place in this header are chosen.
using TSharedImageVector = std::shared_ptr<std::vector<uebyte>>;

class IFingerScanner {
public:
    virtual int Slot0() = 0;
    virtual int Slot1() = 0;
    virtual int Slot2() = 0;
    virtual void Slot3() = 0;
    virtual TSharedImageVector Slot4() = 0;
    virtual void Slot5() = 0;
    virtual void Slot6() = 0;
    virtual void Slot7(int modo) = 0;
};

} // namespace api
