# ecourna: the app/dados/asn/resultadournacadastro converters (CConversorApresentacaoFotoEleitor, ComparecimentoMesario,
# EstadoComparecimento, EstadoHabilitacaoPorCodigo, HabilitacaoBiometrica), the converter they share for the voter's
# identification record (app/dados/asn/cconversorregistroidentificacaoeleitor.cpp, no record names its file) and two
# out-of-line constructors their bodies call (CApresentacaoFotoEleitor, fn 1081 after binaryen's folding;
# CIdentificadorEleitor(TSharedIdentificadorEleitor), fn 5172).
# cconversorresultadournacadastro.cpp is unit 105's, with the converters it builds.
# CConversorHabilitacaoBiometrica::DoDeconverte (9066) is written and `differs`. The target calls
# IConversorASN<EstadoHabilitacaoPorCodigo, CEstadoHabilitacaoPorCodigo>::Deconverte with no landing pad and binaryen
# inlined it there (its 176-byte frame is 9066's fourth stack prologue). With IConversorASN's destructor `{}` ours
# invoked it, through its table slot, and the row was `unresolved` there: a temporary converter, the converter
# declared first in the function, the result in a named local and a named CHabilitacaoBiometrica each kept the invoke
# (wasm-objdump -d -r of the object). With the destructor `= default` (unit 105's fragment, for 9137) the converter
# local has no cleanup, the call is direct and binaryen inlines it as the target does: 140 over 873 rows (7 inserted,
# 5 deleted) with the result passed in the constructor's call, 134 over 870 (4 and 4) with it in a named local, the
# form written (estadoHabilitacao, a chosen name), which loads ultimoScore after Deconverte's code, where the target
# does. A const auto& and a non-const local give the same object function; a temporary converter or a named
# CHabilitacaoBiometrica returned give other code. What is left is DeconverteErroLeituraBiometria's, which binaryen
# inlines too (9066's third prologue): the target tests `>= 13` before the throw, lays the string's landing pad before
# the CErroLeituraBiometria call, and keeps that object at +12 above the string at +0. Written with the return in the
# cases (as here), ours tests `> 12` and lays the pad after the call, with the target's slots; with the cases breaking,
# the default throwing and the return after the switch, the test and the pad are the target's and the two slots swap
# (the string at +4): 125 over 868, 2 rows inserted and 2 deleted; `if (> 12) throw` before the return gives the same
# swap and a signed test (126 over 868). Not found: a form with both. Also measured on the object, each giving our test
# or other code: a return of each enumerator, a CErroLeituraBiometria of each, thirteen separate returns, the switch on
# asInt(), the throw in the default with the return in the cases, an if with the return first, a named result in the
# cases, and the return spelled three other ways.
# CConversorComparecimentoMesario::DoDeconverte (9106) and CConversorEstadoComparecimento::DoDeconverte (9081) match,
# each with a form the target's landing pads decide, measured in the whole link (pnpm wasm score) and on the object:
# - 9106 returns its result through a named local (comparecimento, a chosen name). With `return
#   CComparecimentoMesario(...)` the object lays the constructor's normal path out right after the call and its landing
#   pad later, where the target has the pad first (47 over 225, 4 rows inserted and 13 deleted); with the named local,
#   24 over 221, all operand rows. The IR puts the calls on the same four pads either way. The name, its type spelled as
#   the class, and the local's not being const are choices: TDado and const give the same object function.
# - 9081 holds its second habilitacaoBiometrica_isPresent() test in a named bool (temHabilitacaoBiometrica, a chosen
#   name) before the if. The target gives that test and the last return's constructor a landing pad of their own (16
#   pads in all); the test written in the condition shares the first test's pad (15, 119 over 813, 5 rows deleted);
#   named, 106 over 813, all operand rows; `if (const bool b = ...)` gives other code, so the bytes ask for the value
#   held in a statement before the if. The bool's const is a choice (non-const gives the same object). Why the source
#   tests the field a second time is not known.
DADOS_RUC_ASN_SRCS := app/dados/asn/resultadournacadastro/cconversorapresentacaofotoeleitor.cpp \
                 app/dados/asn/resultadournacadastro/cconversorcomparecimentomesario.cpp \
                 app/dados/asn/resultadournacadastro/cconversorestadocomparecimento.cpp \
                 app/dados/asn/resultadournacadastro/cconversorestadohabilitacaoporcodigo.cpp \
                 app/dados/asn/resultadournacadastro/cconversorhabilitacaobiometrica.cpp \
                 app/dados/asn/cconversorregistroidentificacaoeleitor.cpp \
                 app/dados/resultadournacadastro/capresentacaofotoeleitor.cpp app/dados/cidentificadoreleitor.cpp

# DADOS_RUC_ASN_TRY=1 in the environment leaves these TUs and their roots out, so tools/round/try-tu.sh can compile them as
# candidates.
ifndef DADOS_RUC_ASN_TRY
ECOURNA_SRCS += $(DADOS_RUC_ASN_SRCS)
# prerequisites only (no recipe: the generic rule compiles them): the ASN.1 headers, which the generic rule does not name
$(foreach u,$(DADOS_RUC_ASN_SRCS),$(eval $(ROOT)/$(APP)/ecourna/$(subst /,_,$(u)).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# the converters' users are not reconstructed yet: 09-ecourna-app-dados-asn-resultadournacadastro-roots.cpp keeps them the way the target reaches them
$(ROOT)/$(APP)/09-ecourna-app-dados-asn-resultadournacadastro-roots.o: $(ROOT)/src/units/09-ecourna-app-dados-asn-resultadournacadastro-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/09-ecourna-app-dados-asn-resultadournacadastro-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/09-ecourna-app-dados-asn-resultadournacadastro-roots.o
endif
