# uenux2 api::CMovieField::~CMovieField: the base-object destructor (target fn 5524, slot 0 of the vtable @1579432) and
# the deleting one (fn 11065, slot 1), with Hide (fn 11060, slot 4), in src/uenux2/src/api/gui/cmoviefield.cpp, the
# file the class's one record names (cmoviefield.cpp:53:12, Rect). The destructor is user-declared and defined out of
# line (the D0 calls the D2 and drops its result: an implicit or in-class destructor gives another D0), declared first
# among the class's virtual members, so it is the key function and cmoviefield.o emits the vtable, the D2 and the D0.
# Its body calls Hide, which clang inlines: the D2 stops the timer and clears +40 before the members go. No record
# falls in the destructor or Hide: their lines are a choice, in the target's order (the uses-1 band 11059-11065 of
# ledger/ordinals.tsv gives D0, Draw, Rect, Move, Show, Hide, GetTypeName), the destructor above Rect's line 53 and Hide
# below it. The class header (api/gui/cmoviefield.h, new; its path is chosen, no record names it) has the layout the
# destructor, Draw, Show and the constructor (inlined into fn 5543, with std::make_shared) give; the member names and the
# types of +40 (an int: 32-bit stores) and +44 (a bool) are chosen. The movie and the timer are std::shared_ptrs to the
# forward-declared api::CMovie and api::ITimer; cmoviefield.cpp includes api/util/itimer.h for Hide's Stop. The
# constructor is not reconstructed: it calls api::ITimerScheduler::GetInst (fn 1259), which has no body of ours.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CMOVIEFIELD_SRCS := src/api/gui/cmoviefield.cpp
UENUX2_SRCS += $(CMOVIEFIELD_SRCS)
# Draw (11064), Rect (11063), Move (11062), Show (11061) and GetTypeName (11059) are not reconstructed:
# 52-uenux2-cmoviefield-pending.cpp gives the vtable trapping bodies, compiled with the unit's flags; it reads only
# api/gui headers
$(ROOT)/$(APP)/52-uenux2-cmoviefield-pending.o: $(ROOT)/src/units/52-uenux2-cmoviefield-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/52-uenux2-cmoviefield.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/52-uenux2-cmoviefield-pending.cpp -o $(R)
# the constructor, the vtable's only user in the target, is not reconstructed: 52-uenux2-cmoviefield-roots.cpp takes the
# vtable's address, which keeps both destructors and Hide in the table as the target has them
$(ROOT)/$(APP)/52-uenux2-cmoviefield-roots.o: $(ROOT)/src/units/52-uenux2-cmoviefield-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/52-uenux2-cmoviefield.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/52-uenux2-cmoviefield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/52-uenux2-cmoviefield-pending.o $(APP)/52-uenux2-cmoviefield-roots.o
