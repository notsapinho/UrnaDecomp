# uenux2 api::SRect's out-of-line members in src/uenux2/src/api/gui/primitives.cpp; paths relative to src/uenux2.
#   1915 Move(const SPoint&)         callers 2770, 2783, 10895, 10970, 10976
#   1916 Union(const SRect&) const   callers 1693, 7787, 10896, 10925, 10929
#   MoveX(TPosition)                 no target function of its own: binaryen inlined it into its one caller, fn 10956
# The file is the records' (SRect::Left, Top, Right and Bottom, lines 20, 26, 32 and 38, col 37, in fns 5488, 5537, 5487).
# None of the three written here has a record, so their being in this file, and their lines below Bottom's 38, are a
# choice. Union comes before Move as the band has them: a higher target index, a lower ld_index (how-to step 3). What supports it: in the uses-6
# band of ledger/ordinals.tsv fns 1916 and 1915 lie between fn 1918 (ctextfield.cpp) and fn 1914 (cdirreader.cpp), where a
# file of api/gui/ named primitives sorts. The setters are not written: they throw api::EUeAssertError through fn 463, a
# macro behind `Assert (r >= left)` at col 37 that no header holds, and their callers 5537 and 10977 are not written.
#
# Evidence. Each caller passes its point by address with no copy, and a by-value SPoint gives Move's own 32 rows but keeps
# a stack copy in the callers: 10976 scored 22 over 65 with it, so the parameter is `const SPoint&`. x is read once and y
# after the first store, so both are locals. MoveX is out of line because fn 10956 reads `left` back from memory right
# after storing the whole rectangle, which binaryen inlining a function gives and clang does not (facts/reading.md R10):
# written in place, Rect's object differs in 43 lines. It has one caller, so it stays unrooted. In Union the two reads of
# the right edge are locals, the other's first: it is the one form tried whose compare is the target's.
#
# Chosen, no evidence gives them. The three names; SRect::Normalized, its name, and its being a static member: the target
# has the same min and max at every site, which a constructor of the original would give, and SRect stays an aggregate
# here because the landed bodies brace-initialize it with values already in order.
#
# Same object code, by the function's disassembly with the object-local numbers masked: Move with the old top in a local,
# `top` stored before `left` and `bottom` last. Other bytes: Move through a local size (18 lines); Union with
# `outro.right < right ? right : outro.right` (2 lines), which has the load order and not the compare, and with
# std::max(right, outro.right) (6 lines).
#
# std::operator+(string&&, string&&) (fn 252) stays matched through a stand-in in src/app/roots_uenux2.cpp, whose comment
# says why: the first real callers of CPolySingleton<T>::instance came with these fields, and each instantiates it.
UENUX2_SRCS += src/api/gui/primitives.cpp
# a second call site of Union (108-uenux2-api-gui-primitives-roots.cpp), which binaryen would inline into its one caller
$(ROOT)/$(APP)/108-uenux2-api-gui-primitives-roots.o: $(ROOT)/src/units/108-uenux2-api-gui-primitives-roots.cpp $(ROOT)/src/units/108-uenux2-api-gui-primitives.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/108-uenux2-api-gui-primitives-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/108-uenux2-api-gui-primitives-roots.o
