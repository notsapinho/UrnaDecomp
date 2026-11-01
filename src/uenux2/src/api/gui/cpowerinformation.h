#pragma once

#include <memory>

#include "api/gui/iimage.h"
#include "api/pattern/iobservable.h"
#include "api/util/itimer.h"

namespace api {

// api::CPowerInformation's IconOrientation and the template over it, named by the records of cpowerinformation.cpp
// (:119 the constructor, :131 UpdateBatteryIcon). RTTI: BatteryIconDataSource<(IconOrientation)0> is an si_class of
// IObservable<std::shared_ptr<IImage>>, and the records spell 0 Horizontal and 1 Vertical, each as
// IconOrientation::Horizontal: the pinned clang prints an unscoped enumerator without its enum's name, so the enum is
// scoped. The target builds <Horizontal> with std::make_shared (fn 502) and holds <Vertical> at +4 of
// comum::CInfoMTLCD (fn 5904).
//
// The layout past the base is what the bodies give. The destructor's body (fn 6049, binaryen's merge of the two
// instantiations' D2s, 3837 and 5510, which pass it their vptr) releases a std::shared_ptr at +48 before IObservable's
// members. The constructor, inlined into fns 502 and 5904, builds that std::shared_ptr from slot 0 of
// ITimerScheduler::GetInst() with an interval of 1000 and a std::function over a lambda of the constructor (RTTI
// __func<BatteryIconDataSource<...>::BatteryIconDataSource()::{lambda()#1}, void ()>), and calls the timer's slot 2: an
// ITimer. It stores at +56 the 32-bit value fn 2774 returns, which the lambda (fns 10981 and 10987, UpdateBatteryIcon
// inlined) compares with a new one and uses as a signed key. The members' names and the int's type are chosen.
//
// The destructor is declared in the class without `inline`. Evidence that its D2 is not inlined into its callers: the
// D0s (10990, 11652) free what the D2 returns, and comum::CInfoMTLCD's destructor (fn 5902) calls the member's D2
// (3837). Measured (src/units/164-uenux2-cpowerinformation.mk): `{}`, `= default`, a definition after the class in
// this header and `virtual ~BatteryIconDataSource() {}` give the same object; the implicit destructor and one declared
// `inline` give a D0 holding the D2's body. `{}` is written, one of four. The constructor and UpdateBatteryIcon are
// declared only, and cpowerinformation.cpp stays a stub file: both call fn 2773, which fills a std::map of the icons
// through fn 1263, whose std::make_shared<CFixedImage> calls CFixedImage's string constructor, fn 2246 (unit 158).
class CPowerInformation {
public:
    enum class IconOrientation { Horizontal, Vertical };
};

template <CPowerInformation::IconOrientation Orientation>
class BatteryIconDataSource : public IObservable<std::shared_ptr<IImage>> {
public:
    BatteryIconDataSource();
    ~BatteryIconDataSource() override {}

private:
    void UpdateBatteryIcon();

    std::shared_ptr<ITimer> m_timer;
    int m_estado;
};

} // namespace api
