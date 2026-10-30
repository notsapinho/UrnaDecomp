// Pending members: the api::CImageField members src/uenux2/src/api/gui/cimagefield.cpp does not hold yet. The class's
// vtable needs them defined; their bodies are NOT the target's, they trap. GetTypeName is the class's key function, so
// the vtable and the implicit destructors (target fns 11099 and 11098, which match from here) are emitted in this
// object until GetTypeName moves into cimagefield.cpp. Target functions:
// - GetTypeName 11097 returns "CImageField", through fn 2904, the body binaryen's merge-similar-functions made of four
//   functions returning an 11-character name (with CMovieField 11059, CInputField<CFramedText> 12411 and RHVoice's
//   userdict::empty_string::describe 9690). Written as `return "CImageField";` our link keeps it a body of its own,
//   not merged with describe (the only other such function our link has), so 11097 differs at its first operand;
// - Draw 11102 calls IScreen's vtable slots 22 and 24 (the image-drawing members), which api/gui/iscreen.h does not
//   declare;
// - Rect 11101 (record cimagefield.cpp:52:12) calls CPolySingleton<IScreen>'s instance, fn 512, not named yet;
// - Move 2241 is binaryen's one body for CTextField, CImageField, CDSImageField, CImageFieldUpdate, CTextFieldBlinking
//   and CTextFieldUpdate; it reads the IForm<IScreen> the field belongs to, which api/gui/iform.h does not declare.
// Move each into cimagefield.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/cimagefield.h"

namespace api {

std::string CImageField::GetTypeName() const
{
    __builtin_trap();
}

void CImageField::Draw(IScreen&) const
{
    __builtin_trap();
}

SRect CImageField::Rect() const
{
    __builtin_trap();
}

void CImageField::Move(const SPoint&)
{
    __builtin_trap();
}

} // namespace api
