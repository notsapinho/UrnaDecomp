// Pending members: the api::CMovieField members src/uenux2/src/api/gui/cmoviefield.cpp does not hold yet. The class's
// vtable (emitted with the destructor, its key function, in that TU) needs them defined; their bodies are NOT the
// target's, they trap. Target functions:
//   Rect 11063         record cmoviefield.cpp:53:12; calls CPolySingleton<IScreen>'s instance, fn 512, not named yet
//   GetTypeName 11059  a thunk into binaryen's merge 2904 (f2904(p0, p1, "CMovieField", ...)), whose other callers
//                      are api::CImageField's (11097) and api::CInputField<api::CFramedText>'s (12411) GetTypeName and
//                      RHVoice's userdict empty_string::describe (9690): it matches only once our link merges the same
//                      set. Its source is
//                          std::string CMovieField::GetTypeName() const { return "CMovieField"; }
// cmoviefield.cpp was a stub-only file; its one record is Rect's, at line 53, column 12.
// Move each into cmoviefield.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/cmoviefield.h"

namespace api {

SRect CMovieField::Rect() const
{
    __builtin_trap();
}

std::string CMovieField::GetTypeName() const
{
    __builtin_trap();
}

} // namespace api
