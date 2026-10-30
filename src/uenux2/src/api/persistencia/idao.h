#pragma once

namespace api::persistencia {

// Base of every DAO. The name and the namespace are RTTI's (typeinfo 1558992, kind "class": no base); the path, beside
// iuenuxgenericdao.h, is chosen: no record names this file. The typeinfo lies among the records of
// app/comum/dados/dao/celeitordinamicodao.cpp, a linkonce copy, so the class has no key function.
//
// No data member: one would make the destructor a derived class inlines store this class's vptr, and fn 1704, slot 0
// of all three DAOs, stores none (measured: a std::shared_ptr member here adds that store to the derived class's D2
// even with the derived class final). So the connection at +4 is the derived class's member.
class IDAO {
public:
    virtual ~IDAO() = default;

    // Slot 2. The name is chosen from the role: CDAORepositorio::Entregar (fns 815, 3742) calls the slot on the object it
    // holds and passes the result to __dynamic_cast with this class's typeinfo as the source, so the result is an IDAO*;
    // each DAO returns a new copy of itself (fn 3894). Pure is chosen: the three DAOs override it and the target has no
    // vtable of this class to show the slot.
    virtual IDAO* Clone() const = 0;
};

} // namespace api::persistencia
