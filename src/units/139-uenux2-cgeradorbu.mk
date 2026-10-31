# uenux2 comum::CGeradorBU (app/comum/relatorios/cgeradorbu.cpp and cgeradorbu.h) and its bases
# comum::CGeradorBUBase<comum::CRdvVota, comum::CEleitores> (cgeradorbubase.h) and
# comum::CGeradorRelBase<comum::CRdvVota, comum::CEleitores> (cgeradorrelbase.h, new, its records' file): their
# destructors; and api::CPaperFormBuilder::AddTextField<FONTE> over comum::CPadDS<comum::CToUpperDS<comum::CCargoDSNome>>,
# whose instance this unit's roots object emits. Paths relative to src/uenux2.
#
# Matched:
# - CGeradorBU's D2 (target fn 3698) and D0 (11258), defined in cgeradorbu.cpp, which emits the bases' D2s with them:
#   CGeradorBUBase's (5612) and CGeradorRelBase's (5609), which each derived D2 calls.
# - AddTextField<CPadDS<CToUpperDS<CCargoDSNome>>> (5613), defined in api/gui/cpaperformbuilder.h, from the roots object.
#
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
#   it), and its instance brings CDataText<CPadDS<...>>'s vtable, so GetText (fn 11247) is in the link: it differs (unit
#   129's fragment says how). The control block of that CDataText (11246) comes from this instance now: unit 102's
#   dropped builder for it, which stood for 5613, is gone, and unit 129's stand-in for 11247 too.
#
# Chosen: every data member's name but those the constructors' messages give (headers); CGeradorBU's header path, and
# m_historicoCargas' name, from the title ImprimePreTexto loads before it walks the member; the members' access; the destructors' lines in
# cgeradorbu.cpp and ccalculacv.cpp (no record); DestroyInst's name and class; AddTextField<FONTE>'s name, its place in
# the header and the alignment as CDataText's default (the target's body stores the constant 0).
#
# Not reconstructed (traps in 139-uenux2-cgeradorbu-pending.cpp, its header says what each waits for): ImprimePreTexto
# (11256) and ImprimeConsulta (11253), which call fn 160, std::string::append, as this tree's code does at its -O3 (unit
# 31's AddField and unit 93's DefineHistoricoCarga measure that), and fn 942, CCalculaCV::IncluiString (unit 121, matched);
# ImprimeProporcionalPartido (11255) and ImprimeMajoritario (11254), over fns 942, 2271, 2272 and 1273. Each waits for
# direct callees that have no body or name of ours (the pending file's header lists them).
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
