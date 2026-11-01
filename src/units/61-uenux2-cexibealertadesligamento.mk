# uenux2 vota::CExibeAlertaDesligamento: the destructors (target fn 2883, the base-object destructor in slot 0 of the
# CExibeAlertaDesligamento vtable @1543004, and fn 12019, the deleting one in slot 1), GetInst (fn 5979) with the
# constructor it holds inlined and the two statics, StartState (fn 12018, slot 2) and ProcessTick (fn 12017, slot 8), in
# src/app/vota/eleitor/iniciovotacao/cexibealertadesligamento.cpp, the file the records of StartState and ProcessTick
# name (lines 45, 53, 54). The class is final (its destructor stores no vptr) and holds an api::CDateTime (+12), a
# std::shared_ptr to its form (+24), a tick id (+32) and a state pointer (+36); the destructor releases the shared_ptr.
# It is out of line, as the deleting one calling it shows. Declared first, it is the key function and
# cexibealertadesligamento.o emits the vtable: a choice, as StartState and ProcessTick are out of line in the same file
# too.
#
# GetInst has one target caller, vota::CEstadoComDesligamentoAutomatico::ProcessTick (fn 12061, unit 97), which calls it
# twice, so it stays out of line; the constructor's code sits behind a second stack prologue in it, so binaryen inlined
# a constructor defined out of line (docs/reference/facts/reading.md R10), and the constructor is written out of line
# above GetInst, as unit 169 writes its singletons'. In use band 1 the target links the statics' exit destructors
# (12022, the pointer's, then 12021, the mutex's) before the D0 (12019), StartState and ProcessTick, so the statics,
# the pointer first, are defined above the destructor, which follows them (unit 150's case); with the destructor at the
# head of the file our link put the D0 first (names.tsv's ld_index). The unit no longer needs companions: fn 12061 is
# in the link (the vtable of CEstadoComDesligamentoAutomatico, which its constructor fn 1285 stores, holds it), and it
# reaches GetInst, whose inlined constructor stores this class's vptr; StartState and ProcessTick are written.
#
# Evidence and choices in the three members:
# - StartState stores `this` as the next state, calls slot 2 of the +24 form, copies the 12-byte api::CDateTime at
#   1833312 into +12 (src/uenux2/src/app/vota/eleitor/comum/cinformacaoeleitor.h names it, a chosen name) and calls slot
#   1 (2000, 100) of CPolySingleton<api::IBeep>'s instance (fn 925), at record :45:5. The statements' order is the
#   target's.
# - ProcessTick: on its own tick, compares +12 with the current time (fns 479 and 759); past it, logs "Tempo limite de
#   espera usando bateria interna atingido" through vota::CLogVota::LogaTempoLimiteBateriaInterna (a member binaryen
#   inlines: GetInst is called before its stack frame opens; app/vota/log/clogvota.h) and calls
#   comum::IInterfaceInit::DesligarUrna (fn 5894) on CPolySingleton<comum::IInterfaceInit>'s instance (fn 611), the call
#   at record :53:13; else, when slot 15 of CPolySingleton<api::IPower>'s instance (fn 862) leaves word 0's bits 1-2 not
#   1 (api::IPower::UsandoBateriaInterna, api/hwil/ipower.h), goes to the +36 state. The record :54:24 is that
#   instance() call: its 23 characters before the call are `        } else if (not `, a chosen spelling of that length
#   (docs/reference/facts/reading.md R19); `        } else if (!` is 20 characters, which leaves the call at column 21.
#
# Its base comum::CAppState, the base of every application state: the constructor (fn 224) and the inline
# NeedChangeState (fn 7480, slot 3), in src/app/comum/cappstate.cpp and cappstate.h, with api::CState
# (src/api/pattern/cstate.h). No record names either class's file. The directory app/comum/: the CAppState vtable and
# typeinfo lie between comum::CAbstractTelaProgresso's and the records of app/comum/carquivosresultado.cpp,
# comum::CAppStateContext's vtable right after them, which is the name order of the root of app/comum/ (cappstate.h
# says more); the file name cappstate.cpp is the class-name convention. The destructor is
# its key function: chosen, as no evidence says which member is out of line, only that one is. cstate.h's directory is
# chosen. Chosen names, marked in the headers: CAppState's slots 4 (GetNextState) and 6 (ProcessKey), its constructor's
# argument type and the enumeration of its bits, CExibeAlertaDesligamento::GetInst and SetProximoEstado, the statics'
# names (s_mutex, s_inst), the type of the +24 pointee (api::IForm<api::IScreen>) and every member name. The +12
# member's type is unit 50's api::CDateTime (api/util/cdatetime.h and cdate.h).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CEXIBEALERTADESLIGAMENTO_SRCS := src/app/comum/cappstate.cpp src/app/vota/eleitor/iniciovotacao/cexibealertadesligamento.cpp
UENUX2_SRCS += $(CEXIBEALERTADESLIGAMENTO_SRCS)
