#pragma once

namespace api {

// api::IRWSyncCtl (RTTI: a class with no base, typeinfo @1600468, just after api::CPosixRWMutex's @1600456): the
// interface of a lock with readers and a writer, built through api::CDefaultGenericFactory<api::IRWSyncCtl,
// api::CPosixRWMutex> (vtable @1526988). It has no vtable in the target, so its destructor is inline and its other
// members pure. No record names this header: its path is chosen, beside api/ipc/isyncctl.h. The three members' names are
// the overrider's records'; their order is the order of those records' lines in cposixrwmutex.cpp, a choice, since the
// three slots of api::CPosixRWMutex's vtable hold one body (fn 2219).
class IRWSyncCtl {
public:
    virtual ~IRWSyncCtl() = default;

    virtual void ReadLock() = 0;
    virtual void WriteLock() = 0;
    virtual void Unlock() = 0;
};

} // namespace api
