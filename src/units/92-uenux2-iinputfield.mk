# uenux2 api::IInputField<MEDIA>, api::CInputField<MASK>, api::CInputFieldControlBase<MEDIA>, api::CInputFieldControl<MEDIA>,
# api::CMaskedTextField<MASK>, api::CFramedText and the control blocks and timer lambda those templates bring, with
# api::IFormFieldBase<MEDIA>::Refresh and api::IInput::GetKey. Headers: api/gui/iinputfield.h, cinputfield.h,
# cinputfieldcontrol.h, cmaskedtextfield.h, cframedtext.h, cgrayedframedtext.h, api/util/itimerscheduler.h; each says what
# is evidence in it and what is chosen. The one source is api/gui/cframedtext.cpp. The target functions:
#   IFormFieldBase<IScreen>::Refresh 4118, IInputField's D2s 4021 and 5517 with binaryen's body 6061, Show 6327, Hide 6324,
#   Clear 6317, SetLength 6312; CInputFieldControl's D0s 6328 and 3672 and IScreen's Rect 11153; CMaskedTextField's
#   D2s 12604, 12719 and D0s 12595, 12713 with binaryen's bodies 6063 and 6062, GetTypeName 6507, Rect 6505, Move 6504;
#   CInputField<CFramedText>'s Rect 12405 and Move 12402, and the three Draws that call a mask's MaskText directly
#   (CInputField<CFramedText>'s 12438, CMaskedTextField<CFramedText>'s 12593 and <CGrayedFramedText>'s 12708);
#   CFramedText's MaskText 2780 (record cframedtext.cpp 66:15, the key function, so this object emits the vtable, with the
#   4917 enumerator of EUeGuiError), FillCell 5536, DrawChar 5537, Rect 3677, Move 3676 and DrawFrame 2779, and its
#   constructor 1385, whose record (cframedtext.cpp 28:24) is the default argument of CPolySingleton<IScreen>::instance():
#   the local `IScreen& monitor` gives that column, and its name, the constructor's other lines and the vertical gap
#   written in place (Espaco's form over size / 10) are chosen. The roots give 1385 two callers for its eight in the target.
#   From the roots' control blocks: __shared_ptr_emplace<T>'s D2 and D0 for CInputFieldControl<IScreen> (11072, 11071),
#   <IScreenMT> (11018, 11017), CMaskedTextField<CFramedText> (12618, 12613) and <CGrayedFramedText> (12735, 12727);
#   __shared_ptr_pointer's __get_deleter for CInputField<CFramedText> (12350), CMaskedTextField<CFramedText> (12340),
#   CControlValidation (11152) and CInputFieldControl<IScreenMT> (11019); and IInputField's constructor's lambda, the
#   __func members 12381, 12374, 12361, 12355 for IScreen and 11023, 11022, 11021, 11020 for IScreenMT, with operator()
#   6306, one body for both. Of these, 11071, 11072 and 11152 come from api/gui/cinteractiveformbuilder.cpp's object
#   (unit 120); 12350, the IScreen __func members and 6306 from app/vota/eleitor/comum/ctelasvota.cpp's (unit 110), the
#   first on the link line to instantiate them: its vota::AdicionaCampoNumerico (fn 2383) builds that block and calls
#   IInputField<IScreen>'s constructor, whose copy there stores the __func vtable; and 11019 and 11020 to 11023 from
#   api/gui/cmtformbuilder.cpp's, whose AddInputControl (fn 395) builds that block and whose copy of
#   IInputField<IScreenMT>'s constructor (fn 3673) stores the __func vtable (src/units/31-uenux2-cformbuilder.mk).
#   The two CMaskedTextField blocks' members (12618, 12613, 12735, 12727) and CMaskedTextField's D2s, D0s, Draws,
#   GetTypeName, Rect and Move (12604, 12719, 12595, 12713, 12593, 12708, 6507, 6505, 6504) come from ctelasvota.cpp's
#   object now, whose vota::AdicionaCampoNumero<MASK> (fns 6624's inlined copy and 3060, unit 378) builds both blocks;
#   step 9 renamed the twins' lines to the <CGrayedFramedText> members, the first copies in link order.
#   The roots' builders and sinks that stood for 395 and 3673 went when those two landed, though 5410 stores
#   CInputFieldControl<IScreenMT>'s vptr too: the scan with them and the scan without them each move the same three
#   rows, 395, 3673 and 3674, from the commit before (docs/how-to-decompile.md step 9's join), so no row rests on them.
#   11155 CInputFieldControl<IScreen>::GetTypeName and 12411 CInputField's: thunks of binaryen's 3891 and 2904, which form
#   with three and four functions of the shape, the others units 39's and 44's, and units 29's and 52's and RHVoice's 9690.
#   12387 CInputField<CFramedText>::SetLength, 148:13, in the class. Its width is size_t: the target halves it with an
#   unsigned shift, and a TPosition from Largura() differs in 21 lines. CFramedText::SetLength has no target function:
#   binaryen inlined it, and keeps the mask's address in a local, so it is out of line in cframedtext.cpp, and its name is
#   chosen. Espaco returns TPosition for the extend16 12387 holds.
#   6319, 11024 IInputField's Read: both load IInput::GetKey's record, which the target holds four times (1538968,
#         1547328, 1580692, 1593104), and both match: the scan offers each copy of such a record and the target body
#         picks one (docs/reference/facts/splat.md S12).
#   5537  CFramedText::DrawChar, its name chosen, with Top and Bottom, unit 108's, inlined into it. What the bytes fix,
#         each measured in the link before steps 7 to 9 (pnpm wasm score against our fn):
#         - The text's colour is a parameter, which both callers (2780, 5534) pass as 2: binaryen's dead-argument
#           elimination folds it into the body, and our DrawChar's wasm type is the target's (i32 i32 i32 i32)->().
#           With the 2 written in the body the target stores the CFixedText's alignment (2 at its +4) after its vptr and
#           ours before the string's first bytes: 25 over 270 rows, 3 inserted and 3 deleted, the rest operand-only.
#           With the parameter: 19 over 267, all operand-only, and it matches. In the object (a compile with the
#           unit's flags), the background colour alone as a parameter leaves that store where the body constant has it;
#           a reading of why, from the object's -print-after=finalize-isel dump: there one constant 2 serves the store,
#           the half width's division and DrawText's colour. Both colours as parameters give the same plain link as the
#           one (sha256 1db885ded05acf8a33e4880351db1153c861ac4262859c3bcd57d7fa1d2d4e11 both); one colour, as
#           DrawFrame and FillCell take, is the choice, and so are its name and its place before the screen.
#         - The cell's centre is two TPosition locals, x then y, passed as SPoint{x, y}: the target loads the right edge
#           before the left, which the int half width in a local does not (31 over 273 rows with it, the colour in the
#           body; 25 over 270 with x and y). In the object, the left edge read into a local first, `const int metade =
#           (rect.right - esquerda) / 2`, and y before x give the same DrawChar; the brace (`left + (right - left) / 2`)
#           and x and y assigned in turn to an SPoint store y before the loads, and a local for each edge (right first),
#           `metade + rect.left` and the half width as a TPosition load the left edge first. std::string{caractere},
#           std::string(&caractere, 1), a named string, -O2, -Os, -O1 and -fno-strict-aliasing leave the alignment's
#           store where the body constant has it.
# MaskText (2780) and the cell members, measured: MaskText reads the character once, into a local; read at each use it is
#   loaded twice, as load8_u for the test and load8_s for DrawChar (15 over 392 rows, 3 not operand-only). The space test
#   is `== ' '`: the target lays the space branch first, as that gives (2780 matches), and `!= ' '` lays the other branch
#   first in the object.
#   That test mentions FillCell before DrawChar, and the target's uses-2 band has 5537 before 5536 (a higher index, a
#   lower ld_index), so DrawChar is defined above MaskText and FillCell after it: their lines, and the padding with
#   append rather than resize (not measured), are choices.
# CGrayedFramedText's constructor (5535) is written (unit 173's file, src/units/378-uenux2-ctelasvota-criatela.mk): the
#   SFont {40, 0} at 474880 it passes CFramedText's constructor lies in the data of an app/vota object (after its
#   typeinfo name N4vota19CPreShowProgressBarE, with {30, 0} and {20, 0} beside it), not in cgrayedframedtext.cpp's (its
#   typeinfo name is at 523132), so it is a parameter its callers in ctelasvota.cpp pass, folded by binaryen. Measured
#   before that: `SFont{40, 0}` written in the call compiles to a stack temporary, and a namespace-scope or
#   function-local constant of this file lands in its own data. The roots' CMaskedTextField<CGrayedFramedText> block
#   builder, destructor emitter and sinks went: 3060 builds the block and stores both vtables.
#   the constructors of the other classes, in the headers: only dropped functions or stand-ins reach them, so nothing has
#   measured them. IInputField<IScreen>'s (2024) matches from unit 110's ctelasvota.cpp object, the first to emit it
#   (its fn 2383 calls it), and CInputFieldControlBase<IScreen>'s (5565) from unit 120's, whose AddInputControl (901,
#   5530) calls them both.
# CInputMenuField's own members, among them 10893 (GetTypeName) and 5491, are unit 84's, with CMenuItem and the list of
#   them at +140. CInputFieldMT is unit 146's.
# Evidence for the forms is in the headers; what follows is what the bytes do not decide, measured by compiling each variant
# and comparing the functions with the object-local numbers masked (docs/how-to-decompile.md step 3).
# - m_alterado as a std::atomic<bool>, the best reading: api/gui/iformfield.h. Measured: a plain bool gives `i32.eq 1` where 4118 has
#   `i32.and 1`, and so do std::exchange and an atomic read and store; a bit-field stores `and 254`. exchange with
#   memory_order_relaxed, _acquire or _acq_rel and std::atomic_exchange give one function.
# - IInput::GetKey with `inline`: measured, without it Read differs. Everything else in that line is a choice.
# - Invalidate as a member against its statements in place: the same functions.
# - IInputField's destructor in the class with or without `inline`, and with an early return: the same functions.
# - Show, Clear, SetLength, Read, Rect and the rest: the headers list forms that give the same functions, and ones that do not;
#   DrawFrame with a local SRect gives the same too. move-by-members of CFramedText::Move does not: 3676 copies the SPoint whole.
# - CFramedText's three members are in cframedtext.cpp by choice. No record places them. They were out of line in the
#   target, with three callers each in other TUs (the templates' users and cinputmenufield.cpp), so they are not in a
#   header, and the class's file is the plain one. 3676's and 3677's stubs lay in stretch 989, labelled
#   cinputmenufield.cpp, in band 3 next to fn 3675, which the record of another function gives: it can be a neighbour's
#   label (docs/how-to-decompile.md step 3). Their lines are chosen too.
# - The two masks in their own headers beside the recorded .cpp, and cmaskedtextfield.h, are chosen paths.
# - The roots compile with APP_CXXFLAGS. Against the same file compiled with UENUX2_CXXFLAGS, by function with call and global indices and relocated constants masked: 212 of the 244 functions the two compiles
#   both define compare equal, and the 32 that differ, all libc++'s std::format code and std::string's operator+, are
#   the same 32 as at bbf27ac1's roots (224 of 256 equal); the link keeps none of the 32 from this object.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
#
# The control-block roots are builders the link drops, with the block's vtable kept in the sink: the shape of unit 83's
# roots file. They reach no member that has no body in the link.
IINPUTFIELD_SRCS := src/api/gui/cframedtext.cpp
UENUX2_SRCS += $(IINPUTFIELD_SRCS)
# $(UENUX2_HDRS) is still empty when the fragments are read, so the companion rules name the directories they read.
IINPUTFIELD_HDRS := $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h $(ROOT)/src/uenux2/src/api/hwil/*.h $(ROOT)/src/uenux2/src/api/util/*.h $(ROOT)/src/ecourna/api/exception/*.hpp $(ROOT)/src/ecourna/api/uetypes.hpp)
$(ROOT)/$(APP)/92-uenux2-iinputfield-roots.o: $(ROOT)/src/units/92-uenux2-iinputfield-roots.cpp $(ROOT)/src/units/92-uenux2-iinputfield.mk $(ROOT)/src/Makefile $(IINPUTFIELD_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/92-uenux2-iinputfield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/92-uenux2-iinputfield-roots.o
