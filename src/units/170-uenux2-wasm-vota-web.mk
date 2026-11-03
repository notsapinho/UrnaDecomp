# uenux2: the executable TU of the web voting simulator, /home/rubio/tse/uenux2/wasm/vota_web/vota_web_wasm.cpp, in
# part: (anonymous namespace)::CVotaWebEngine's layout, SetAudioEnabled (record 592:9) and a key-press member, the
# engine's getter, the exports votaPressKey (target fn 10703) and votaSetAudioEnabled (10240), and
# api::g_polySingletonsInfo with api::polySingletonsInfoPadrao (11265), which unit 100 kept in a file of its own while
# this TU could not be compiled. The fragment is this comment: the TU's object, its rule and flags and its place first
# on the link line are src/Makefile's (VOTA_WEB_CXXFLAGS, VOTA_WEB_OBJS; docs/reference/facts/levels.md V1 measures each
# flag on the whole link), and the benchmark's setup `vota-web` names that object.
#
# Matches (127, none lost, against 84f5d8d by index, how-to step 10). The TU's own functions: 2094 (the engine's getter,
# by its content), 4954 and 5101 (the unique_ptr's reset and destructor), 9832 (the unique_ptr's exit destructor), 10703
# (votaPressKey). The rest are the TU's -Oz copies of what the written code instantiates,
# api::CPolySingleton<api::ISound>::instance above all, the target's copies, since the TU links first (levels.md V1):
# CError::~CError 4636; CBaseError<api::EUePatternError, ...>'s and CBaseError<ecourna::api::pattern::EPatternError,
# ...>'s constructors 235 and 331 with 2379 and binaryen's 2294 (unit 94's fragment), and the latter's ~CBaseError 1940;
# CMutexCompartilhado::lock_shared 3095 and its condition_variable wait 13876; libc++'s std::string code 148, 155, 176,
# 709, 1148 and 13229, and std::optional<std::string>'s 153 and 154; and libc++'s std::format code, 732 784 1395 1402
# 1403 1409 1549 1949 1951 2287 2290 2293 2842 2847 2852 2857 2866 2867 2869 2873 2874 2878 2889 2905 3033 3846 3848
# 3850 3852 3856 3858 3859 3860 3866 3868 3878 3979 4017 4124 5646 5826 5829 5830 5835 5840 5847 5858 5865 5871 5877
# 5884 5893 5912 5919 5937 5939 5955 5975 5976 5981 5988 6016 6283 6377 6450 7256 7324 11570 11604 11624 11643 11645
# 11647 11879 11887 11928 11936 11944 11965 11971 11977 12565, with binaryen's 2907 and 6072 over them. 2094, 3979,
# 5858, 5988, 6283 and 6377 came from the content pass; each one's target callers that match call it under the name it
# took (2094's 10703; 3979's and 6283's 6377; 6377's 5988), and 5858's one caller (4027) is not matched. 252 and 3717
# come from this object too, where src/app/roots_uenux2.cpp held 252 (facts/splat.md S10 item 10). At -std=c++23, the
# tree's, it matches eleven more, libc++'s code for C++23's escaped-string formatter: 1417 (the parser), 1729, 1955,
# 5814, 5820, 5926, 5927 (__write_escaped_code_unit), 5933, 5944 (to_chars<unsigned>), 11753 and 11769 (__escape); and
# 13229 is then std::string::substr's const& overload (levels.md V1).
#
# Rows of library objects that match with the unit, by names it released or the link's table moved: 4658
# (std::to_string(long long), whose __itoa callee 2869 this object now names) and 5476 (unit 125's
# CDateTime::ConvertFromLocalTime, self-voted on 4658 at the base); 4725, 7886, 7888 and 7889 (libc++'s locale.o, over
# unique_ptr<char, void (*)(void*)>, whose operator= had no target name at the base and whose reset and destructor 343
# and 658 now name, the renames below); 2556, 3340 and 4666 (locale.o and string.o; why each moved is not traced); 1227,
# 3363, 4760, 7850 and 8046 (num_get's install and use_facet and three of their callers), named by a table vote for 7850
# (`evidence:table`) that the base did not have. Match lines renamed to twins (how-to step 10): 343 and 658 to
# unique_ptr<char, void (*)(void*)>'s destructor and reset, and 6168 from send to sendto.
#
# Two hand lines of unit 100 go, each measured on this link (splat-symbols, splat-match and the splat build, the
# target's sha256, no row lost): the one that named CPolySingletonList::find<const TPolySingletonsInfo> at 305
# (callers+content), since this object holds the executable TU's two find instantiations with their landing pads, so our
# link keeps 305 and 608 apart as the target does and generated call lines name find<TPolySingletonsInfo> 305 and the
# const one 608, which the hand line contradicted; without it 3387, 2509, 4867 and 4873 (has<T>), 2924, 3928 and 6131
# (binaryen's has<T> bodies) and 11004 (IForm<IPaper>::GetRenderForm, which holds has<T>) match. And the one that named
# 2924 while it differed: 2924 and its thunks 1654, 2160 and 2469 stay `match` without it.
# asmlift-wasm/test/splat-symbols.test.ts's case on the first line now reads the two generated lines.
#
# Evidence and choices.
# - The flags: levels.md V1 (each one measured on this link, -std=c++23 as the tree's).
# - The class's name is the records'. Its 40 bytes are operator new's argument in 2094; its fields' offsets and widths
#   come from the target's bodies: +2 the byte SetAudioEnabled stores (10240), +24 a std::string the getter builds from
#   "{}" (literal 8150) and votaGetStateJson (10171) returns the characters of; +0, +1, +3, +4 and +5 bytes, +8 an int,
#   +16 a double, read and written by votaTick (10619, a byte compare of +0 with 1, a 16-bit store over +4 and +5, a
#   double add to +16) and votaInit (7840, a byte store to +3), neither written. Every field name and the bool types are
#   chosen; the widths are the bodies'.
# - The default initializers are measured, the TU compiled at VOTA_WEB_CXXFLAGS with Engine()'s disassembly compared
#   numbers masked (how-to step 3): without those of the five false bools, the +8 store of 0 after the memset is gone;
#   without the int's, an i64 store of 0 at +16 takes its place; `{}` for `= false` and `= 0` gives the same bytes, and
#   so does the double with or without its initializer. The memset reads as std::make_unique's value-initialization.
# - The engine's pointer is a namespace-scope std::unique_ptr: 2094 reads it with no guard, and its exit destructor
#   (9832) matches. That 11265's guard (.bss 1832596) is the word before it (1832600), and g_polySingletonsInfo the
#   first word of the TU's .data (0x174a30, unit 100's note), are read as this TU holding both: placement by the data, a
#   reading.
# - votaSetAudioEnabled takes an int: 10240 stores `p0 != 0`. SetAudioEnabled takes a bool (the record), and Mute is
#   ISound's slot 6 (api/audio/isound.h), passed !habilitado. The record's column 9 is the start of the instance() call
#   whose default argument makes it, in a member body defined in the class.
# - votaPressKey calls the getter and drops its result, then tests the pointer and builds the string simulador::PushKey
#   (9649) takes: PressKey as a member, the getter's name (Engine), g_engine and every parameter name are chosen.
# - Lines: 592 is the record's; 361 and 515, the records of CPoliticaExecucaoEleitorWeb::LimpaBufferInput (10835) and
#   CVotaWebEngine::Init (7840), stay blank, 361 at namespace level and 515 inside the class, which starts after 361.
#   Every other line, and the order of the definitions, is a choice.
# - The default arguments' records of instance() name this file only at 592: the TU's other calls of instance() are in
#   functions not written.
#
# Not written, and what each waits for (and what matches since, said so):
# - 10240 (votaSetAudioEnabled) matches now, with no edit of its own, and so does 1091 (instance<ISound>, this TU's
#   copy; callers 1204 1455 3143 3851 4449 7010 7029 7242 7248 10240 and 7840 by invoke), from this object: unit 97's
#   and unit 150's members call 1091, so binaryen keeps it out of line. While 10240 was its one caller in our link,
#   binaryen inlined it there, and 10240 read `unresolved`. Measured then on a scratch link with a stand-in calling instance<ISound> and has<ISound> once each
#   and a hand line naming has<ISound> 3343 (its thunk passes ISound's type name, as unit 100's has<T> lines read): 1091
#   stays out of line and stops `unresolved` at +0xc11 on ~shared_ptr<ISound>, `pnpm wasm score` 340 over 1315 rows, 132
#   inserted: our link inlines 5650 and 5656 (target callers 455 and 1091), keeps ~CTravaLeitura whole where the target
#   calls 1322 (a thunk of 6147, which forms with the push bodies' 642), and our ~shared_ptr<ISound> drops the `this`
#   that 388 returns. main (below) is written now; the row read `unresolved +0xb30 call 509: ~shared_ptr<void> has no
#   target function`, the same 388 as main's push bodies (below), until unit 237 matched 388; it reads `differs +0x0`
#   on the locals now, with 1091 inlined into it as above. None of the scratch helps landed: no row matched with them.
# - 7840, votaInit (CVotaWebEngine::Init inlined, 6669 B, 109 invoke_* call sites): src/app/vota_init.cpp stands in. It
#   invokes about 50 functions, most with no name and no stub: 14477, 11571 and 11546, which take votaInit's argument
#   and a key string ("audioEleitorHabilitado", "municipio", ...), read as readers of its options, comum::CPath's
#   GetPathTrab and GetPathRootSemSA (358, 634), a builder and its setters (10268, 10197, 10188, 10181, 10176), 11733,
#   11572, 11641, 11642, 7787 and more.
# - 10619 (votaTick) and 10171 (votaGetStateJson): 5500 (6871 B, read as the state's text: votaGetStateJson moves its
#   result into +24; stub in celeitorvotando.cpp), 3594 (IExecucaoVota::GetInst, unit 165's), 5408, 407, 2369, 10376,
#   10857: all but 407 and 3594 have no name. 2737 and 977, the -Oz copies of std::string::find(const char*) and of
#   std::__str_find that votaTick and 5500 call (977 is 3355's callee too), have no caller in our link.
# - The copies the docs name for this TU that what is written does not instantiate: 306, 520 and 4967, 5294, 1698, 5532,
#   9873, 2247, 2249 and 1843 (src/app/roots_vector.cpp keeps them, the last three with minsize instances measured
#   there; since unit 253 the link's 306, 520, 4967, 5294, 5532 and 9873 are mock/app/comum/cappinfobuilder.cpp's, at
#   this TU's rule), and units 100's and 94's rows that wait for the TU (their fragments). 3552, 518 and 2650, listed
#   here before, match since unit 229 (asn1.md A10): 3552 and 518 from src/app/roots_coderenv.cpp at this TU's rule,
#   and 2650's call reaches 388's body. 11489 and 11518 (unit 82) match since unit 237, from its tree root
#   src/app/roots_texttospeech.cpp at this TU's rule.
#
# main (fn 10307) and what it builds, added after the rest: the settings (unit 188's simulador::SConfiguracao, fn 8311),
# InitApplication ("VOTA", "Software de Votacao" in Latin-1, the version text, an ELogAplicativos of 1: the
# literals' addresses, 334482 being the tail of "rodapeZEVOTA"), eleven singletons, then simulador::Inicializa (fn 8302,
# unit 188) with a std::function over main's lambda, which sets ISound to a simulador::CWasmWebSound and emits
# "vota:ready" with "{}" (fn 3533). The classes it builds that no header of ours had: (anonymous namespace)::CWasmSavd
# over comum::IInterfaceSavd (20 bytes, the base's members zeroed: `new CWasmSavd()`), CPoliticaExecucaoEleitorWeb at
# line 361 (LimpaBufferInput, the record 361:46: the instance call starts at column 46 of a member defined in the class)
# and CSincronismoVotoEleitorWeb (slot 2 is the shared `return 1`, 434), simulador::CFingerPrepareSimulador
# (mock/app/simulador/wasm/cfingerpreparesimulador.h, chosen) and api::CDefaultGenericFactory<AP, T>
# (api/pattern/igenericfactory.h, with IGenericFactory's slots 3 and 4 at their records' lines 44 and 50, their codes
# 6761 and 6762 new enumerators of EUePatternError, names chosen from the messages). CWasmSavd's members are
# IInterfaceSavd's slots (unit 95's names): Escreve empty (425), RecebeMensagem (10949) and Slot4 (10930), which store
# and return 212593824, a constant under a chosen name; RecebeMensagem throws std::invalid_argument with the record-less
# text "CWasmSavd::RecebeMensagem - mensagem de tamanho invalido" when the size is not 12 and else answers a
# ueRespostaSavd with the mark 254.
# Matches from this object with it (against 0fe14b05): 5503 and 10965 (IInterfaceSavd's D2, CWasmSavd's D0), 10930,
# 10835, the factories' slots 10839 10845 10854 10856 10863 10864 10865 10868 10871 10872 and binaryen's 1561 and 6023
# over them, the lambda's __func slots 10365 10375 10400 10406 and 5120 (~function), 11265 and 10620 (a static's
# destructor of this object, __cxx_global_array_dtor.4), the set and push helpers the -Oz copies of CPolySingleton's code bring (1562 and the has<T> thunks 3343 3618
# 3627 5423 5431 5434 5436 with 1166, 6147 with 642 and 1322, 624, 1126, 13974, 1119, 5650, 5656, 6700, the
# SPolySingletonInfo vector's 1005 1009 4852 5779 10325 10424 10464 10507 10547 10582 10607 10643 10679 10714 10750
# 10801 11533 11544 11548 11549, the control blocks' constructors 10335 10432 10470 10513 10555 10585 10618 10652 10687
# 10723 10759 10807), vector<unsigned char>'s 5493, 5494 and 10890, and 8319 (std::length_error's constructor).
# Matches with the has<T> roots, the value-initialized sound and Inicializa's reference parameter (against b7c2e8a5, by
# target index): 5417, 5425 and 5427, has<T> over IGenericFactory<IRWSyncCtl>, IFingerPrepare and
# ISymmetricCipherFactory, which 170-uenux2-wasm-vota-web-roots.cpp gives the second call site their unwritten target
# callers give them: with one caller here, binaryen inlined each into its set<T> body, and the three bodies merged into
# one (9039 and 9135 were `no-candidate`, 8834 `differs` against a twin). Whole again, those bodies take their names by srcloc-anchor, and the
# raw-pointer sets over them match: 9650, 9831, 9897. With them main (10307) and its lambda's operator() (10384), each
# after a form measured on the whole link (`pnpm wasm score` against the plain link, before the names):
# - `new simulador::CWasmWebSound()` in the lambda, value-initialized: the object is zeroed and the implicit
#   constructor's stores leave the target's i32 at +4 and i64 at +8 (15 over 123 rows, all operand-only), where
#   `new simulador::CWasmWebSound` gave an i64 at +4 and a byte at +12 (23 over 126, 3 inserted, 3 deleted).
#   `new simulador::CWasmWebSound{}` gives the same object as `()` (`cmp`, the TU compiled at its rule).
# - simulador::Inicializa taking the std::function by reference (unit 188's fragment): by value, main's frame is 96
#   bytes and InitApplication's first string has a slot of its own (234 over 958 rows, 15 inserted); by `const&`, as
#   written, or by `&&` (both 80 bytes, the TU's object compiled alone) the frame is 80 bytes, the string sharing the
#   std::function's slot at +0 as in the target (203 over 951, every row an operand but the eight `invoke` table slots
#   the diff aligns apart). `const&` is chosen.
# main's last callee name, fn 8302's, is a hand line (splat/symbol_addrs.txt, unit 188's): main's table vote is its only
# voter, and the scan refused main as `unresolved self-voted` without it.
#
# Not matched yet, each written:
# - The push bodies 10090, 5384, 8758, 8911, 8986, 9233, 3882 (under 5395, 5398, 5407), 8834, 9039, 9135 and 7667 differ
#   in one frame slot: depura's std::format_string ("sz[{}] ptr[{}]") is at +280 in the target, below the format buffer
#   at +288, and at +584 in ours, above it, every slot between moved 8 (10090: 156 over 885 rows, all operand-only). None
#   of the forms of push tried gives it. Measured on the TU's object (wasm-objdump -d, the slot of that string's store in each push):
#   a scratch explicit instantiation of push<comum::IInterfaceSavd> above the TU's code, a line that only steers the
#   compiler and does not land, gives every push of the TU +280; a strong function with a std::format call there, an
#   explicit instantiation of CPolySingleton<api::ISound> or of CPolySingletonList::instance<api::ISound>, or the two
#   exports moved below main give +584, and so do six forms of push in the header (std::lock_guard, a local for the
#   size, static_cast<void*>, a non-const shared_ptr, a local pair for find's result, the shared_ptr made before depura's
#   call); a named local for depura's text gives +552, a std::string nome +568. Read with unit 100's frame paragraph: the
#   slot follows whether a push's format calls are emitted before any other format body of the TU. Ours emits
#   instance<ISound>'s first (SetAudioEnabled);
#   the target's records of this TU run CVotaWebEngine::Init's (515:13), then 7667's push (set<ITextToSpeech>), then
#   instance<ISound>'s, so they wait for Init (votaInit, 7840).
# - 10949 (RecebeMensagem): `differs` at +0x63 on the response's zeroing; `pnpm wasm score` against ours reads 22
#   over 74 rows, 15 replaced (all operand-only), 3 inserted and 4 deleted, the rows of the response's slot. The target
#   holds the 12-byte comum::ueRespostaSavd at +4 of the frame, 4-aligned (`i64.store align=2 offset=4`, `i32.store
#   offset=12`, the mark's `i32.store8 offset=4`, and `i32.const 4; i32.add` for assign's range); ours at +0, 8-aligned
#   (`i64.store align=3 offset=0`, `i32.store offset=8`). The
#   TU compiled alone at its flags with three forms of the zeroing, `resposta{}` then the mark (written), `resposta{254}`,
#   and the declaration above the size test, gives our slot for each (wasm-objdump -d of the object, RecebeMensagem's
#   stores). 5496 (vector<unsigned char>'s __assign_with_size, which assign calls) is out of line now and matches
#   (below).
# - 10878 (the CWasmThread factory's Create): 35 over 40 rows, 29 deleted. The target's object is 16 bytes, zeroed, with
#   an i16 8192 at +12 and the vptr (`f137(16)`, then two i64 stores of 0), and a word of the frame that it nulls, reads
#   back and frees (fn 136, emscripten_builtin_free); our simulador::CWasmThread is 8 bytes (cwasmthread.h, unit 99's: m_contexto
#   at +4 alone). It waits for that layout.
# - 10869 (the CPosixMutex factory's Create): `unresolved`, CPosixMutex's constructor (target fn 10254, the record
#   cposixmutex.cpp 30:15) has no target name: it is `no-candidate`, and ours (unit 01's) scores 19 over 209 rows
#   against it, 1 deleted, not read further.
#
# Stand-ins this unit ended: src/app/roots_uenux2.cpp's minsize instance of fn 252 and its extern template of append
# (252 and 3717 match from this object), src/app/vota_api.cpp's votaPressKey and votaSetAudioEnabled, src/app/main.cpp
# (main), and the roots lines that stood for main's table slots (units 100's Registra, 137's CPrng constructor, 171's
# InitApplication). Unit 100's chosen
# file src/uenux2/src/api/pattern/cpolysingletonlist.cpp goes too: its two definitions are here. Unit 74's roots file,
# which kept CWasmWebSound's vtable for the vptr store of main's lambda, went with the lambda's match: that store is in
# the link (a link without the file moved no row: steps 7 to 10).
#
# Rows of this object that match with fragment 241 and the GetInsts unit 165 writes (against 36dda756, by index): the
# has<T> thunks 2736, 2741 and 2744 (IExecucaoVota, impl::ISincronismoVotoEleitor, impl::IPoliticaExecucaoEleitor),
# which this TU's static initializer (14478), its set<T> bodies and the three GetInsts call (3594, and the copies 7181
# and 5925 hold inlined), with binaryen's body 3884 they share; the push thunks 5395, 5398 and 5407 (into binaryen's
# 3882, which differs on its frame offset, as the bullet on 10307 says); the set<T> bodies 8728, 9437 and 9507; and
# 9372 (CPolySingleton<IExecucaoVota>::set<CExecucaoVotaCooperativa>, which passes 8728's table slot to 1562).
# What held them was the type's name: this TU passed the name's
# own address, from the typeinfo it emitted, where the target's thunks pass the typeinfo's name field (the typeinfo +
# 4), the typeinfo being external since each interface's destructor is out of line, its key function (unit 165's
# fragment has the evidence). At the base 2736, 2741, 2744 and 3884 were `no-candidate`, and 5395, 5398 and 5407 read
# `differs` on that constant (`git show 36dda756:splat/scan.tsv`).
# And 5496, vector<unsigned char>'s __assign_with_size, this TU's -Oz copy: RecebeMensagem (10949) calls it through
# assign, and 170-uenux2-wasm-vota-web-roots.cpp stands for its other target caller, 5702 (ecourna's, not written), so
# that binaryen keeps it out of line. The roots object compiles at APP_CXXFLAGS and emits no TSE code: it calls 5496
# through an asm label.
$(ROOT)/$(APP)/170-uenux2-wasm-vota-web-roots.o: $(ROOT)/src/units/170-uenux2-wasm-vota-web-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/170-uenux2-wasm-vota-web.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/170-uenux2-wasm-vota-web-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/170-uenux2-wasm-vota-web-roots.o
