# uenux2 the iniciovotacao states that no landed file holds: vota::CConfirmaRegerarZeresima (ProcessInput, target fn
# 11838; its StartState is one body with vota::CConfirmaImpressaoZeresima's, fn 5958), vota::CImpressaoZeresimaTardia
# (StartState, fn 11932, with vota::CLogVota::LogaMesarioIndagadoHorarioUrna, which it holds inlined, added to
# app/vota/log/clogvota.cpp), and the four states vota::CMaisInformacoes::ProcessInput (fn 11896, unit 104's file) goes
# to, vota::CImpressaoEstadoUrna, CImpressaoListaEleitores, CImpressaoVersaoPacotes and CImpressaoPU: their GetInst and
# constructors, which fn 11896 holds inlined, and their statics, whose exit-time destructors match (11913 and 11912,
# 11910 and 11909, 11907 and 11906, 11904 and 11903, each pointer's first). The class heads say what each layout rests
# on; 176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.cpp names every slot left and what it waits for. Not
# written: the constructor, GetInst and statics of CImpressaoZeresimaTardia (fn 11927 holds them inlined; the
# constructor copies vota::CTelasVota::GetInst()'s +60, which app/vota/eleitor/comum/ctelasvota.h has no accessor for);
# their statics' exit destructors (11934, 11933) wait with them.
# CConfirmaRegerarZeresima's constructor, GetInst and statics are written, unit 104's shape, and
# vota::CReinicioVotacao::StartState (fn 11835, unit 138) holds GetInst inlined: the new of 20 bytes, the base's
# constructor (fn 224) with 2, the vptr, the copy of CTelasVota's +84 and +88 (a getter added to ctelasvota.h, its name
# chosen), the mutex's unlock (fn 150); its statics' exit destructors match with 11835 (11840 the pointer's, 11839 the
# mutex's, @1834940 and @1834916, which 11835 alone votes for and these two destructors read too), and the roots' sink
# of this class's vtable went, 11835 storing it.
#
# Evidence, each measured in the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv:
# - CConfirmaRegerarZeresima has a TU of its own. Written in cregerarzeresima.cpp, the TU that defines
#   CRegerarZeresima::GetInst, clang inlined that GetInst into ProcessInput (wasm-objdump -d of the object: its body and
#   no call), and fn 11838 scored 39 over 108 rows (6 inserted, 5 deleted: the target keeps `this` on the stack for one
#   store of the next state after a block with a result); in a TU of its own, where binaryen inlines it, 16 over 102
#   rows, all operand-only.
# - 11896 holds the four GetInst inlined with no index of their own, as binaryen's one-caller inlining gives here
#   (11896 scores 48 over 299 rows, all operand-only), and their statics' destructors run in link order before
#   CMaisInformacoes's (11899): each class's statics are defined below its GetInst, pointer first, as unit 104 measured.
# - 11932 calls CLogVota::GetInst (fn 184) and only then opens the stack frame that builds "Mesário indagado se horário
#   da urna está correto" for comum::IEventosLog::loga (fn 233): the shape of a CLogVota member binaryen inlined
#   (docs/reference/facts/reading.md R10), as unit 169's LogaAguardandoConfirmacaoZeresima. 10 over 73 rows, all
#   operand-only.
#
# Chosen, no evidence names them: every data member's name, GetInst, s_mutex, s_inst and the local trava (unit 104's
# convention); the destructor declared first; the private constructors of CConfirmaRegerarZeresima and
# CImpressaoZeresimaTardia, declared and not defined; StartState as the key function of the four CImpressao* states,
# so the pending object emits three of their vtables and cimpressaoversaopacotes.cpp the fourth;
# LogaMesarioIndagadoHorarioUrna's name, from its message, and its place last in clogvota.cpp. The paths, by how-to step 3's rules (no record names these classes' files), each header beside
# its .cpp and named after the class (rule 4):
# - cconfirmaregerarzeresima.cpp in iniciovotacao/ (rule 2): its vtable and typeinfo follow vota::CRegerarZeresima's in
#   the data with nothing between (@1546492 to @1546608), and its statics' destructors follow CRegerarZeresima's slot 10
#   (fn 11841) in link order and precede vota::CReinicioVotacao's (11837). The directory's data run from
#   cquerreimprimirzeresima.cpp (@1546340) through cregeraresumozeresima.cpp and cregerarzeresima.cpp to
#   creiniciovotacao.cpp (@1546628) is in name order, where this file's name sorts elsewhere: the name is a choice
#   against that order (how-to step 3, rule 3's note).
# - cimpressaozeresimatardia.cpp in iniciovotacao/: its vtable (@1544640) lies between CGeraZeresima's and
#   CConfirmaImpressaoZeresima's, with iniciovotacao/'s recorded files on both sides (cinformacaozeresimatardia.cpp
#   @1543708, cverificaeleicaopassou.cpp @1545012; docs/reference/facts/placing.md P5).
# - the four CImpressao* states in auxiliares/: their vtables (@1545056 to @1545224) lie between
#   iniciovotacao/cverificaeleicaopassou.cpp's record (@1545012) and CMaisInformacoes's vtable (@1545304), and their
#   functions (11913 to 11902) between cverificaeleicaopassou.cpp's (11914, records :56 and :70) and CMaisInformacoes's
#   (11899) in link order; auxiliares/ is a choice, beside cmaisinformacoes.cpp (unit 104's choice), whose ProcessInput
#   builds them. The list below keeps the target's order (EstadoUrna, ListaEleitores, VersaoPacotes, PU), in which
#   cimpressaopu.cpp does not sort by name: a choice against name order.
#
# vota::CImpressaoVersaoPacotes::StartState (target fn 11905, slot 2) is written in cimpressaoversaopacotes.cpp and
# matches, named by its records (srcloc-anchor): cfileasn.h's lines 78, 48, 60, 135 and 143 and iconversorasn.h's 71,
# CFileASN's two ReadFromFile, DecodeObjectFunction and IConversorASN::Desconverte for ModuloDadosDisponiveisCarga, which
# it holds inlined through vota::LeDadosDisponiveisCarga (unit 287's, out of line in a TU of its own; that fragment has
# the measurement). In the order of the disassembly (the folded readout prints the log's literal before
# CLogVota::GetInst, the disassembly after): comum::CAppInfo::GetInst; the md::CDadosDisponiveisCarga of
# (CPath::GetPathEstatico(FLASH_INTERNA) / "dadoscarga.dat").string(), whose temporaries go in the reverse of their
# construction once it is read; comum::CGeradorRelVersaoPacoteDados (unit 287) over its packages, the constructor held
# inlined; CLogVota::GetInst().loga("Imprimindo versões dos pacotes"); the generator's Imprime (fn 5592) with "versões dos
# pacotes" and std::format("{}ª via", the byte at +75 of GetVota()'s result plus one); then the byte at +75 of a second
# GetVota()'s result plus one, CSincronizaVota::SincronizaEstadoGeralVota (fn 491), CMaisInformacoes::GetInst with 0
# (fn 1280) as the next state, the generator's D2 (fn 3691) and the data's destruction. 183 over 2146 rows, all
# operand-only, before step 8. Chosen: `&CMaisInformacoes::GetInst()` through its default argument for the 0, the
# names of the locals, `.string()` for the path's text, and the two members that reach +75
# (cestadogeralvota.h's non-const GetNumViasImpressasRelatorios, cnumviasimpressasrelatorios.h's
# IncrementaNumViasVersoesDados). Its object now gives the copies of libc++'s destroy of the two vectors
# md::CDadosDisponiveisCarga holds (fns 3863 and 5956), with strict aliasing, which the tree root
# src/app/roots_dadoscarga.cpp stood for until this file was written: it went, and the two keep their scores, 4 over 104
# and 4 over 118 rows, the four calls of free, and their matches.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_ELEITOR_INICIOVOTACAO_ESTADOS_SRCS := src/app/vota/eleitor/iniciovotacao/cimpressaozeresimatardia.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoestadourna.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaolistaeleitores.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoversaopacotes.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaopu.cpp \
    src/app/vota/eleitor/iniciovotacao/cconfirmaregerarzeresima.cpp
UENUX2_SRCS += $(APP_VOTA_ELEITOR_INICIOVOTACAO_ESTADOS_SRCS)
# The members not reconstructed: 176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.cpp gives the vtables
# trapping bodies, compiled with the unit's flags
$(ROOT)/$(APP)/176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.o: $(ROOT)/src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/auxiliares/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/util/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.cpp -o $(R)
# nothing reconstructed stores CImpressaoZeresimaTardia's vptr yet:
# 176-uenux2-app-vota-eleitor-iniciovotacao-estados-roots.cpp takes its vtable's address
$(ROOT)/$(APP)/176-uenux2-app-vota-eleitor-iniciovotacao-estados-roots.o: $(ROOT)/src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.o $(APP)/176-uenux2-app-vota-eleitor-iniciovotacao-estados-roots.o
