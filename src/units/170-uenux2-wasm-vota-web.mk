# uenux2: the executable TU of the web voting simulator, /home/rubio/tse/uenux2/wasm/vota_web/vota_web_wasm.cpp, in
# part: (anonymous namespace)::CVotaWebEngine's layout, SetAudioEnabled (record 592:9) and a key-press member, the
# engine's getter, the exports votaPressKey (target fn 10703), votaSetAudioEnabled (10240), votaGetStateJson (10171) and
# votaTick (10619, written, not matched), the state's JSON (5500, written, not matched) and the helpers and posts they
# call (the section "votaTick and votaGetStateJson" below), main, and api::g_polySingletonsInfo with
# api::polySingletonsInfoPadrao (11265), which unit 100 kept in a file of its own while this TU could not be compiled.
# The fragment is this comment: the TU's object, its rule and flags and its place first on the link line are
# src/Makefile's (VOTA_WEB_CXXFLAGS, VOTA_WEB_OBJS; docs/reference/facts/levels.md V1 measures each flag on the whole
# link), and the benchmark's setup `vota-web` names that object.
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
#   double add to +16; written, below) and votaInit (7840, a byte store to +3; not written). Every field name and the
#   bool types are chosen; the widths are the bodies'.
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
# - Lines: 361 and 592 are the records' (CPoliticaExecucaoEleitorWeb::LimpaBufferInput, 10835, in its class at
#   namespace level, and SetAudioEnabled); 515, the record of CVotaWebEngine::Init (7840, not written), stays blank
#   inside the class, which starts after 361, and the members written beside it go after it (src/README.md "Gaps"):
#   Tick and GetStateJson from 517, EstadoJson after PressKey, below 592. Every other line, and the order of the
#   definitions, is a choice. The engine's members are inline: EstadoJson at 425 to 512, above Init's record, or after
#   PressKey gives a cmp-identical object (measured; that clang emits them in the order of their first use is a
#   reading).
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
# - 10619 (votaTick) and 10171 (votaGetStateJson) are written, and 10171 matches: the section "votaTick and
#   votaGetStateJson" below.
# - The copies the docs name for this TU that what is written does not instantiate: 306, 520 and 4967, 5294, 1698, 5532,
#   9873, 2247, 2249 and 1843 (src/app/roots_vector.cpp keeps them, the last three with minsize instances measured
#   there; since unit 253 the link's 306, 5294, 5532 and 9873 are mock/app/comum/cappinfobuilder.cpp's, at this TU's
#   rule, and 520 and 4967 this TU's own twins, std::vector<unsigned int>'s, below), and units 100's and 94's rows that
#   wait for the TU (their fragments). 3552, 518 and 2650, listed here before, match since unit 229 (asn1.md A10): 3552
#   and 518 from src/app/roots_coderenv.cpp at this TU's rule, and 2650's call reaches 388's body. 11489 and 11518 (unit
#   82) match since unit 237, from its tree root src/app/roots_texttospeech.cpp at this TU's rule.
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
# - The push bodies 10090, 5384, 8758, 8911, 8986, 9233, 3882 (under 5395, 5398, 5407), 8834, 9039 and 9135 differ in
#   one frame slot: depura's std::format_string ("sz[{}] ptr[{}]") is at +280 in the target, below the format buffer
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
#   instance<ISound>'s, so they wait for Init (votaInit, 7840). 7667's copy is src/app/roots_texttospeech.cpp's (at
#   this TU's rule, unit 237's), which emits that set code before its builder's, in this TU's order: these records do
#   not place the builder, whose code has none. The evidence is the data between them: ITextToSpeech's vtable (1526520)
#   lies after push's record (1526348) and std::format_error's typeinfo and vtable (1526388, 1526400; that root's
#   comment lists the run and the commands). The step from that run to the TU's code order is that root's reading: the
#   TU's typeinfos and vtables lie in the order its code first refers to them, and the builder's constructor is what
#   refers to that vtable first. With the set code first 7667 has +280 and matches; with the builder first it had +584
#   too (unit 237's fragment).
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
#
# 10869 (the CPosixMutex factory's Create) matches since CPosixMutex's constructor (target fn 10254, the record
# cposixmutex.cpp 30:15, unit 01's) does: unit 01's fragment says what the constructor waited for.
#
# Stand-ins this unit ended: src/app/roots_uenux2.cpp's minsize instance of fn 252 and its extern template of append
# (252 and 3717 match from this object), src/app/vota_api.cpp's votaPressKey and votaSetAudioEnabled, src/app/main.cpp
# (main), and the roots lines that stood for main's table slots (units 100's Registra, 137's CPrng constructor, 171's
# InitApplication). Unit 100's chosen
# file src/uenux2/src/api/pattern/cpolysingletonlist.cpp goes too: its two definitions are here. Unit 74's roots file,
# which kept CWasmWebSound's vtable for the vptr store of main's lambda, went with the lambda's match: that store is in
# the link (a link without the file moved no row: steps 7 to 10).
#
# votaTick and votaGetStateJson, and what they call (added after the rest). Matches (18, none lost, against 21a541d4 by
# index, how-to step 10): 10171 (votaGetStateJson), 5408 and 5521 (the state's class name and its demangling), 10857
# (the error report), the three posts 10376, 11026 and 11100 with binaryen's 3903 over them and 7708 (Insert(const
# SMessage&), the TU's -Oz copy), and the TU's -Oz copies 2737 (std::string::find(const char*)), 977 (std::__str_find),
# 11011 (map<unsigned, comum::md::CCandidatura>::find), 11025, 11033 and 11267 (ostream's << of a char, a C string and a
# std::string); with them 6222 (libc++abi's __cxa_demangle), 2369 (unit 110's ctelasvota.cpp, below) and 9640 (unit 99's
# wasmjs.cpp: its fragment has it). Match lines renamed to twins this TU now brings first: 520 and 4967 to
# std::vector<unsigned int>'s destructor and __destroy_vector, and 2896 to the
# __split_buffer<CPriorityMessageQueue<SMessage>::SItem> merge body's name.
# - votaGetStateJson (10171): Engine(), the state's JSON (5500) into a temporary moved into the engine's +24 string, and
#   that string's characters. 5500's name is a callers+content hand line (splat/symbol_addrs.txt), on the JSON texts
#   only 5500 loads; this match is the row it carries.
# - 5408 (NomeEstadoEleitor) calls vota::IExecucaoVota::GetInst() (3594) and its slot 9, and returns the state's typeid
#   name through 5521, or "" (literal 450187) with no state. 5521 (Desmangle) calls __cxa_demangle(name, nullptr,
#   nullptr, &status) and builds the string from the result when the status is 0 and the result non-null, else from the
#   name or "", then frees the result. Both are this TU's -Oz code: 5521 calls std::string's constructor (148), which
#   uenux2's -O3 inlines (the two compiled at UENUX2_CXXFLAGS and at this TU's rule into probe objects: Desmangle 98
#   against 40 instructions, wasm-objdump -d). Their linkage (the anonymous namespace), names and parameter types are
#   chosen. 6222 matches with 5521: its other target caller, 212 (CPolySingletonList::trace), was its one caller in our
#   link, and binaryen inlined it there.
# - 10857 (ReportaErro): `std::string("{\"message\":\"") + simulador::EscapaJson(texto) + "\"}"` (literal 439251),
#   simulador::ConsoleError(texto), simulador::EmitEvent("vota:error", ...) (literal 83682). votaTick invokes it through
#   table slot 60 in both its catch handlers, and votaInit (7840) through the same slot. Name and linkage chosen.
# - The posts: 10376, 11026 and 11100 are each `f3903(p0, <5, 1 or 9>)` in the target, and 3903 builds a SMessage of
#   that type with its parameter as the queue (the word at +12 of the frame stored before the type at +8) and calls
#   7708, `f501(p0, p1, 1)`: three functions alike but for the type, which binaryen merged; with one caller 7708 would
#   have been inlined into 3903, so each called it before the merge (a reading of binaryen's one-caller inlining, how-to
#   step 3). Written so: SinalizaSincronismo (5, votaTick's, after four increments of the sync bar),
#   HabilitaAudioEleitor (9) and LiberaEleitor (1), votaInit's, which it invokes through slots 55 and 57 with
#   IExecucaoVota's queue (slot 8: 11100 when the voter's audio flag at +3 is 1, else CEstadoAudio::Desativa, then
#   11026). The types' roles are read from the operator states that post them (Post(5) in CSincronismoOperador, Post(9)
#   or Post(8) then Post(1) in CHabilitaAudioEleitor::ProcessInput); the three names are chosen. The message is built in
#   each, not with `fila.Post(N)`: at this rule Post(short) stays a call (wasm-objdump -d of a probe object), where 3903
#   holds the stores. Linkage and place: external, since clang inlines a one-call internal function; defined after
#   main, since the target's table holds priority_queue::push (which Insert invokes) at slot 237, after main's slots
#   111 to 124: read with the table's order (below), the posts' bodies, which first mention Insert, came after main
#   (SinalizaSincronismo declared above the engine class for Tick); 11100 above 11026 in the file, as their target
#   indices order them, and SinalizaSincronismo last, a choice. Measured: the object's first mentions of function
#   addresses in code order (wasm-objdump -d -r) put push's 45th, before main's, with the three posts above main or
#   with SinalizaSincronismo alone above it, and 71st, after InitApplication's (46th), with the three after main, which
#   our link's table gives push as slot 71; that link, measured with unit 97's last stand-in gone too, and one with
#   the three above main (between the exports and main) and the stand-in kept give the same match rows through steps
#   7 to 9, no verdict moved, the symbol file and the match list byte-identical, slot 3 std::string's constructor in
#   both. votaInit's two have no caller in our TU: 170-uenux2-wasm-vota-web-roots.cpp stands for 7840's
#   invokes. Without them binaryen merges nothing and inlines 7708 into SinalizaSincronismo (`pnpm wasm score` against
#   10376 read 20 over 23 rows, 18 inserted). Since they are written, this TU instantiates Insert first on the link
#   line, so the tree root src/app/roots_messagequeue.cpp, which gave 501 at this TU's rule (unit 269), went.
# - 2369 (vota::CTelasVota::IncrementaBarraSincronismo, in ctelasvota.cpp, unit 110's source, an add-only hunk):
#   `m_barraSincronismo->Incrementa()`, the shared_ptr at +180 (5508, matched); out of line, since 7174 (uenux2, -O3,
#   unit 241's) calls it four times. Its name, its being a member, its file and its line (in the gap before
#   GetTelaCargo's record, 3530) are chosen; in use band 5 it links after 2380 and 2376, as their indices order them
#   (ld_index 2795, 2811, 2827). Unit 110's fragment and README row name it.
# - The -Oz copies come with what is written: 2737 and 977 because 5500's form calls find(const char*) out of line, and
#   170-uenux2-wasm-vota-web-roots.cpp gives 977 the second caller the target gives it (3355, not written; with one
#   caller binaryen inlined it into 2737's copy); 11011 from ListaCandidatos's lookup; the ostream copies from
#   EstadoJson.
# - votaTick (10619): written, `differs`, 194 over 692 rows (same 498, replaced 120 [114 operand-only], inserted 38,
#   deleted 36; pnpm wasm score against our link). What the target's body gives: Engine(); nothing unless +0 is 1 and +1
#   is 0; in a try, the state's name before and after IExecucaoVota's slot 7; while that name holds CSincronismoEleitor
#   (literal 83021) a wait on emscripten_get_now: the first tick sets +4 and clears +5 (one i16 store), the count at +8
#   and the deadline at +16 to now + 120; later ticks, unless +5 is set or now is below the deadline, increment the sync
#   bar (2369 on CTelasVota::GetInst, 407) up to four times with the deadline at now + 160, then post 5 (10376) and set
#   +5; any other state clears +16, +8 and +4..+5; CAguardaMensagem (literal 151396) after another state sets +1; the
#   JSON (5500) is assigned to +24 and emitted as "vota:state" when the name or the JSON changed, and in the tick that
#   sets +1 "vota:done" with a new JSON; catch std::exception reports what(), catch (...) the literal 158360. The rows
#   and their order are the target's; the block layout is not: our object places the landing pads of the first three
#   invokes (the first name, GetInst and slot 7, the second name) between the +120 arm and the +5 test, where the target
#   places them after the main path. Measured on the TU's object (wasm-objdump -d, the order of the +120 arm, the pads'
#   __cxa_find_matching_catch_4 calls and the +5 test): the if/else swapped (the pads move before the arm), `agora >=
#   m_proximoAviso` and the two flags as unsigned char (the written layout). The IR after the EH lowering (-mllvm
#   -print-after=wasm-lower-em-ehsjlj) has no branch weights on the __THREW__ tests. Not explained. Every callee is
#   named, so the row waits for that layout alone.
# - 5500 (EstadoJson, the state's JSON): written, `differs`, 1220 over 2837 rows (same 1617, replaced 869 [759
#   operand-only], inserted 104, deleted 247). It loads the same 48 strings as the target's body (the keys and values of
#   the JSON, and the class names it searches the state's names for, which are tails of longer literals: "Branco" at
#   140708 ends the text at 140680), and our object takes the functions it invokes by table slot in the order the
#   target's table gives them (its slots 83 to 103), with ostream's << of a std::string (11267) among them, which the
#   target's votaInit takes first (slot 73). One part of the remainder is measured: the target calls 977 directly at
#   eleven of its twelve find sites and 2737 at the first (CInstrucaoVotacaoAcessibilidade); ours calls 2737 at all
#   twelve, too costly to inline at each (-Rpass-missed=inline: cost 75, threshold 5). string_view's find, the contains
#   of std::string and of string_view, find with a string_view or an explicit length, and the hot and cold attributes
#   all keep a call in probe objects at this rule; only `flatten`, an attribute, gives the call of __str_find. The rest
#   is not explained. NomeSubestadoEleitor (the dynamic_cast to vota::CEleitorVotando, a final class, and its m_pEstado
#   through the getter GetEstadoCargo, a chosen name added to celeitorvotando.h) and ListaCandidatos are held inline in
#   5500: written apart, internal, each with one caller. Every name, the JSON's assembly order the strings and slots do
#   not fix, and the locals are chosen.
# - Order in use band 1 (how-to step 3): this object's new members read inverted against their target indices (11100,
#   11026, 10857 and 11267 link after 10376, ld_index 22, 25, 16, 63 against 12). The target's table shows why: its
#   votaInit, first in the TU, mentions 11100, 11026, 5500, 10857 and 11267 first (slots 55, 57, 58, 60, 73), before
#   votaTick mentions 10376 (110); ours has no votaInit, so each takes its place at a later mention.
# - The table: our link's table follows the order in which the objects' code first takes each function's address
#   (measured: the TU's object's table relocations and GOT.func references in code order, first mentions only, give our
#   link's first 16 slots), so our TU's first three references give slots 1 to 3, the third std::string's constructor,
#   as the target's slot 3. A census pair reads a slot below 1024 as a literal (the addr tier), so 988 (locale::classic)
#   pairs at addr only while ours passes 3 too: a form with SinalizaSincronismo defined above the engine class, first,
#   moved Insert's first mention ahead of votaPressKey's and the constructor to slot 4, and 988 fell to `shape`, taking
#   the `table` names of the locale::__imp::install members it held and 1227, 1524, 3363, 4760, 5152, 7833, 7850, 8046,
#   8327 and 9405 out of match (steps 7 to 9 on that link).
# Stand-ins this section ends, measured together: a link without them, and without unit 97's LegendaValida address,
# gives the same 12558 match lines, and no scan row moves (step 9's join against the link with them):
# src/app/vota_api.cpp (votaTick and votaGetStateJson; its APP_OBJS entry with it), unit 40's CampoIncrementa (for
# 2369), unit 165's w165_execucao (for 5408), unit 99's address of ConsoleError (for 10857), unit 103's address of
# ostream's << of an unsigned short (4755, the target's slots 96 and 103, which 5500 takes first), and the tree root
# src/app/roots_messagequeue.cpp (above). Unit 97's LegendaValida address (for 5500) went later, with that unit's roots
# file, measured again on the tree it left (unit 97's fragment).
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
# assign, and so does its other target caller, 5702 (fragment 335's comum::asn::DesconverteMinucias), so binaryen keeps
# it out of line. The roots object compiles at APP_CXXFLAGS and emits no TSE code: it calls has<T> and __str_find, and
# takes the addresses of votaInit's two posts, through asm labels.
$(ROOT)/$(APP)/170-uenux2-wasm-vota-web-roots.o: $(ROOT)/src/units/170-uenux2-wasm-vota-web-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/170-uenux2-wasm-vota-web.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/170-uenux2-wasm-vota-web-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/170-uenux2-wasm-vota-web-roots.o
