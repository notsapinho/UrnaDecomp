# uenux2 comum::impl::CValidaMidia (src/app/comum/validamidia/cvalidamidia.cpp): its slot 2, EhValida (target fn 11173),
# the class's key function, with the head of the class (cvalidamidia.h, a chosen path), the slots its interface
# comum::impl::IValidaMidia (ivalidamidia.h, unit 100's head) now declares pure, and the head of
# comum::EAplicativosDeUrna (app/comum/eaplicativosdeurna.h, a chosen path). With them IValidaMidia::GetInst (fn 5575),
# written and not matched (below), and what this object emits with it: api::CPolySingletonList::has over the interface
# (fn 3686, matched), the control block's __get_deleter (fn 11164, matched, from this object since GetInst's push<T>
# builds the block) and the exit destructor of GetInst's static mutex (fn 11165, not matched).
#
# What the target fixes.
# - The vtable @1577024 [174, 144, 11173, 11172, 11171, 11170, 11169, 11168, 11167, 11166] and the typeinfos
#   (CValidaMidia's @1577072, a si_class over IValidaMidia's @1577084, which follows it): the class implements the
#   interface, and IValidaMidia::GetInst (fn 5575, record cvalidamidia.cpp:182) allocates 4 bytes and stores this vptr,
#   so the class has no data member. Slots 0 and 1 are binaryen's shared bodies (a destructor that destroys nothing).
# - fn 11173 calls slot 3 through the vtable (+12) with a 16-byte frame, its result's address (+8) first and its own two
#   arguments after this, and returns the result's byte at +0: slot 3 returns an 8-byte class by value (fn 11172 stores
#   a byte at +0 and a word at +4 of it). EhValida is written as that one call; no other form was compiled.
# - Slot 3's arguments: 11172 holds the record of CFabricaConteudoMidiaStart::ConteudoIncializacao(const
#   EAplicativosDeUrna, const EUrnaTurno) and tests its first argument against 1 to 20 and its second against 49 and 50,
#   so slots 2 and 3 are typed with those two types (a reading; no other type was compiled).
# - GetInst (5575). Its record (`awk -F'\t' '$6 ~ /(^|,)5575(,|$)/' ledger/source-locations.tsv`) is
#   `static IValidaMidia &comum::impl::IValidaMidia::GetInst()` at cvalidamidia.cpp:182, column 76, beside the records
#   of push<T>, instance<T> and CPolySingleton<T>::instance over the interface. Column 76 is the closing parenthesis of
#   POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(IValidaMidia, CValidaMidia) written at column 1
#   (api/pattern/polysingletongetinst.h): unit 50's reading of the columns, 52 plus the two names' lengths, which this
#   unit follows. The body (`pnpm wasm fn ../target/vota_web_wasm.wasm 5575`) holds, in that order, has<T>'s test (fn
#   3686, which instance calls again further on), the 4-byte object and its vptr store, push<T> behind a second
#   stack-pointer prologue (512 B) with __shared_ptr_pointer<IValidaMidia*>'s vptr (1577120, at +0x681),
#   CPolySingleton<T>::instance and CPolySingletonList::instance<T> (prologues of 112 and 576 B) and last
#   f150(1839144), the unlock of the mutex whose exit destructor is fn 11165 (f150(1839144); no direct caller, table
#   slot 3059). In the uses-1 band 11165 follows slot 9's 11166 in link order, so the mutex is defined after the slots
#   (a static's destructor is emitted where the static is defined), as the macro's line 182 puts it after EhValida.
# - GetInst's one caller, fn 12134, calls it twice (ledger/callgraph.tsv) and is not reconstructed:
#   179-uenux2-cvalidamidia-roots.cpp stands for it. GetInst stores the vptr, so the roots no longer keep the vtable.
# - 3686 builds the interface's type name and finds it under a shared lock, the has<T> of polysingletongetinst.h's
#   macro. The target has a second caller of it, __wasm_call_ctors (14478), which calls it once over
#   g_polySingletonsInfo() and drops the result, as it calls the other interfaces' has<T> (3622, 1954 and others): our
#   link has no such call, and 3686 matches without it (16 over 161 rows before step 9, all operand-only).
#
# Not matched.
# - GetInst (5575) reads `no-candidate`: no evidence names it, since its opcodes are not the target's (below), so no
#   srcloc-anchor forms. In our link (ours 5652) `pnpm wasm score ../target/vota_web_wasm.wasm 5575
#   ../build/out/wasm/vota_web/vota_web_wasm.wasm 5652` gives 218 over 1627 rows, 213 operand-only, every row that is no
#   call, no data address and no table slot inside the inlined push<T>: its frame's offsets (60 memarg offsets, and the
#   constants of frame addresses) and five frame addresses computed with i32.sub where the target adds (four) or the
#   reverse (one). That is what a TU emitted first, docs/reference/facts/codegen.md C5: a variant object of this file
#   with one function above line 182 that returns std::format("{}: {}", __func__, s), swapped into a copy of the plain
#   link (docs/reference/facts/workflow.md W13, "One variant object in the whole link"), gives 136 over 1627 rows, all
#   operand-only, and `splat-remap ...
#   --against 5575` with that link's own kinds prints IDENTICAL once a scratch copy of the symbol file names the static
#   mutex (1839144 in the target), the one operand no name reaches; the plain link with the same scratch copy prints
#   `differs at body byte 97 (target instruction +5f i32.store align=2 offset=172)`. In the target, slots 3 and 5 (fns
#   11172 and 11170) call std::format's __vformat_to (fn 146) and are defined above GetInst (the band order above);
#   neither can be written yet (11172 calls fns 5572 and 5574, 11170 calls fn 2784, which calls 5572; 5572 calls fn
#   2762), so GetInst waits for them. The variant's function only steers the compiler and does not land.
# - 11165 reads `differs`: the census pairs it with another class's mutex destructor of the same shape (ours, this
#   object's __cxx_global_array_dtor, scores 2 over 4 rows, both operand-only); it waits for the mutex's name, which
#   only GetInst's match can vote.
#
# Not written, with what each waits for (stubs in src/uenux2/unplaced.cpp):
# - fn 3685, the destroy of a std::map<std::string, std::vector<std::string>>'s tree (it frees the key at +16 and the
#   vector at +28 of each node), reads as this object's copy: in the uses-3 band it follows has<IValidaMidia> (3686) and
#   precedes api/gui/capplication.cpp's 3684 (a reading; its cluster label in ledger/tu-clusters.tsv is
#   capplication.cpp's). Its one caller besides itself is fn 5571, not written (it calls fns 4678 and 4679, which have
#   no name); it waits for 5571.
# - fn 5574 is the priority-6 wrapper api/util/uedebug.h describes over fn 2921, with its word at @1577092, right after
#   IValidaMidia's typeinfo (@1577084, 8 bytes), so among this object's data (a reading); its one caller is slot 3
#   (11172), which calls it twice, so it waits for 11172.
#
# Chosen: every name of the slots (EhValida, Valida, Slot4 to Slot9), SResultadoValidacao and its members, the slots'
# types beyond their wasm widths, that the slots are pure in IValidaMidia (src/units/README.md "Pending members": an
# interface whose one implementer overrides every slot shows no default) and non-const, cvalidamidia.h's and
# eaplicativosdeurna.h's paths, EAplicativosDeUrna's scope, EhValida's line in cvalidamidia.cpp (no record places
# it; the target's order puts 11173 first of the slots, as they are declared), and GetInst's place among
# IValidaMidia's declarations (last).
#
# How the matches are named: 11173 by a pair-fingerprint line of splat/symbol_addrs.txt, 3686 by a content-anchor line
# (the interface's type name it builds), 11164 by a content-anchor line.
# Pending (179-uenux2-cvalidamidia-pending.cpp): slots 3 to 9, fns 11172 to 11166; that file's header says what each
# body shows and waits for. The Slot5 trap is a function of its own (no other trap has its wasm type), so the symbol file
# names fn 11170 after it by vtable evidence and its row reads `differs` with the pending object; the other traps merge
# with traps of their wasm types and their rows stay `no-candidate`. The stub-only file
# app/comum/validamidia/cfabricaconteudomidiastart.cpp, whose one stub was 11172's, went at step 9.
CVALIDAMIDIA_SRCS := src/app/comum/validamidia/cvalidamidia.cpp
UENUX2_SRCS += $(CVALIDAMIDIA_SRCS)
$(ROOT)/$(APP)/179-uenux2-cvalidamidia-pending.o: $(ROOT)/src/units/179-uenux2-cvalidamidia-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/179-uenux2-cvalidamidia.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/validamidia/*.h) $(wildcard $(ROOT)/src/uenux2/src/app/comum/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/179-uenux2-cvalidamidia-pending.cpp -o $(R)
# GetInst (fn 5575) has no caller in the link yet: 179-uenux2-cvalidamidia-roots.cpp stands for fn 12134, which calls it
# twice; it declares GetInst through its mangled name and includes nothing
$(ROOT)/$(APP)/179-uenux2-cvalidamidia-roots.o: $(ROOT)/src/units/179-uenux2-cvalidamidia-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/179-uenux2-cvalidamidia.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/179-uenux2-cvalidamidia-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/179-uenux2-cvalidamidia-pending.o $(APP)/179-uenux2-cvalidamidia-roots.o
