#pragma once

// api::CPreShowClearMT: the class is named by RTTI (an si_class of api::IPreShow<api::IScreenMT>, ledger/classes.json).
// The header's path is chosen. No data members: the destructors are the shared empty fns 174 and 144.

#include "api/gui/ipreshow.h"

namespace api {

class IScreenMT;

class CPreShowClearMT : public IPreShow<IScreenMT> {
public:
    void PreShow(IScreenMT& screen) override;
};

} // namespace api
