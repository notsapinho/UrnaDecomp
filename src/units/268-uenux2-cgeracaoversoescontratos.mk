# uenux2 comum::CGeracaoVersoesContratos (app/comum/gravadores/cgeracaoversoescontratos.{h,cpp}, the file the record of
# its GetInst names, cgeracaoversoescontratos.cpp:38): ObtemDependencias (target fn 5869), written and not matched, and
# the std::set<std::string> instances it brings, of which the hinted insert (fn 2281) matches.
#
# Evidence. fn 5869 is (i32 i32 i32 i32)->(): a std::set<std::string> returned by value, `this`, a string and a set. It
# calls CDependenciasContratos::GetValor (fn 3826) on `this` plus 0 with the string, splits the value on ',' (fn 1880,
# CStringUtils::Split, char 44), and for each non-empty piece inserts it into the set (fn 5868, the set's
# __emplace_unique_key_args), tests the result's bool against 1, inserts it a second time with the same arguments,
# recurses with the piece and the set and destroys the recursion's result (fn 633); then destroys the pieces, copies the
# set into the result (fn 1163 per element, at the end hint) and destroys the value last. Its one caller besides itself,
# fn 12098, which stores GetInst's record, builds a 48-byte object (it runs the INI loader, fn 5480, on +0 and on +24,
# and calls fn 3826 on +0 and fn 3825, CVersoesContratos::GetValor, on +24) and passes it to 5869 for each name of a
# list, one set for all. In the uses-2 band 5869 and 5868 lie between ccopiadormr.cpp's rows and
# md/cversoesarquivos.cpp's (fn 5867).
#
# What it waits for (pnpm wasm score against the target at the default depth, ours from each link's names.tsv):
# - in this link (comum/gravadores builds with -fno-strict-aliasing, docs/reference/facts/app-flags.md F6): 5869 14 over
#   211 rows (5 inserted: the set's copy calls __emplace_hint_unique_key_args with the result, tree, hint, key and
#   value, where the target calls fn 1163 with tree, hint and value), 5868 10 over 189 (5 inserted, among them the
#   inserted node loaded again through the child pointer after the begin-node store). The census pairs neither and
#   nothing names them, so both rows read no-candidate.
# - this object built with strict aliasing (one variant object in the whole link, docs/reference/facts/workflow.md W13):
#   clang keeps __emplace_hint_unique_extract_key<const std::string&> out of line, the emplace inlined into it (1163's
#   shape), 5868 scores 2 over 184, operands only, and 5869 91 over 284: binaryen inlines that wrapper into its one
#   caller in our link. With a stand-in for 1163's other target callers, 5360 and 11620 (each builds a set from an
#   initializer list, two and eight inserts at the end hint), calling the wrapper through its label: 5869 9 over 206,
#   5868 2 over 184, 1163 2 over 84, every differing row a call's or a data address's operand. That stand-in links only
#   with the flag: at this flag set wasm-ld stops on the wrapper as an undefined symbol. Through steps 6 to 10 with the
#   flag on this file alone (UENUX2_TBAA_DIRS given on the make line) and that stand-in, 1163 and 5868 match, 5869 reads
#   unresolved at its recursive call (the census pairs it at shape, which names nothing, and its other caller, 12098, is
#   not in the link), and 2281 and 5309 leave match (below).
# - the other twelve top-level files of comum/gravadores built with strict aliasing as well give the same sha256 as this
#   object alone, with the stand-in and without it.
# So the three wait for strict aliasing on this file, a flag decision that is the user's, with the label stand-in, and
# 5869 for its caller 12098 too.
#
# 2281, std::set<std::string>'s __emplace_hint_unique_key_args<std::string, const std::string&> (target callers 1248 and
# 5309, RHVoice's, and 12098), matches from this object: at this flag set clang keeps it out of line here, and this
# object links ahead of RHVoice's language.cpp, whose copy our link kept before and which scores 26 over 107 rows
# against it (its frame 32 bytes where the target's is 16). So the target's copy reads as a uenux2 object's built
# without strict aliasing (a reading; which object is not known). RHVoice's property<std::set<std::string>> constructor
# (5309) calls it twice and matches with it: the body is RHVoice's, released by this unit. With strict aliasing on this
# file this object no longer defines 2281, and both rows then need another copy ahead of RHVoice's (a reading). Two were
# measured, each the instance a set's hinted insert gives at the tree's flags without strict aliasing: in
# roots_cbasetype.cpp it also gives __tree_balance_after_insert (152) ahead of roots_rhvoice.o's, and 152 then differs
# from the target and 447 (RHVoice::str::less) reads unresolved, self-voted (steps 6 to 10); in an object linked after
# roots_boost.o 152 stays, and a scan of that link with this unit's symbol file, its match list and 1163's and 5868's
# lines matches 1163, 2281, 5309 and 5868 and loses no match (docs/reference/facts/workflow.md W13, "Scan a variant with
# the committed symbol file"; no census).
#
# Choices. The class's members, their names and access, ObtemDependencias's name and its parameters' names are chosen;
# its being a member is a reading (it reads the object's +0, and 12098 passes it the singleton). Its line, after
# GetInst's record line, is a choice. The value is a named const local and the second insert repeats `insert`; one form
# of each was measured. GetInst and the constructor are not written: they wait for 12098 and the INI loader (fn 5480).
# Nor is the destructor (fn 5866, a function of its own in the target, called by 12098 and fn 11636): its band place
# follows md/cversoesarquivos.cpp's rows, not this file's.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
W268_SRCS := src/app/comum/gravadores/cgeracaoversoescontratos.cpp
UENUX2_SRCS += $(W268_SRCS)
# ObtemDependencias's one target caller besides itself, fn 12098, is not reconstructed:
# 268-uenux2-cgeracaoversoescontratos-roots.cpp stands for it
W268_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/268-uenux2-cgeracaoversoescontratos-roots.o: $(ROOT)/src/units/268-uenux2-cgeracaoversoescontratos-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/268-uenux2-cgeracaoversoescontratos.mk $(W268_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/268-uenux2-cgeracaoversoescontratos-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/268-uenux2-cgeracaoversoescontratos-roots.o
