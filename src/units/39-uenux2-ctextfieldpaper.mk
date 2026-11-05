# uenux2 api::CTextFieldPaper ctor (target fn 2771) and Draw (10920) in src/uenux2/src/api/gui/ctextfieldpaper.cpp, the
# file the ctor's std::source_location record names (line 23 col 15, the CUeGuiError 4973 throw), with the class header
# (api/gui/ctextfieldpaper.h), api::IPaper with its nested EStyle and the slot Draw calls (api/gui/ipaper.h; the path is
# chosen, no record names it) and the 4973 enumerator of api/gui/eueguierror.h. Draw is the class's only virtual member
# defined out of line (its key function), so this object also emits the vtable with the implicit destructors (10919,
# 10918) and IFormField<IPaper>::GetTypeName (slot 7, 11014, inline in api/gui/iformfield.h). The D2 stores
# IFormFieldBase<IPaper>'s vptr, which brings that base's vtable and destructor (11013); binaryen merges it with the
# IScreen and IScreenMT ones into one body taking the vptr (1566), as the target's link did. 11014 is a thunk into 3891,
# the body binaryen shares between it and two other GetTypeName members (api::CTextFieldBlinking's 10940,
# api::CInputFieldControl<api::IScreen>'s 11155); binaryen merges the three 18-character bodies into one identical to
# 3891, but leaves two unmerged (measured with stand-in bodies in a try link), so the three match together.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CTEXTFIELDPAPER_SRCS := src/api/gui/ctextfieldpaper.cpp
UENUX2_SRCS += $(CTEXTFIELDPAPER_SRCS)
# No roots: the ctor's four target callers (193, 604, 5613 and 12105, ledger/callgraph.tsv) are in the link, 193 and
# 604 in cpaperformbuilder.cpp, 5613 from unit 139's roots and 12105 from fragment 372's (through
# CPaperFormBuilder::AddTextField over a formatted source); the stand-ins that stood for 12105 went with it.
