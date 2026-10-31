# uenux2 api::CMovieField::~CMovieField: the base-object destructor (target fn 5524, slot 0 of the vtable @1579432) and
# the deleting one (fn 11065, slot 1), with Hide (fn 11060, slot 4), in src/uenux2/src/api/gui/cmoviefield.cpp, the
# file the class's one record names (cmoviefield.cpp:53:12, Rect). The destructor is user-declared and defined out of
# line (the D0 calls the D2 and drops its result: an implicit or in-class destructor gives another D0), declared first
# among the class's virtual members, so it is the key function and cmoviefield.o emits the vtable, the D2 and the D0.
# The D2 stops the timer and clears +40 before the members go; the body is written as a call to Hide, which clang
# inlines (Hide's two stores spelled out give the same object, so the spelling is a choice). No record
# falls in the destructor or Hide: their lines are a choice, in the target's order (the uses-1 band 11059-11065 of
# ledger/ordinals.tsv gives D0, Draw, Rect, Move, Show, Hide, GetTypeName), the destructor above Rect's line 53 and Hide
# below it. The class header (api/gui/cmoviefield.h, new; its path is chosen, no record names it) has the layout the
# destructor, Draw, Show and the constructor (inlined into fn 5543, with std::make_shared) give; the member names and the
# types of +40 (an int: 32-bit stores) and +44 (a bool) are chosen. The movie and the timer are std::shared_ptrs to the
# forward-declared api::CMovie and api::ITimer; cmoviefield.cpp includes api/util/itimer.h for Hide's Stop. The
# constructor is not reconstructed: it calls api::ITimerScheduler::GetInst (fn 1259), which has no body of ours.
# Move and Show (fns 11062, 11061, slots 9 and 3) are written in the band's order, below line 53, at lines that are a
# choice. Move is CTextField's (27-uenux2-ctextfield.mk lists the forms) with the position at +32: binaryen keeps it
# apart, as the target does. Show stores 1 at +40, rewinds the movie and redraws as Move does; CMovie::Rewind, a member
# added to api/gui/cmovie.h for the store at the movie's +12, is chosen, name and all: defined out of line in cmovie.cpp
# with this one caller it gives the same bytes in the whole link (binaryen inlines it; scored against 11061, one operand
# row, the call to 150), so its being inline in the class is a choice too.
# Draw (fn 11064, slot 2) is one call of IScreen's slot 26, DrawMovie in api/gui/iscreen.h, between the destructor and
# Rect's line 53, in the band's order; its lines are a choice.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CMOVIEFIELD_SRCS := src/api/gui/cmoviefield.cpp
UENUX2_SRCS += $(CMOVIEFIELD_SRCS)
# Rect (11063) reads the movie before instance() and its size after it, which a reference to the size gives: a copy loads
# the size before the call (15 lines). `const CMovie& filme = *m_movie` with filme.Tamanho() at each use gives the same
# object code, so the local's form is a choice. GetTypeName (11059) is a thunk of binaryen's 2904, 29-uenux2-cimagefield.mk
# has its set; in the .cpp, last, as the band shows, is a choice: CImageField's, in the class, is a thunk too.
# the constructor, the vtable's only user in the target, is not reconstructed: 52-uenux2-cmoviefield-roots.cpp takes the
# vtable's address, which keeps both destructors and Hide in the table as the target has them
$(ROOT)/$(APP)/52-uenux2-cmoviefield-roots.o: $(ROOT)/src/units/52-uenux2-cmoviefield-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/52-uenux2-cmoviefield.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/52-uenux2-cmoviefield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/52-uenux2-cmoviefield-roots.o
