# uenux2 api::BatteryIconDataSource<Horizontal> and <Vertical> (src/api/gui/cpowerinformation.{h,cpp}): the constructor
# and UpdateBatteryIcon, in cpowerinformation.cpp, where their records are (119:16 and 131:24), with the map of icons they
# read, and the destructors, which the class definition gives. The target functions:
#   D2 of <Horizontal> 5510 and of <Vertical> 3837   thunks into fn 6049, passing their vptr
#   D2 body                                          6049, binaryen's merge of the two D2s (byn$mgfn-shared)
#   D0 of <Horizontal> 10990 and of <Vertical> 11652 f136(D2(p0))
#   the constructor                                  no function of its own: inlined into fns 502 and 5904 (unit 153)
#   the lambda's std::function, <Horizontal>         10979 to 10982, 10984 (operator() 10981 holds UpdateBatteryIcon)
#   the lambda's std::function, <Vertical>           10985 to 10989 (operator() 10987 holds UpdateBatteryIcon)
#   the map's icons                                  CriaIcones 1263, CarregaIcones 2773 (written, differs, below)
#   the map's static destructor and tree             10991, and __tree::destroy 2238
#   IPower::GetEstadoBateria                         2774 (api/hwil/ipower.h)
# and api::IObservable<std::shared_ptr<api::IImage>>'s D2 and D0 (11651, 11650), which the D2s' vptr store brings and
# which unit 134 matched from a stand-in until now (src/units/134-uenux2-iobservable.mk). <Vertical>'s D2, D0 and vtable
# link from cinfomtlcd.cpp.o (unit 153) and <Horizontal>'s from cpowerinformation.cpp.o, both at UENUX2_CXXFLAGS.
#
# The class's layout and members are in its header, with what gives each. The destructor's form is measured: a probe of
# the roots' shape (an optnone function that calls both destructors) compiled with the destructor written five ways in an
# -iquote overlay of the header, at UENUX2_CXXFLAGS, and its functions compared (call and global indices masked).
# `~BatteryIconDataSource() override {}`, `override = default` and `virtual ~BatteryIconDataSource() {}` give the same
# object, with a D0 that passes the D2's result to operator delete;
# the implicit destructor and `inline ... override {}` give a D0 that holds the D2's body; a definition after the class
# in the header gives the same object as `{}` in it. Under an explicit instantiation of both classes, the D0 calls the
# D2, drops its result and frees this, the out-of-line shape (docs/reference/facts/reading.md R5), which the target's
# 10990 and 11652 are not, whether the destructor is defined in cpowerinformation.cpp or `{}` in the class: what the
# bytes rule out is an explicit instantiation in the file whose copy the link kept. The evidence for a definition in
# the header is the data: BatteryIconDataSource<Vertical>'s vtable sits in cinfomtlcd.cpp's data, so that file saw it.
# cpowerinformation.cpp instantiates the two constructors explicitly, members only (the records put their bodies in
# that file, and fns 502 and 5904, in other files, hold them), and 10990, its D0 of <Horizontal>, still matches.
#
# What the bodies give, read from 5904, 10981 and 10987 and measured in the whole link (pnpm wasm score: 5904 15 over 301
# rows, 10981 and 10987 9 over 202 each, all operand-only, before steps 7 to 9):
# - the constructor builds m_timer and m_estado in its list (CreateTimer's result is written in place at +48, as a
#   member initializer gives; a reading), then copies the icon into the value under the mutex and starts the timer
#   after the unlock and after the copy's release, which the scope written gives; it notifies no observer (no loop over
#   the vector, which UpdateBatteryIcon has);
# - UpdateBatteryIcon returns when the state is the same, else stores it and calls IObservable::SetValor;
# - the icon lookup (if the map is empty, CarregaIcones; then find, and the orientation's element of the vector or an
#   empty pointer) is inlined at all four sites; GetIcone is `inline`: without it clang keeps it a function of its own
#   (the object's symbols), and binaryen does not inline a function with four callers. CarregaIcones is external: as a
#   file-static function, clang inlined it into its one caller in the object, where the target keeps it (2773, with
#   four callers once the lookup is inlined);
# - CarregaIcones assigns the map from an initializer list of ten pairs (map::operator=, libc++'s __assign_unique: the
#   node reuse and the vector's assign are 2773's), keys 0 to 9 with a horizontal and a vertical path each, in the
#   order of the target's literals; CriaIcones (1263) is a two-element vector of make_shared<CFixedImage>.
# - s_icones is a namespace-scope std::map: its static destructor is 10991, which calls 2238 on its address (1839232),
#   and its readers are 2773, 5904, 10981 and 10987. Its name in the symbol file is a vote (vote:14 by 5904, 10981,
#   10987, 10991); the other readers of the address and the destructor are what ties it to the object.
# Chosen: the names of CriaIcones, CarregaIcones, GetIcone, s_icones and their parameters and locals, the anonymous
# namespace for CriaIcones, GetIcone and s_icones, every line's place but the two records'.
#
# Written and not matching (docs/how-to-decompile.md step 5): CarregaIcones (2773), 863 over 2704 rows (pnpm wasm score,
# the whole link). Its body holds std::vector<std::shared_ptr<IImage>>::__assign_with_size inlined, where the target
# calls fn 3668, a body RHVoice's fn 1245 (no-candidate in our link) also calls, twice: that reads as the target's merge
# of this instantiation with RHVoice's vector<shared_ptr<userdict::correction>> one, which kept the body a function of
# its own. In our link that RHVoice copy (ours 4262) differs from 3668 (102 over 414 rows), so nothing merges with ours,
# which has one caller and is inlined (ours is 6489 B, the target's 5642 B). What it waits for is a reading, not
# measured: a copy binaryen merges with ours, so that ours keeps a body of its own, and that body being 3668's.
#
# The roots file stands for fn 502, which builds <Horizontal> and is not written (cformbuilder.cpp); its header says how.
CPOWERINFORMATION_SRCS := src/api/gui/cpowerinformation.cpp
UENUX2_SRCS += $(CPOWERINFORMATION_SRCS)
W164_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/164-uenux2-cpowerinformation-roots.o: $(ROOT)/src/units/164-uenux2-cpowerinformation-roots.cpp $(ROOT)/src/units/164-uenux2-cpowerinformation.mk $(ROOT)/src/Makefile $(W164_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/164-uenux2-cpowerinformation-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/164-uenux2-cpowerinformation-roots.o
