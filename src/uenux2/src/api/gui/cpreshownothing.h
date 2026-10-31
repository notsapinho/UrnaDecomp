#pragma once

#include "api/gui/ipreshow.h"

namespace api {

// RTTI: api::CPreShowNothing<IScreen> and <IPaper>, si_class of IPreShow<MEDIA>; vtables [174, 144, 425], slot 2 the
// shared empty body. fns 11891 and 5515 build them as std::shared_ptr<IPreShow<MEDIA>>(new CPreShowNothing<MEDIA>).
// The path is chosen, beside ipreshow.h: no record names it.
template <typename MEDIA>
class CPreShowNothing : public IPreShow<MEDIA> {
public:
    void PreShow(MEDIA&) override {}
};

} // namespace api
