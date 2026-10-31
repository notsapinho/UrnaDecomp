#pragma once

#include <memory>

#include "api/gui/iimage.h"
#include "api/pattern/iobservable.h"

namespace api {

// api::CPowerInformation's IconOrientation and the template over it, named by the records of cpowerinformation.cpp (:119
// the constructor, :131 UpdateBatteryIcon). RTTI: BatteryIconDataSource<(IconOrientation)0> is an si_class of
// IObservable<std::shared_ptr<IImage>>, and the records spell 0 Horizontal and 1 Vertical. Recovered: the head only.
// The target builds it with std::make_shared (fn 502). The constructor is not reconstructed, and that the enum is
// scoped is chosen.
class CPowerInformation {
public:
    enum class IconOrientation { Horizontal, Vertical };
};

template <CPowerInformation::IconOrientation Orientation>
class BatteryIconDataSource : public IObservable<std::shared_ptr<IImage>> {
public:
    BatteryIconDataSource();
};

} // namespace api
