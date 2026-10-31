# uenux2 api::CImageField ctor (target fn 2242) in src/uenux2/src/api/gui/cimagefield.cpp, the class header
# cimagefield.h and the IImage / SharedIImage / EAnchorPoint declarations it takes (iimage.h); paths relative to
# src/uenux2. No record names the ctor: it is the class's because it stores CImageField's vptr over the IFormFieldBase
# members, and the file is the class's (record cimagefield.cpp:52:12 of Rect). Its parameter types are taken from the
# records of the CImageFieldUpdate and CDSImageField ctors (const SPoint &, const SharedIImage &, EAnchorPoint); they
# and the parameter and member names are not in the bytes. No record names the header of IImage or EAnchorPoint, so
# iimage.h is chosen (see its header comment). Move (one of the five functions of target fn 2241, see
# 27-uenux2-ctextfield.mk, which lists the forms) is in cimagefield.cpp, below Rect's line 52, a choice; api::CDSImageField
# inherits it. Draw (target fn 11102, slot 2) is above Rect's line 52, in the band's order (uses 1, 11097-11102); no
# record falls in it, so its lines are a choice. Testing m_tamanho for null first is evidence: testing it != nullptr
# first swaps the two calls. Same object code, by the function's disassembly with the object-local numbers masked: the
# test of m_imagem as an outer `if` around the rest, `!m_imagem` and `!m_tamanho`, and a `return` after the first call in
# place of the `else`; so those spellings are choices.
# Rect (11101) is at its record's line. `!m_imagem` and `return SRect{};` give the same object code, so those are choices.
# GetTypeName (11097, a thunk of binaryen's 2904, which forms with CMovieField's 11059, CInputField<CFramedText>'s 12411 and
# RHVoice's 9690) is in the class: the band puts it after the destructors, as CTextFieldBlinking's. Draw is then the key
# function, and this object emits the vtable and the destructors (11099, 11098). SetImage (5533) has no record: by
# value, as Update's copy into a temporary shows (trivial-ABI, facts/reading.md R12); its name, its class and its file are
# chosen: its place in the uses-2 band, between cgrayedframedtext.cpp's fn 5534 and cimagefieldupdate.cpp's 5531, fits this file.
UENUX2_SRCS += src/api/gui/cimagefield.cpp
# two callers of the ctor (29-uenux2-cimagefield-roots.cpp, two make_shared<CImageField> as the target's callers do) so
# binaryen neither inlines it nor folds its anchor argument; the control block they instantiate,
# __shared_ptr_emplace<CImageField> (target fns 12639, 12640), matches from cformbuilder.cpp.o, which 5547 instantiates it in
$(ROOT)/$(APP)/29-uenux2-cimagefield-roots.o: $(ROOT)/src/units/29-uenux2-cimagefield-roots.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/29-uenux2-cimagefield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/29-uenux2-cimagefield-roots.o
