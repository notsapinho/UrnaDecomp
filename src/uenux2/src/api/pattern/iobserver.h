#pragma once

// api::IObserver<T>, the observer of an api::IObservable<T> (api/pattern/iobservable.h). No record names its file:
// the path is chosen, beside the other api pattern templates of this directory, and so is the class's layout below.
//
// RTTI gives api::IObserver<std::shared_ptr<api::IImage>> (typeinfo 1551900) as a class with no base, the base of
// comum::CInfoMTLCD (at +0) and of api::CDSImageField (at +44). Its slots are read from the vtables of those classes
// (ledger/vtables.json): slots 0 and 1 are the destructors, so it is virtual, and slot 2 is Update, named and typed by
// the record of comum::CInfoMTLCD's override (`virtual void comum::CInfoMTLCD::Update(const api::SharedIImage &)`).
// The class holds no data, only its vptr: CDSImageField's own member follows it at +48. Its destructor's body is empty:
// CDSImageField's destructor (target fn 2778) stores no IObserver vptr at +44 once its own members are gone, a store
// clang leaves out only for a base destructor with an empty body and no member to destroy. ledger/vtables.json has no
// vtable of IObserver's own: its constructor is inlined into the derived ones, which store their vptr over it.

namespace api {

template <typename T>
class IObserver {
public:
    virtual ~IObserver() = default;

    virtual void Update(const T& valor) = 0;
};

} // namespace api
