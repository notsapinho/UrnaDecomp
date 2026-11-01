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
# api/util/eueutilerror.h, are choices no evidence makes).
# vota::CMostraQRCodeBU, the file's other class: GetInst (fn 2888), the constructor, the out-of-line destructor (fns
# 785, 1560, shared with other states) and the statics, whose mutex's exit-time destructor (fn 12056) matches;
# cmostraqrcodebu.h says what its layout rests on. Its StartState (fn 12055) and ProcessInput (fn 12051) are traps in
# 37-uenux2-iqrcodebuds-pending.cpp, which names what they wait for, and AjustaTela (fn 5982) and GetQRDSInst (fn 1956)
# keep their stubs. GetInst's two callers in the link are unit 156's ProcessInputs (fns 12026, 12038); the target has a
# third, fn 12081.
# GetInst matches since unit 138's caplicacaoencerrada.cpp defines vota::CAplicacaoEncerrada's two statics (their
# exit-time destructors are fns 12060 and 12059): its s_inst (@1833848) had no voter but GetInst (`unresolved
# self-voted`) until the pointer's exit-time destructor (fn 12057) matched, and the target's 12057 is a thunk into fn
# 1564, binaryen's merge of such destructors over the D2 fn 785, which forms only from three members; CMostraQRCodeBU's
# and unit 156's CMostraQRCodeCertificado's were two. With the third the link forms the merge, and 1564, 2888 and 12057
# match, as measured here before.
# Chosen as unit 104's states are (the shape it measured): GetInst's name and reference result, s_inst and s_mutex and
# their order after GetInst, the local trava, the constructor out of line and above the destructor, declared first;
# the definitions' lines, after IQRCodeBUDS's constructor and above the records of the members not written; the
# member's name, and its type spelled out (unit 156's fragment says why not CFormInterativoTelaVota).
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
IQRCODEBUDS_SRCS := src/app/vota/eleitor/fimvotacao/cmostraqrcodebu.cpp
UENUX2_SRCS += $(IQRCODEBUDS_SRCS)
# CMostraQRCodeBU's members not reconstructed: 37-uenux2-iqrcodebuds-pending.cpp gives its vtable trapping bodies,
# compiled with the unit's flags
$(ROOT)/$(APP)/37-uenux2-iqrcodebuds-pending.o: $(ROOT)/src/units/37-uenux2-iqrcodebuds-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/37-uenux2-iqrcodebuds.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/fimvotacao/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/uenux2/src/api/audio/*.h $(ROOT)/src/uenux2/src/api/util/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/37-uenux2-iqrcodebuds-pending.cpp -o $(R)
# IQRCodeBUDS's users are not reconstructed yet: 37-uenux2-iqrcodebuds-roots.cpp takes the vtable's address, the only
# way the target reaches the two destructors
$(ROOT)/$(APP)/37-uenux2-iqrcodebuds-roots.o: $(ROOT)/src/units/37-uenux2-iqrcodebuds-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/37-uenux2-iqrcodebuds-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/37-uenux2-iqrcodebuds-pending.o $(APP)/37-uenux2-iqrcodebuds-roots.o
