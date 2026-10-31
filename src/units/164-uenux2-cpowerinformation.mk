# uenux2 api::BatteryIconDataSource<Horizontal> and <Vertical>'s destructors (src/api/gui/cpowerinformation.h). No source of
# its own (src/units/README.md "What a fragment holds" item 2): every function the unit matches is code the compiler
# writes from the class definition, emitted by the roots object, whose header says how. The target functions:
#   D2 of <Horizontal> 5510 and of <Vertical> 3837   thunks into fn 6049, passing their vptr
#   D2 body                                          6049, binaryen's merge of the two D2s (byn$mgfn-shared)
#   D0 of <Horizontal> 10990 and of <Vertical> 11652 f136(D2(p0))
# and api::IObservable<std::shared_ptr<api::IImage>>'s D2 and D0 (11651, 11650), which the D2s' vptr store brings and
# which unit 134 matched from a stand-in until now (src/units/134-uenux2-iobservable.mk).
#
# The class's layout and members are in its header, with what gives each. The destructor's form is measured: a probe of
# the roots' shape (an optnone function that calls both destructors) compiled with the destructor written five ways in an
# -iquote overlay of the header, at UENUX2_CXXFLAGS, and its functions compared (call and global indices masked).
# `~BatteryIconDataSource() override {}`, `override = default` and `virtual ~BatteryIconDataSource() {}` give the same
# object, with a D0 that passes the D2's result to operator delete;
# the implicit destructor and `inline ... override {}` give a D0 that holds the D2's body. Declared in the class and
# defined in cpowerinformation.cpp under an explicit instantiation of both classes, the D0 calls the D2, drops its result
# and frees this, the out-of-line shape (docs/reference/facts/reading.md R5), which the target's 10990 and 11652 are not.
#
# Pending, with what each waits for (cpowerinformation.cpp stays a stub file):
# - the constructor (record cpowerinformation.cpp 119:16, inlined into fns 502 and 5904) and UpdateBatteryIcon (record
#   131:24, inlined into the lambda's operator(), fns 10981 and 10987, slot 6 of the two std::__function::__func
#   vtables; their other slots, 10979, 10980, 10982, 10984, 10985, 10986, 10988 and 10989, come with them): they call
#   fn 2773, which fills a std::map of ten keys, 0 to 9, each with a pair of icons it builds through fn 1263,
#   std::make_shared<CFixedImage> of a path, whose constructor CFixedImage(const std::string&), fn 2246, is not written;
#   and fn 2774, the state read from IPower.
# - 2773, 2774, 1263, and 2238 and 10991, which destroy the map's tree (10991 calls 2238 on the map's address, 1839232):
#   no caller here until the constructor lands.
W164_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/164-uenux2-cpowerinformation-roots.o: $(ROOT)/src/units/164-uenux2-cpowerinformation-roots.cpp $(ROOT)/src/units/164-uenux2-cpowerinformation.mk $(ROOT)/src/Makefile $(W164_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/164-uenux2-cpowerinformation-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/164-uenux2-cpowerinformation-roots.o
