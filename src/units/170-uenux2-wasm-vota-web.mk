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
# Not written, and what each waits for:
# - 10240 (votaSetAudioEnabled): written and `unresolved`. The target's 1091 (instance<ISound>, this TU's copy; callers
#   1204 1455 3143 3851 4449 7010 7029 7242 7248 10240 and 7840 by invoke) has one caller in our link, so binaryen
#   inlines it into 10240. Measured on a scratch link with a stand-in calling instance<ISound> and has<ISound> once each
#   and a hand line naming has<ISound> 3343 (its thunk passes ISound's type name, as unit 100's has<T> lines read): 1091
#   stays out of line and stops `unresolved` at +0xc11 on ~shared_ptr<ISound>, `pnpm wasm score` 340 over 1315 rows, 132
#   inserted: our link inlines 5650 and 5656 (target callers 455 and 1091), keeps ~CTravaLeitura whole where the target
#   calls 1322 (a thunk of 6147, which forms with the push bodies' 642), and our ~shared_ptr<ISound> drops the `this`
#   that 388 returns. Each waits for this TU's main (10307), which calls the push bodies and builds
#   CPoliticaExecucaoEleitorWeb, whose LimpaBufferInput holds 455. None of the scratch helps landed: no row matched with
#   them.
# - 10835, CPoliticaExecucaoEleitorWeb::LimpaBufferInput (record 361:46):
#   `api::CPolySingleton<api::IInputKbd>::instance()` then IInput's slot 4, Clear (api/hwil/iinput.h), in the target.
#   Only main builds the class (a 4-byte `new`, vptr 1527156, then 9507, which removes a
#   vota::impl::IPoliticaExecucaoEleitor it finds and calls that push, 5407), so with main unwritten its vtable would
#   not link.
# - 7840, votaInit (CVotaWebEngine::Init inlined, 6669 B, 228 invoke_* calls): src/app/vota_init.cpp stands in. It
#   invokes about 50 functions, most with no name and no stub: 14477, 11571 and 11546, which take votaInit's argument
#   and a key string ("audioEleitorHabilitado", "municipio", ...), read as readers of its options, comum::CPath's
#   GetPathTrab and GetPathRootSemSA (358, 634), a builder and its setters (10268, 10197, 10188, 10181, 10176), 11733,
#   11572, 11641, 11642, 7787 and more.
# - 10307, main: 8302 (28435 B, read as the simulator's setup), 8311, 11159, 7828, the slots of the TU's CWasmSavd
#   (5503, 10965, 10949, 10930) and of main's lambda's __func (10406, 10400, 10384, 10375, 10365), and 5120.
# - 10619 (votaTick) and 10171 (votaGetStateJson): 5500 (6871 B, read as the state's text: votaGetStateJson moves its
#   result into +24), 5408, 407, 2369, 10376, 10857.
# - The copies the docs name for this TU that what is written does not instantiate: 306, 520 and 4967, 5294, 1698, 5532
#   and 9873 (src/app/roots_vector.cpp keeps them), 2247 and 2249 (asn1.md A5), 1928, 3552, 518 and 1843 (asn1.md A10),
#   11489 and 11518 (unit 82), and units 100's and 94's rows that wait for the TU (their fragments).
#
# Stand-ins this unit ended: src/app/roots_uenux2.cpp's minsize instance of fn 252 and its extern template of append
# (252 and 3717 match from this object), src/app/vota_api.cpp's votaPressKey and votaSetAudioEnabled. Unit 100's chosen
# file src/uenux2/src/api/pattern/cpolysingletonlist.cpp goes too: its two definitions are here.
