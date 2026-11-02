# uenux2: api::ITextToSpeech's Synthesize (target fn 11530, slot 0) and what it calls: the options, the key, the lookup
# and the store of the recent-audio cache and the kept map, written inline in src/uenux2/src/api/audio/itexttospeech.h
# (unit 82's header, whose comment has the evidence of each member). No source of its own: the target's copies are the
# executable TU's, and the tree root src/app/roots_texttospeech.cpp emits them at that TU's rule, VOTA_WEB_CXXFLAGS
# (its rule and its APP_OBJS entry are src/Makefile's; its comment says whose copies and why there). This file holds the
# evidence, the measurements and the rule of 237-uenux2-itexttospeech-roots.cpp, the stand-ins.
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
# Stand-ins, 237-uenux2-itexttospeech-roots.cpp, at APP_CXXFLAGS (it calls through __asm__ labels and includes nothing):
# w237_guarda for fn 921 (5685's other direct caller), and w237_par for fn 3552 (the one reader of 1928's result) until
# unit 229's root brought 3552. Measured on a variant link without them: 11447 372 over 394 (367 inserted: 5685 inlined
# into it), and a drop deleted in each of 11436 (two), 3722, 3746 and 5720; with them every one is operand-only.
# w237_guarda goes when 921 is in the link. w237_par went with 3552 in the link (from unit 229's root, which reads 1928's
# result): a link without it moves no row (unit 229's fragment).
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
#   3281 and 5417, ours 3618 and 5423).
# - 9650, 9831, 9897 and 10307 (main): `unresolved` on table slots of set<T> bodies that have no target name; 640 on
#   unlock_shared_and_lock's; 9372 on a table slot of ours whose function the target's table does not hold.
#   Since then 9372 matches (fragment 241), and 9650, 9831, 9897, 10307 and 640 with unit 170's has<T> roots and unit
#   100's guard parameter of unlock_shared_and_lock; the push bodies' frame slot is no form of push but the order in
#   which the executable TU emits its format code (unit 170's fragment), and 8834's first call matches (5417).
# - 2650 called the body matched as 424 (named after a twin with no result, boost's
#   ~shared_ptr<basic_regex_implementation> of ecourna's cstringutils.cpp.o) where the target calls 388, read as waiting
#   for a copy of ~shared_ptr<ASN1::IAbstractVisitor> with 388's body ahead of the runtime: it matches since unit 229's
#   root emits that copy.
# - 921 (above) and 13877 (unit 82's fragment) are not written; 3552 matches from unit 229's root, and 1928's line names
#   that root's pair<string, shared_ptr<IAbstractVisitor>> copy now, the same body, which links ahead of this one's.
$(ROOT)/$(APP)/237-uenux2-itexttospeech-roots.o: $(ROOT)/src/units/237-uenux2-itexttospeech-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/237-uenux2-itexttospeech.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/237-uenux2-itexttospeech-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/237-uenux2-itexttospeech-roots.o
