#pragma once

// api::CInteractiveFormBuilder (/home/rubio/tse/uenux2/src/api/gui/cinteractiveformbuilder.cpp: the records of
// AddLabeledInputControl, lines 76 and 86, fn 653, name the class and its file; this header's path is the class's name in
// lower case beside it, a choice). Nothing here is TSE's text. Recovered: what fn 554 needs. It passes its `this` as
// the vector of fields, and fn 653 passes its `this` to api::CFormBuilder::AddField (fn 426), so the builder's fields are
// api::CFormBuilder's at offset 0; that it derives from api::CFormBuilder is a choice, holding one at offset 0 gives the
// same bytes. GetInteractiveForm's name and its parameters' names are chosen.

#include <memory>
#include <string>

#include "api/gui/cformbuilder.h"
#include "api/gui/cinteractiveform.h"
#include "api/gui/ipreshow.h"
#include "api/hwil/iinput.h"

namespace api {

class CInteractiveFormBuilder : public CFormBuilder {
public:
    std::shared_ptr<CInteractiveForm<IScreen, IInputKbd>> GetInteractiveForm(const std::shared_ptr<IPreShow<IScreen>>& preShow,
                                                                         const std::string& nome, bool limpaTeclado);
};

} // namespace api
