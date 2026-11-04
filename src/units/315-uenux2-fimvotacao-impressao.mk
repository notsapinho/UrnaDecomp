# uenux2 two print states of app/vota/eleitor/fimvotacao/ in files no landed unit compiled, cimprimindobehb.cpp and
# cimprimirbjust.cpp, the files their records name (their stub-only files before), with their heads beside them:
# - vota::CImprimindoBEHB: StartState (target fn 12074, records cimprimindobehb.cpp 45:88 and 46:108), which holds the
#   private ImprimeRelatorio (record :55:22) behind a 144-byte prologue, matched; GetInst (inlined into fn 12071, unit
#   104's CImprimindoBim::StartState), the constructor and the statics, whose exit destructors 12075 and 12076 match;
# - vota::CImprimirBJust: StartState (fn 12068, records cimprimirbjust.cpp 51:87 and 52:107), which holds the private
#   imprimeBJust (record :69:29) behind a 144-byte prologue, matched; GetInst (inlined into fn 12065, unit 104's
#   CImprimirBUOutrasObrigatorias::StartState, not matched), the constructor and the statics (exit destructors 12069,
#   12070: they wait for 12065's match, which names the objects).
#  Evidence: the vtables (@1541428 and @1541636: slots 0 and 1 the bodies the states with no data member share, 174 and
# 144, slot 2 the StartState); the vptr stores 1541436 and 1541644, the base's constructor with 0 and the .bss words
# (@1833680 and @1833656, @1833736 and @1833712) in the inlining callers; the records' function names (`void
# vota::CImprimindoBEHB::ImprimeRelatorio()`, `void vota::CImprimirBJust::imprimeBJust()`, non-static members, their
# case the records'); the Assert texts, as CImprimindoBim's (codes 3484 and 3485, 3468 and 3469 in
# api/util/eueasserterror.h, names chosen to the columns). Each StartState asserts the vote's and the closing's states
# and prints its report as unit 104's CImprimindoBim does (that fragment has the sequence): "behb.dat" and "behb.vsu",
# LogaImprimindoRelatorio with RELATORIO_ELEITORES_HABILITADOS_BIOGRAFICAMENTE (12) and 1 after CriaArquivoImprimindo,
# and the title "boletim de eleitores\nhabilitados biograficamente"; "buj.dat" and "buj.vsu", the log call with
# RELATORIO_BUJ (4) in StartState, before imprimeBJust's frame opens, and the title "boletim de justificativa
# eleitoral". The titles are named const char arrays (each text lies right before its class's typeinfo name, @485744
# and @485872, and the target's eight-byte loads of it are align=3), their names chosen. CImprimindoBEHB then goes to
# vota::CRetirarMR::GetInst (fn 2291, unit 156's); CImprimirBJust to CRetirarMR unless comum::CInformacaoEleicao's
# ImprimeBJust (fn 1950) holds, then to vota::CImprimindoBim (fn 5985): the target tests the negation first, so the
# if/else spells it so (the other order put the arms the other way round: 61 over 430 rows, 1 deleted).
#  Measured in the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv before steps 7 to 9:
# 12074 54 over 407 rows, 12068 60 over 430, all operand-only.
#  Chosen: the files' layout above and between the records, the local names (impresso, and impressoraBJust, whose 28
# characters with its indent put the instance() call at the record's column 29), the members' being private, and the
# heads' paths beside the .cpp files.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
FIMVOTACAO_IMPRESSAO_SRCS := src/app/vota/eleitor/fimvotacao/cimprimindobehb.cpp \
    src/app/vota/eleitor/fimvotacao/cimprimirbjust.cpp
UENUX2_SRCS += $(FIMVOTACAO_IMPRESSAO_SRCS)
# cimprimirbjust.cpp includes app/comum/dados/cconfiguracaoeleicao.h, which reaches Boost through
# CConfiguracaoMunicipio's CHorariosUrna (an include path, not a flag of the code: unit 104 adds the same)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/fimvotacao/cimprimirbjust.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
