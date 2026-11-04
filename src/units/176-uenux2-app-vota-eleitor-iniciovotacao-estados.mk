# uenux2 the iniciovotacao states that no landed file holds: vota::CConfirmaRegerarZeresima (ProcessInput, target fn
# 11838; its StartState is one body with vota::CConfirmaImpressaoZeresima's, fn 5958), vota::CImpressaoZeresimaTardia
# (StartState, fn 11932, with vota::CLogVota::LogaMesarioIndagadoHorarioUrna, which it holds inlined, added to
# app/vota/log/clogvota.cpp), and the four states vota::CMaisInformacoes::ProcessInput (fn 11896, unit 104's file) goes
# to, vota::CImpressaoEstadoUrna, CImpressaoListaEleitores, CImpressaoVersaoPacotes and CImpressaoPU: their GetInst and
# constructors, which fn 11896 holds inlined, and their statics, whose exit-time destructors match (11913 and 11912,
# 11910 and 11909, 11907 and 11906, 11904 and 11903, each pointer's first). The class heads say what each layout rests
# on. CImpressaoListaEleitores::StartState (fn 11908) is written in cimpressaolistaeleitores.cpp, over fragment 317's
# comum::ImprimeListaEleitores, and does not match yet (src/units/317-uenux2-relatorios-aptos.mk has the measurement);
# its trap and the unit's pending file went with it.
# CImpressaoZeresimaTardia's constructor, GetInst, statics and ProcessInput are written since (below).
# CConfirmaRegerarZeresima's constructor, GetInst and statics are written, unit 104's shape, and
# vota::CReinicioVotacao::StartState (fn 11835, unit 138) holds GetInst inlined: the new of 20 bytes, the base's
# constructor (fn 224) with 2, the vptr, the copy of CTelasVota's +84 and +88 (a getter added to ctelasvota.h, its name
# chosen), the mutex's unlock (fn 150); its statics' exit destructors match with 11835 (11840 the pointer's, 11839 the
# mutex's, @1834940 and @1834916, which 11835 alone votes for and these two destructors read too), and the roots' sink
# of this class's vtable went, 11835 storing it.
#
# vota::CImpressaoPU::StartState (slot 2, target fn 11902) is written in cimpressaopu.cpp and matches: the shape of
# CImpressaoVersaoPacotes's (11905) over comum::CGeradorRelPU (unit 183's cgeradorrelpu.{h,cpp}, which say what it
# prints): the object built in the frame (its vptr and the zeroed builder; the class has no key function, so this object
# emits its vtable and destructors now), CLogVota's "Imprimindo par�metros de urna", Imprime with "par�metros de urna"
# (the same literal's tail) and std::format("{}� via") of the PU's copies (the byte at +76 of GetVota()'s
# CNumViasImpressasRelatorios, GetNumViasPU) plus one, as an int, then that byte incremented (IncrementaNumViasPU,
# added to cnumviasimpressasrelatorios.h, its name chosen), CSincronizaVota::SincronizaEstadoGeralVota (491) and
# CMaisInformacoes as the next state (1280). 287 over 2778 rows (pnpm wasm score, the plain link before step 8), all
# operand-only, the one operand that is no call and no data address being the format buffer's table slot (148 in the
# target). Its stand-ins in units 123, 183, 234, 246 and 265 went with it (their fragments say which).
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
# convention); the destructor declared first; the private constructor of CConfirmaRegerarZeresima, declared and not
# defined; StartState as the key function of the four CImpressao* states, so each class's .cpp emits its vtable;
# LogaMesarioIndagadoHorarioUrna's name, from its message, and its place in clogvota.cpp, after
# LogaApresentadaTelaReinicioVotacao. The paths, by how-to step 3's rules (no record names these classes' files), each
# header beside its .cpp and named after the class (rule 4):
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
# Written since, measured in the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv before
# steps 7 to 9 matched it:
# - vota::CImpressaoZeresimaTardia's constructor, GetInst and statics, in cimpressaozeresimatardia.cpp after the
#   destructor and before StartState (lines a choice; the file has no record): unit 104's shape, the new of 20 bytes,
#   the base's constructor with 2 and the copy of CTelasVota's +60 and +64 through ctelasvota.h's
#   GetTelaImpressaoZeresimaTardia (a getter added after GetTelaFimVoto, its name chosen). Its one target caller,
#   vota::CConfirmaImpressaoZeresima::ProcessInput (fn 11927, unit 169), holds GetInst inlined, and the statics' exit
#   destructors match with it, by the scan's content pass: 11934 the pointer's (@1834240), 11933 the mutex's
#   (@1834216). The mutex's name is `vote:1 by:11927` in splat/symbol_addrs.txt; its other reader is its exit
#   destructor, 11933.
# - vota::CImpressaoZeresimaTardia::ProcessInput (fn 11931): Read() on the form (record cinteractiveform.h:57); on
#   api::INPUT_CORRIGE (5) a CLogVota member and vota::CInformacaoZeresimaTardia::GetInst (unit 169's file, inlined
#   here, its one caller) as the next state; on INPUT_CONFIRMA (9) the vote's state EAVGERARZE (52) through
#   CEstadoGeralVota::SetEstadoVota (unit 169's fragment), vota::CSincronizaVota::SincronizaEstadoGeralVota (fn 491),
#   another CLogVota member and vota::CGeraZeresima::GetInst (fn 5962). 42 over 264 rows, operand-only (calls, data,
#   and the .bss addresses of CInformacaoZeresimaTardia's statics). Each log member is called on CLogVota::GetInst()'s
#   result (fn 184), whose stack frame opens after that call (docs/reference/facts/reading.md R10), and builds its
#   text for comum::IEventosLog::loga (fn 233): LogaMesarioConfirmaHorarioUrnaErrado and
#   LogaMesarioConfirmaHorarioUrnaCorreto, from their texts ("Mesário confirma que o horário da urna está errado" and
#   "... correto"), added to app/vota/log/clogvota.cpp below LogaEleitorImpedido; their names and that place are
#   chosen. The order of the cases and the empty default are chosen (the other order was not measured).
#
# vota::CImpressaoVersaoPacotes::StartState (target fn 11905, slot 2) is written in cimpressaoversaopacotes.cpp and
# matches, named by its records (srcloc-anchor): cfileasn.h's lines 78, 48, 60, 135 and 143 and iconversorasn.h's 71,
# CFileASN's two ReadFromFile, DecodeObjectFunction and IConversorASN::Desconverte for ModuloDadosDisponiveisCarga,
# which it holds inlined through vota::LeDadosDisponiveisCarga (unit 287's, out of line in a TU of its own; that
# fragment has the measurement). In the order of the disassembly (the folded readout prints the log's literal before
# CLogVota::GetInst, the disassembly after): comum::CAppInfo::GetInst; the md::CDadosDisponiveisCarga of
# (CPath::GetPathEstatico(FLASH_INTERNA) / "dadoscarga.dat").string(), whose temporaries go in the reverse of their
# construction once it is read; comum::CGeradorRelVersaoPacoteDados (unit 287) over its packages, the constructor held
# inlined; CLogVota::GetInst().loga("Imprimindo versões dos pacotes"); the generator's Imprime (fn 5592) with "versões
# dos pacotes" and std::format("{}ª via", the byte at +75 of GetVota()'s result plus one); then the byte at +75 of a
# second GetVota()'s result plus one, CSincronizaVota::SincronizaEstadoGeralVota (fn 491), CMaisInformacoes::GetInst
# with 0 (fn 1280) as the next state, the generator's D2 (fn 3691) and the data's destruction. 183 over 2146 rows, all
# operand-only, before step 8. Chosen: `&CMaisInformacoes::GetInst()` through its default argument for the 0, the
# names of the locals, `.string()` for the path's text, and the two members that reach +75
# (cestadogeralvota.h's non-const GetNumViasImpressasRelatorios, cnumviasimpressasrelatorios.h's
# IncrementaNumViasVersoesDados). Its object now gives the copies of libc++'s destroy of the two vectors
# md::CDadosDisponiveisCarga holds (fns 3863 and 5956), with strict aliasing, which the tree root
# src/app/roots_dadoscarga.cpp stood for until this file was written: it went, and the two keep their scores, 4 over 104
# and 4 over 118 rows, the four calls of free, and their matches.
#
# vota::CImpressaoEstadoUrna::StartState (target fn 11911, slot 2) is written in cimpressaoestadourna.cpp, after the
# statics (its line is chosen), and matches, over comum::CImprimirExtratoCarga::Imprime (5591): both, the measurements
# and what is chosen are in src/units/296-uenux2-relatorios-impressao.mk, whose roots keep 5591's other call site.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_ELEITOR_INICIOVOTACAO_ESTADOS_SRCS := src/app/vota/eleitor/iniciovotacao/cimpressaozeresimatardia.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoestadourna.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaolistaeleitores.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoversaopacotes.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaopu.cpp \
    src/app/vota/eleitor/iniciovotacao/cconfirmaregerarzeresima.cpp
UENUX2_SRCS += $(APP_VOTA_ELEITOR_INICIOVOTACAO_ESTADOS_SRCS)
