# uenux2 api::CTextFieldUpdate::~CTextFieldUpdate: the base-object destructor (target fn 5495, slot 0 of the vtable
# @1582988) and the deleting one (fn 10917, slot 1), with GetTypeName (fn 10912, slot 7), in
# src/uenux2/src/api/gui/ctextfieldupdate.cpp, the file the class's records name (ctextfieldupdate.cpp:38:15, the
# constructor; :73:21, Rect). The destructor is user-declared and defined out of line (the D0 calls the D2: an implicit
# or in-class destructor would have its body inlined into the D0), declared first among the class's virtual members, so
# it is the key function and ctextfieldupdate.o emits the vtable, the D2 and the D0. No record falls in the destructor or
# GetTypeName: their lines are a choice, in the target's order (the uses-1 band 10912-10917 of ledger/ordinals.tsv
# gives D0, Draw, Show, Hide, Rect, GetTypeName). The class header (api/gui/ctextfieldupdate.h) has the layout the
# constructor (fn 3658) and Draw (fn 10916) store; the member names are chosen and the timer at +72 is a
# std::shared_ptr to a forward-declared api::ITimer.
# The constructor (target fn 3658), its throw on its record's line 38 with the 4974 enumerator of EUeGuiError, makes
# the timer with ITimerScheduler::GetInst (fn 1259, unit 101) and a lambda. Its wasm type has no parameter for the
# colours: it stores 2 and 1, which all three callers pass and binaryen folds. Measured in the link: it stores two bytes
# of m_textoDesenhado, which `m_textoDesenhado("")` gives, where the string's default constructor zeroes all twelve. The lambda's __func members 10907 (target_type) and 10908 (target) match, and
# operator() (10909) with the lambda calling Atualiza, a member defined out of line: the target's operator() loads the
# capture before a frame prologue, binaryen's inlining of a callee clang left out of line, and the test written in the
# lambda gives a body whose prologue comes first. Atualiza, its name and its being a member are chosen. The two __clone
# members (10910, 10911) match since src/api/ builds with strict aliasing (src/Makefile UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6): the target
# stores the capture before the vptr, which this object gives at -O3 without -fno-strict-aliasing and not with it, nor at
# -O2, -Os or -Oz with it (each compiled, the store order of both __clone members read in the object).
# Show and Hide (fns 10915, 10914, slots 3 and 4) are Start and Stop of the timer, whose class the source includes
# (api/util/itimer.h); their lines are a choice, above Rect's line 73, in the band's order. Move (one of the five
# functions of target fn 2241, see 27-uenux2-ctextfield.mk, which lists the forms) is below line 73, a choice.
# Draw (target fn 10916, slot 2) is above Show, in the band's order; its lines are a choice. Its first test is evidence
# for an inline function that returns 16 bits and is compared with 1 (a member, its name and the return's sign are
# chosen: a free function, a uint16_t return and a lambda give the same object): `m_rectDesenhado.Width() != 1`
# (api/gui/primitives.h, whose body is right - left + 1, as fn 10958 shows) gives the target's subtraction and 16-bit
# mask, and clang inlines it in the object (no call remains). The same expression written in place, cast to TPosition,
# gives `i32.eq` on the two loads, and so does `right != left`; `> 1` gives a sign extension and a compare. The name
# Width is chosen, and only functions of this shape are told apart. Same object code, by the function's disassembly
# with the object-local numbers masked: a local TPosition for the width, `!(Width() == 1)`, an inline test that returns
# `Width() == 1`, and a local std::string moved into m_textoDesenhado. A local SRect for DrawText's result does not: the
# frame grows from 16 to 32 B.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CTEXTFIELDUPDATE_SRCS := src/api/gui/ctextfieldupdate.cpp
UENUX2_SRCS += $(CTEXTFIELDUPDATE_SRCS)
# Rect (10913) is a thunk of fn 3889: 27-uenux2-ctextfield.mk has it.
# the constructor's three callers are not reconstructed: 42-uenux2-ctextfieldupdate-roots.cpp stands in for them with two
# make_shared callers, and the constructor's vptr store keeps the vtable
$(ROOT)/$(APP)/42-uenux2-ctextfieldupdate-roots.o: $(ROOT)/src/units/42-uenux2-ctextfieldupdate-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/42-uenux2-ctextfieldupdate.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h $(ROOT)/src/uenux2/src/api/util/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/ecourna/api/exception/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/42-uenux2-ctextfieldupdate-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/42-uenux2-ctextfieldupdate-roots.o
