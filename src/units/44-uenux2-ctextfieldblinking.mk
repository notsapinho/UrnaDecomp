# uenux2 api::CTextFieldBlinking's implicit destructors (target fns 10942 and 10941, vtable slots 0 and 1), the
# compiler's code for the class definition in src/uenux2/src/api/gui/ctextfieldblinking.h: they store the class's vptr,
# release the std::shared_ptr<api::ITimer> at +56 and the SharedIText at +28, then run IFormFieldBase<IScreen>'s part
# (its vptr, m_nome at +12). The destructor is implicit: the deleting one holds the base-object body inlined, where an
# out-of-line destructor's would call it. The header goes beside ctextfieldblinking.cpp, the file whose records name
# the constructor (lines 39 and 42, column 15) and Rect (70:21); no record names a header. api::ITimer is only
# forward-declared (the destructors need no complete type; api/util/itimer.h defines it).
# ctextfieldblinking.cpp holds Show and Hide (target fns 10945, 10944, slots 3 and 4: Start and Stop of the timer, whose
# class it includes, api/util/itimer.h) at lines that are a choice, above Rect's line 70 in the band's order, and Move (one
# of the five functions of target fn 2241, see 27-uenux2-ctextfield.mk, which lists the forms) below it, a choice. Draw
# (target fn 10946, slot 2), the class's key function, is above Show, in the band's order, at lines that are a choice, so
# that object emits the vtable and the implicit destructors. The one call with a choice of colour is evidence: an if/else
# with two calls gives another body. Same object code, by the function's disassembly with the object-local numbers
# masked: the colour in a local TColor, and `!m_aceso ? m_corPisca : m_corTexto`; so those spellings are choices. The
# constructor has no target function of its own (binaryen inlined it into its one caller, fn 1265) and is not
# reconstructed, so lines 39 and 42 stay free for its throws. Paths relative to src/uenux2.
# Rect (10943) is a thunk of fn 3889: 27-uenux2-ctextfield.mk has it. GetTypeName (10940) is in the class, last in the
# band, and a thunk of fn 3891, which forms with IFormField<IPaper>'s 11014 and CInputFieldControl<IScreen>'s 11155: three
# 18-character names, each written as a plain return. Every header the class includes is in src/uenux2/src/api/gui/, which
# the wildcard below names ($(UENUX2_HDRS) is set after src/Makefile reads the fragments: here it would be empty).
CTEXTFIELDBLINKING_SRCS := src/api/gui/ctextfieldblinking.cpp
UENUX2_SRCS += $(CTEXTFIELDBLINKING_SRCS)
# nothing calls the destructors directly in the target, which reaches them through the vtable only:
# 44-uenux2-ctextfieldblinking-roots.cpp keeps the vtable, as the constructor inlined into fn 1265 does
$(ROOT)/$(APP)/44-uenux2-ctextfieldblinking-roots.o: $(ROOT)/src/units/44-uenux2-ctextfieldblinking-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/44-uenux2-ctextfieldblinking.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/44-uenux2-ctextfieldblinking-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/44-uenux2-ctextfieldblinking-roots.o
