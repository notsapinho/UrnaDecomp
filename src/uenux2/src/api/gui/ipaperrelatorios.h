#pragma once

// api::IPaperRelatorios: RTTI gives an si_class of api::IPaper (typeinfo 1531152), the interface of the paper the
// reports print on: api::IFormImpressao<api::IPaperRelatorios> renders on it (record cpaperformbuilder.h:51:54). No
// record names this file, so its path is chosen, beside ipaper.h. It declares nothing: every slot of its one implementer
// is read as IPaper's (ipaper.h says which could be this class's).

#include "api/gui/ipaper.h"

namespace api {

class IPaperRelatorios : public IPaper {
};

} // namespace api
