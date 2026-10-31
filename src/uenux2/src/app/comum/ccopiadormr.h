#pragma once

namespace comum {

// RTTI: comum::CCopiadorMR, a class with no base, and CCopiadorWSQMR, an si_class of it; both vtables are [11638, 5872,
// 5874, 5873]. fn 12134 (records of ccopiaresultadoparamr.cpp) builds them with std::make_shared, 16 bytes each.
// Recovered: the heads only, the two slots named after their slot. The constructors are declared only, and their
// parameters are not recovered. Not final: the blocks' __on_zero_shared go through the vtable (fn 411). The path is
// chosen: no record names either class.
class CCopiadorMR {
public:
    CCopiadorMR();
    virtual ~CCopiadorMR();

    virtual void Slot2();
    virtual void Slot3();
};

class CCopiadorWSQMR : public CCopiadorMR {
public:
    CCopiadorWSQMR();
};

} // namespace comum
