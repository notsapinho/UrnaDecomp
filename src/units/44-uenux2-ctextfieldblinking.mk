# uenux2 api::CTextFieldBlinking's implicit destructors (target fns 10942 and 10941, vtable slots 0 and 1), the
# compiler's code for the class definition in src/uenux2/src/api/gui/ctextfieldblinking.h: they store the class's vptr,
# release the std::shared_ptr<api::ITimer> at +56 and the SharedIText at +28, then run IFormFieldBase<IScreen>'s part
# (its vptr, m_nome at +12). The destructor is implicit: the deleting one holds the base-object body inlined, where an
# out-of-line destructor's would call it. The header goes beside ctextfieldblinking.cpp, the file whose records name
# the constructor (lines 39 and 42, column 15) and Rect (70:21); no record names a header. api::ITimer is only
# forward-declared (the destructors need no complete type, and api/util/itimer.h is not in this tree yet).
# The unit has no source of its own yet: every virtual member is pending, so the vtable, its key function Draw and with
# it the implicit destructors are emitted in the pending object (as units 26 and 30 emit theirs); they move to
# ctextfieldblinking.o when Draw does. The constructor has no target function of its own (binaryen inlined it into its
# one caller, fn 1265) and is not reconstructed, so lines 39 and 42 stay free for its throws. ctextfieldblinking.cpp
# held only stubs, and none is left (the destructors match, and the pending members' stubs go with the vtable), so
# make -C src stubs removed the file; it comes back with the first member written there. Paths relative to src/uenux2.
# Draw, Show, Hide, GetTypeName, Rect and Move (target fns 10946, 10945, 10944, 10940, 10943, 2241) are not
# reconstructed: 44-uenux2-ctextfieldblinking-pending.cpp defines them with trapping bodies, compiled with the unit's
# flags, and its header names what each waits for. Every header the class includes is in src/uenux2/src/api/gui/, which
# the wildcard below names ($(UENUX2_HDRS) is set after src/Makefile reads the fragments: here it would be empty).
$(ROOT)/$(APP)/44-uenux2-ctextfieldblinking-pending.o: $(ROOT)/src/units/44-uenux2-ctextfieldblinking-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/44-uenux2-ctextfieldblinking.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/44-uenux2-ctextfieldblinking-pending.cpp -o $(R)
# nothing calls the destructors directly in the target, which reaches them through the vtable only:
# 44-uenux2-ctextfieldblinking-roots.cpp keeps the vtable, as the constructor inlined into fn 1265 does
$(ROOT)/$(APP)/44-uenux2-ctextfieldblinking-roots.o: $(ROOT)/src/units/44-uenux2-ctextfieldblinking-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/44-uenux2-ctextfieldblinking.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/44-uenux2-ctextfieldblinking-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/44-uenux2-ctextfieldblinking-pending.o $(APP)/44-uenux2-ctextfieldblinking-roots.o
