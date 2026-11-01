# uenux2 comum::CCandidaturasDSNumero's call operator (src/app/comum/dados/ccandidaturasds.cpp), which binaryen inlines
# into its one caller, api::CDataText<comum::CCandidaturasDSNumero>::GetText (target fn 12742; unit 79's roots keep the
# class's vtable, and unit 102's roots object gives the GetText the link keeps).
#
# What the bytes give (ccandidaturasds.h has the class): 12742 builds "CCandidaturasDSNumero" for GetCandidaturaAtual
# (fn 2838), then reads the post's digit count (CConfiguracaoEleicao::GetInst, fn 187, and GetCargo, fn 861, the byte at
# +12) before the candidacy's number at +4, and formats the two as unsigned with "{:0{}}"; the digit count in a local
# before the call gives that order. The operator has no target function of its own, so where it is defined is a choice:
# a file of its own beside the class's header, named after it (docs/how-to-decompile.md step 3, rule 4). Its siblings'
# operators are in ccandidaturas.cpp, unit 89's, another choice; a definition there or in the class was not measured.
#
# 12742 matches since fn 11973 is in the link (unit 183): the end of its format string, "{:0{}}", is in the target the
# tail of "  {}{}{:0{}}" (address 1042, 11973's literal). Without that literal it read `unresolved` on that one
# operand, a string of its own in our link (pnpm wasm score: 16 over 214 rows, all operand-only, in the whole link
# before steps 7 to 9), and a variant link that held the literal (docs/reference/facts/workflow.md W13 "One variant
# object in the whole link") re-pointed it `IDENTICAL` with its operand kinds verified, as it did 12621 (unit 121's
# row), which ends in the same literal.
#
# Chosen: the file's path, the local's name and type (uebyte, the byte the body reads).
CCANDIDATURASDS_SRCS := src/app/comum/dados/ccandidaturasds.cpp
UENUX2_SRCS += $(CCANDIDATURASDS_SRCS)
# cconfiguracaoeleicao.h reaches CHorariosUrna, which includes Boost (as unit 88's sources do).
$(ROOT)/$(APP)/uenux2/$(CCANDIDATURASDS_SRCS).o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
