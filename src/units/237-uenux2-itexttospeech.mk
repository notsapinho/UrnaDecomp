# uenux2: api::ITextToSpeech's Synthesize (target fn 11530, slot 0) and what it calls: the options, the key, the lookup
# and the store of the recent-audio cache and the kept map, written inline in src/uenux2/src/api/audio/itexttospeech.h
# (unit 82's header, whose comment has the evidence of each member), and Cache (fn 921, below), which keeps a text's
# audio in the kept map. No source of its own: the target's copies of the first are the executable TU's, and the tree
# root src/app/roots_texttospeech.cpp emits them at that TU's rule, VOTA_WEB_CXXFLAGS (its rule and its APP_OBJS entry
# are src/Makefile's; its comment says whose copies and why there); Cache's copy is read as a vota TU's, which
# 237-uenux2-itexttospeech-roots.cpp emits at that TU's flags. This file holds the evidence, the measurements and the
# rule of 237-uenux2-itexttospeech-roots.cpp, the stand-ins.
#
# Matches (50, none lost, against a081739b by index, how-to step 10):
# - from the root, ITextToSpeech's members: 11530 Synthesize, 5758 MakeKey, 5754 Lookup, 5750 Store, 11436
#   SRecentCache::Put; and, written by unit 82 and `differs` from its object until now, 11518 SetVoice, 11489 the D2 and
#   3764 the cache's destructor (SRecentCache::Get has no index of its own: binaryen inlined it into 5754);
# - from the root, the libc++ code they instantiate: the kept map's operator[] 11447 (table slot 210), its
#   __emplace_unique_key_args 5685, its node holder's reset 3722, its destructor 3746 and its piecewise pair constructor
#   11345; find 2808 (both maps' instances, one body); the index's operator[] 3732 (binaryen inlined its emplace there),
#   __erase_unique 11353 (slot 212), its node holder's reset 2804 and its pair constructor 11396 (slot 215);
#   __rehash<true> 5695 (slots 214 and 216: both maps' instances, one body) and the bucket array's 5687, 5724 and 5722;
#   the string hash 3729; the list's splice 5701, pop_back 11346 (slot 213) and __delete_node 5720; pair<string,
#   shared_ptr<CWavFile>>'s constructor 11342 (slot 218) and destructor 1928 (docs/reference/facts/asn1.md A10's row,
#   whose -Oz copy no root could give by name); shared_ptr<CWavFile>'s copy assignment 5707;
# - from libc++.a, objects the rehash and the hash bring into the link: 4769 (__next_prime) and 4768 (the lower_bound
#   it calls) and 8054 (std::overflow_error's constructor) from hash.o, 4773 (__murmur2_or_cityhash) from functional.o;
# - from the executable TU's object: 388, its ~shared_ptr<void>, which keeps its `this` now that Synthesize reads it
#   (`p0 = f388(p0)` in 11530, the one target function that reads it); its callers 455 (CPolySingleton<IInputKbd>::
#   instance), 2584 (~SPolySingletonInfo) and 4180 (shared_ptr<void>'s move assignment), and 13540
#   (vector<SPolySingletonInfo>::erase, over 4180); the set thunks 9574, 9685, 9731 and 9986, `unresolved` at a081739b on
#   the table slot of their set<T> bodies, which step 8 names now (srcloc-anchor lines for the push bodies 8758, 8911,
#   8986, 9233, 5384 and 10090, whose rows still differ: below, and for 9495, unit 11's), and 10356
#   (CPolySingletonList::set<ISound>, over 5384); 1113 (__format_arg_store<unsigned long, const void*>) and 2270 (its packed storage's lambda), read as kept out
#   of line by MakeKey's two calls of the same body (unsigned is unsigned long's width here);
# - from libc++.a's filesystem objects, callers of 388: 4774 (~filesystem_error), 8089, 8090 and 8092 (its
#   constructors) and 2154 (shared_ptr<__dir_stream>::reset).
# Match lines renamed to twins the root brings first (how-to step 10): 1390 (allocator<wchar_t>::allocate to the
# index's bucket array's) and 1925 (__allocation_guard's __destroy, filesystem_error's to the list node's).
# 3732, 5685 and 11436 came from the content pass, 5695, 5750, 5754, 5758, 11447, 9574, 9685, 9731, 9986 and 10356
# from the census's pair; each was read against what calls it or holds its slot (above, and the header's comment).
#
# Measured: variant links, the plain link's objects with the root's object compiled against a variant of the header
# in its place, scored member by member (pnpm wasm score, default depth; every member operand-only with the header as
# written: 11530 19 over 183, 5758 16 over 351, 5754 3 over 82, 5750 8 over 59, 11436 18 over 213):
# - Synthesize: the options' initializer written in it, 30 over 183 rows (5 deleted: the local that holds the options'
#   address, and the address its destructor takes); an SOptions constructor of the five values, 59 over 200. Read as
#   GetOptions, a function of its own that binaryen inlined (how-to step 3's signs).
# - MakeKey: options.tag passed as is, 73 over 351 (6 deleted; every frame offset 16 off): the tag is a prvalue.
# - Lookup: Get's code written in it, 15 over 83 (6 deleted).
# - Store: a bool for the last argument, 10 over 59 (2 deleted); the target compares it with 1.
# - Put: the last entry taken by reference, not copied, 282 over 406.
# - The same rows for every member: the looked-up result a local of a block, tested with `if (wav)`; index.contains(key)
#   or index.count(key) in Get's and Put's tests; an int compared with 1 for the enum; `(long long)options.tag`;
#   MakeKey as a free function that takes the object first (a friend found by argument-dependent lookup).
# Chosen (the header lists them): every name, the enum, MakeKey a member (how-to step 3: its callers pass an object it
# never reads), the cast's spelling, the root's file name, the stand-ins' names.
#
# Stand-ins of 237-uenux2-itexttospeech-roots.cpp while it compiled at APP_CXXFLAGS (it called through __asm__ labels
# and included nothing): w237_guarda for fn 921 (5685's other direct caller), and w237_par for fn 3552 (the one reader
# of 1928's result) until unit 229's root brought 3552. Measured, before 921 was written, on a variant link without
# them: 11447 372 over 394 (367 inserted: 5685 inlined into it), and a drop deleted in each of 11436 (two), 3722, 3746
# and 5720; with them every one is operand-only. w237_par went with 3552 in the link (from unit 229's root, which reads
# 1928's result): a link without it moves no row (unit 229's fragment). w237_guarda went with 921 in the link, whose own
# call of 5685 is 5685's second call site (below).
#
# Hand lines: the five that a generated line now repeats or that nothing needs went from splat/symbol_addrs.txt: 3746
# and 3764 (unit 158's, callers+content; 3746 has a generated pair-addr line) and 3618, 3627 and 5423 (unit 100's has<T>
# lines, which generated `call` lines by the push bodies 8758, 8911 and 8986 now repeat). Weighed by removal on copies, each alone and the five together, with
# the match lines of each and of its matched callers out (3618 with 4356, 3627 with 3164, 5423 with 3598, 3746 and
# 3764 with 5441, 9427 and 11489): two scans give 11313 match rows beside the control, and splat-build verifies 11313.
#
# ITextToSpeech's vtable and typeinfo come from the root now, where unit 82's pending object emitted them strong.
#
# Not matched, each measured on this link:
# - the executable TU's push bodies 10090, 5384, 8758, 8911, 8986 and 9233 read `differs` now on a frame offset, 288
#   against 280 (10090: 156 over 885, all operand-only, its frame offsets from the target's 288 up 8 lower), read as a
#   form of CPolySingletonList::push (unit 100's header); 7667 and 8834 on their first call, a has<T> thunk (target
#   3281 and 5417, ours 3618 and 5423). 3281 matches since, from src/app/roots_texttospeech.cpp, where
#   set<api::ITextToSpeech> instantiates it (the root's explicit instance went, below), and 7667 read so while no body
#   of ours was the executable TU's set<api::ITextToSpeech> (its census pair was 8758's body); the root holds that copy
#   now (below).
# - 9650, 9831, 9897 and 10307 (main): `unresolved` on table slots of set<T> bodies that have no target name; 640 on
#   unlock_shared_and_lock's; 9372 on a table slot of ours whose function the target's table does not hold.
#   Since then 9372 matches (fragment 241), and 9650, 9831, 9897, 10307 and 640 with unit 170's has<T> roots and unit
#   100's guard parameter of unlock_shared_and_lock; none of the forms of push tried moves the push bodies' frame slot,
#   read as the order in which the executable TU emits its format code (unit 170's fragment), and 8834's first call
#   matches (5417).
# - 2650 called the body matched as 424 (named after a twin with no result, boost's
#   ~shared_ptr<basic_regex_implementation> of ecourna's cstringutils.cpp.o) where the target calls 388, read as waiting
#   for a copy of ~shared_ptr<ASN1::IAbstractVisitor> with 388's body ahead of the runtime: it matches since unit 229's
#   root emits that copy.
# - 13877 (unit 82's fragment) is not written (921 is now, below); 3552 matches from unit 229's root, and 1928's line
#   names that root's pair<string, shared_ptr<IAbstractVisitor>> copy now, the same body, which links ahead of this
#   one's.
#
# CPolySingleton<api::ITextToSpeech>::set<simulador::CWasmNullTextToSpeech>, target fn 4162 (143 bytes, landing pads),
# added after the rest: the executable TU's copy, which votaInit (fn 7840, not written) reaches through invoke_vii's
# table slots 7 and 46 (elem[7] and elem[46] of the target's table) and fn 8302 (unit 188) calls directly. The root
# takes its address in a static constructor's sink, which stands for votaInit's two slots, so that it emits the copy
# with what the copy instantiates and binaryen keeps it out of line beside 8302's call (the root's comment has the
# evidence and the measurement without the sink). 8302's call reaches it, as the target's does: this object links ahead
# of simulador.cpp.o.
# Matches with it (4, none lost, against 34125a18 by index, how-to step 10): 4162, from the census's pair with our copy
# (shape); CPolySingletonList::set<api::ITextToSpeech> (fn 7667, push<api::ITextToSpeech> inlined, slot 65 of 4162's
# invoke_vii), the executable TU's copy, from this object (below: the root's order); and two thunks that 7667 invokes,
# into binaryen's bodies 1009 and 1010: 14423 (vector<SPolySingletonInfo>::emplace_back for
# shared_ptr<api::ITextToSpeech>, table slot 154) and 14456 (shared_ptr<api::ITextToSpeech>'s constructor from
# unique_ptr, slot 153), named by step 8's `table` evidence by 7667, which has its srcloc-anchor now (its
# push<api::ITextToSpeech> record, which this object loads). No match line was renamed; each new match was read against
# its callers (4162: 8302 and the two slots of 7840; 7667: 4162; 14423 and 14456: 7667).
# Two lines went with it, both taken out in one link, steps 7 to 9, that moves no scan row (its scan differs from the
# link with them in two `ours` numbers of the detail column only, and the match list and symbol file are the same): the
# root's explicit instantiation of has<api::ITextToSpeech> (3281), which set<api::ITextToSpeech> instantiates in the
# same object (with and without the line, 3281's, 7667's and 4162's bodies in the object are the same, wasm-objdump -d
# with object numbers masked; only the object's order of functions differs), and the two calls of 388
# (~shared_ptr<void>) in src/units/100-uenux2-cpolysingleton-roots.cpp, which stood for 7667 alone (that file's
# comment).
# The root's order: its sink and the sink's struct come before urna_texttospeech_constroi, so that the object emits the
# set code before the builder's, in the executable TU's order. That TU's records (CVotaWebEngine::Init's 1526324,
# 7667's push<api::ITextToSpeech> 1526348, instance<api::ISound>'s 1526584) do not give it, since the builder's code
# has none. The evidence is the TU's data between them, which the root's comment lists with the commands:
# ITextToSpeech's typeinfo (1526340) and push's record (1526348), then the typeinfo of the error push throws and its
# base's, std::format_error's typeinfo and vtable and the format bool strings (1526364 to 1526428), the errors' vtables
# and the vtable and typeinfo of the __shared_ptr_pointer 7667 makes (1526440 to 1526508), and only then ITextToSpeech's
# vtable (1526520). The step from that run to the TU's code order is the root's reading: the TU's typeinfos and vtables
# lie in the order its code first refers to them, and an ITextToSpeech constructor's vptr store, the builder's, is what
# refers to that vtable first, so the builder came after push and push's format code. In the root's order the object
# emits those 13 .data.rel.ro objects as the target lies them out; with the builder first it emits ITextToSpeech's
# vtable and std::format_error's typeinfo and vtable ahead of push's record (wasm-objdump -x, the object's data
# segments). Past that one order the root's lines are free (src/units/README.md "Companion files"). Measured both ways,
# steps 6 to 9 and the splat build on each, the target's sha256 both times: in this order 7667 matches, 12190 matches;
# with the builder first, as the root was first written, 12189, and 7667 `differs` on the frame slot of depura's
# std::format_string (+584 in ours where the target has +280, the slots between 8 off), as the executable TU's other
# push bodies do (unit 170's fragment, whose reading this fits: the slot follows which format code a TU emits first).
#
# api::ITextToSpeech::Cache, target fn 921 (584 bytes, no landing pads), added after the rest, inline in the header
# beside Synthesize (the header's comment has what its body shows).
# - Whose copy. Its one target caller, fn 7787 (not written), calls it 14 times, all inside a frame of their own there
#   (a second stack-pointer prologue of 48 bytes at +0x241bb) that loads the records of
#   vota::CInstrucaoVotacaoAcessibilidade::CacheInstructionAudio, cinstrucaovotacaoacessibilidade.cpp:161 (1533776, at
#   +0x24240, before the calls, which run from +0x242dd to +0x24513) and :157 (1533760, at +0x2456f, in its throw):
#   pnpm --silent wasm fn ../target/vota_web_wasm.wasm 7787 | /usr/bin/grep -E 'call 921 |i32.const 15337(60|76) '.
#   So CacheInstructionAudio was a function of its own that binaryen inlined into 7787 (how-to step 3's signs), its
#   calls of Cache were emitted in cinstrucaovotacaoacessibilidade.cpp's TU, and 921 is read as that TU's copy (no
#   other target function calls it). That file builds at uenux2's -O3 with strict aliasing (src/app/vota/ is in
#   UENUX2_TBAA_DIRS, the file not in UENUX2_NOTBAA_FILES). What the calls pass, read from 7787's code: the
#   ITextToSpeech instance and, for each of five speeds, 13 key names (fn 744, api::KeyName) and the message fn 4407
#   returns.
# - The rule. The roots object now emits Cache, TSE code meant to match, so it compiles at that file's flags,
#   $(call uenux2_cxxflags,...) of its path, no longer at APP_CXXFLAGS (src/units/README.md "Companion files"). Compiled
#   with and without -fno-strict-aliasing, its Cache and its stand-in are the same code (llvm-objdump -d of both
#   objects, raw); 86 of its other 109 functions differ (object-local numbers masked), Lookup, SRecentCache::Put, the
#   maps' members and std::format code among them, linkonce copies that objects ahead of it on the link line define
#   too: of this object the link keeps Cache and the stand-in alone (awk -F'\t' '$3 ~ /237-uenux2/'
#   build/out/wasm-map/vota_web/names.tsv). So no match rests on that flag.
# - The stand-in. w237_cache stands for 7787 and calls Cache twice (7787 has 14 calls), each with the default kind,
#   eCacheKept, so that binaryen keeps 921 out of line and its dead-argument elimination folds the one value every
#   call passes into the body, the constant 1 the target's 921 passes Store.
# - Measured, the variant link (this object compiled against a variant of the header, linked in its place:
#   docs/reference/facts/workflow.md W13; pnpm wasm score at the default depth): with eCacheKept written in Cache and no
#   parameter, 921 scores 136 over 358 rows (87 inserted: Store inlined; -Rpass=inline on this object's compile prints
#   Store into Cache at cost 210, threshold 250); as written, Store costs 280 there, stays a call, and 921 matches.
# - Chosen (the header lists them): the name Cache, the kind's default argument and its place after the text (the folded
#   parameter leaves no trace of either), ECache's place and access, the stand-in's name.
# Matches with it (1, none lost, against 5d769991 by index, how-to step 10): 921, from the census's pair (shape) with
# Cache, read against its caller (above) and its callees, 5758, 5754, 5685 and 5750 (matched from
# src/app/roots_texttospeech.o). No match line was renamed and no hand line added; step 8 changed no line of
# splat/symbol_addrs.txt.
#
# Since the executable TU's votaInit (unit 170) is written, that TU builds simulador::CWasmNullTextToSpeech itself and
# emits ITextToSpeech's vtable and inline members, and set<CWasmNullTextToSpeech> (4162) with what it instantiates,
# first on the link line: the tree root src/app/roots_texttospeech.cpp, its rule and its APP_OBJS entry went, measured
# with unit 170's other removals (no scan row moves, the symbol file and the match list byte-identical). The rows
# above match from that TU's object now; the text above describes them as the root's.
$(ROOT)/$(APP)/237-uenux2-itexttospeech-roots.o: $(ROOT)/src/units/237-uenux2-itexttospeech-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/237-uenux2-itexttospeech.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(call uenux2_cxxflags,src/app/vota/eleitor/cinstrucaovotacaoacessibilidade.cpp) -c src/units/237-uenux2-itexttospeech-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/237-uenux2-itexttospeech-roots.o
