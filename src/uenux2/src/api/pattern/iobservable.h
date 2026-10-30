#pragma once

// api::IObservable<T>, a value of type T that tells its observers (api::IObserver<T>, api/pattern/iobserver.h) when
// it changes. No record names its file: the path is chosen, beside iobserver.h, and the names of the members below
// are chosen too (no record names any of them).
//
// RTTI gives four instantiations as classes with no base: T = std::shared_ptr<api::IImage> (typeinfo 1551936, the base
// of api::BatteryIconDataSource<Horizontal|Vertical>) and std::vector<api::FormHandle<MEDIA>> for IScreen, IScreenMT
// and IPaper. Each vtable has two slots, the destructors (11651 and 11650 for SharedIImage), so the destructor is
// virtual and no other member is. The layout is read from those destructors, which destroy, in this order, a
// std::mutex at +24, a std::vector at +12 and a std::shared_ptr at +4:
//   +4  T, the value: an observer's Update receives it (the attach inlined into fn 502 passes this + 4)
//   +12 std::vector<IObserver<T>*>, the observers: the detach that the destructors of api::CDSImageField (fn 2778) and
//       comum::CInfoMTLCD (fn 5902) inline searches it with std::find (wmemchr, fn 736) and erases what
//       std::remove leaves
//   +24 std::mutex, held while the vector changes: its unlock is the call of fn 150 (std::mutex's unlock and
//       destructor are one body in the target); the lock is inlined away
// Detach is the one member written here, from those two destructors. Attaching (find, push_back through fn 543, then
// the observer's Update with the value, under the mutex; inlined into fn 502) and notifying are not recovered.

#include <algorithm>
#include <mutex>
#include <vector>

#include "api/pattern/iobserver.h"

namespace api {

template <typename T>
class IObservable {
public:
    virtual ~IObservable() = default;

    void Detach(IObserver<T>* observer)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
    }

protected:
    T m_valor;
    std::vector<IObserver<T>*> m_observers;
    std::mutex m_mutex;
};

} // namespace api
