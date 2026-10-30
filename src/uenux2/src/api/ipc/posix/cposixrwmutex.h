#pragma once

#include <pthread.h>

#include "api/ipc/irwsyncctl.h"

namespace api {

// api::CPosixRWMutex (RTTI: si_class of api::IRWSyncCtl; vtable @1600332 [5353, 10244, 2219, 2219, 2219]). The records
// of cposixrwmutex.cpp name the constructor, ReadLock, WriteLock and Unlock. The target's bodies hold no read or store
// of the lock, as the pthread_rwlock_* calls of this build leave no code, so the member is read from the size: fn 10864,
// api::CDefaultGenericFactory<api::IRWSyncCtl, api::CPosixRWMutex>'s slot 2, passes 36 and this constructor's table slot
// (244), the vptr and one 32-byte pthread_rwlock_t. Its name is chosen. The destructor is out of line: the D0 (fn 10244)
// calls the D2 and frees `this`, and the D2 (fn 5353) keeps its vptr store for the call that the link removes. Declared
// first, it is the key function, a choice.
class CPosixRWMutex : public IRWSyncCtl {
public:
    CPosixRWMutex();
    virtual ~CPosixRWMutex();

    virtual void ReadLock();
    virtual void WriteLock();
    virtual void Unlock();

private:
    pthread_rwlock_t m_rwlock;
};

} // namespace api
