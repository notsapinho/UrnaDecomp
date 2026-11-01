# uenux2 comum::CGeradorBU (app/comum/relatorios/cgeradorbu.cpp and cgeradorbu.h) and its bases
# comum::CGeradorBUBase<comum::CRdvVota, comum::CEleitores> (cgeradorbubase.h) and
# comum::CGeradorRelBase<comum::CRdvVota, comum::CEleitores> (cgeradorrelbase.h, new, its records' file): their
# destructors and two of the base's slots; and api::CPaperFormBuilder::AddTextField<FONTE> over
# comum::CPadDS<comum::CToUpperDS<comum::CCargoDSNome>>, whose instance this unit's roots object emits. Paths relative
# to src/uenux2.
#
# Matched:
# - CGeradorBU's D2 (target fn 3698) and D0 (11258), defined in cgeradorbu.cpp, which emits the bases' D2s with them:
#   CGeradorBUBase's (5612) and CGeradorRelBase's (5609), which each derived D2 calls.
# - AddTextField<CPadDS<CToUpperDS<CCargoDSNome>>> (5613), defined in api/gui/cpaperformbuilder.h, from the roots object.
# - CGeradorBUBase<CRdvVota, CEleitores>::ImprimeProporcionalPartido (11255, slot 3, record cgeradorbubase.h:187), with
#   ImprimeVotosCandidatos (record :222) inlined by binaryen (a second 400-byte frame), defined in the class in
#   cgeradorbubase.h; cgeradorbu.cpp's object, which emits the base's vtable, emits it.
#
# Written and not matched: ImprimeMajoritario (11254, slot 4, record :246), beside it. The scan's first difference,
# `+0xae target +0xad i32.const 8975 | ours +0xad i32.const 8944` (splat/scan.tsv), is the end of its literal "{:02}",
# which the target's linker merged as the tail of "-{:02}-{:02}" (8963, begin 8970, end 8975), the format string of fn
# 10425, vota::CMostraEleitorVotando's slot 6, not written; our link holds no such string and merges "{:02}" into
# "{:04}{:02}{:02}T{:02}{:02}{:02}", whose end is 8944. With that literal added (a whole-link try-tu of one scratch TU
# that returns it), `pnpm wasm splat-remap ... --against 11254` prints IDENTICAL. Unit 75's 8168 waits for the same
# literal.
#
# The two slots, read from the target and measured in the whole link (`pnpm wasm score` against the plain link):
# - Each record is the default std::source_location of a CPolySingleton<CCalculaCV>::instance() call (the record's
#   address is stored, then fn 1282 is called with it), so each such call is on its record's line; at column 37 the
#   line holds `CCalculaCV& calculadoraCV = ` before the call, a choice of what fills the column. That the members are
#   defined in the class is a reading of the columns: the constructor's throws at column 19 (lines 66 to 111) put
#   `throw` 12 spaces in, in a body at 8, which an in-class definition gives.
# - Each std::format result outlives the form calls after IncluiString (the target frees it after them, where a
#   temporary would be freed at the end of its statement), so each is a named local; ImprimeMajoritario's "{:02}" one
#   lives to the end of the function.
# - The packed argument types say which: ImprimeVotosCandidatos formats the candidate and the votes as two unsigned
#   (198), ImprimeMajoritario the candidate as unsigned and the votes as int (102), so its votes are an int local.
# - ImprimeVotosCandidatos, first written with the digits read before the post's id and a range-for: 11255 scored
#   108 over 765 rows (4 inserted, 5 deleted): the target loads the digits first and reloads the vector's end on each
#   pass. With the id read first and a loop of iterators that calls end() each time, 51 over 761, all operand-only.
#   ImprimeMajoritario reads the digits first: 39 over 632, all operand-only, as first written.
# Evidence, and what was measured:
# - The layouts are the D2s' and the constructors' (fn 12110 holds all three constructors inlined): each header says what
#   it holds and which names its messages give. CGeradorBU is final: its D2 does not open with its own vptr store
#   (docs/reference/facts/reading.md R4). Its destructor is out of line: the D0 calls the D2 and then frees (R5). The
#   bases' D0s are slot 1's 325, the trap of an abstract class.
# - fn 3698 opens with code binaryen inlined from a function of its own: a 16-byte frame that ends before the vector at
#   +116 is freed (`pnpm --silent wasm fn ../target/vota_web_wasm.wasm 3698`, from asmlift-wasm/: g0 is restored at +0x88).
#   That code gets the singletons' info, builds typeid(CCalculaCV).name() as a std::string and calls fn 640,
#   CPolySingletonList::remove(const std::string&, TPolySingletonsInfo&), with no has<T> test; in 12110, 7160 and 8302
#   the call of 640 follows a has<T> thunk (1954 has<CCalculaCV>, 2446, 3387, 4853 by splat/symbol_addrs.txt). So the D2
#   calls a function of another TU, CCalculaCV::DestroyInst (a chosen name) in ccalculacv.cpp, unit 121's file. Measured
#   on the objects, uenux2's flags: the same function written in cgeradorbu.cpp is inlined by clang (-Rpass=inline: cost
#   155, threshold 225), so the frame would be the D2's; and with the info call as remove's second argument the string
#   is built first (the object's rows), where 3698 gets the info first.
# - CGeradorRelBase's destructor: `virtual ~CGeradorRelBase() = default;` and `virtual ~CGeradorRelBase() {}` in the class
#   give the same object, compared by function with the object-local numbers masked; `inline virtual ... = default;`
#   makes clang inline it into CGeradorBUBase's D2 (its masked listing grows from 240 lines to 336), where fn 5612
#   calls it. CGeradorBUBase's is implicit; its D0 is a trap and its one caller calls it, so the bytes do not tell its
#   form either.
# - fn 5613 is fn 604's body over a source passed by value: in the whole link pnpm wasm score gives it 12 rows over 232,
#   all operand-only, before steps 7 to 9. Its definition outside the class or inside it gives the same rows (the roots
#   object, masked). It needs CPadDS's and CToUpperDS's layout (app/comum/dados/ccargods.h, unit 129, says what gives
#   it), and its instance brings CDataText<CPadDS<...>>'s vtable, so GetText (fn 11247) is in the link: it matches (unit
#   129's fragment says how). The control block of that CDataText (11246) comes from this instance now: unit 102's
#   dropped builder for it, which stood for 5613, is gone, and unit 129's stand-in for 11247 too.
#
# Chosen: every data member's name but those the constructors' messages give (headers); in cgeradorbubase.h, where the
# class declares its data members, ImprimeConsulta's declaration's line, ImprimeVotosCandidatos' access, the locals'
# names and the `!= 0` and `continue` forms of the tests; CGeradorBU's header path, and
# m_historicoCargas' name, from the title ImprimePreTexto loads before it walks the member; the members' access; the destructors' lines in
# cgeradorbu.cpp and ccalculacv.cpp (no record); DestroyInst's name and class; AddTextField<FONTE>'s name, its place in
# the header and the alignment as CDataText's default (the target's body stores the constant 0).
#
# Not reconstructed (traps in 139-uenux2-cgeradorbu-pending.cpp, its header says what each waits for): ImprimePreTexto
# (11256) and ImprimeConsulta (11253), which call fn 160, std::string::append, as this tree's code does at its -O3 (unit
# 31's AddField and unit 93's DefineHistoricoCarga measure that), and fn 942, CCalculaCV::IncluiString (unit 121, matched).
# Each waits for a direct callee that has no body of ours (the pending file's header lists them).
# The three constructors, GeraRelatorio and the records of cgeradorbu.cpp (CriaQRCode, DefineTipo) are in fn 12110 and
# not written; their lines stay blank.
CGERADORBU_SRCS := src/app/comum/relatorios/cgeradorbu.cpp
UENUX2_SRCS += $(CGERADORBU_SRCS)
W139_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
# the members the vtables need that are not reconstructed trap here, at the tree's flags
$(ROOT)/$(APP)/139-uenux2-cgeradorbu-pending.o: $(ROOT)/src/units/139-uenux2-cgeradorbu-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/139-uenux2-cgeradorbu.mk $(W139_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/139-uenux2-cgeradorbu-pending.cpp -o $(R)
# the users of CGeradorBU (fn 12110) and of AddTextField<CPadDS<...>> (fns 3699, 12110) are not reconstructed:
# 139-uenux2-cgeradorbu-roots.cpp keeps them, at the tree's flags, since it emits that instance
$(ROOT)/$(APP)/139-uenux2-cgeradorbu-roots.o: $(ROOT)/src/units/139-uenux2-cgeradorbu-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/139-uenux2-cgeradorbu.mk $(W139_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/139-uenux2-cgeradorbu-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/139-uenux2-cgeradorbu-pending.o $(APP)/139-uenux2-cgeradorbu-roots.o
