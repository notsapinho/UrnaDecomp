// Roots: the CTextFieldMultiLine ctor has two callers in the target (fns 2782 and 12055, both a
// std::make_shared<CTextFieldMultiLine> with the colours 2 and 1, which binaryen's dead-argument elimination folds
// into the ctor). Both are in the link: 2782 (api::CFormBuilder::AddTextFieldMultiLine, unit 31) and 12055, whose
// call is vota::AdicionaTextoMultiLinha's (ctelasvota.cpp, inlined into it by binaryen; unit 37), so the stand-in that
// stood for 12055 went. Address-taken from a static constructor. Compiled as uenux2 code.
#include <memory>
#include <string>

#include "api/gui/ctextfieldmultiline.h"
#include "api/gui/eueguierror.h"

namespace {

// two more CUeGuiError throw sites (the target has 36 callers of its ctor thunk, fn 406): with one, binaryen inlines
// the CBaseError<EUeGuiError> ctor into the ctextfieldmultiline.cpp throw
__attribute__((noinline)) void LancaGui1(int c, const std::string& m) { throw api::CUeGuiError(static_cast<api::EUeGuiError>(c), m); }
__attribute__((noinline)) void LancaGui2(int c, const std::string& m) { throw api::CUeGuiError(static_cast<api::EUeGuiError>(c), m + "2"); }

void* volatile w5498_sink;

struct SW5498Roots {
    SW5498Roots()
    {
        w5498_sink = reinterpret_cast<void*>(&LancaGui1);
        w5498_sink = reinterpret_cast<void*>(&LancaGui2);
    }
} w5498_roots;

} // namespace
