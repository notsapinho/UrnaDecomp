# uenux2 comum::IInterfaceInit in src/app/comum/iinterfaceinit.cpp, the file the records of the class's members name: the
# destructor (target fn 5898, slot 0 of the IInterfaceInit vtable @1552152 and of simulador::CWasmInit's @1528764: one
# table entry, 535, so CWasmInit's destructor is this one; no record falls in it: it is placed at the top, and the link
# order puts it before line 148, iinterfaceinit.h says why), which frees the two members, a std::string at +12 and a
# std::shared_ptr<bool> at +4, after storing the vptr; CurrentBootDevice (11646, slot 2, record 47:15),
# IsMRPresenteSemHabilitar and IsMRMontadoSemHabilitar (2862, 5897, 137:15, 148:15: thunks into binaryen's body 6046,
# which those two form), DesmontarMRSemDesabilitar (3832, 184:15, 188:15), EnviarMensagemThrowVoid (3833, 731:15, 737:15),
# GetDemoMode (729, 753:15, 757:15) with __shared_ptr_pointer<bool*, ...>::__get_deleter (11644), and HabilitarMR (2863,
# a chosen name) with DesabilitarMR (a chosen name, no target function: binaryen inlines it into 7160, unit 329's, as
# ours does since that unit wrote 7160 and the roots' stand-in for it went). With them the
# class header (src/app/comum/iinterfaceinit.h) and the out-of-line constructor, which no target function holds (binaryen
# inlined it into its one caller, fn 8302). DesligarUrna (5894, records 522:18, 527:15, 531:15) was added after the unit
# landed, once unit 111 gave fn 837 (CPolySingleton<IEventosLog>::instance) and fn 233 (IEventosLog::loga) their
# bodies: it logs "Urna desligada a pedido do aplicativo", sends message 48 and throws codes 7268 and 7269
# (euecomumerror.h). The instance in a local named `logs`, as unit 111's clogcomum.cpp has it, fills column 18; the
# local's name and `auto&` are chosen.
# MontarMRSemHabilitar (5896, records 159:15, 163:15, 172:22), added since, with DispositivoMR (records 632:15, 636:15)
# and GetSerialNumberMR (855:33), which have no target function of their own: their records are 5896's. It sends
# message 34 and throws codes 7239 and 7240 with "Resposta nula" and "Falha ao montar m�dia de resultado ({})"
# (euecomumerror.h); DispositivoMR holds HabilitarMR's code (message 10, "habilitando MR"), sends message 12 and throws
# 7282 and 7283 with "Resposta nula" and "Falha ao obter dispositivo da MR: {}" on an empty answer or -1; when the serial
# GetSerialNumberMR reads differs from the member at +12, 5896 logs "Tamanho da MR: {}" over FormataTamanho (1947) of
# the device's size through IEventosLog::loga (172:22 is the start of the instance call, as DesligarUrna's 522:18 is),
# calls 5895, the priority-6 debug wrapper, with "Serial da MR: %s", and stores the serial. GetSerialNumberMR (855:33
# is the start of CPolySingleton<api::IUrna>::instance()) takes two sysfs serial paths by the model the urna returns
# (2009, 2010, 2011 and 2013; 2015; 2020 and 2022: the strings 157091 to 156985), the first that exists (posix_stat, fn
# 1055) and its content trimmed (ecourna's CFile::ReadFileContent, fn 3522, and CStringUtils::Trim, fn 1374). It also
# formats "sd{:c}" for the device and reads nothing of it, as written: the match measures that source (a reading of
# the target's code, which keeps the format). The device's size, with no record and no target index, is
# /sys/block/sd?/size times its queue/logical_block_size (ecourna's CStringUtils::ToInt32, fn
# 2200, of each file's content), written as TamanhoMR, a free function of this file declared in iinterfaceinit.h.
# Chosen: TamanhoMR's name, its being a free function and its int result; the locals' names; the lines of
# DispositivoMR (627 to 639) and GetSerialNumberMR (848 to 884) around their records and TamanhoMR's after them; the
# switch's case order. Of its two target callers, 7160 is in the link (unit 329) and 12134 is not reconstructed:
# 35-uenux2-iinterfaceinit-roots.cpp stands for 12134. The scan matched it by its records (srcloc-anchor), with no hand
# line.
# LogDiskInfo (record 285:15), added since, has no target index: binaryen inlines it into its one caller, fn 10226
# (vota::CThreadMonitor::Run, unit 116's), behind a 32-B stack frame of its own. It sends message
# 19, throws code 7277 with "Resposta nula" when the answer is empty (euecomumerror.h) and, when its first word is not 0,
# logs "%s: erro [%d] ao tentar logar informações sobre as partições" with "LogDiskInfo" (the strings 72624 and 134831)
# through the target's fn 5895: f2921(p0, p1, 6, @1552472), the priority-6 wrapper whose word lies right after this
# class's typeinfo (@1552464), so this object's copy, written as DepuraInfo in api/util/uedebug.h. Its lines (281 to 290)
# are a choice inside the range its record's data order allows (after 188's record, before 522's); `__func__` for the
# literal is a reading. DepuraInfo's other target caller is 5896: with 5896 in the link it has its two call sites, stays
# out of line, and 10226 matches (unit 116's Run paragraph). uedebug.h's include took one blank line of the run above
# line 43, so no record moved.
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
# comum::FormataTamanho (fn 1947), added since, a free function of this file: a byte count as "{}.{} GB", "{}.{} MB" or
# "{}.{} KB" with one decimal digit, else "{} B". Evidence: its four std::format calls (strings 333538, 333515, 333524,
# 334286; argument types 198, two unsigned, and 6), the count's shifts by 30, 20 and 10 and the digit's `& 1023`, `* 10`
# and `>> 10`, all on an unsigned 32-bit word, and its callers (ledger/callgraph.tsv): vota::CThreadMonitor::Run (10226,
# unit 116's, four calls on the low word of 64-bit values), MontarMRSemHabilitar (5896, this file's) and
# vota::CLogVota::LogaQuantidade (3268, fragment 234's paragraph), all three in the link now. The target computes the count's `>> 20`
# before its first test and its `>> 10` after it, which the three quotients named first give; with each branch's test
# written as `tamanho >= 1024 * 1024 * 1024` the object compares with the bound instead (try-tu.sh --symbols, read with
# wasm-objdump -d). Its file is a choice the band leaves open: in band 6 it lies right after cpath.cpp's 1948, and in
# bands 1, 3 and 4 this file's functions follow cpath.cpp's (11649 and 11648, then 11646 and 11644; 3834, then 3833
# and 3832; 2864, then 2863 and 2862), so a last function of cpath.cpp would lie there as well as this file's first;
# its call from this file's MontarMRSemHabilitar (5896) is what tips it here. Chosen: the file, the name, the
# namespace, the size_t parameter (the bytes give an unsigned 32-bit word), its declaration in iinterfaceinit.h, its
# line (83) and the locals' names. pnpm wasm score before step 8: 29 over 644 rows, all operand-only; the scan
# matched it by content. Its stand-in in fragment 234's roots went once its three callers were in the link.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
IINTERFACEINIT_SRCS := src/app/comum/iinterfaceinit.cpp
UENUX2_SRCS += $(IINTERFACEINIT_SRCS)
# the destructor's reachers are in the link (CWasmInit's vtable and deleting destructor, unit 127); the other members'
# callers are not reconstructed yet, and 35-uenux2-iinterfaceinit-roots.cpp gives them call sites
$(ROOT)/$(APP)/35-uenux2-iinterfaceinit-roots.o: $(ROOT)/src/units/35-uenux2-iinterfaceinit-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/35-uenux2-iinterfaceinit.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/35-uenux2-iinterfaceinit-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/35-uenux2-iinterfaceinit-roots.o
