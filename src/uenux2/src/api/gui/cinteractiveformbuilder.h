#pragma once

// api::CInteractiveFormBuilder (/home/rubio/tse/uenux2/src/api/gui/cinteractiveformbuilder.cpp: the records of
// AddLabeledInputControl, lines 76 and 86, fn 653, name the class and its file; this header's path is the class's name in
// lower case beside it, a choice). Nothing here is TSE's text. Recovered: what fns 554 and 653 need. Fn 554 passes its `this`
// as the vector of fields, and fn 653 passes its `this` to api::CFormBuilder::AddField (fn 426), so the builder's fields are
// api::CFormBuilder's at offset 0; that it derives from api::CFormBuilder is a choice, holding one at offset 0 gives the
// same bytes. GetInteractiveForm's name and its parameters' names are chosen.
//
// SharedInput is the record's name (653's return type, CInteractiveFormBuilder::SharedInput); that it is a
// std::shared_ptr<IInputField<IScreen>> is read from 653, which returns either a field of the form cast to
// IInputField<IScreen> (its __dynamic_cast's typeinfo, 1538832) or a new control field. AddInputControl (fns 901 and
// 5530) builds an api::CInputFieldControl<IScreen> with std::make_shared (the control block @1579276), adds it and
// returns it: 901 with the keys 4 of its default constructor, 5530 with its argument. Their names, the overloading,
// and their being members of this class rather than of CFormBuilder are chosen.
//
// AddInputMenuField (fn 3675) is defined in cinteractiveformbuilder.cpp, after AddInputControl: below.

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "api/gui/cformbuilder.h"
#include "api/gui/cinteractiveform.h"
#include "api/gui/iinputfield.h"
#include "api/gui/ipreshow.h"
#include "api/hwil/iinput.h"

namespace api {

class CInputMenuField;

class CInteractiveFormBuilder : public CFormBuilder {
public:
    using SharedInput = std::shared_ptr<IInputField<IScreen>>;

    // the keys' labels at the foot of the screen, a line above them and the form's control field: the record's signature
    // (cinteractiveformbuilder.cpp 86:15); the parameters' names are chosen
    SharedInput AddLabeledInputControl(const std::vector<std::pair<char, std::string>>& teclas, const SRect& area,
                                       bool semRotulos);

    SharedInput AddInputControl();

    SharedInput AddInputControl(int teclas);

    std::shared_ptr<CInteractiveForm<IScreen, IInputKbd>> GetInteractiveForm(const std::shared_ptr<IPreShow<IScreen>>& preShow,
                                                                         const std::string& nome, bool limpaTeclado);
};

// fn 3675 (target callers 11881, 11884 and 11888): builds a CInputMenuField with std::make_shared, gives it its
// instruction text and adds it to the builder (api::CFormBuilder::AddField, fn 426), and returns it. No record names it:
// its records are those of CInputMenuField's constructor and members binaryen inlines into it (cinputmenufield.cpp 251
// and 477, the constructor behind a second prologue). Its file is a reading of its use bands (how-to step 3, rule 5):
// in band 3 it lies between CFramedText::Move (3676, cframedtext.cpp's) and CMTFormBuilderBase::AddField (3674,
// cmtformbuilder.cpp's), while cinputmenufield.cpp's own band-3 members (3657, 3655) lie 17 indices on; in band 1 the
// control block only it builds (11070, 11069) comes right after the one AddInputControl builds (11072, 11071), at the end
// of the run this object's members first mention (11079 to 11071). Measured with pnpm wasm score in the
// plain link: in cinputmenufield.cpp, 162 over 528 rows (16 inserted, 18 deleted); here, 29 over 512, every row an
// operand. Its name, its being a free function of api rather than a member of this class (it reaches the builder
// through CFormBuilder::AddField alone), the parameter's type CFormBuilder& and the parameters' names are chosen.
std::shared_ptr<CInputMenuField> AddInputMenuField(CFormBuilder& builder, const SPoint& posicao, const SFont& font,
                                                   const std::string& instrucao, TPosition alturaMaxima);

} // namespace api
