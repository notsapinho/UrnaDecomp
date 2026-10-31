# uenux2 api::IInputField<MEDIA>, api::CInputField<MASK>, api::CInputFieldControlBase<MEDIA>, api::CInputFieldControl<MEDIA>,
# api::CMaskedTextField<MASK>, api::CFramedText and the control blocks and timer lambda those templates bring, with
# api::IFormFieldBase<MEDIA>::Refresh and api::IInput::GetKey. Headers: api/gui/iinputfield.h, cinputfield.h,
# cinputfieldcontrol.h, cmaskedtextfield.h, cframedtext.h, cgrayedframedtext.h, api/util/itimerscheduler.h; each says what
# is evidence in it and what is chosen. The one source is api/gui/cframedtext.cpp. The target functions:
#   IFormFieldBase<IScreen>::Refresh 4118, IInputField's D2s 4021 and 5517 with binaryen's body 6061, Show 6327, Hide 6324,
#   Clear 6317, SetLength 6312; CInputFieldControl's D0s 6328 and 3672 and IScreen's Rect 11153; CMaskedTextField's
#   D2s 12604, 12719 and D0s 12595, 12713 with binaryen's bodies 6063 and 6062, GetTypeName 6507, Rect 6505, Move 6504;
#   CInputField<CFramedText>'s Rect 12405 and Move 12402; CFramedText's Rect 3677, Move 3676 and DrawFrame 2779.
#   From the roots' control blocks: __shared_ptr_emplace<T>'s D2 and D0 for CInputFieldControl<IScreen> (11072, 11071),
#   <IScreenMT> (11018, 11017), CMaskedTextField<CFramedText> (12618, 12613) and <CGrayedFramedText> (12735, 12727);
#   __shared_ptr_pointer's __get_deleter for CInputField<CFramedText> (12350), CMaskedTextField<CFramedText> (12340),
#   CControlValidation (11152) and CInputFieldControl<IScreenMT> (11019); and IInputField's constructor's lambda, the
#   __func members 12381, 12374, 12361, 12355 for IScreen and 11023, 11022, 11021, 11020 for IScreenMT, with
#   operator() 6306, one body for both.
#   11155 CInputFieldControl<IScreen>::GetTypeName and 12411 CInputField's: thunks of binaryen's 3891 and 2904, which form
#   with three and four functions of the shape, the others units 39's and 44's, and units 29's and 52's and RHVoice's 9690.
#   12387 CInputField<CFramedText>::SetLength, 148:13, in the class. Its width is size_t: the target halves it with an
#   unsigned shift, and a TPosition from Largura() differs in 21 lines. CFramedText::SetLength has no target function:
#   binaryen inlined it, and keeps the mask's address in a local, so it is out of line in cframedtext.cpp, and its name is
#   chosen. Espaco returns TPosition for the extend16 12387 holds.
# Written, and not matched:
#   6319, 11024 IInputField's Read: the bodies are the target's. Both load IInput::GetKey's record, which the target holds
#         four times (1538968, 1547328, 1580692, 1593104), and the scan calls such a record `ambiguous` and leaves the row
#         `unresolved`: no function that loads such a record has matched. In a copy of the ledger that keeps only the
#         function's own row of the record, splat-remap prints IDENTICAL for both. They wait for the toolkit
#         to take a record's address from among its copies; no source change can close this.
#   12438, 12593, 12708 the Draws: they call MaskText directly, which is a trap (the pending file says what it waits for).
#   the constructors, in the headers: only dropped functions reach them, so nothing has measured them.
# Not reconstructed: CInputMenuField's own members, among them 10893 (GetTypeName) and 5491: its vtable needs CMenuItem and
#   a list of them at +140. CInputFieldMT.
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
# - The roots compile with APP_CXXFLAGS. Under UENUX2_CXXFLAGS 9 of their 257 functions differ, all libc++ format
#   functions, and the link keeps none of the 9 from this object; the others compare equal, 12387, 11155 and 12411 among them.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
#
# The control-block roots are builders the link drops, with the block's vtable kept in the sink: the shape of unit 83's
# roots file. They reach no member that has no body in the link.
IINPUTFIELD_SRCS := src/api/gui/cframedtext.cpp
UENUX2_SRCS += $(IINPUTFIELD_SRCS)
# $(UENUX2_HDRS) is still empty when the fragments are read, so the companion rules name the directories they read.
IINPUTFIELD_HDRS := $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h $(ROOT)/src/uenux2/src/api/hwil/*.h $(ROOT)/src/uenux2/src/api/util/*.h $(ROOT)/src/ecourna/api/exception/*.hpp $(ROOT)/src/ecourna/api/uetypes.hpp)
$(ROOT)/$(APP)/92-uenux2-iinputfield-pending.o: $(ROOT)/src/units/92-uenux2-iinputfield-pending.cpp $(ROOT)/src/units/92-uenux2-iinputfield.mk $(ROOT)/src/Makefile $(IINPUTFIELD_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/92-uenux2-iinputfield-pending.cpp -o $(R)
$(ROOT)/$(APP)/92-uenux2-iinputfield-roots.o: $(ROOT)/src/units/92-uenux2-iinputfield-roots.cpp $(ROOT)/src/units/92-uenux2-iinputfield.mk $(ROOT)/src/Makefile $(IINPUTFIELD_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/92-uenux2-iinputfield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/92-uenux2-iinputfield-pending.o $(APP)/92-uenux2-iinputfield-roots.o
