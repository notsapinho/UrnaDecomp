# uenux2 comum::CGeracaoVersoesContratos (app/comum/gravadores/cgeracaoversoescontratos.{h,cpp}, the file the record of
# its GetInst names, cgeracaoversoescontratos.cpp:38), the one file of comum/gravadores built with strict aliasing
# (src/Makefile UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6): ObtemDependencias (target fn 5869), written
# and not matched, and the std::set<std::string> instances it brings, of which the insert (fn 5868) matches from this
# object, and the hinted-insert wrapper its copy calls (fn 1163) and the tree's destroy (fn 633) matched from it until
# objects ahead of it emitted them too: unit 227's cmontadorhash.cpp.o (1163, with strict aliasing, src/api) and unit
# 136's cgravadorhashes.cpp.o (633), linked ahead of it in unit 190's list, give the link's copies now.
#
# Evidence. fn 5869 is (i32 i32 i32 i32)->(): a std::set<std::string> returned by value, the address of an object it
# reads at +0 (`this`, a reading: Choices), a string and a set. It calls CDependenciasContratos::GetValor (fn 3826) on
# that object plus 0 with the string, splits the value on ',' (fn 1880, CStringUtils::Split, char 44), and for each
# non-empty piece inserts it into the set (fn 5868, the set's __emplace_unique_key_args), tests the result's bool
# against 1, inserts it a second time with the same arguments, recurses with the piece and the set and destroys the
# recursion's result (fn 633); then destroys the pieces, copies the set into the result (fn 1163 per element, at the
# end hint) and destroys the value last. Its one caller besides itself, fn 12098, which stores GetInst's record, builds
# a 48-byte object (it runs the INI loader, fn 5480, on +0 and on +24, and calls fn 3826 on +0 and fn 3825,
# CVersoesContratos::GetValor, on +24) and passes it to 5869 for each name of a list, one set for all. In the uses-2
# band 5869 and 5868 lie between ccopiadormr.cpp's rows and md/cversoesarquivos.cpp's (fn 5867).
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
# 5869 reads unresolved, at its recursive call (`ours +0x82 call 5687: ... has no target function`): the census pairs it
# at shape, which names nothing, and its other caller, 12098, is not in the link. It waits for 12098 (its call names
# 5869) or a census pair that names it; in this link it scores 9 over 206 rows, every differing row a call's or a data
# address's operand.
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
# steps 6 to 10 with it and the flag turn 1163 and 5868 match and lose none, 11542 to 11544 matches.
#
# Choices. The class's members, their names and access, ObtemDependencias's name and its parameters' names are chosen;
# its being a member is a reading (it reads the object's +0, and 12098 passes it the singleton). Its line, after
# GetInst's record line, is a choice. The value is a named const local and the second insert repeats `insert`; one form
# of each was measured. GetInst and the constructor are not written: they wait for 12098 (the INI loader, fn 5480, is
# written in fragment 379, not matched). Nor is the destructor (fn 5866, a function of its own in the target, called by
# 12098 and fn 11636): its band place follows md/cversoesarquivos.cpp's rows, not this file's. A
# std::shared_ptr<CGeracaoVersoesContratos> built from a std::unique_ptr, the target's block
# (__shared_ptr_pointer<CGeracaoVersoesContratos*, default_delete<...>, ...>, vtable @1553544, whose vptr fn 12098 alone
# stores, its __on_zero_shared fn 11636), compiled at uenux2's -O3, with strict aliasing or without, inlines the
# implicit destructor into __on_zero_shared (four tree destroys and the delete), where the target's 11636 calls 5866:
# the block's TU did not see the destructor's body, or was built at another level (a reading). The stand-in for 1163's
# callers (two calls through its label), roots_set.cpp's body (an uncalled insert at the end hint) and its name are
# choices; one form of each was measured. The root's place is measured as far as it goes: ahead of roots_rhvoice.o 152
# differs and 447 reads unresolved (above), so it links after it; that it is last, after roots_boost.o too, is the
# choice.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
W268_SRCS := src/app/comum/gravadores/cgeracaoversoescontratos.cpp
UENUX2_SRCS += $(W268_SRCS)
# ObtemDependencias's one target caller besides itself, fn 12098, and fn 1163's callers 5360 and 11620 are not
# reconstructed: 268-uenux2-cgeracaoversoescontratos-roots.cpp stands for them
W268_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/268-uenux2-cgeracaoversoescontratos-roots.o: $(ROOT)/src/units/268-uenux2-cgeracaoversoescontratos-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/268-uenux2-cgeracaoversoescontratos.mk $(W268_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/268-uenux2-cgeracaoversoescontratos-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/268-uenux2-cgeracaoversoescontratos-roots.o
