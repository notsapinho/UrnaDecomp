# uenux2 comum::IInterfaceInit in src/app/comum/iinterfaceinit.cpp, the file the records of the class's members name: the
# destructor (target fn 5898, slot 0 of the IInterfaceInit vtable @1552152 and of simulador::CWasmInit's @1528764: one
# table entry, 535, so CWasmInit's destructor is this one; no record falls in it: it is placed at the top, and the link
# order puts it before line 148, iinterfaceinit.h says why), which frees the two members, a std::string at +12 and a
# std::shared_ptr<bool> at +4, after storing the vptr; CurrentBootDevice (11646, slot 2, record 47:15),
# IsMRPresenteSemHabilitar and IsMRMontadoSemHabilitar (2862, 5897, 137:15, 148:15: thunks into binaryen's body 6046,
# which those two form), DesmontarMRSemDesabilitar (3832, 184:15, 188:15), EnviarMensagemThrowVoid (3833, 731:15, 737:15),
# GetDemoMode (729, 753:15, 757:15) with __shared_ptr_pointer<bool*, ...>::__get_deleter (11644), and HabilitarMR (2863,
# a chosen name) with DesabilitarMR (a chosen name, no target function: binaryen inlines it into 7160). With them the
# class header (src/app/comum/iinterfaceinit.h) and the out-of-line constructor, which no target function holds (binaryen
# inlined it into its one caller, fn 8302). DesligarUrna (5894, records 522:18, 527:15, 531:15) was added after the unit
# landed, once unit 111 gave fn 837 (CPolySingleton<IEventosLog>::instance) and fn 233 (IEventosLog::loga) their
# bodies: it logs "Urna desligada a pedido do aplicativo", sends message 48 and throws codes 7268 and 7269
# (euecomumerror.h). The instance in a local named `logs`, as unit 111's clogcomum.cpp has it, fills column 18; the
# local's name and `auto&` are chosen. MontarMRSemHabilitar (5896) and LogDiskInfo (inlined into fn
# 10226, vota::CThreadMonitor's slot 2) are not reconstructed.
# Evidence and choices. The records fix each throw's line; EnviarMensagemThrowVoid's `inline` is read from where its
# records lie (iinterfaceinit.h). HabilitarMR's place before line 137 is read from fn 2863 sitting before fn 2862 in
# their use band, with fn 3833 after it and before fn 3832 in theirs (docs/reference/facts/reading.md R8, an inline
# function sits right after its first caller); its line, DesabilitarMR's and every name without a record are chosen.
# What the bytes decide, measured on this object, function by function with object-local numbers masked: GetDemoMode
# returns a local, not *m_demoMode, which reloads the byte (4 rows more); DesmontarMRSemDesabilitar reads resposta[0]
# twice, the second read for the format argument, and a local `erro` gives other code.
# Forms that give the same function, measured the same way, the one written first:
# - CurrentBootDevice: a switch, an if chain, a conditional expression, a switch over a local int;
# - IsMR*: `resposta[0] == 0`, `!resposta[0]`, `resposta.front() == 0`;
# - DesmontarMRSemDesabilitar: `resposta[0] != 0` and `resposta[0]`;
# - EnviarMensagemThrowVoid: with and without `inline` (only the offset of its records moves, which the link rewrites);
# - GetDemoMode: `m_demoMode = std::shared_ptr<bool>(new bool(x))` and `m_demoMode.reset(new bool(x))`; `!= 0` and
#   static_cast<bool>; `if (m_demoMode)` and `!= nullptr`.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
IINTERFACEINIT_SRCS := src/app/comum/iinterfaceinit.cpp
UENUX2_SRCS += $(IINTERFACEINIT_SRCS)
# the destructor's reachers are in the link (CWasmInit's vtable and deleting destructor, unit 127); the other members'
# callers are not reconstructed yet, and 35-uenux2-iinterfaceinit-roots.cpp gives them call sites
$(ROOT)/$(APP)/35-uenux2-iinterfaceinit-roots.o: $(ROOT)/src/units/35-uenux2-iinterfaceinit-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/35-uenux2-iinterfaceinit.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/35-uenux2-iinterfaceinit-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/35-uenux2-iinterfaceinit-roots.o
