# comum::CEleitores::DynamicCreate (target fn 5761, celeitores.cpp, which unit 110's list compiles) and what it brings:
# md::CEleitorDinamico's third constructor (2800) and its equality (celeitordinamico.{h,cpp}, unit 91's list),
# dao::CEleitorDinamicoDAO::InserirTodos (no target index, inlined into 5761; celeitordinamicodao.cpp, now in unit
# 110's list, below), and the instances DynamicCreate's object emits: std::vector<CEleitorDinamico>::__destroy_vector
# (3763), std::__introsort over CEleitorDinamico with DynamicCreate's comparator (3762) and the helpers it calls,
# __sort3 (1392), __sort4 (3757), __sort5 (5749) and __insertion_sort_incomplete (5748), std::swap<CEleitorDinamico>
# (282) and CEleitorDinamico's implicit move assignment (470). All ten match. This fragment holds notes, the Boost path
# of two objects and a roots file; its sources are in units 110's and 91's lists. Scores are `pnpm wasm score <target>
# <index> <link> <ours>` at the default depth on whole links.
#
# Evidence:
# - 5761's records, celeitores.cpp:301 and :305 (column 15, codes 7837 "Não há informações carregadas" and 7838
#   "Informações dinâmicas já carregadas") and :358 (column 19, 7839, std::format of "Já existem informações dinâmicas
#   no banco {}" with the parameter), give the signature, the const and the throws' places. The body: the records'
#   map empty (+12) and the first record's dynamic data (CEleitorDetalhe's optional flag at +192) are tested; three
#   linear searches of the set at +52 for 0, 1 and 2 run once, before the loop; each record's identity
#   (GetIdentidadePorTipo, 708) and coverage (GetAbrangencia, 3721, with +32 and +44) give a CEleitorDinamico of state
#   0 or 1 (a br_table on the coverage: 0 when the set holds that coverage or a wider one); then
#   CEleitorDinamicoDAO's constructor (3768) over the parameter, RecuperarTodos (3766), and either the insert loop
#   (behind a 96-byte frame of its own) or two sorts (3762, twice) and a size test and element loop that throws 7839;
#   then the destructors, the table's vector first, the DAO (1704), the built vector last.
# - 2800's body: the two identities, the state, and constants for the rest (celeitordinamico.h lists them). 5761 holds
#   two emplace_back slow paths binaryen inlined, each behind a 32-byte frame: one calls 2800 with the constant 0, the
#   other with the state loaded from the caller's frame, where the fast path stored 1. Two instantiations, one per
#   call site; emplace_back(identidade, identidade) through a default argument gives the constant, and the three-
#   argument call binds its state to the slow path's reference.
# - 3762 and its helpers: its two constants 2015 and 10753 are libc++'s __limit and __ninther_threshold over 84-byte
#   elements (24 * 84 - 1, 128 * 84 + 1, sort.h of the image's libc++), not a pointer into string 1985; its comparisons
#   are CEleitorIdentidade's ordering of the voter (text, then the type unsigned). It has four parameters (no
#   comparator) and one 176-byte frame, the partitions', insertion sorts' and heap sort's code inlined by clang; the
#   matched sorts over a lambda comparator (5373, 5605, 5719) have that shape, those over std::__less<> or a function
#   pointer (5769, 2722, 2837, 5789) five parameters and a frame per helper binaryen inlined. A lambda of a function
#   that is not inline has a closure type of its TU alone, so the sort's instances over it are internal, and clang
#   inlines each helper with one call site into it (`-Rpass=inline` on celeitores.cpp: the partitions, insertion sorts
#   and heap code at costs near -13800 against 250, the sole-call bonus; __sort3 to __sort5 and
#   __insertion_sort_incomplete, called from several places, stay out of line, as 3762's calls show).
#
# Forms measured:
# - The comparator. std::sort's default order through a CEleitorDinamico::operator< (the first link of this unit):
#   3762 `3698 over 5014 rows` (1313 inserted, 1149 deleted): clang kept the helpers out of line
#   (`-Rpass-missed=inline` on celeitores.cpp: the partitions, insertion sorts and __sift_down cost 1120 to 1305 against
#   250) and binaryen inlined each into its one caller; with one lambda passed to both sorts, `56 over 3701`, every
#   row an operand. The lambda's being one local passed twice is the target's one 3762 for both sorts.
# - The coverage test. Each case written as its whole `||` (`temMunicipal || temEstadual || temFederal` for
#   municipal, and so on) put the cases in another br_table order with other values hoisted; a switch whose cases fall
#   through, each adding its own search's result, gives the target's: `has0 | has1` hoisted, `| has2` per case. With
#   that and the lambda, 5761 went from `563 over 1535` (94 inserted, 92 deleted) to `488 over 1474` (33, 32).
# - The equality (inlined into 5761 by binaryen; its result kept in a local and tested again). The four state tests
#   in the order Faltou to Votou gave the target's `xor`s reversed; Votou first gives its order. The photo's two words
#   compared in place keep a branch between them where the target ANDs them; an inline function of their own gives the
#   `and`. With both (that function a free one then), 5761 read `469 over 1466` (25, 24); the landed form,
#   CApresentacaoFotoEleitor's defaulted operator==, is the class's member that reads them, and matches. Its
#   object is the same with and without strict aliasing (celeitordinamico.cpp is in a strict-aliasing directory; the
#   function's code compared in the two objects of `tools/round/try-tu.sh --symbols`).
# - The objects' order. What that 469 had left is local numbering and what binaryen orders by it (two compares'
#   operands, one flag kept in a local), with dao/celeitordinamicodao.cpp's object (InserirTodos) linked after
#   celeitores.cpp's, as unit 91's list put it. A scratch link of the plain link.cmd with only that object moved right
#   before celeitores.cpp.o (docs/reference/facts/workflow.md W13) gives `56 over 1441`, every row an operand
#   (codegen.md C4). The target's data put that file there: records @1558832 celeitordetalhe.cpp, @1558940
#   celeitordinamicodao.cpp, @1559096 celeitores.cpp. So unit 110's list holds the file between those two now, and
#   unit 91's no longer does. codegen.md C4's count of objects out of the data order against it: 243 at unit 91's
#   place, 150 here. The move renames four twins' match lines to CEleitorDinamicoDAO's, whose object now links ahead of
#   cjustificadordao.cpp's: 1704 and 3767 (the DAOs' D2 and D0) and binaryen's 2297 and 3894; 1715 (CBaseError<
#   api::EUePersistenciaError>'s constructor) and 5760 (construct_at<CEleitorDinamico>) match from its object now.
#
# The sets at +52 of CEleitores and +604 of CConfiguracaoEleicao take md::ETipoAbrangencia (celeitores.h,
# cconfiguracaoeleicao.h): DynamicCreate compares the first's elements with 0, 1 and 2 against GetAbrangencia's
# result, the identifier types run 1 to 3, and both sets have one recursive destroy, 1594, which our link keeps as two
# functions while the element types differ (~CEleitores, 5773, left match so, on `call … __tree<ETipoAbrangencia>::
# destroy … has no target function`). That type is a reading. The two types' objects differ in symbol names only
# (cconfiguracaoeleicao.cpp.o, celeitorencontrado.cpp.o: their code compared with the names masked), and step 9
# renamed 1594's and 6733's match lines (the set's destroy and range insert); unit 283's roots label for 6733 follows.
#
# Order: band 2 runs 5765, 5764, 5763, 5762, 5761 and band 3 3763, 3762 in link order; in celeitores.cpp.o 5761 comes
# before 5764 and 5765, and 3762 before 3763, three pairs inverted. DynamicCreate's records hold it at lines 298 to 361
# (placing.md P9, a record bounds the order), and the target's order is that of a TU where CompleteLoad (6734,
# records :205 to :238, not written) mentions 5764, 5765 and 3763 first: its direct calls (ledger/callgraph.tsv) hold
# all three. A reading, until 6734 is written.
#
# Chosen: every local's name (temMunicipal, temEstadual, temFederal, vota, dinamicos, gravados, dinamicoDAO, porEleitor)
# and the lambda's parameters; std::find for the three searches; the vector's `!=` for the size test and element loop
# (std::equal not measured); DynamicCreate's lines but the records' (a blank run before the 358 throw) and the DAO
# header's include, which takes the blank line after the file's own header's include (no blank run is left above the
# file's first record outside the namespace); InserirTodos (its name, membership, const, line) and the by-value
# range-for; operator== being a member of CEleitorDinamico out of line in celeitordinamico.cpp, and the predicates
# (celeitordinamico.h); the default argument against a two-argument constructor of the same body;
# CApresentacaoFotoEleitor's operator== being defaulted; the names of the state values, read from ecourna's
# CEstadoComparecimento.
#
# Stand-ins: 383-uenux2-celeitores-dinamicos-roots.cpp's CriaDinamicos stands for 6737's two calls of 5761. 3763's
# third caller, 6734, needs none: 5761 calls it twice. Unit 91's roots' calls for 5761 (3768's constructor, once; 3759
# and 3758) went with it.

# celeitores.cpp includes the DAO's header, whose SQL headers include Boost, and celeitordinamicodao.cpp left unit
# 91's list, whose line gave it the path (an include path, not a flag of the code: unit 66's fragment says why).
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/celeitores.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/dao/celeitordinamicodao.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)

# the caller (fn 6737) is not reconstructed yet: 383-uenux2-celeitores-dinamicos-roots.cpp reaches DynamicCreate the
# way the target does
$(ROOT)/$(APP)/383-uenux2-celeitores-dinamicos-roots.o: $(ROOT)/src/units/383-uenux2-celeitores-dinamicos-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/383-uenux2-celeitores-dinamicos.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/383-uenux2-celeitores-dinamicos-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/383-uenux2-celeitores-dinamicos-roots.o
