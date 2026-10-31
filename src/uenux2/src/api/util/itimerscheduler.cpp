// Reconstruction's note, not TSE's text. GetInst's record is line 23, column 12. api::CTimerScheduler is here by data
// order, as api::CSystemDateTime is in isystemdatetime.cpp: its vtable (@1585396) and typeinfo (@1585416) lie right before
// this file's record at 1585468, and only fn 5444 stores its vptr. The class's header is a choice.

#include "api/util/ctimerscheduler.h"
#include "api/util/itimerscheduler.h"

namespace api {

// (original lines 10-17: content not recovered)
#line 18
ITimerScheduler& ITimerScheduler::GetInst()
{
    if (!CPolySingletonList::has<ITimerScheduler>()) {
        CreateInst<CTimerScheduler>();
    }
    return CPolySingleton<ITimerScheduler>::instance();
}

} // namespace api
