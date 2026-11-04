# uenux2 comum relatorios: comum::CDataSourcesRelatorio<RDV, DSAptos> (app/comum/relatorios/cdatasourcesrelatorio.h, its
# records' file), the report's text sources, of which the target has the instance <comum::CRdvVota, comum::CEleitores>,
# header code this unit's roots object emits; and comum::CGeradorRelPU (cgeradorrelpu.{h,cpp}, chosen paths beside the
# family's sources). Paths relative to src/uenux2.
#
# Matched:
# - DetalheCandidatoZE (target fn 11973, record cdatasourcesrelatorio.h:152:80) and DetalheCandidato (11972, no record),
#   from the roots object until fn 3872, their one user (table slots 1635 and 1636), was written (unit 325's, in
#   iniciovotacao/cgeradorresumozeresima.cpp): they match from that object now, built with strict aliasing
#   (src/app/vota/), with the same scores, and the roots' two lines went.
# - CGeradorRelPU::AdicionaParametro (677), in cgeradorrelpu.cpp.
# - With this unit's literal in the link, three written bodies of other units match too: comum's FormataNumero (fn
#   1161, unit 131), CDataText<comum::CRespostasDSNumero>::GetText (12621, the row unit 121's fragment describes) and
#   CDataText<comum::CCandidaturasDSNumero>::GetText (12742, unit 180's operator inlined), both GetText emitted by unit
#   102's roots object, whose format strings end in "{:0{}}", which the target holds as the tail of 11973's
#   "  {}{}{:0{}}" (@1042). The bodies are those units'.
#
# What the bytes decide, measured with `pnpm wasm score` against our plain link:
# - 11973 and 11972 read the post's id (+0) and its digit count (+12) before the candidacy is looked up, and the digit
#   count again after the vote count is read; the format reads the candidate's number from before. As written (a reading
#   of those loads), the id, the digit count and the number are locals and the format calls the accessor again; of the
#   other forms only the declaration order was linked. Declaring the id before the digit count
#   gives the target's load order (+12 first); the other declaration order gives the loads the other way round, 33 over
#   432 rows for 11973 with 2 inserted and 2 deleted. As written, 11973 scores 27 over 430 and 11972 20 over 417, all
#   operand-only, before steps 7 to 9; their operand rows that are no call and no data address are table slots: the
#   format buffer's __prepare_write (target slot 148, fn 7324) in both, and CError's D2 (slot 69, fn 4636), the thrown
#   object's destructor, in 11973.
# - 11973's throw is ASSERT (api/util/eueasserterror.h) with code 3410, the target's constant, and the text "Assert (qtd ==
#   0u)", the condition stringized; the record's column 80 is the invocation's closing parenthesis, which the
#   enumerator's chosen length puts there (that header says how).
# - 11972 formats the vote count as an int: argument type 3 in the packed types 3348909, where the unsigned number and
#   the unsigned char digit count are type 6. The count, a md::TQtdVoto (unsigned short), is held in a `const int`.
# - 677 copies the name before it calls CStringUtils::PreencheAEsquerda (fn 753) and appends the result (fn 160): the
#   copy is a statement of its own, then +=. It scores 5 over 111 rows, all operand-only.
#
# Chosen: DetalheCandidato's name and lines; the members' access and that they are defined in the class; where the class
# closes (its other records, lines 188 to 348, lie past the end of the file, blank); the name-padding statements' form
# (a helper both members call was not tried); AdicionaParametro's name; CGeradorRelPU's member name; the paths of
# cgeradorrelpu.{h,cpp}. cgeradorrelpu.h says what the class's data show.
#
# CGeradorRelPU's destructors, matched first from this unit's roots object and now from unit 176's cimpressaopu.cpp.o
# (below): the D2 and D0 (target fns 11901, 11900), each a
# thunk that passes the vptr to a body binaryen merged, 6055 and 6054, whose other callers are RHVoice's
# RHVoice::dtree::in_list D2 and D0 (9937, 9936; `pnpm --silent wasm fn ../target/vota_web_wasm.wasm 6054` from
# asmlift-wasm/ lists callers 9936 and 11900). The class has no key function (cgeradorrelpu.h), and its one user, fn
# 11902, is not written, so the roots build the object in an unrooted optnone function, which emits the vtable and the
# inline destructor's D2 and D0 (src/units/README.md "A class with no key function", unit 67's shape), and keep the
# vtable in a sink, the reference 11902's inlined constructor stores. With the two destructors in the link binaryen
# forms the same two bodies, named byn$mgfn-shared$_ZN5comum13CGeradorRelPUD0Ev and ...D2Ev after the first member in
# link order, and
# six rows match: 11900, 11901, 6054, 6055 and RHVoice's 9936 and 9937, whose bodies did not change (they were
# `differs`, whole bodies where the target has thunks). `pnpm wasm score` against the plain link before steps 7 to 9:
# 2 over 5 rows for each thunk, 2 over 65 and 1 over 64 for the bodies, all operand-only. The target's copy is a vota
# TU's (the vtable lies in CImpressaoPU's data), a directory built with strict aliasing, and the roots compile at
# UENUX2_CXXFLAGS, with -fno-strict-aliasing: the roots object compiled both ways gives the same D2 and D0
# (wasm-objdump -d of the two functions: 148 lines in each object, cmp-equal). Since 11902 is written, its object, that
# vota TU, builds the object and emits the vtable and both destructors (names.tsv's object column), the roots' builder
# and sink went, and the six rows keep `match`.
#
# CGeradorRelPU's members for vota::CImpressaoPU::StartState (11902, unit 176's file), in cgeradorrelpu.cpp: Imprime
# (the title block, the parameters, the footer, then CPaperFormBuilder::Show with the title, the copy's text and true),
# ImprimeTituloJE (1543 over the local's municipality, zone, section and name with "Parâmetros de urna", the
# contingency header for an eUrnaContingencia urna and the pleito-2 flag set, a new line, GetIdentificacaoUrna (1942)
# at the left, CRelUtil::ImprimeDataHora of now with "Data" and "Hora", ImprimeResumoCorrespondencia and
# ImprimeSeparadorFase, each with a new line), ImprimeParametros (CConfiguracaoEleicao's municipality and pleito and
# CAppInfo's internal general state; the pleito 2 taken as CRelUtil's IncluiCabecalhoEleicoes takes it, a pleito
# nothing then reads; ImprimeHorarios; then the parameters, each AdicionaParametro of its label and std::to_string of
# the count, or "Sim"/"Não"), ImprimeHorarios (the four times of the municipality's schedule, copied first, each as
# "{} -" of ecourna's FormataHora, 2686, then FormataData, 2687, under an empty label) and ImprimeRodape (5596's text:
# unit 296's paragraph and unit 287's say why its match line names it). Each but Imprime sits in 11902 behind a stack
# frame of its own (48, 272 and 448 bytes); 11902 matches (unit 176's fragment). What the bytes decide, measured with
# pnpm wasm score of 11902 against the plain link:
# - The definition order: callees before their callers (ImprimeHorarios before ImprimeParametros, Imprime last), 287
#   over 2778 rows, all operand-only; with Imprime second and ImprimeHorarios after ImprimeParametros, 528 over 2796 (18
#   inserted, 20 deleted: local numbers, and the municipality's +496 folded into the four loads where the target adds it
#   once). docs/how-to-decompile.md step 3 says why an order can decide that.
# - The urna's type read before the title string is built (a named bool), and the municipality's reference taken before
#   the general state is read (its GetInst call precedes CAppInfo's in the target); "Sim" and "Não" built as two
#   std::string, one per arm (a conditional over the two char literals gives one copy from a select, 687 over 2846
#   with the type's read inline too).
# - The counts formatted by std::to_string(int) (fn 296, not the unsigned 327), with no cast: ecourna's
#   cparametrosurna.hpp declares the nine getters read here int, changed with this unit since uedword picks 327 (its
#   comment has the other readers that read them signed); every object that includes the header compiles unchanged.
# Chosen: the members' names and order (but the measured one above), their being members, the locals' names.
# The roots' stand-ins for 11902 went: w183_parametros (677's caller) and the sink that kept the vtable, since 11902
# builds the object.
#
# LinhaPartido (fn 11261, no record; its name and its place in the class, after DetalheCandidatoZE, are chosen) is
# written for unit 296, which says why and what it measures: its one user, fn 12110, passes its address (table slot
# 2921), so the roots take it beside the others. It matches by the scan's content pass.
#
# Not reconstructed: the other records of cdatasourcesrelatorio.h (TrailerProporcionalPartido 11260,
# GetLinhasEleitoresAptos's lambda 11968, TrailerProporcional 11981, TrailerMajoritario 11980, CodVerificador 11974);
# fn 3872, the one user of 11972 and 11973, is unit 325's (vota::CriaDetalheCandidato).
RELATORIOS183_SRCS := src/app/comum/relatorios/cgeradorrelpu.cpp
UENUX2_SRCS += $(RELATORIOS183_SRCS)
# cconfiguracaoeleicao.h reaches ecourna's chorariosurna.hpp, which includes Boost (unit 123 adds the path the same way)
$(addprefix $(ROOT)/$(APP)/uenux2/,$(addsuffix .o,$(RELATORIOS183_SRCS))): UENUX2_CXXFLAGS += -I$(BOOST_HDR)
W183_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
# the callers of this unit's functions are not reconstructed: the roots keep them, at the tree's flags, since the
# object emits the data sources' instances
$(ROOT)/$(APP)/183-uenux2-relatorios-roots.o: $(ROOT)/src/units/183-uenux2-relatorios-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/183-uenux2-relatorios.mk $(W183_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/183-uenux2-relatorios-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/183-uenux2-relatorios-roots.o
