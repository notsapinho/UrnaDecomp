# uenux2 comum::CSigVerifier constructor (target fn 1540) in src/uenux2/src/app/comum/relatorios/csigverifier.cpp, the
# file the record of its Verify names (line 32 col 19); the constructor has no record of its own, its class is the
# vptr it stores (_ZTVN5comum12CSigVerifierE). With it: the class header (csigverifier.h), the api::ISigVerifier
# interface it implements (api/gui/isigverifier.h; RTTI names the base, no record names its file: it goes with the
# paper reports that take it) and the ESavdAplic type of its +4 member (app/comum/iinterfacesavd.h, beside the file
# whose records spell it). That +4 member is a constructor parameter that wasm-opt's dead-argument elimination folded
# (every caller passes 1), so the target's signature has no trace of it: its position in the parameter list (first,
# before the three strings) is a choice no evidence fixes, and only our symbol's mangling depends on it, not the
# bytes. The destructor is implicit (the target's callers inline it): its bodies (fns 11178, 11176, vtable slots 0
# and 1) are the compiler's, emitted with the vtable in the TU of the key function Verify, so the pending file's for
# now. They store no vptr, so the class is final (csigverifier.h says why). Paths relative to src/uenux2; the generic
# uenux2 rule depends on the source and every uenux2 header.
CSIGVERIFIER_SRCS := src/app/comum/relatorios/csigverifier.cpp
UENUX2_SRCS += $(CSIGVERIFIER_SRCS)
# Verify (target fn 11179) is not reconstructed: 26-uenux2-csigverifier-pending.cpp gives the vtable a trapping body,
# compiled with the unit's flags
$(ROOT)/$(APP)/26-uenux2-csigverifier-pending.o: $(ROOT)/src/units/26-uenux2-csigverifier-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/26-uenux2-csigverifier.mk $(ROOT)/src/uenux2/src/app/comum/relatorios/csigverifier.h $(ROOT)/src/uenux2/src/api/gui/isigverifier.h $(ROOT)/src/uenux2/src/app/comum/iinterfacesavd.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/26-uenux2-csigverifier-pending.cpp -o $(R)
# the constructor's seven callers are not reconstructed yet: 26-uenux2-csigverifier-roots.cpp gives it two direct
# callers that pass the same ESavdAplic, as the target's do
$(ROOT)/$(APP)/26-uenux2-csigverifier-roots.o: $(ROOT)/src/units/26-uenux2-csigverifier-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/26-uenux2-csigverifier-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/26-uenux2-csigverifier-pending.o $(APP)/26-uenux2-csigverifier-roots.o
