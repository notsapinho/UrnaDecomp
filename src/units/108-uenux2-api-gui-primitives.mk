# uenux2 api::SRect's out-of-line members in src/uenux2/src/api/gui/primitives.cpp; paths relative to src/uenux2.
#   5488 Left(TPosition), 5487 Right(TPosition)   records 20:37 and 32:37; callers 5537 and 10977
#   1915 Move(const SPoint&)         callers 2770, 2783, 10895, 10970, 10976
#   1916 Union(const SRect&) const   callers 1693, 7787, 10896, 10925, 10929
#   2768 Adjust(TPosition x4) const  callers 2770, 5545, 7787, 10977
#   MoveX(TPosition)                 no target function of its own: binaryen inlined it into its one caller, fn 10956
# The file is the records' (SRect::Left, Top, Right and Bottom, lines 20, 26, 32 and 38, col 37, in fns 5488, 5537, 5487).
# Top and Bottom ("Assert (bottom >= t)", code 3401; "Assert (b >= top)", 3403) have no target function of their own:
# binaryen inlined each into its one caller, fn 5537 (CFramedText::DrawChar, unit 92's, written and not matched), behind a
# second stack prologue, and our link does the same; they stay unrooted. The setters throw api::CUeAssertError (api/util/eueasserterror.h, new, its path chosen) through its constructor, fn 463, by
# the ASSERT macro there: the record's column 37 is the invocation's closing parenthesis, and the message is the
# condition the macro stringizes ("Assert (right >= l)", code 3400; "Assert (r >= left)", 3402), which also gives the
# parameters' names. None of the four others written here has a record, so their being in this file, and their lines below
# Bottom's 38, are a choice. Union comes before Move as the band has them: a higher target index, a lower ld_index (how-to
# step 3). What supports it: in the uses-6 band of ledger/ordinals.tsv fns 1916 and 1915 lie between fn 1918
# (ctextfield.cpp) and fn 1914 (cdirreader.cpp), where a file of api/gui/ named primitives sorts. Adjust (2768) lies in the
# uses-4 band after 2770, cinputmenufield.cpp's, and before 2767, api/io/cencryptedfile.cpp's, and the uses-2 band has
# cinputmenufield.cpp's 5491 to 5489 just before Left and Right: so primitives.cpp follows cinputmenufield.cpp in the link,
# and Adjust fits here, a choice. Its body adds each amount to its edge and normalizes, Normalized's code (byte-exact in
# the plain link).
#
# Evidence. Each caller passes its point by address with no copy, and a by-value SPoint gives Move's own 32 rows but keeps
# a stack copy in the callers: 10976 scored 22 over 65 with it, so the parameter is `const SPoint&`. x is read once and y
# after the first store, so both are locals. MoveX is out of line because fn 10956 reads `left` back from memory right
# after storing the whole rectangle, which binaryen inlining a function gives and clang does not (facts/reading.md R10):
# written in place, Rect's object differs in 43 lines. It has one caller, so it stays unrooted. In Union the two reads of
# the right edge are locals, the other's first: it is the one form tried whose compare is the target's.
#
# Chosen, no evidence gives them. The names of Move, Union, MoveX and Adjust; SRect::Normalized, its name, and its being a static member: the target
# has the same min and max at every site, which a constructor of the original would give, and SRect stays an aggregate
# here because the landed bodies brace-initialize it with values already in order.
#
# Same object code, by the function's disassembly with the object-local numbers masked: Move with the old top in a local,
# `top` stored before `left` and `bottom` last. Other bytes: Move through a local size (18 lines); Union with
# `outro.right < right ? right : outro.right` (2 lines), which has the load order and not the compare, and with
# std::max(right, outro.right) (6 lines).
#
# std::operator+(string&&, string&&) (fn 252), which the first real callers of CPolySingleton<T>::instance brought with
# these fields, matches from the executable TU's object (unit 170), first on the link line at -Oz;
# src/app/roots_uenux2.cpp held it until that unit.
UENUX2_SRCS += src/api/gui/primitives.cpp
# second call sites of Union, Left, Right and Adjust (108-uenux2-api-gui-primitives-roots.cpp says for which callers)
$(ROOT)/$(APP)/108-uenux2-api-gui-primitives-roots.o: $(ROOT)/src/units/108-uenux2-api-gui-primitives-roots.cpp $(ROOT)/src/units/108-uenux2-api-gui-primitives.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/108-uenux2-api-gui-primitives-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/108-uenux2-api-gui-primitives-roots.o
