#pragma once

#include "api/gui/ipreshow.h"

namespace api {
class IScreen;
}

namespace vota {

// RTTI: CPreShowFormVota is an si_class of api::IPreShow<api::IScreen>, vtable @1532600 [174, 144, 7707], and
// CPreShowProgressBar an si_class of it, vtable [174, 144, 13550]. Recovered: the heads only. Slot 2 is fn 7707 and fn
// 13550, not reconstructed. Neither class is final: their blocks' __on_zero_shared go through the vtable (fns 172 and
// 411). The path is chosen, under app/vota/comum: no record names either class, and the file holds both because the
// second derives from the first.
class CPreShowFormVota : public api::IPreShow<api::IScreen> {
public:
    void PreShow(api::IScreen& tela) override;
};

class CPreShowProgressBar : public CPreShowFormVota {
public:
    CPreShowProgressBar();

    void PreShow(api::IScreen& tela) override;
};

} // namespace vota
