# uenux2 api::CTextFieldUpdate::~CTextFieldUpdate: the base-object destructor (target fn 5495, slot 0 of the vtable
# @1582988) and the deleting one (fn 10917, slot 1), with GetTypeName (fn 10912, slot 7), in
# src/uenux2/src/api/gui/ctextfieldupdate.cpp, the file the class's records name (ctextfieldupdate.cpp:38:15, the
# constructor; :73:21, Rect). The destructor is user-declared and defined out of line (the D0 calls the D2: an implicit
# or in-class destructor would have its body inlined into the D0), declared first among the class's virtual members, so
# it is the key function and ctextfieldupdate.o emits the vtable, the D2 and the D0. No record falls in the destructor or
# GetTypeName: their lines are a choice, in the target's order (the uses-1 band 10912-10917 of ledger/ordinals.tsv
# gives D0, Draw, Show, Hide, Rect, GetTypeName). The class header (api/gui/ctextfieldupdate.h) has the layout the
# constructor (fn 3658) and Draw (fn 10916) store; the member names are chosen and the timer at +72 is a
# std::shared_ptr to a forward-declared api::ITimer. The constructor (3658) is not reconstructed: it calls
# api::ITimerScheduler::GetInst (fn 1259), which has no body of ours, and keeps its stub; line 38 stays free for it.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CTEXTFIELDUPDATE_SRCS := src/api/gui/ctextfieldupdate.cpp
UENUX2_SRCS += $(CTEXTFIELDUPDATE_SRCS)
# Draw (10916), Show (10915), Hide (10914), Rect (10913) and Move (2241) are not reconstructed:
# 42-uenux2-ctextfieldupdate-pending.cpp gives the vtable trapping bodies, compiled with the unit's flags; it reads only
# api/gui headers
$(ROOT)/$(APP)/42-uenux2-ctextfieldupdate-pending.o: $(ROOT)/src/units/42-uenux2-ctextfieldupdate-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/42-uenux2-ctextfieldupdate.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/42-uenux2-ctextfieldupdate-pending.cpp -o $(R)
# the constructor, the vtable's only user in the target, is not reconstructed: 42-uenux2-ctextfieldupdate-roots.cpp takes
# the vtable's address, which keeps both destructors in the table as the target has them
$(ROOT)/$(APP)/42-uenux2-ctextfieldupdate-roots.o: $(ROOT)/src/units/42-uenux2-ctextfieldupdate-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/42-uenux2-ctextfieldupdate.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/42-uenux2-ctextfieldupdate-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/42-uenux2-ctextfieldupdate-pending.o $(APP)/42-uenux2-ctextfieldupdate-roots.o
