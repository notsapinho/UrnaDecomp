# uenux2 vota::IQRCodeBUDS::~IQRCodeBUDS, the D2 and D0 in slots 0 and 1 of the class's vtable (target fns 12050 and
# 12049, vtable @1542084, RTTI N4vota11IQRCodeBUDSE), in src/uenux2/src/app/vota/eleitor/fimvotacao/cmostraqrcodebu.cpp,
# the file the record of the class's constructor names (line 38 col 15, the CUeVotaError 9372 throw). The destructor has
# no record: it is the inline one declared in the class (cmostraqrcodebu.h, a chosen path: the class's only record is in
# the .cpp that defines its members, and no record names a header), because the target's D0 holds the D2's body, which
# clang gives only for an inline destructor. An inline destructor of a class with no other virtual member is emitted,
# with the vtable, only by a TU that defines a constructor, so the unit writes the constructor too (its record's throw
# on line 38). The constructor has no target function of its own: GetQRDSInst (fn 1956, record line 31) holds it,
# inlined by binaryen through IQRCodeBUDS::CreateInst (below). With them: the class header and the 9372 enumerator of a
# new app/vota/euevotaerror.h (RTTI CBaseError<vota::EUeVotaError, SErrorLimits{9300, 9500}> gives the enum's name and
# limits; the enumerator's name, chosen from the message, the header's path and the CUeVotaError alias name, both after
# api/util/eueutilerror.h, are choices no evidence makes).
# vota::CMostraQRCodeBU, the file's other class: GetInst (fn 2888), the constructor, the out-of-line destructor (fns
# 785, 1560, shared with other states) and the statics, whose mutex's exit-time destructor (fn 12056) matches;
# cmostraqrcodebu.h says what its layout rests on. GetInst matches since unit 138's caplicacaoencerrada.cpp defines
# vota::CAplicacaoEncerrada's two statics (their exit-time destructors are fns 12060 and 12059): its s_inst (@1833848)
# had no voter but GetInst (`unresolved self-voted`) until the pointer's exit-time destructor (fn 12057) matched, and
# the target's 12057 is a thunk into fn 1564, binaryen's merge of such destructors over the D2 fn 785, which forms only
# from three members; CMostraQRCodeBU's and unit 156's CMostraQRCodeCertificado's were two.
#
# Matches: ProcessInput (fn 12051, record line 85), with CMostraQRCodeCertificado::GetInst inlined; through its vote the
# certificate state's statics are named, and their exit-time destructors (fns 12041, 12042, unit 156's object) match.
# The switch on Read()'s result writes its cases in the target's block order, CONFIRMA before BRANCO (with BRANCO first
# the two case blocks swap, 60 over 210 rows); the CONFIRMA test, the step back and forth and the AjustaTela call are
# IQRCodeBUDS's inline members, chosen.
#
# Written, not matching:
# - GetQRDSInst (fn 1956, record 31, `unresolved`): it calls CCabecalhoQRCodeBuilder::DefineHistoricoCarga (fn 5622),
#   written in unit 93 and `no-candidate` (its body is the target's but for its locals' numbers: 89 over 431 rows, every
#   replaced row operand-only), and Gera (fn 5604, unit 155's, `no-candidate`). It holds, inlined by binaryen, two
#   functions with frames of their own (IQRCodeBUDS::GeraPartes, 880 bytes, and IQRCodeBUDS::CreateInst, 16), and from
#   other files CAppInfo::GetGap's non-const overload (record cappinfo.cpp:42) and CPolySingleton's set, push and
#   instance. It scores 650 over 2482 rows (51 inserted, 57 deleted): the gap's correspondences are read through a local
#   holding +184 where the target folds 184 into the loads, and GeraPartes's empty-loop and throw blocks sit apart from
#   the target's. Both are measured, not explained. Its name reaches it by its callers' votes (`call by:5982,12051`).
# - AjustaTela (fn 5982, record 195, `unresolved self-voted`): 44 over 696 rows, all operand-only, but its callee
#   FindFieldAs<CTextField> (fn 1721, api/gui/iform.h, record 142) has no voter but 5982, and 1721 `differs`: 51 over
#   163 rows, its type-mismatch throw placed after the loop where the target keeps it before the loop's step (with the
#   field copied before the cast, as the target increments the count before dynamic_cast; without the copy, 46 over 142
#   and the increment after the cast; with std::find_if, 137 over 222). The seven fields are CTextFields: fn 940, which
#   it calls on them, is api::CTextField::SetCorTexto (unit 27), the body binaryen shares with CTextBox::SetStatus, and
#   whose match line moves to that name (a twin rename).
#
# Pending: StartState (fn 12055, record 70), a trap in 37-uenux2-iqrcodebuds-pending.cpp, which says what it waits for.
# The roots file stands for StartState's call of AjustaTela.
#
# Chosen as unit 104's states are (the shape it measured): GetInst's name and reference result, s_inst and s_mutex and
# their order after GetInst, the local trava, the constructor out of line and above the destructor, declared first;
# the definitions' lines, after IQRCodeBUDS's constructor and above the records of the members not written; the
# member's name, and its type spelled out (unit 156's fragment says why not CFormInterativoTelaVota). Chosen too:
# GeraPartes and CreateInst as IQRCodeBUDS's static members (two functions, from the two frames; free functions in
# cmostraqrcodebu.cpp would serve), their bodies' order of statements as the target's, the accessors, and every
# function's line but the records'.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
IQRCODEBUDS_SRCS := src/app/vota/eleitor/fimvotacao/cmostraqrcodebu.cpp
UENUX2_SRCS += $(IQRCODEBUDS_SRCS)
# CMostraQRCodeBU's members not reconstructed: 37-uenux2-iqrcodebuds-pending.cpp gives its vtable trapping bodies,
# compiled with the unit's flags
$(ROOT)/$(APP)/37-uenux2-iqrcodebuds-pending.o: $(ROOT)/src/units/37-uenux2-iqrcodebuds-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/37-uenux2-iqrcodebuds.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/fimvotacao/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/uenux2/src/api/audio/*.h $(ROOT)/src/uenux2/src/api/util/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/37-uenux2-iqrcodebuds-pending.cpp -o $(R)
# 37-uenux2-iqrcodebuds-roots.cpp stands for StartState's call of AjustaTela (the file says why)
$(ROOT)/$(APP)/37-uenux2-iqrcodebuds-roots.o: $(ROOT)/src/units/37-uenux2-iqrcodebuds-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/37-uenux2-iqrcodebuds-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/37-uenux2-iqrcodebuds-pending.o $(APP)/37-uenux2-iqrcodebuds-roots.o
