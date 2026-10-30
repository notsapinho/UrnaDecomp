# uenux2 vota::impl::CInformacaoThreadOperador's implicit destructors (target fns 10552 and 10551, vtable slots 0
# and 1), the compiler's code for the class definition in src/uenux2/src/app/vota/operador/comum/
# cinformacaothreadoperador.h: the class is final (the destructors store no vptr) and they destroy the three members
# that have a destructor, the std::optional<comum::md::CEleitorIdentidade> at +68 and +48 and the
# std::optional<std::string> at +24. The destructor is implicit: the deleting one holds the base-object body inlined,
# and in the target's function order (ledger/ordinals.tsv) both come after the class's members, which are in slot
# order. With it: the vota::impl::IInformacaoThreadOperador interface it implements (iinformacaothreadoperador.h beside
# it), and the layouts of comum::md::CEleitorIdentidade (src/app/comum/dados/md/eleitor/celeitoridentidade.h),
# api::CDateTime and api::CDate (src/api/util/cdatetime.h and cdate.h). No record names any of these headers: the class
# and its interface go beside cinformacaothreadoperador.cpp, the file whose records name four of its members
# (474-504:15) and GetInst (554:102); CEleitorIdentidade goes with the comum::md voter classes, whose records are in
# md/eleitor/; CDate and CDateTime beside their records' cdate.cpp and cdatetime.cpp. 25 of the 29 other members have
# no evidence for a name: iinformacaothreadoperador.h names them after their slot (SlotN) and says what is chosen.
# The unit has no source of its own yet: every member is pending, so the vtable, its key function Slot2 and with it the
# implicit destructors are emitted in the pending object (as unit 26's are); they move to cinformacaothreadoperador.o
# when Slot2, the first member the class declares, moves there. vota::TipoToStr (fn 10586) and GetInst (fn 599), the
# file's other functions, keep their stubs in the stub-only cinformacaothreadoperador.cpp; the 29 members' stubs go
# with the vtable (slot 19's, fn 10566, was in src/app/comum/dados/md/estadoaplicacao/cestadogeralvota.h, the file of a
# record of the function it inlines). Paths relative to src/uenux2.
# The 29 members of slots 2 to 30 are not reconstructed: 50-uenux2-cinformacaothreadoperador-pending.cpp defines them
# with trapping bodies, compiled with the unit's flags, and its header names each with its target function
$(ROOT)/$(APP)/50-uenux2-cinformacaothreadoperador-pending.o: $(ROOT)/src/units/50-uenux2-cinformacaothreadoperador-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/50-uenux2-cinformacaothreadoperador.mk $(ROOT)/src/uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.h $(ROOT)/src/uenux2/src/app/vota/operador/comum/iinformacaothreadoperador.h $(ROOT)/src/uenux2/src/app/comum/dados/md/eleitor/celeitoridentidade.h $(ROOT)/src/uenux2/src/api/util/cdatetime.h $(ROOT)/src/uenux2/src/api/util/cdate.h $(ROOT)/src/uenux2/src/api/util/ctime.h $(ROOT)/src/ecourna/app/dados/tiposbasicos.hpp $(ROOT)/src/ecourna/app/dados/resultadournacadastro/capresentacaofotoeleitor.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/50-uenux2-cinformacaothreadoperador-pending.cpp -o $(R)
# nothing calls the destructors directly in the target, which reaches them through the vtable only:
# 50-uenux2-cinformacaothreadoperador-roots.cpp keeps the vtable, as the constructor inlined into GetInst does
$(ROOT)/$(APP)/50-uenux2-cinformacaothreadoperador-roots.o: $(ROOT)/src/units/50-uenux2-cinformacaothreadoperador-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/50-uenux2-cinformacaothreadoperador.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/50-uenux2-cinformacaothreadoperador-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/50-uenux2-cinformacaothreadoperador-pending.o $(APP)/50-uenux2-cinformacaothreadoperador-roots.o
