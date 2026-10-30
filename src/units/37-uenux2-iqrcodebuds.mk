# uenux2 vota::IQRCodeBUDS::~IQRCodeBUDS, the D2 and D0 in slots 0 and 1 of the class's vtable (target fns 12050 and
# 12049, vtable @1542084, RTTI N4vota11IQRCodeBUDSE), in src/uenux2/src/app/vota/eleitor/fimvotacao/cmostraqrcodebu.cpp,
# the file the record of the class's constructor names (line 38 col 15, the CUeVotaError 9372 throw). The destructor has
# no record: it is the inline one declared in the class (cmostraqrcodebu.h, a chosen path: the class's only record is in
# the .cpp that defines its members, and no record names a header), because the target's D0 holds the D2's body, which
# clang gives only for an inline destructor. An inline destructor of a class with no other virtual member is emitted,
# with the vtable, only by a TU that defines a constructor, so the unit writes the constructor too (its record's throw
# on line 38). The constructor has no target function of its own: GetQRDSInst (fn 1956, not reconstructed; its record is
# line 31) inlines it, and our link drops it as unreferenced. With them: the class header and the 9372 enumerator of a
# new app/vota/euevotaerror.h (RTTI CBaseError<vota::EUeVotaError, SErrorLimits{9300, 9500}> gives the enum's name and
# limits; the enumerator's name, chosen from the message, the header's path and the CUeVotaError alias name, both after
# api/util/eueutilerror.h, are choices no evidence makes). vota::CMostraQRCodeBU, the file's other class (fns 12055
# 12051 5982 2888), keeps its stubs.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
IQRCODEBUDS_SRCS := src/app/vota/eleitor/fimvotacao/cmostraqrcodebu.cpp
UENUX2_SRCS += $(IQRCODEBUDS_SRCS)
# the class's users are not reconstructed yet: 37-uenux2-iqrcodebuds-roots.cpp takes the vtable's address, the only
# way the target reaches the two destructors
$(ROOT)/$(APP)/37-uenux2-iqrcodebuds-roots.o: $(ROOT)/src/units/37-uenux2-iqrcodebuds-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/37-uenux2-iqrcodebuds-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/37-uenux2-iqrcodebuds-roots.o
