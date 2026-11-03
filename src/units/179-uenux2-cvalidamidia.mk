# uenux2 comum::impl::CValidaMidia (src/app/comum/validamidia/cvalidamidia.cpp): every slot but 8 (target fns 11173 to
# 11168 and 11166: EhValida, Valida, ContemApenasArquivosPermitidos, ContemResultado, ContemArquivosResultado,
# ContemArquivo, LimpaMidia), EhValida the class's key function, with the head of the class (cvalidamidia.h, a chosen
# path), the slots its interface comum::impl::IValidaMidia (ivalidamidia.h, unit 100's head) declares pure, and
# comum::EAplicativosDeUrna (app/comum/eaplicativosdeurna.h, a chosen path) with chosen enumerators and a formatter;
# IValidaMidia::GetInst (fn 5575); the checks the slots call, in
# app/comum/validamidia/cfabricaconteudomidiastart.cpp (its record names it): comum::CFabricaConteudoMidiaStart::
# ConteudoIncializacao (no index of its own), comum::impl's ValidaConteudo (5572), ConteudoValido (2784) and
# RemoveArquivosDeSistema (5571) with its map's tree destroy (3685), and the error enum comum::EUeComumValidaMidiaError
# (validamidia/euecomumvalidamidiaerror.h, a chosen path); and three members of landed files the checks call:
# api::CasamTodos (2758, api/util/csystem.cpp, unit 32), api::CStringUtils's CasaRegex and CasaCaractere (5465, 5464,
# api/util/cstringutils.cpp, unit 196) and ecourna's CStringUtils::FindRegexPosition (no index,
# ecourna/api/util/cstringutils.cpp, unit 00). Those units' fragments point here; the notes are here. With them what
# cvalidamidia.cpp's object emits: has<IValidaMidia> (3686) and the control block's __get_deleter (11164), matched, and
# GetInst's mutex's exit destructor (11165).
#
# What the target fixes.
# - The vtable @1577024 [174, 144, 11173, 11172, 11171, 11170, 11169, 11168, 11167, 11166] and the typeinfos
#   (CValidaMidia's @1577072, a si_class over IValidaMidia's @1577084, which follows it): the class implements the
#   interface, and IValidaMidia::GetInst (fn 5575, record cvalidamidia.cpp:182) allocates 4 bytes and stores this vptr,
#   so the class has no data member. Slots 0 and 1 are binaryen's shared bodies (a destructor that destroys nothing).
# - fn 11173 calls slot 3 through the vtable (+12) with a 16-byte frame and returns the result's byte at +0: slot 3
#   returns an 8-byte class by value. 12134 (vota::CCopiaResultadoParaMR's slot 2, not written) calls GetInst twice and
#   then slot 3 (+12) and slot 6 (+24).
# - GetInst's record: `static IValidaMidia &comum::impl::IValidaMidia::GetInst()` at cvalidamidia.cpp:182, column 76,
#   the closing parenthesis of POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(IValidaMidia, CValidaMidia) at column 1
#   (api/pattern/polysingletongetinst.h; unit 50's reading of the columns). The macro's line puts the mutex after the
#   slots: in the uses-1 band 11165, its exit destructor, follows slot 9's 11166.
# - The slots' bodies, read from the target (pnpm wasm fn ../target/vota_web_wasm.wasm <index>):
#   slot 3 (11172, Valida): 4 for an application outside 1 to 20, 5 for one of 7 to 10 and 15 to 17 without turn '1'
#     or '2', else ValidaConteudo over CPath::GetPathMR() and the list ConteudoIncializacao gives (its code inlined,
#     with the record cfabricaconteudomidiastart.cpp:62, binaryen's work: a second stack frame), and, from reason 4 on,
#     the priority-6 debug wrapper (5574) with "mídia inválida [%d] arquivos:" and with "- %s" per name (the tail of
#     81551's literal);
#   slot 4 (11171): ConteudoValido over the path and an empty list; slot 5 (11170): std::format of
#     "#regex#{}{:05}{}{:05}{:04}{:04}-[a-z]+\\.[a-z]+" over its last argument (a char) and the others in order
#     (argument types 2, 6, 13, 6, 6, 6: char, unsigned, a string, unsigned three times) into a one-name list, then
#     ConteudoValido; slot 6 (11169): the same over "#regex#[ost][0-9]{5}[a-z]{2}[0-9]{13}-[a-z]+\\.[a-z]+"; slot 7
#     (11168): over a list of its one argument, a std::string; slot 9 (11166): RemoveArquivosDeSistema over the path.
#     Slots 6 and 7 build the list before the path (a named local), slot 4 after it (a temporary).
#   ConteudoValido (2784): ValidaConteudo's byte at +0. ValidaConteudo (5572): RemoveArquivosDeSistema, then 1 or 6 when
#     the directory is missing or empty (CSystem::ExistDir 5459, IsEmptyDir 2762) for an empty or a non-empty list, else
#     CDirReader over it, skipping "." and "..": 7 on a directory, files collected; then 8 when more names are expected
#     than found, 9 unless api::CasamTodos (2758) finds every file among the 14 permitted names, 10 unless it finds
#     every expected name among the files, else 2; valid (+0 set) for 1 and 2.
#   RemoveArquivosDeSistema (5571): std::filesystem::remove_all (__remove_all inlined, binaryen's: fn 4678 called with
#     -100) of the path joined to each name of a std::map<std::string, std::vector<std::string>> built from two pairs,
#     "macOS" over ten names and "Windows" over six (the map's initializer_list constructor inlined by binaryen, a
#     second stack frame; its tree destroy is 3685, called last).
#   CasamTodos (2758): false when either list is empty; for each name a copy moved into an object (+0 copied, +16 moved
#     into), a search of the second list with it, false when nothing matches; a pattern and a name match when either
#     begins with "#regex#" (CasaRegex, 5465, over that one and the other), or when they have one length and each pair
#     of characters is equal or passes CasaCaractere (5464) one way or the other. CasaRegex: FindRegex (2199) over the
#     pattern after its 7 bytes, its start compared with npos, behind a 16-byte stack frame of its own (binaryen's
#     work). CasaCaractere: '#' a digit, '?' a letter, a digit, '-' or '_', '@' isalpha (fn 2314, a call), else false;
#     the letter-or-digit test is read as musl's isalnum inlined (splat/symbol_addrs.txt names no isalnum: a reading).
#
# Forms measured. Frame layouts on scratch objects at the tree's flags (build/docker-build.sh em++ -O3 -fPIC -std=c++23
# -DNDEBUG -fno-strict-aliasing -Isrc -Isrc/uenux2/src -c on a copy of the source), each function's store sequence
# (opcode and offset) set against the target's, which binaryen does not move; the rest in the whole link, pnpm wasm
# score after tools/round/link-map.sh.
# - 5571: the map comes from a function that returns it, which clang inlines (ArquivosDeSistema, static): its pairs
#   then lie at +48 of the 96-byte frame, the target's (the first pair's size byte at +59, its vector at +60 to +68).
#   A local map gives the pairs at +24, a range-for over a temporary map +44 in a 112-byte frame, a static local map a
#   336-byte frame. A named copy of the helper's result and a range-for over it give the same stores; the range-for is
#   written. The buffers of the names are freed in the target's order (allocation 13 down to 1).
# - 5572: the permitted names come from a function that returns them, external (ArquivosPermitidos), which clang leaves
#   out of line and binaryen inlines: the target stores the vector through a local holding frame+4 (offsets 0 and 8),
#   as such a callee's result does, and the same helper static, inlined by clang, stores at frame offsets 4 and 12.
#   The reader in an else branch, with {true, 2} returned after it, gives the target's success store after the reader
#   and the list are destroyed; with the reader at the function's top level the stores of every return merge into one.
# - 2758: the name copied into an object that a by-value constructor fills by moving it (CCasaNome): the copy at +0,
#   the move into +16 of a 32-byte frame, the target's; std::any_of, std::find_if, std::ranges over a lambda that
#   captures the name, or a by-value loop variable, all give a 16-byte frame. std::find_if, the result compared after
#   the loop, and `padroes.size() == 0` (the end loaded first, as the target does; `empty()` loads the begin first).
#   The name test (CasaPadrao) external: the target reads the moved name through a local holding frame+16, which a
#   function clang leaves out of line and binaryen inlines gives; a static one, inlined by clang, reads the frame.
# - 5464: '?' as isalnum (musl's, which the target holds inlined); written as the two ranges it reads as 8-bit
#   compares. ConteudoIncializacao's test through a switch in a helper (IndependeDoTurno) compiles to the target's
#   bit mask 1341440; Valida's as 7 to 10, 16, 17 and then 15, of the orders tried the nearest the target's three tests.
#
# Matched: GetInst (5575), now that slot 5's std::format is defined above it (the variant measurement this fragment
# held: a TU emits the format code first) and it matches by its record (srcloc-anchor); its mutex's exit destructor
# (11165), matched by the scan's content pass, its operand the mutex GetInst's match names; slots 4, 5, 6, 7 and 9
# (11171, 11170, 11169, 11168, 11166, named by vtable, 11171 by pair-addr); ConteudoValido (2784) and ValidaConteudo
# (5572), named by their callers' calls; the map's tree destroy (3685, pair-addr); CasaRegex (5465), with
# FindRegexPosition inlined, matched by the content pass (its one target caller is 2758, ours CasamTodos).
# Not matched, written, and what each waits for (pnpm wasm score after link-map):
# - Valida (11172), `146 over 1040 rows (104 replaced, 103 operand-only, 21 inserted, 21 deleted)`:
#   ConteudoIncializacao's early test and Valida's own application test have the target's operations in another
#   order (the forms tried are above); not explained.
# - RemoveArquivosDeSistema (5571), `394 over 992 rows (311 operand-only, 42 inserted, 39 deleted)`: the frame, the
#   names' order and the order their buffers are freed are the target's (allocation 13 down to 1 on both sides); the
#   scan's first difference is the frame pointer's local, 2 where the target has 1 (docs/reference/facts/reading.md
#   R10, "Locals alone"): not explained. Its callers match all the same, as its name comes from their calls (5572 and
#   slot 9, both matched).
# - CasamTodos (2758), `101 over 278 rows (56 operand-only, 21 inserted, 14 deleted)` with CasaPadrao over two
#   std::string_view (its first form, an index loop over the strings, `144 over 325`; std::equal, `129 over 300`):
#   its row reads unresolved on CasaCaractere, which has no target function name.
# - CasaCaractere (5464), no-candidate, `30 over 58 rows (10 inserted, 19 deleted)`: our link calls isalnum, which the
#   target holds inlined. musl's ispunct calls isalnum too, and our link keeps ispunct through
#   boost::char_separator<char>::operator() (src/app/roots_boost.o), which the target does not hold, so isalnum keeps
#   two call sites in our link and one in the target. 5464 waits for that tree root not to keep the separator; the
#   alpha-or-digit test written by hand would copy the library's arithmetic (how-to step 3).
# - the priority-6 debug wrapper of this file (5574), unresolved on its word (api/util/uedebug.h).
#
# Chosen: every name but the records' (ConteudoIncializacao, CFabricaConteudoMidiaStart, GetInst, the classes RTTI
# names): the slots' (EhValida, Valida, ContemApenasArquivosPermitidos, ContemResultado, ContemArquivosResultado,
# ContemArquivo, Slot8, LimpaMidia), the helpers' (ValidaConteudo, ConteudoValido, RemoveArquivosDeSistema,
# ArquivosPermitidos, ArquivosDeSistema, IndependeDoTurno, CasamTodos, CasaPadrao, CCasaNome, CasaRegex,
# CasaCaractere, FindRegexPosition), SResultadoValidacao and its members, EAplicativosDeUrna's enumerators,
# EUeComumValidaMidiaError's enumerator; the slots' types beyond their wasm widths (bool for the words slots 4 to 7
# return, unsigned and char for slot 5's, read from its format's argument types); that the slots are pure in
# IValidaMidia (src/units/README.md "Pending members") and non-const; the paths of cvalidamidia.h,
# cfabricaconteudomidiastart.h, euecomumvalidamidiaerror.h and eaplicativosdeurna.h and EAplicativosDeUrna's scope;
# EAplicativosDeUrna's formatter's base (SFormatoEnum, as for the enums that share fn 536); the helpers' being free
# functions of comum::impl in cfabricaconteudomidiastart.cpp (the band puts 5572 and 5571 after GetInst and
# DepuraInfo, among the objects between api/gui/capplication.cpp's and comum/relatorios/csubstituidortitulo.cpp's, and
# 2784, which clang would inline into slots of its own file, out of cvalidamidia.cpp: a reading), the linkage of each
# (ArquivosPermitidos and CasaPadrao external, as measured above; ArquivosDeSistema and IndependeDoTurno static),
# CasamTodos and CasaPadrao in csystem.cpp, CasaRegex and CasaCaractere as static members of uenux2's api::CStringUtils,
# FindRegexPosition as one of ecourna's CStringUtils (the uses-2 band puts 5465 and 5464 between cgenerictags.cpp's
# functions and csystem.cpp's, and 2758 after csystem.cpp's uses-4 run; api/util's objects link in name order there,
# and cstringutils.cpp sorts between: a reading; 5465 holds FindRegexPosition behind a frame of its own, so that is
# another object's, a choice of which); the lines of everything without a record, the order of ConteudoIncializacao's
# cases, and IndependeDoTurno's being declared above ConteudoIncializacao and defined after it (the record leaves no
# room above).
#
# Pending (179-uenux2-cvalidamidia-pending.cpp): slot 8 (11167), the one trap left; that file's header says what its
# body shows. Its trap merges with traps of its wasm type, so its row stays no-candidate. The six traps that went
# shared wasm types with other units' traps: unit 13's CRdvVota::Confere trap (11486) is a function of its own now,
# named by vtable evidence, and its row reads differs on the pending object (how-to step 9).
#
# libc++'s std::filesystem members 5571 reaches, which unit 261's roots kept in the link with a stand-in for 5571 until
# 5571 was written (that unit is gone with its stand-in): 5571 holds __remove_all inlined (its ErrorHandler<uintmax_t>
# built in its frame with "remove_all" at 153755, a null error_code pointer and the path, then a direct call of fn 4678
# with -100, AT_FDCWD), and with it remove_all_impl (4678, operations.o), which calls itself through table slot 8859 and
# reaches libc's unlinkat (6239, unlinkat.o); ErrorHandler<unsigned long long>::report (4679), whose other target caller
# is CZip::DoAdd (9538, unit 06); posix_readdir (4791, directory_iterator.o) and path's constructor from a string_view
# (4789), whose table slots (8857, 8858) remove_all_impl's invoke calls take, so binaryen keeps them out of line in
# __dir_stream::advance (4793) too. 4678, 4679, 4791, 4793 and 6239 match. 4789 is named (`table`) and differs: the
# target's 4789 is a 15-byte thunk f1085(p0, p1, p2, 8296) of binaryen's merged body 1085, which twelve thunks share
# (4676, 4686, 4789, 5641, 10078, 10134, 11154, 11211, 11264, 11637, 11895, 12045), and our 4789 is a whole body, so no
# such merge forms; it waits for the merge to form, and 1085, 4676 and 4686 with it.
# The roots (179-uenux2-cvalidamidia-roots.cpp) stand for GetInst's one target caller, 12134, not written.
CVALIDAMIDIA_SRCS := src/app/comum/validamidia/cvalidamidia.cpp src/app/comum/validamidia/cfabricaconteudomidiastart.cpp
UENUX2_SRCS += $(CVALIDAMIDIA_SRCS)
$(ROOT)/$(APP)/179-uenux2-cvalidamidia-pending.o: $(ROOT)/src/units/179-uenux2-cvalidamidia-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/179-uenux2-cvalidamidia.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/validamidia/*.h) $(wildcard $(ROOT)/src/uenux2/src/app/comum/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/179-uenux2-cvalidamidia-pending.cpp -o $(R)
# GetInst (fn 5575) has no caller in the link yet: 179-uenux2-cvalidamidia-roots.cpp stands for fn 12134, which calls it
# twice; it declares GetInst through its mangled name and includes nothing
$(ROOT)/$(APP)/179-uenux2-cvalidamidia-roots.o: $(ROOT)/src/units/179-uenux2-cvalidamidia-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/179-uenux2-cvalidamidia.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/179-uenux2-cvalidamidia-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/179-uenux2-cvalidamidia-pending.o $(APP)/179-uenux2-cvalidamidia-roots.o
