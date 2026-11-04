# uenux2 vota::CSincronizaVota (src/app/vota/comum/csincronizavota.cpp, a stub-only file until now; its header
# csincronizavota.h is new) and api::CUeDesligandoError (src/api/hwil/euedesligandoerror.{h,cpp}, new), the error its
# VerificaUrnaDesligando throws. Paths relative to src/uenux2.
#
# Target functions:
#   1685  api::CUeDesligandoError::CUeDesligandoError(std::source_location)  record csincronizavota.cpp 47:15 (its
#         location is VerificaUrnaDesligando's throw); matched by that srcloc anchor
#   1836  CSincronizaVota::SincronizaRelatorios(const std::string&)  record 392:15 (the throw of code 9302); matched by
#         that srcloc anchor
#   4687  CSincronizaVota::SincronizaAssinaturaVota()   no record; matched by the scan's content pass
#   4682  CSincronizaVota::GravaBancoDadosMV()          no record; content pass
#   4668  CSincronizaVota::AssinaRDVEBancoDados()       no record; content pass
#   4662  CSincronizaVota::SincronizaBancoDados()       no record; content pass
#   4657  CSincronizaVota::GravaBancoDadosMI()          no record; content pass
#   3336  CSincronizaVota::MarcaUrnaDesligando()        no record; the census's addr pair (step 9's `ledger`), one of a
#         six-way tie of that hash (five OpenSSL ossl_init_* setters), so the match stands on its re-pointed bytes,
#         which only 3336 has: the one store of s_urnaDesligando (named by 1836's vote), which it sets to 1; its file and its place ahead of VerificaUrnaDesligando are a
#         choice (in use band 3, 3333, which holds VerificaUrnaDesligando inlined, lies three places away, with 3334
#         and 3335, 3335 stubbed in src/ecourna/unplaced.cpp, between them). Its callers, 7709 and 7710
#         (vota::CThreadVota's TrataErro), traps in unit 116's pending file, and 10226 (CThreadMonitor::Run, unit
#         116's, matched); w205_desligando stands for the first two.
# and, with no target index of their own: VerificaUrnaDesligando (record 47:15, inlined by clang into each of its seven
# target callers, 491, 1836, 3333, 4662, 6737, 7174 and 10590), SincronizaAssinaturaRelatorio (binaryen inlined it into
# 1836, its one caller, behind a stack frame of its own), AssinaESincroniza (an anonymous-namespace helper clang
# inlines into 4657) and SincronizaJustificativa (binaryen inlined it into its one caller, vota::CPedeAnoNascimento::
# ProcessInput, fn 10590, behind a 176-byte frame; a chosen name, after SincronizaEstadoGeral, and unit 283's fragment
# has its notes), which makes AssinaArquivo, the file's other signing helper, a helper of two callers that clang
# inlines into both (491 still matches).
#
# What the target fixes.
# - The class: its records name only static members (VerificaUrnaDesligando, SincronizaRelatorios), so the five members
#   no record names join it as static members, as api::CSystem's do (docs/how-to-decompile.md step 3, "Names no evidence
#   gives"); that they are members is a choice, and so are their names and the header's path. 4662 holds
#   VerificaUrnaDesligando inlined, so its code is this file's, a reading (clang inlines a static member of this .cpp
#   only here, and binaryen would not inline a function of seven callers); for 4687, 4682, 4668 and 4657 the file is a
#   choice: they are vota's file-copy and signing steps beside the ones this file's records name. In use band 2 they
#   run 4687, 4682, 4668, 4662, 4657, the order they are defined in here.
# - The flag VerificaUrnaDesligando tests: the byte at 1832936, read by 14 target functions and stored (1) by fn 3336
#   alone (csincronizavota.h says what its type rests on). Step 8 names it `vote:1 by:1836`, and 4662, which reads it
#   too, is a second match that holds the name. A callers+content hand line for it (the six other target functions that
#   throw through 1685 after testing it) was weighed by reference/splat.md's removal (a scan run twice and splat-build
#   on copies without it, beside a control): 11094 match rows and the target's sha256 either way, so it carries nothing
#   and is not kept.
# - api::CUeDesligandoError: RTTI names it and its base; 1685 builds the message "Urna desligando" with the code 4201
#   and stores the class's vptr, and its wasm type has lost the location parameter (euedesligandoerror.h says what
#   places it and why its constructor is out of line, in a file of api/).
# - The callees' order in each body is the target's, and their arguments: the ESavdPacote and ESavdArquivoUE constants
#   (CArquivosSavd's keys, written as casts of the values: the enumerators are not recovered), CopyFile's bools (false,
#   and the true every target caller passes, folded), the CriaContexto kinds and texts.
# - 1836: the report given must be one of six files (ESavdArquivoUE 86, 84, 88, 89, 106, 108), compared in that order
#   (an if chain), else CUeVotaError 9302, "O arquivo" + name + " não é um relatório válido para sincronização"
#   (both literals without the space between them, as the target holds them); it signs that file, copies it from the
#   internal flash's work directory to the external's, and SincronizaAssinaturaRelatorio copies the matching signature
#   package (all six when none matches) for the turno.
#
# Measured.
# - 4657: with the signing block (CAssinadorVota, Assina, Sync) written in place, in a nested scope, the frame's slots
#   sit 8 bytes lower than the target's (156 over 456 rows, 2 deleted); in AssinaESincroniza, which clang inlines, it
#   brings its CAssinadorVota above the caller's own slots (docs/reference/facts/codegen.md C5) and 4657 scores 47 over
#   456, operand-only (copies of link.cmd with csincronizavota.cpp.o alone recompiled).
# - That SincronizaAssinaturaRelatorio is a static member and not an anonymous-namespace function is a reading: clang
#   inlines a function of internal linkage with one call site, and the target has it behind a frame of its own; the
#   anonymous form was not measured.
# Chosen and not measured against another form: `.string()` for each path passed as a std::string (the implicit
# conversion is the other spelling); the named locals' and the helpers' names.
#
# Roots (205-uenux2-csincronizavota-roots.cpp): the callers in the link are counted, and stand-ins stand for the rest;
# 1685's second call site comes through VerificaUrnaDesligando, so that every call passes the same record and binaryen
# folds it as in the target. Its header lists the callers each stands for.
#
# 491, CSincronizaVota::SincronizaEstadoGeralVota (no record; its name is chosen from its context's texts, "Gravando o
# estado da urna" and "... sincronização do estado geral do VOTA."), matched by the scan's content pass. It takes the
# title of the context in force from the stack's last context (an std::optional<api::CApplicationContext> built in
# place, at +152, its flag at +204) or "Erro de sincronização", then under CriaContexto(2, ...) checks the shutdown flag
# (VerificaUrnaDesligando inlined), saves the internal flash's vota state (CAppInfo::SalvaVotaInterno, 3790, unit 109),
# signs file 31 and syncs, and under CriaContexto(4, ...) saves the external one (3789), calls SincronizaAssinaturaVota
# and syncs. The signing is a second file-local helper, AssinaArquivo (a chosen name), which clang inlines: its
# CAssinadorVota is the frame's highest object (+208), above the function's own, as an inlined callee's are
# (docs/reference/facts/codegen.md C5), and it is destroyed before the sync, where AssinaESincroniza (4657 holds it)
# syncs first; with AssinaESincroniza 491 differed by those two rows (2 inserted, 2 deleted, the rest operand-only).
# That the optional and the title are written in place, the two scopes, the helper's linkage and the member's line are
# chosen. Its 31 target callers are not written but 10710 and 10734 (unit 277): w205_estado stands for the others.
# SincronizaEstadoGeral (3333, its name chosen from its contexts' texts, "Gravando o estado geral da urna na MI" and
# "... na MV"), added with unit 277's 10710, one of its callers: after VerificaUrnaDesligando it builds the title as
# SincronizaEstadoGeralVota does and passes it to neither context: both CriaContexto calls (fn 676) get a string of
# length 0 (the target zeroes the size and first byte at +132 and at +48), and the title at +200 is only destroyed at
# the end. Written so (`""`; `std::string()` and `{}`, other spellings of the empty argument, are likely the same
# bytes and were not measured), its body scores 59 over 529 rows, every one an operand (with the title passed, 158 over
# 573, inserted 44, deleted 5), and it matches by the content pass; 10710 calls it at the aligned site. In between: a
# CAssinadorVota of package 120 (fn 1501), CAppInfo::SalvaGeralInterno (unit 109's file; binaryen inlines it behind a
# 16-byte frame), Assina(25) (fn 1277) and Sync, then SalvaGeralExterno, CopyFile of package 120 to 121 (fn 378) and
# Sync. That the title is built and not passed is the bytes'; the member's line after SincronizaEstadoGeralVota and its
# being a static member, as this class's others, are chosen. w205_estado_geral stands for its other callers, 7160 and
# 7306.
#
# Not written here: SincronizaRDVInternoSeguro and SincronizaRDVExternoSeguro (records 290 and 303, in the anonymous
# namespace), which fn 7174 (vota::impl::CSincronismoVotoEleitor's slot 2) holds inlined; 6737, which holds
# VerificaUrnaDesligando inlined too and calls 1551, 1701, 2826, 5736, 5737, 5761 and 5762, none of them matched. Fn 1164, CArquivosSavd::GetInst, which
# most members here call,
# is unit 95's, matched with strict aliasing in its TU (that fragment has the measurement); its name comes
# from the calls of 1501 and 1836 (step 8's `call by:1501,1836`).
#
# s_urnaDesligando is a plain bool (csincronizavota.h): vota::CImprimirBUOutrasObrigatorias::StartState (fn 12065,
# unit 104) tests it in a loop, at the loop's head only, and returns when it is set. That return, not the flag's type,
# gives the target's loop: std::atomic<bool> compiles 12065 to the same object.
CSINCRONIZAVOTA_SRCS := src/api/hwil/euedesligandoerror.cpp src/app/vota/comum/csincronizavota.cpp
UENUX2_SRCS += $(CSINCRONIZAVOTA_SRCS)
# nothing in the link calls most of these functions yet: 205-uenux2-csincronizavota-roots.cpp gives each its call sites.
# It compiles at the tree's flags.
$(ROOT)/$(APP)/205-uenux2-csincronizavota-roots.o: $(ROOT)/src/units/205-uenux2-csincronizavota-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/205-uenux2-csincronizavota.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/205-uenux2-csincronizavota-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/205-uenux2-csincronizavota-roots.o
