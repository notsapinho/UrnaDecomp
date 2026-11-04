# ecourna: the app/dados/asn/resultadournacadastro converters (CConversorApresentacaoFotoEleitor, ComparecimentoMesario,
# EstadoComparecimento, EstadoHabilitacaoPorCodigo, HabilitacaoBiometrica), the converter they share for the voter's
# identification record (app/dados/asn/cconversorregistroidentificacaoeleitor.cpp, no record names its file) and two
# out-of-line constructors their bodies call (CApresentacaoFotoEleitor, fn 1081 after binaryen's folding;
# CIdentificadorEleitor(TSharedIdentificadorEleitor), fn 5172).
# cconversorresultadournacadastro.cpp is unit 105's, with the converters it builds.
# CConversorHabilitacaoBiometrica::DoDeconverte (9066) is written and `unresolved` on the table slot of
# IConversorASN<EstadoHabilitacaoPorCodigo, CEstadoHabilitacaoPorCodigo>::Deconverte: the target calls that member with
# no landing pad and binaryen inlined it there (its 176-byte frame is 9066's fourth stack prologue), where ours invokes
# it. In the object's LLVM IR the converter local's cleanup pad is empty but joins the pad of the
# CEstadoHabilitacaoPorCodigo temporary before the resume, so the invoke stays. A temporary converter, the converter
# declared first in the function, the result in a named local and a named CHabilitacaoBiometrica each keep the invoke
# (wasm-objdump -d -r of the object); the call is direct only with no converter object to destroy, which no form of this
# function tried gives.
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
#   named, 106 over 813, all operand rows. Why the source tests the field a second time is not known.
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
