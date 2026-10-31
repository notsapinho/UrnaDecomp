#pragma once

#include "api/gui/ipreshow.h"

namespace api {

class IScreen;

// RTTI: an si_class of IPreShow<IScreen>, vtable [174, 144, 11139]. Recovered: the head only; slot 2 (fn 11139), a call
// of one IScreen slot with 1, is not reconstructed. fn 11140 builds it as a std::shared_ptr<IPreShow<IScreen>>. The path
// is chosen, beside ipreshow.h and cpreshowclearmt.h.
class CPreShowClearScreen : public IPreShow<IScreen> {
public:
    void PreShow(IScreen& tela) override;
};

} // namespace api
