# uenux2 comum::CGeradorBU (app/comum/relatorios/cgeradorbu.cpp and cgeradorbu.h) and its bases
# comum::CGeradorBUBase<comum::CRdvVota, comum::CEleitores> (cgeradorbubase.h) and
# comum::CGeradorRelBase<comum::CRdvVota, comum::CEleitores> (cgeradorrelbase.h, new, its records' file): their
# destructors, the base's three slots and CGeradorBU's ImprimePreTexto; and api::CPaperFormBuilder::AddTextField<FONTE>
# over comum::CPadDS<comum::CToUpperDS<comum::CCargoDSNome>>, whose instance this unit's roots object emits too (the
# link keeps cgeradorbu.cpp.o's, below). Paths relative to src/uenux2.
#
# Matched:
# - CGeradorBU's D2 (target fn 3698) and D0 (11258), defined in cgeradorbu.cpp, which emits the bases' D2s with them:
#   CGeradorBUBase's (5612) and CGeradorRelBase's (5609), which each derived D2 calls.
# - AddTextField<CPadDS<CToUpperDS<CCargoDSNome>>> (5613), defined in api/gui/cpaperformbuilder.h, from cgeradorbu.cpp.o
#   since its caller 3699 (comum::CriaTituloCargo, fragment 325) is written there; from the roots object before.
# - CGeradorBUBase<CRdvVota, CEleitores>::ImprimeProporcionalPartido (11255, slot 3, record cgeradorbubase.h:187), with
#   ImprimeVotosCandidatos (record :222) inlined by binaryen (a second 400-byte frame), defined in the class in
#   cgeradorbubase.h; cgeradorbu.cpp's object, which emits the base's vtable, emits it.
# - CGeradorBU::ImprimePreTexto (11256, slot 2, record cgeradorbu.cpp:257:27, the default std::source_location of its
#   CPolySingleton<CCalculaCV>::instance() call), with two free functions binaryen inlines into it, each behind a
#   stack-pointer prologue of its own: ImprimeHistoricoCargas (a 416-byte frame) adds a 38-dash line, the title
#   "Histórico de código de carga" and a second dash line, then for each load code "{}: {}" of its number from 1 and
#   CRelUtil::GetIDCargaFormatado's text (fn 2786), a new line, CRelUtil::DSCodigoVerificador by its table slot (3048,
#   fn 11182, unit 123) and a new line; ConcatenaHistoricoCargas (a 32-byte frame) joins the codes, each followed by "@".
#   ImprimePreTexto builds the form, hands the joined codes to CCalculaCV::IncluiString (fn 942) and calls the form's
#   slot 2. Measured with `pnpm wasm score` in the whole link, all before steps 7 to 9:
#   - the helpers as const members of CGeradorBU over m_historicoCargas, defined before ImprimePreTexto: 250 over 768
#     rows (15 inserted, 17 deleted; the target copies `this` to another local before the first prologue and loads
#     +116 and +120 through it); the same members after ImprimePreTexto: 278 over 775; declared inline: 391 over 820;
#   - as free functions taking the vector, defined before ImprimePreTexto: 133 over 763 (the vector's address held in a
#     local, loaded at offsets 0 and 4); defined after it, as written: 41 over 753, all operand-only, the one operand that
#     is no call and no data address the format buffer's table slot (148 in the target), which 11182 and 3700 hold too.
#   Their external linkage is the bytes': made static, clang inlines both into ImprimePreTexto (llvm-nm of that object
#   then lists only ImprimePreTexto), and their own frames in 11256 go.
#   ConcatenaHistoricoCargas is a std::accumulate whose lambda returns `historico + carga + "@"`: the target builds the
#   string in the helper's frame and copies it to the result at the end, which reads as accumulate's by-value initial
#   value returned (a reading). A range-for that assigns `historico = historico + carga + "@"` to a named local and
#   returns it scores ImprimePreTexto 291 over 783 (30 inserted, 47 deleted). The two dash lines are std::string(38, '-'):
#   the target fills each with eight-byte stores of 0x2D, where the title is copied from the data. The formatted line is
#   a named local: the target frees the load code's text before AddTextField and the line after it.
# - std::__introsort over ImprimeConsulta's comparator (5610, 5599 B, recursive), the instance its std::sort brings, in
#   cgeradorbu.cpp's object: named by its census pair (pair-addr), so its recursive call did not wait for 11253,
#   which matches since (below). It calls __sort4 (1920), __insertion_sort_incomplete (2790) and iter_swap (248), whose bodies are
#   byte-identical in our link to CGeradorBUQRCode::GetCamposConsulta's instances (unit 155): iter_swap is one instance
#   in both objects, and step 9 renamed the lines of 1920 and 2790 to this object's copies, which link first. The
#   target's introsort keeps the comparator's address as its third parameter (5 parameters), where GetCamposConsulta's
#   (5605) has 4. Measured on the objects (wasm-objdump -x): cgeradorbuqrcode.cpp.o's instances are local and already
#   take 4 (clang dropped the empty lambda's address), this object's are weak and take 5; in our link the __sort4 and
#   __insertion_sort_incomplete copies lose it and join unit 155's, and the introsort keeps it, as the target's does
#   (a reading: its recursive call passes it on). pnpm wasm score in the whole link, before steps 7 to 9: 73 over 2732
#   rows, all operand-only, each a call or a data address.
#
# Matched since fn 10425 (vota::CMostraEleitorVotando's slot 6, unit 142's) was written with the one literal both
# waited for; until then each was written and `differs`:
# - ImprimeMajoritario (11254, slot 4, record :246), beside it. The scan's first difference was `+0xae target +0xad
#   i32.const 8975 | ours +0xad i32.const 8962` (splat/scan.tsv at this unit's landing; our side moves with the data),
#   the end of its literal "{:02}", which the target's linker merged as the tail of "-{:02}-{:02}" (8963, begin 8970,
#   end 8975), the format string 10425 holds; our link held no such string then and merged "{:02}" into
#   "{:04}{:02}{:02}T{:02}{:02}{:02}". With that literal added (a whole-link try-tu of one scratch TU that returns it),
#   `pnpm wasm splat-remap ... --against 11254` printed IDENTICAL. Unit 75's 8168 waited for the same literal and
#   matched with it.
# - ImprimeConsulta (11253, slot 5, record :286), after it: the same first difference then, `+0xb3 target
#   +0xb2 i32.const 8975 | ours +0xb2 i32.const 8962`, its "{:02}" of the post's id. pnpm wasm score in the whole link, before steps 7
#   to 9: 65 over 1218 rows, all operand-only; the operands that are no call and no data address are the format
#   buffer's table slot (148 in the target), four times (11254, 11255 and 11256 load it too). Its other literals are
#   in our link as the target holds them: "{:0{}}" the tail of "  {}{}{:0{}}" (1042, fn 11973's), "{:04}" of
#   "Local ... {:04}" (8828, fn 11188's), "  " of ",\n  " (445546, sqlite3EndTable's). With "-{:02}-{:02}" added (a
#   whole-link try-tu of one scratch TU that returns it, link-map, link-kinds, splat-kinds), `pnpm wasm splat-remap
#   ... --against 11253` printed IDENTICAL, as it did for 11254 and 5610 in that link. Its record anchors it
#   (evidence:srcloc-anchor); its call votes give fn 1923 (CCargo::GetDetalheConsulta) a `call` line and add 11253 to
#   IncluiString's (942) voters, and both matched before it was written.
#
# The slots 3 and 4, read from the target and measured in the whole link (`pnpm wasm score` against the plain link),
# and slot 5 where it says so (ImprimeConsulta's record, column and named format results are of the same kind; its own
# measurements are in their paragraph below):
# - Each record is the default std::source_location of a CPolySingleton<CCalculaCV>::instance() call (the record's
#   address is stored, then fn 1282 is called with it), so each such call is on its record's line; at column 37 the
#   line holds `CCalculaCV& calculadoraCV = ` before the call, a choice of what fills the column. That the members are
#   defined in the class is a reading of the columns: the constructor's throws at column 19 (lines 66 to 111) put
#   `throw` 12 spaces in, in a body at 8, which an in-class definition gives.
# - Each std::format result outlives the form calls after IncluiString (the target frees it after them, where a
#   temporary would be freed at the end of its statement), so each is a named local; ImprimeMajoritario's and
#   ImprimeConsulta's "{:02}" ones live to the end of the function.
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
# Chosen, for ImprimePreTexto: the helpers' names, their being free functions in comum rather than static members of
# CGeradorBU (they read only the vector they are given; the members' forms above score worse, and their external linkage
# is the bytes', below), their declarations in cgeradorbu.cpp above ImprimePreTexto, the parameters' and locals' names,
# `CCalculaCV& calculo = ` before the call as what fills line 257 to column 27, and ALINHAMENTO_ESQUERDA and
# ALINHAMENTO_CENTRO for the alignments 0 and 2 the target passes (style 1 is a cast: IPaper::EStyle has no
# enumerators).
# Chosen: every data member's name but those the constructors' messages give (headers); in cgeradorbubase.h, where the
# class declares its data members (after ImprimeConsulta), ImprimeConsulta's lines (its head at 280, six lines above
# its record as ImprimeMajoritario's is, and 273 to 279 blank), its sort's comparator (a lambda over GetNumero, as
# GetCamposConsulta's is; its type is in the symbols of 5610, 1920 and 2790, and what the bytes show is an empty
# comparator passed by address whose call inlines to an unsigned compare of the numbers at +0, i32.lt_u in 1920), the
# index's type, ImprimeVotosCandidatos' access, the locals' names and the `!= 0` and `continue` forms of the tests;
# CGeradorBU's header path, and m_historicoCargas' name, from the title ImprimePreTexto loads before it walks the
# member; the members' access; the destructors' lines in cgeradorbu.cpp and ccalculacv.cpp (no record); DestroyInst's
# name and class; AddTextField<FONTE>'s name, its place in the header and the alignment as CDataText's default (the
# target's body stores the constant 0).
#
# ImprimeConsulta, read from the target (fn 11253) and measured: each "differs" below is ImprimeConsulta's listing in
# cgeradorbu.cpp's object (try-tu --symbols with the variant header under -iquote, wasm-objdump -d, offsets, call
# indices, (type N), env. and constants of 4096 and up masked; the header as landed gives the build's listing, 0 lines
# off), counted in lines of a diff of 1329:
# - It reads the post's answers into a copy (CDetalheConsulta's vector, copied element by element: a number and two
#   strings, 28 bytes) and sorts it, as GetCamposConsulta does (unit 155), then walks it by index: the target addresses
#   each answer as begin + i * 28 against a count read once after the sort. A range-for differs (112 lines), and so
#   does an int index against static_cast<int>(size()) (112).
# - CRdvVota::GetInst() is called in each pass (the target's call 555 is in the loop); a `const RDV& rdv` read before
#   the loop differs (65).
# - The answer's number formatted to the post's digits ("{:0{}}") is a named local declared after the builder: the
#   target frees it after the form's Slot2 and before the builder's vector. Declared before the builder, it differs
#   (64).
# - The printed line is a temporary of the AddTextField call: the target frees it and the six temporaries it is built
#   from (left to right: PreencheADireita's copy, the "  " insert, PreencheAEsquerda's copy, two appends, the "{:04}"
#   string) right after AddTextField, before Build. A named local `linha` differs (50).
# - The packed argument types: "{:05}{:04}" and "{:0{}}" format two unsigned (198), "{:02}" and "{:04}" one (6). Fn
#   1881, PreencheADireita, has its ' ' folded into its body (every caller passes it) and gets 26; fn 753,
#   PreencheAEsquerda, gets ' ' (32) and 4. AddTextField (fn 193) gets style 1 and alignment 0.
# - The same object: `unsigned int` for the std::size_t index; `respostas[i]` at each use for the `resposta`
#   reference; `if (votos != 0) { ... }` for the `continue`; the post's id read before its digits.
# The three constructors, GeraRelatorio and the records of cgeradorbu.cpp (CriaQRCode, DefineTipo) are in fn 12110 and
# not written; their lines stay blank.
CGERADORBU_SRCS := src/app/comum/relatorios/cgeradorbu.cpp
UENUX2_SRCS += $(CGERADORBU_SRCS)
W139_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
# the users of CGeradorBU (fn 12110) and AddTextField<CPadDS<...>>'s caller 12110 (3699 is in the link) are not
# reconstructed:
# 139-uenux2-cgeradorbu-roots.cpp keeps them, at the tree's flags, since it emits that instance
$(ROOT)/$(APP)/139-uenux2-cgeradorbu-roots.o: $(ROOT)/src/units/139-uenux2-cgeradorbu-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/139-uenux2-cgeradorbu.mk $(W139_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/139-uenux2-cgeradorbu-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/139-uenux2-cgeradorbu-roots.o
