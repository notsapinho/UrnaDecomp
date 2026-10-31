#pragma once

#include "api/gui/iform.h"

namespace api {

class IPaper;

// RTTI: api::IFormImpressao<IPaperRelatorios>, an si_class of IForm<IPaper>. Recovered: the head only, which is all the
// block of std::shared_ptr<IForm<IPaper>>(new IFormImpressao<IPaperRelatorios>) needs (fn 5515). The template
// parameter's name and the path are chosen, beside iform.h.
template <typename PAPER>
class IFormImpressao : public IForm<IPaper> {};

} // namespace api
