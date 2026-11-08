# uenux2 comum::CGeracaoVersoesContratos (app/comum/gravadores/cgeracaoversoescontratos.{h,cpp}, the file the record of
# its GetInst names, cgeracaoversoescontratos.cpp:38), the one file of comum/gravadores built with strict aliasing
# (src/Makefile UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6): ObtemDependencias (target fn 5869) and the
# destructor (fn 5866), matched, with the library instances they bring: of std::set<std::string>, the insert (fn 5868),
# which matches from this object, and the hinted-insert wrapper its copy calls (fn 1163) and the tree's destroy (fn
# 633), which matched from it until objects ahead of it emitted them too: unit 227's cmontadorhash.cpp.o (1163, with
# strict aliasing, src/api) and unit 136's cgravadorhashes.cpp.o (633), linked ahead of it in unit 190's list, give the
# link's copies now; and std::map<std::string, api::CIniSection>'s tree destroy (fn 2859), which the destructor calls,
# from this object. GetInst and the constructor are written and compared with nothing, and the control block GetInst
# builds matches from this object: __on_zero_shared (fn 11636) and __get_deleter (fn 11635) (GetInst, below). Two
# functions that only code of fn 12098 (vota::CGravaResultado::StartState, not written) calls besides the static
# constructors match with the roots' stand-ins: api::CPolySingletonList::has<CGeracaoVersoesContratos> (fn 2860), from
# this object since GetInst instantiates it, and libc++'s std::make_format_args over a std::string and the char array
# "20260601173148" (fn 5870), from unit 227's md/cdependenciascontratos.cpp.o since the md constructors are written
# there, and from the roots object before (Roots, below).
#
# Evidence. fn 5869 is (i32 i32 i32 i32)->(): a std::set<std::string> returned by value, the address of an object it
# reads at +0 (`this`, a reading: Choices), a string and a set. It calls CDependenciasContratos::GetValor (fn 3826) on
# that object plus 0 with the string, splits the value on ',' (fn 1880, CStringUtils::Split, char 44), and for each
# non-empty piece inserts it into the set (fn 5868, the set's __emplace_unique_key_args), tests the result's bool
# against 1, inserts it a second time with the same arguments, recurses with the piece and the set and destroys the
# recursion's result (fn 633); then destroys the pieces, copies the set into the result (fn 1163 per element, at the
# end hint) and destroys the value last. Its one caller besides itself, fn 12098, which stores GetInst's record, builds
# a 48-byte object (it runs the INI loader, fn 5480, on +0 and on +24, and calls fn 3826 on +0 and fn 3825,
# CVersoesContratos::GetValor, on +24) and passes it to 5869 for each name of a list, one set for all.
#
# The destructor, fn 5866 (51 B), destroys the four maps from +36 down, the CIniKey maps (fn 1397) at +36 and +12 and
# the CIniSection maps (fn 2859) at +24 and +0, those of the two api::CIniFile members (fragment 379), and returns. Its
# target callers are 12098, whose code after the push of the singleton deletes the object a std::unique_ptr holds, and
# 11636, __on_zero_shared of std::__shared_ptr_pointer<CGeracaoVersoesContratos*, default_delete<...>, allocator<...>>
# (slot 2 of the vtable ledger/vtables.json gives, address point 1553552, which only 12098 stores: /usr/bin/grep -rlE
# 'i32\.const 1553552($|[^0-9])' build/out/splat/pieces/asm). Both are `if (p) { f5866(p); f136(p); }`: the result
# dropped, then `this` freed. Measured on scratch TUs at this file's rule (llvm-objdump -d), with a std::shared_ptr
# built from a std::unique_ptr and a std::unique_ptr's delete: with the destructor defined out of line in the TU, both
# call the D1, drop its result and free the object, as the target's do; with the implicit destructor __on_zero_shared
# holds the four destroys inlined; with the destructor only declared it frees the D1's result. push<T>'s record for this
# class (cpolysingletonlist.h:129, at 1553528) follows GetInst's (1553504) in the target's data, so the block is code of
# GetInst's TU, this file (a reading), and the destructor is defined here. In the uses-2 band (ledger/ordinals.tsv)
# 5870, 5869, 5868 and 5866 have the ordinals 4337 to 4340, in that link order; 5867 (md/cversoesarquivos.cpp's
# constructor) sits among them by its ordinal, 434, which sorts as text between 4340 and 4339
# (docs/reference/facts/link-order.md L1, items 1 and 8), so it is no neighbour. The destructor follows
# ObtemDependencias and its insert in this object, defined after them (ld_index 5874 to 5876 in
# build/out/wasm-map/vota_web/names.tsv for 5869, 5868 and 5866 when the destructor landed). GetInst, written since at
# line 38 above them, leaves that order (ld_index 5936 to 5938 for 5869, 5868 and 5866 in the link with it), so the
# reading this paragraph gave before (that ObtemDependencias would then go above line 38) does not hold. Why, a
# reading: GetInst names the destructor only through the delete of the std::unique_ptr CPolySingleton<T>::set takes by
# value, a linkonce body clang generates at the end of the TU, after the destructor's definition has taken its place.
# `= default` and `{}` give cmp-equal objects at this file's rule. Step 8 names 5866 and 2859 (pair-addr).
#
# GetInst (record cgeracaoversoescontratos.cpp:38, column 12: the start of CPolySingleton<T>::instance()'s call, whose
# std::source_location default argument the record is) and the constructor are written, unrooted, and compared with
# nothing: their one target caller, fn 12098, holds them inlined and is not written, so wasm-ld drops both (how-to step
# 5, a member right by construction). Read from 12098's code behind its 112-byte stack prologue: has<T> (fn 2860) on
# g_polySingletonsInfo() (the pointer @1526320), and when it is false two path temporaries, CPath::GetPathRoot() /
# "etc/dependencias.properties" and / "etc/versoes.properties", each copied into a std::string, all made before the
# 48-byte allocation; the members' constructors (behind 528-byte prologues: CDependenciasContratos on +0 and
# CVersoesContratos on +24, each the INI loader fn 5480 on the string, then GetValor("tag") against "20260601173148" and
# a throw, the md files' records 27 and 29, not written); CPolySingleton<T>::set behind a 16-byte prologue (has<T>,
# remove<T> through fn 640, push<T> behind a 512-byte prologue, then the delete of its by-value std::unique_ptr, fn
# 5866); the eight temporaries destroyed after it in the reverse of their making (one full-expression, a reading); and
# CPolySingleton<T>::instance with GetInst's record (a 112-byte prologue, then CPolySingletonList::instance<T> behind
# one of 576 bytes). No mutex is taken. Chosen: std::make_unique (a reading: `new` in a std::unique_ptr would allocate
# before the arguments, C++17's sequencing of a new-expression), .string() for each path's copy, the constructor out of
# line in this file with two const std::string& parameters, and the lines above 38.
# The control block. push<T> builds std::__shared_ptr_pointer<CGeracaoVersoesContratos*, std::default_delete<...>,
# std::allocator<...>> from the std::unique_ptr, so this object emits the block, its builder GetInst, which the link
# drops (src/units/README.md "A control block"); with the destructor defined here its __on_zero_shared deletes as the
# target's 11636 does (above). The vtable's address point 1553552 is stored by 12098 alone, and the roots' sink stands
# for that store (Roots). Step 8 names 11636 (pair-addr) and 11635 (content-anchor:
# default_delete<CGeracaoVersoesContratos>'s typeinfo name @495522, which only 11635 loads: /usr/bin/grep -rlE
# 'i32\.const 495522($|[^0-9])' build/out/splat/pieces/asm), and both match; in use band 1 (ledger/ordinals.tsv) they
# lie at ld_index 5941 and 5942, the target's order. Before step 8 they scored 1 over 11 and 1 over 9 rows, each row a
# call's or a data address's operand (pnpm wasm score).
#
# The flag (pnpm wasm score against the target at the default depth, ours from each link's names.tsv):
# - with -fno-strict-aliasing, the rest of comum/gravadores' flag (the link at e5577685): 5869 14 over 211 rows (5
#   inserted: the set's copy calls __emplace_hint_unique_key_args with the result, tree, hint, key and value, where the
#   target calls fn 1163 with tree, hint and value), 5868 10 over 189 (5 inserted, among them the inserted node loaded
#   again through the child pointer after the begin-node store), both no-candidate.
# - with strict aliasing (one variant object in the whole link, docs/reference/facts/workflow.md W13): clang keeps
#   __emplace_hint_unique_extract_key<const std::string&> out of line, the emplace inlined into it (1163's shape), 5868
#   scores 2 over 184, operands only, and 5869 91 over 284: binaryen inlines that wrapper into its one caller in our
#   link. With the roots' stand-in for 1163's other target callers, 5360 and 11620 (each builds a set from an
#   initializer list, two and eight inserts at the end hint), which calls the wrapper through its label: 5869 9 over
#   206, 5868 2 over 184, 1163 2 over 84, every differing row a call's or a data address's operand. That stand-in links
#   only with the flag: without it wasm-ld stops on the wrapper as an undefined symbol.
# - the other twelve top-level files of comum/gravadores built with strict aliasing as well give the same sha256 as
#   this object alone, with the stand-in and without it: so the file is listed, and its directory's other files keep
#   -fno-strict-aliasing, which gravadores/asn/ and gravadores/md/ need (F6). Listing the file is a choice.
# So this file builds with strict aliasing (the user's decision) and the stand-in is in the roots: 1163 and 5868 match.
# Of the two callers the stand-in stands for, 5360 (unit 227's) is in the link and calls 1163 twice; 11620 (unit 136's)
# is in the link but its set is cpath.cpp's code, built without strict aliasing, which calls the emplace instead (unit
# 190's fragment), so the stand-in stays for 11620.
# 5869's name. The body calls itself, and its other target caller, 12098, is not written, so no call vote reaches the
# name; the census pairs it at shape, which names nothing. Without a name it read unresolved at its recursive call
# (`ours +0x82 call ...: has no target function`), at 9 over 206 rows, every differing row a call's or a data address's
# operand. Its line below the hand-edit marker of splat/symbol_addrs.txt is `pair-depth0`: its depth-0 fingerprint, addr
# and shape hashes are one function's on each side (pnpm wasm fingerprint <wasm> --depth 0); at depths 1 and 2 the
# fingerprint and addr hashes part through three matched callees whose depth-0 hashes differ between the links (3826,
# 1880 and 136), and the shape hash is the same. Weighed by removal (docs/reference/splat.md "Reviewing a match": two
# scans without the line and 5869's match line, beside a control without the match line, then splat-build on each): 5869
# alone leaves match, to unresolved, and both copies build to the target's sha256 (12908 and 12909 matches).
#
# 2281, std::set<std::string>'s __emplace_hint_unique_key_args<std::string, const std::string&> (target callers 1248
# and 5309, RHVoice's, and 12098), matched from this object while it built without strict aliasing: there clang keeps
# it out of line, and this object links ahead of RHVoice's language.cpp, whose copy scores 26 over 107 rows against it
# (its frame 32 bytes where the target's is 16). With strict aliasing this object defines no 2281, and through steps 6
# to 10 with the flag 2281 and RHVoice's property<std::set<std::string>> constructor (5309), which calls it twice, leave
# match. So the target's copy reads as a uenux2 object's built without strict aliasing, not this file's (a reading;
# which object is not known). Two places were measured for such a copy, each the instance a set's hinted insert gives
# at UENUX2_CXXFLAGS: in src/app/roots_cbasetype.cpp it also gives __tree_balance_after_insert (152) ahead of
# roots_rhvoice.o's, and 152 then differs from the target and 447 (RHVoice::str::less) reads unresolved, self-voted
# (steps 6 to 10); in a tree root linked after roots_boost.o 152 stays roots_rhvoice.o's, and 1163, 2281, 5309 and 5868
# match with no match lost (steps 6 to 9 on a private link, with APP_OBJS on the make line, and splat-build). That root
# is src/app/roots_set.cpp, last in APP_OBJS, whose comment says what it stands for and when it goes; built in place,
# steps 6 to 10 with it and the flag turn 1163 and 5868 match and lose none, 11542 to 11544 matches. That instance went
# once cpath.cpp's object (unit 190's, without strict aliasing), whose set's inserts call 2281's body out of line, gave
# the copy: 2281 matches from it, and a link without the root's instance keeps every row.
#
# Choices. The class's members, their names and access, ObtemDependencias's name and its parameters' names are chosen;
# its being a member is a reading (it reads the object's +0, and 12098 passes it the singleton). Its line and the
# destructor's, after GetInst's record line, are choices, and so are the destructor's `= default` (`{}` gives the same
# object) and its declaration first in the class. The value is a named const local and the second insert repeats
# `insert`; one form of each was measured. GetInst's and the constructor's choices are above (GetInst). The stand-in
# for 1163's callers (two calls through its label),
# roots_set.cpp's set instance (an uncalled insert at the end hint) and its name were choices; one form of each was
# measured.
# The root's place is measured as far as it goes: ahead of roots_rhvoice.o 152 differs and 447 reads unresolved
# (above), so it links after it; that it is last, after roots_boost.o too, is the choice.
#
# Roots (268-uenux2-cgeracaoversoescontratos-roots.cpp, at APP_CXXFLAGS; the object compiled at uenux2's -O3 -std=c++23,
# with strict aliasing and without it, is cmp-equal to it): w268_dependencias stands for 12098's call of 5869,
# w268_conjunto for 1163's caller 11620 (above), w268_destroi for 5866's caller 12098 (its other caller, 11636, is in
# the link: its call there went), w268_tem for 2860's callers 12098 (which calls it three times) and 14478
# (__wasm_call_ctors: a static initializer of a TU not written calls it and drops the result), and w268_formata for
# 5870's one caller, 12098, which calls it twice; each calls once per caller it stands for, twice for 5870. The sink
# w268_sink_contratos[3] holds the control block's vtable for 12098, the one target function that stores its address
# point (GetInst, above): it goes when 12098 is in the link. 2860 matches from this object, the first of ours with an
# instance since GetInst is written (has<T> is api/pattern/cpolysingletonlist.h's template, unit 100's, whose target
# copy reads as GetInst's TU's, this file's: a reading, 12098 holding GetInst's three calls); it matched from the roots
# object before, at APP_CXXFLAGS, and both copies give the target's body. 5870 matched from the roots object while no
# object of ours ahead of it instantiated it, and matches from md/cdependenciascontratos.cpp.o (unit 227's list) since
# the md constructors are written there, unrooted (the same symbol; the stand-in stays for 12098's two calls).
# make_format_args is libc++'s, whose
# two target call sites hold the messages of the throws whose records are md/cdependenciascontratos.cpp:27 and
# md/cversoescontratos.cpp:29, the two md classes' constructors, which 12098 holds behind prologues of their own; its
# ordinal, 4337, just before 5869's, and that file's records, first of the contract files' in the data, read as
# md/cdependenciascontratos.cpp's copy (a reading). Its body holds the array's address, which dead-argument elimination
# folded: the stand-in passes one literal of the same bytes from both calls, and [[clang::noinline]] keeps them (without
# it clang inlines both and the object defines no make_format_args). Step 8 names 2860 by a content-anchor, the class's
# typeinfo name, whose target holders are 2860 and 12098 (/usr/bin/grep -rlE 'i32\.const 495375($|[^0-9])'
# build/out/splat/pieces/asm), 12098 not in our link; 5870 has no symbol line, and step 9 matched it on the census's
# shape pair (source `ledger` in its first scan): its target caller is 12098 alone, its body loads "20260601173148"
# (341442), which only it and 12098 load, and its band neighbour 5869 is this unit's.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
W268_SRCS := src/app/comum/gravadores/cgeracaoversoescontratos.cpp
UENUX2_SRCS += $(W268_SRCS)
# The target callers not reconstructed (fn 12098 above all; 14478 and 11620 too) have stand-ins in
# 268-uenux2-cgeracaoversoescontratos-roots.cpp (Roots, above)
W268_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/268-uenux2-cgeracaoversoescontratos-roots.o: $(ROOT)/src/units/268-uenux2-cgeracaoversoescontratos-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/268-uenux2-cgeracaoversoescontratos.mk $(W268_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/268-uenux2-cgeracaoversoescontratos-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/268-uenux2-cgeracaoversoescontratos-roots.o
