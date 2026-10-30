# uenux2 api::CStepsProgressBar::~CStepsProgressBar: the D2 (target fn 3665, vtable @1581868 slot 0) and the D0 (fn
# 10973, slot 1), with GetTypeName (10969, slot 7) and Rect (10968, slot 8), in src/uenux2/src/api/gui/cstepsprogressbar.cpp,
# the file the constructor's std::source_location record names (cstepsprogressbar.cpp:428:15
# api::CStepsProgressBar::CStepsProgressBar(const uedword, const std::vector<std::string> &, const SRect &, const TColor
# x7)). The constructor is not reconstructed: it is inlined into fn 13550 (slot 2 of vota::CPreShowProgressBar), which
# keeps its stub, so line 428 stays free for it. No record falls in the destructor, GetTypeName or Rect, so their lines
# (after the constructor's) are a choice; their order (destructor, then GetTypeName, then Rect) follows the four
# members that share a use band in the target, where the D0 comes first and Rect last (the solver's ordinals in
# ledger/ordinals.tsv: 10973 4279, Move 10970 4281, 10969 4282, 10968 4283). The destructor is user-declared and
# defined out of line: the D0 10973 is `f3665(p0); f136(p0)`, the call to the D2 that clang gives only for an
# out-of-line destructor (one defined in the class would have the D2's body inlined into the D0). Declared first of
# the class's virtual members, it is the key function, so cstepsprogressbar.o emits the vtable, the D2 and the D0.
# The class header (api/gui/cstepsprogressbar.h, the file chosen) has the layout the inlined constructor stores and
# Draw (fn 5504) and the D2 read: IFormFieldBase<IScreen> (+0 .. +24), the current step +24, the steps' texts
# (std::vector<std::string>) +28, the SRect +40 (what Rect returns), seven TColors +48 .. +72, a flag +76, an SFont
# +80 and the segments Draw builds +88 (a std::vector of 28-byte elements: a std::vector of 56-byte path commands, an
# SPoint, a std::string). The D2 destroys +88, then +28, then the IFormFieldBase<IScreen> part (its vptr store and
# m_nome). The member, parameter and type names are not evidenced. Draw (5504) and Move (10970, which calls the unnamed
# fn 1915) are pending. Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2
# header.
CSTEPSPROGRESSBAR_SRCS := src/api/gui/cstepsprogressbar.cpp
UENUX2_SRCS += $(CSTEPSPROGRESSBAR_SRCS)
# Draw and Move are not reconstructed: 41-uenux2-cstepsprogressbar-pending.cpp gives the vtable trapping bodies,
# compiled with the unit's flags; it depends on every header its compile reads (cstepsprogressbar.h, iformfield.h and
# primitives.h in api/gui, and ecourna's uetypes.hpp; UENUX2_HDRS is not set yet where src/Makefile reads the fragments)
$(ROOT)/$(APP)/41-uenux2-cstepsprogressbar-pending.o: $(ROOT)/src/units/41-uenux2-cstepsprogressbar-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/41-uenux2-cstepsprogressbar.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/41-uenux2-cstepsprogressbar-pending.cpp -o $(R)
# the destructor's caller other than the deleting destructor (fn 13550) is not reconstructed yet:
# 41-uenux2-cstepsprogressbar-roots.cpp gives it a second direct caller and takes its address
$(ROOT)/$(APP)/41-uenux2-cstepsprogressbar-roots.o: $(ROOT)/src/units/41-uenux2-cstepsprogressbar-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/41-uenux2-cstepsprogressbar.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/41-uenux2-cstepsprogressbar-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/41-uenux2-cstepsprogressbar-pending.o $(APP)/41-uenux2-cstepsprogressbar-roots.o
