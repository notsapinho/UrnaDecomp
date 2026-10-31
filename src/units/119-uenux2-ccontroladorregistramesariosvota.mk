# uenux2 vota::CLogVota (src/app/vota/log/clogvota.cpp, the file its std::source_location records name) and
# vota::CControladorRegistraMesariosVota (src/app/vota/eleitor/fimvotacao/ccontroladorregistramesariosvota.cpp), with the
# slots of their interface comum::IControladorRegistraMesarios (unit 100's head). Target fns:
# - 184, CLogVota::GetInst: CPolySingletonList::has<comum::IEventosLog>, then CPolySingleton<comum::IEventosLog>::set with
#   push, both inlined by binaryen (two more stack prologues), then the instance through dynamic_cast to CLogVota&;
# - the controller's 37 slots (10800 down to 10766, with 434 in slot 8), and the bodies binaryen merged some of them into:
#   3887 (slots 31 to 33 in the target, 32 and 33 here: below), 3888 (slots 29, 34 and 36), 6017 (slots 19 and 27).
# Matched: 184, 3887, 3888, 6017, 10766 to 10770, 10772, 10773, 10775 to 10779, 10781 to 10785, 10788, 10791, 10798 and
# 10799. Slot 8 is the shared 434 (`return true`), matched before. Unit 02 matches 422 and 5451, which slot 3 reaches.
#
# clogvota.cpp:
# - GetInst's one record, line 37 column 37, is instance()'s default std::source_location: four spaces of indent and
#   `return dynamic_cast<CLogVota &>(` put the call there. That spelling is a choice; any of the same length gives it.
# - The constructor is out of line above GetInst. Measured in the object (wasm-objdump -x): so, its .data.rel.ro has the
#   vtable before GetInst's record and the two typeinfos, the target's order (@1532784, @1532800, @1532816, @1532824);
#   defined in the class, the vtable comes after them.
# - The four Loga members: slots 19, 23, 26 and 27 call GetInst and then run the member in a stack frame of their own (a
#   second prologue), so each is an out-of-line member that binaryen inlined into its one caller. They read +4 and call
#   api::CLoga::loga, so comum::IEventosLog's m_aplicativo is protected (ieventoslog.h). Each names its message before the
#   call: passing the temporary to api::CLoga::loga reads +4 before the message is built, one row out of place (10779
#   `score 13 over 70 rows (same 57, replaced 11 [11 operand-only], inserted 1, deleted 1)`, 6017 `13 over 211`). Their
#   names, lines and order are chosen.
# - LogaMesarioRegistrado and LogaMesarioJaRegistrado are above GetInst, measured: a std::format body emitted before push's
#   moves push's frame slots (unit 100's fragment has the effect on 4879). With no such body above GetInst the link gave
#   184 `score 158 over 947 rows (same 789, replaced 158 [153 operand-only], inserted 0, deleted 0)`, its first slot at
#   +120 of push's frame where the target has +172; with them above it, every row but operands is the target's.
#
# ccontroladorregistramesariosvota.cpp and the interface:
# - No record names a file of the class. The path is chosen: ledger/tu-clusters.tsv's stretch 346, the slots' run, guesses
#   it by class convention only. The class has a key function in its own .cpp: fn 7160 builds the object (4 bytes, the
#   vptr alone), and the vtable (@1586600) is not among fn 7160's records (@1534296 to @1534560), where a class with no key
#   function would have it (docs/reference/facts/reading.md R6). Which member is first is chosen (AddTick).
# - comum::IControladorRegistraMesarios declares the 35 slots pure: the target has no vtable of the interface, and its one
#   implementer gives the order and the wasm types. Every name is chosen (the interface header says from what); a slot
#   with nothing to name it is SlotN.
# - Slots 2 to 4 call the ticks of vota::CThreadOperador (fn 270). CThreadVota::AddTick is out of line in cthreadvota.cpp
#   beside StopTick and StartTick (a choice); binaryen inlines it into slot 2, its one caller. Slots 17 and 18 return and
#   assign +96 of CThreadOperador, unit 116's second string, now m_tituloMesario with an inline getter and setter (chosen:
#   an out-of-line pair was not measured); slots 31 to 33 format it.
# - Slot 30 takes the four scores as a const std::vector<int>& (chosen: it loads a data pointer and four ints, each of
#   type code 3). Slot 12 returns CFinalizaOperador::GetInst() (fn 5342) as comum::CAppState&, a chosen type.
# - The members are defined in slot order, a choice: the band puts 10793 (slot 11) above 10792 (slot 10) and 10788
#   (slot 17) above 10787 (slot 15), and those slots are pending here.
#
# Written, not matching, and what each waits for:
# - 10771, slot 31: its literal is 44 bytes, and at -O2 its std::format keeps the search of the literal for a brace
#   (`score 253 over 255 rows (same 2, replaced 4 [1 operand-only], inserted 249, deleted 0)`); the target has none, which
#   is -O3's limit (docs/reference/facts/reading.md R13). Slots 32 and 33 form 3887 without it, with the same parameters.
# - 10800, slot 2: `unresolved`, its call names no target function: CTickManager::AddTick (3644) is `no-candidate` at -O2
#   (unit 02's fragment).
#
# Pending (119-uenux2-ccontroladorregistramesariosvota-pending.cpp names each and what it waits for): slots 5, 6, 7, 9,
# 10, 11, 13, 14, 15, 16 and 28 (fns 10797, 10796, 10795, 10794, 10792, 10793, 10790, 10789, 10787, 10786, 10774), and
# behind them fns 6018 and 2264.
#
# Roots: the controller's vtable in a sink (fn 7160, its builder, is not written). GetInst's callers are the slots.
CCONTROLADORREGISTRAMESARIOSVOTA_SRCS := src/app/vota/log/clogvota.cpp src/app/vota/eleitor/fimvotacao/ccontroladorregistramesariosvota.cpp
UENUX2_SRCS += $(CCONTROLADORREGISTRAMESARIOSVOTA_SRCS)
CCONTROLADORREGISTRAMESARIOSVOTA_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/119-uenux2-ccontroladorregistramesariosvota-pending.o: $(ROOT)/src/units/119-uenux2-ccontroladorregistramesariosvota-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/119-uenux2-ccontroladorregistramesariosvota.mk $(CCONTROLADORREGISTRAMESARIOSVOTA_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/119-uenux2-ccontroladorregistramesariosvota-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/119-uenux2-ccontroladorregistramesariosvota-pending.o
$(ROOT)/$(APP)/119-uenux2-ccontroladorregistramesariosvota-roots.o: $(ROOT)/src/units/119-uenux2-ccontroladorregistramesariosvota-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/119-uenux2-ccontroladorregistramesariosvota.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/119-uenux2-ccontroladorregistramesariosvota-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/119-uenux2-ccontroladorregistramesariosvota-roots.o
