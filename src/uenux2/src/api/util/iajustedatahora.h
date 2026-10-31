#pragma once

// api::IAjusteDataHora: RTTI gives the class and no base, and its one implementer api::CAjusteDataHora (vtable @1584156):
// slots 0 and 1 are the members, 2 and 3 the destructor. The class has no key function: its typeinfo lies in its implementer's
// object (1584192, after that vtable). Slot 1 takes a pointer to a 64-bit time and hands it to ISystemDateTime's slot 1, and
// slot 0 does the same with what fn 1381 reads from an api::CDateTime. Member names, const and the path are chosen: no
// record names a file of this class.

#include <ctime>

namespace api {

class CDateTime;

class IAjusteDataHora {
public:
    virtual void Ajusta(const CDateTime& dataHora) = 0;
    virtual void Ajusta(const time_t& agora) = 0;
    virtual ~IAjusteDataHora() = default;
};

} // namespace api
