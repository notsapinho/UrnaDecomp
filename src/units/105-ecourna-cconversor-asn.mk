# ecourna: the CConversor* converters of app/dados/asn that the earlier units left out, the data classes they build and
# what they share. Written, by class (slot 2, slot 3): CConversorDetalhamentoComparecimento (9222, 9221),
# CConversorFederacao (9217, 9216), CConversorFederacoes (9212, 9207), CConversorParametrizacaoUrna (9173, 9171),
# CConversorConfiguracaoMunicipios (9141, 9137), CConversorConfiguracaoMunicipio (9144, 9142),
# CConversorIdentificacaoSecaoEleitoral (9129, 9127), CConversorComparecimentoSecao (9126, 9120),
# CConversorIdentificacaoJustificativa (9065, 9064), CConversorDadosCifracao (9062, 9061),
# CConversorDadosComparecimentoCifrado (9060, 9057), CConversorDadosComparecimento (9102, 9095) and
# CConversorResultadoUrnaCadastro (9056, 9052); with them the Converte and Deconverte thunks of IConversorASN that those
# classes instantiate, the two helpers below and the constructors of CDetalhamentoComparecimento (5094), CFederacoes
# (9045), CParametrizacaoUrna (9029), CMunicipioZona (5108), CIdentificacaoSecaoEleitoral (5110), CComparecimentoSecao
# (5092) and CIdentificacaoJustificativa (1875). CConversorHorariosUrna::DoConverte (9133) and
# CConversorMunicipioZona::DoDeconverte (9130) moved into units 15's and 16's sources. CConfiguracaoMunicipio's
# constructor is out of line and binaryen inlines it into 9142, its only caller: a clang inline gives the temporary's
# call-slot optimization, no copy, where 9142 copies four words.
#
# Files. Records name asn/resultadournacadastro/cconversorresultadournacadastro.cpp only. The others are chosen by
# how-to step 3, rule 3: the record directories for the result and parametrization families, asn/federacoes/ mirroring
# dados/federacoes/ (no record names it), asn/ beside CConversorHorariosUrna for the municipalities and the section,
# dados/parametrizacaourna/ and dados/federacoes/ beside their siblings for the new data classes.
# asn/sequenciaasn.hpp (ConverteSequencia, DeconverteSequencia) and asn/octetstringasn.{hpp,cpp} (ConverteOctetos 9063,
# DeconverteOctetos 5095) are chosen files and names. ParaVetor and ParaMapa (9134) are chosen names and private statics
# of CConversorConfiguracaoMunicipios by measurement: a file-static ParaMapa is inlined into 9137. Chosen too: the
# getters' and parameters' names of the new classes, which follow the ASN.1 fields.
#
# Forms that the bytes decide (each measured against the alternative in the target function's own shape):
# - ConverteSequencia is std::transform with a lambda, not a range-for: the range-for gives the landing pads of 1970 in
#   the other order. It returns ASN1::SEQUENCE_OF<TEntidade>, whose vptr and theInfo 1970 receives.
# - 9217 is std::transform over a back_inserter: the range-for keeps the field's load inside the loop, and with a
#   reference taken once the frame holds the vector at +16 where 9217 has +4.
# - 9141 calls ParaVetor, inlined: written in place, the transform's cleanup and the outer one are one block.
# - 9120 binds the vector to a const reference. A by-value local, a temporary or a copy of the sequence first give one
#   block for the two exception paths (94 over 389); the reference gives the target's two, each with its call of ~vector,
#   which keeps 5100 out of line. The form is this function's: 9217's vector goes from 506 rows to 381 with it, and
#   9102's justificativas from 1741 to 1455.
# - 9129 holds the converted MunicipioZona in a named local, destroyed after the two stores; a temporary goes first.
# - 9129, 9173: the entity is declared before the converter, and 9173's second converter after the first assignment:
#   the other declaration orders give other rows.
# - 9217, 9144, 9222 go through a value_type temporary: set_identificador(v) gives 471 rows, not 506.
# - 9212 calls set_federacoes(const_reference): set_federacoes() = v inlines it. Its if tests empty() first: the other
#   order gives other rows.
# - 9063 is an insert into an empty OCTET_STRING: the (first, last) constructor gives other rows.
# - 9102's optional fields insert the sequence: their value_type classes exist in the target, and take no assignment
#   from SEQUENCE_OF<T>.
# Forms that give the same bytes (rows of the function in the object, object-local numbers masked):
# set_local(v) and set_local() = v (rows 128); set_chave() = x and set_chave(x) (315); set_anoNascimentoEleitor(v) and
# set_anoNascimentoEleitor() = v (144); set_sigla(v) and set_sigla() = v (506); plain values and TQtdEleitor temporaries
# in 9221's constructor call (57); const auto for const TVectorNumeroPartido in 9217 (506); const auto& for the by-value
# local in 9141 (676) and in 9102's sequencia (1741). The form written is the shorter, or the one the sibling lines use.
#
# Headers changed for this unit, each from the target: src/asn1/modules/ModuloConfiguracaoMunicipios.h (HorariosUrna's
# fields are DataHoraJE: 9133 builds each through a temporary, vtable 1556172), ModuloResultadoUrnaCadastro.h,
# ModuloConfiguracaoMunicipios.h and ModuloFederacoes.h (eleitores, justificativas, configuracoes, federacoes and partidos
# are typedefs of SEQUENCE_OF<T>: RTTI holds no value_type class for them, src/asn1/README.md), ModuloFederacoes.h
# (set_federacoes(const_reference), 9209) and dados/federacoes/cfederacao.hpp (TVectorNumeroPartido holds 2-byte
# TPartidoID: 9217 and 9216 step by 2; 9047 keeps its bytes and its match line follows the new symbol).
# ModuloInformacaoMidia.h: data, dataInicial and dataFinal are DataHoraJE too: 9203 and 9201 store vtable 1556172, and
# RTTI holds no DataGeracao, a made-up name, so ModuloTiposEleitorais.h lists only the fields it still holds.
# cidentificacaosecaoeleitoral.hpp and cconfiguracaomunicipio.hpp replace the layout stand-ins of units 10 and 07.
#
# Names. Hand edits in splat/symbol_addrs.txt, each with its evidence: 9029 and 9043 (one holder of the slot), 3813 and
# 5842 (one written caller, and 11616 not written), 516 and 1076 (names only: our bodies differ, so those rows do not
# match), and five theInfo records by the type name each holds (docs/reference/facts/asn1.md A3). The thunks 9098 9100
# 9123 9140 9183 9210 and 9099 9122 9139 9160, their merges 1970 and 2926 and 9209 need no line: the scan pairs them by
# content, each alone and all together.
#
# Written, and not a match yet:
# - 9226, 9200, 9061, 9057, 9056, 9052, 9054 and 5095: `target call 306 | ours call 2671`. 306 is
#   __exception_guard_exceptions<vector<uebyte>::__destroy_vector>'s destructor with __destroy_vector out of line (call
#   4967); ours inlines it and joins 2671, which is the vector<TPartidoID> guard. A probe at -Oz -fexceptions gives that
#   shape, 9 rows and the call, and ecourna's flags give 34 rows and no call, so -Oz fits. That the copy is the executable
#   TU's is a reading, not measured: no object of ours holds it. Rows otherwise operand-only (9061 52 over 538, 9057 71
#   over 555, 9056 134 over 857, 9052 100 over 889).
# - 9060, 9062: table slot of vector<char>::__assign_with_size, target 1158 (slots 6259, 7008), 39 over 175 rows.
# - 9130, 9127, 9142, 9221, 9228: operand-only, on the CBaseType constructors 5850, 5848, 5849, 2851, 1960 and 5682, whose
#   names their other callers or cbasetype.hpp's unit bring. 9202 waits for CDadosGeracaoMidia's 2240 too.
# - 9216: `NOME` of TFederacaoID (.bss), and 191 rows over 723: the inlined range test is written the other way round
#   and the element goes through a temporary (a loop gives neither that nor 9214 out of line).
# - 9179: `NOME` of TProcessoEleitoralID (.bss). 9117: numeroInscricao's theInfo (.bss).
# - 9106 and 9081: one extra branch island or landing pad around a call of an ASN.1 copy (47 over 225, 121 over 813; an
#   if for the ternary gives 48 over 226, and const auto& on the registro local changes neither).
# - 9137: 118 over 399 as written, a temporary, with 22 rows inserted and 21 deleted. const auto& on the vector gives 65
#   over 390, 13 and 13, and stops on `target br 2 | ours local.get 2` at +0x279, the placement of the map's cleanup.
# - 3733, 3734, 5365, 5708 and their merges 6031, 6032: uenux2's copies of Converte and Deconverte (records under
#   p/include/, no landing pads). They come first in the link once a uenux2 TU instantiates them: their callers
#   10290, 10291, 11399, 11400, 11422, 11440 and 11616 are not written.
# - 1006, 3813, 5842, 5846: copies that 11616, a uenux2 function not written, brings first in the link. 1006 is one test
#   off (2 over 121, `i32.and | i32.ne` at +0x20): a probe of the destructor at uenux2's flags gives the target's
#   `i32.and; i32.eqz`, ecourna's gives `i32.ne`. 3813, 5842 and 5846 have no landing pads in the target, and ours do
#   (206 over 352, 185 over 295, 312 over 449).
# - 9029: 3777, CParametrosUrna's copy constructor, is a call in the target, and binaryen inlines it here, its one caller
#   in our link (440 over 454): its other caller, 7787, is not written.
CCONVERSOR_ASN_SRCS := app/dados/cdetalhamentocomparecimento.cpp app/dados/federacoes/cfederacoes.cpp \
                 app/dados/parametrizacaourna/cparametrizacaourna.cpp \
                 app/dados/processoeleitoral/cconfiguracaomunicipio.cpp app/dados/cmunicipiozona.cpp \
                 app/dados/cidentificacaosecaoeleitoral.cpp \
                 app/dados/resultadournacadastro/ccomparecimentosecao.cpp app/dados/resultadournacadastro/cidentificacaojustificativa.cpp \
                 app/dados/asn/cconversordetalhamentocomparecimento.cpp \
                 app/dados/asn/federacoes/cconversorfederacao.cpp app/dados/asn/federacoes/cconversorfederacoes.cpp \
                 app/dados/asn/parametrizacaourna/cconversorparametrizacaourna.cpp \
                 app/dados/asn/cconversorconfiguracaomunicipios.cpp app/dados/asn/cconversorconfiguracaomunicipio.cpp \
                 app/dados/asn/cconversoridentificacaosecaoeleitoral.cpp \
                 app/dados/asn/resultadournacadastro/cconversorcomparecimentosecao.cpp \
                 app/dados/asn/resultadournacadastro/cconversoridentificacaojustificativa.cpp \
                 app/dados/asn/octetstringasn.cpp \
                 app/dados/asn/resultadournacadastro/cconversordadoscifracao.cpp \
                 app/dados/asn/resultadournacadastro/cconversordadoscomparecimentocifrado.cpp \
                 app/dados/asn/resultadournacadastro/cconversordadoscomparecimento.cpp \
                 app/dados/asn/resultadournacadastro/cconversorresultadournacadastro.cpp
ECOURNA_SRCS += $(CCONVERSOR_ASN_SRCS)
# prerequisites only (no recipe: the generic rule compiles them): the ASN.1 headers, which the generic rule does not name
$(foreach u,$(CCONVERSOR_ASN_SRCS),$(eval $(ROOT)/$(APP)/ecourna/$(subst /,_,$(u)).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# the converters' users are not reconstructed yet: 105-ecourna-cconversor-asn-roots.cpp keeps them the way the target reaches them
$(ROOT)/$(APP)/105-ecourna-cconversor-asn-roots.o: $(ROOT)/src/units/105-ecourna-cconversor-asn-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/105-ecourna-cconversor-asn-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/105-ecourna-cconversor-asn-roots.o
