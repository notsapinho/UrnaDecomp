# uenux2 comum::md voter classes and the DAOs' shared bodies. Matched: CEleitorDinamico::GetTituloMesarioHabilitacao
# (target fn 1548) and the class's two constructors (5664, 5663), CBiometriaEleitor::GetDedo (3720),
# CEleitorDecorator::GetIdentidadePorTipo (708),
# CEleitorDinamicoDAO::ExcluirID (11543), the three defaults of api/persistencia/iuenuxgenericdao.h with their merge
# (11540, 11467, 10398, 10397, 10396, thunks of 2297), and the three DAOs' Clone with theirs (11541, 11468, 10399, thunks
# of 3894), and CBaseError<api::EUePersistenciaError>'s and CBaseError<comum::EUeComumJustificativaError>'s constructors
# (1715, 2260), thunks of fn 710, with unit 94's constructor; CComparecimentoMesarioDAO's Inserir (10403, slot 3), its
# two converters ConverteEstadoBiometria and ConverteDedoHabilitacao (5391, 5390, records ccomparecimentomesariodao.cpp
# lines 200 and 232) and CBaseError<comum::EUeComumComparecimentoMesarioError>'s constructor they throw with (3611, a
# thunk of fn 710; app/comum/comparecimentomesario/euecomumcomparecimentomesarioerror.h). 1715's name is a hand edit,
# evidence:rtti-vptr (the only target function holding that vptr); 2297 calls it, and the line is older than the votes
# of what an anchor's vote names.
# All three DAOs must be in the link: binaryen forms 2297 and 3894 from those members, and unit 66's file holds
# the third of each. The sources are the files the records name: md/eleitor/{celeitordinamico,cbiometriaeleitor,
# celeitordecorator}.cpp, dados/dao/celeitordinamicodao.cpp, comparecimentomesario/dao/ccomparecimentomesariodao.cpp.
#
# - CBiometriaEleitor::CriaComum (2799) matches since comum's data classes build with strict aliasing (src/Makefile
#   UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6). With -fno-strict-aliasing it differed by one reload of __child
#   after __tree::__insert_node_at's begin-node store (clang inlines the insert); eight spellings of the insert kept the
#   reload with the flag, at -O2 and -O3, c++20 and c++23.
# Written and unmatched (docs/how-to-decompile.md step 5, "A written body that does not match yet"):
# - CEleitorDinamicoDAO's constructor, Inserir and Atualizar (3768, 5776, 5775) match at the tree's -O3: clang inlines
#   string::append(const char*, size_t) at -O2, and the target calls it (fn 160). With this one object at -O3 in the -O2
#   link they scored 22 over 267, 18 over 404 and 18 over 400 rows, operands only, short of the name of the .bss string
#   NOME_TABELA (1838780, built in __wasm_call_ctors, freed by fn 11545), which the three bodies' votes now give
#   (splat/symbol_addrs.txt: `evidence:vote:13 by:3768,5775,5776,14478`).
#
# Read from the bytes:
# - 10403 binds its columns from the offsets the class header lists and converts data_hora_registro with
#   CDateTime::ConvertToLocalTime (fn 1381), then a multiply by 1000000 and the add of the epoch's microseconds, inlined:
#   boost::posix_time::from_time_t is written (no other spelling of that conversion tried). It loads the statement once
#   before it tests id_arquivo's flag, then calls SetInt or SetNull
#   through it: `stmt->` in each branch loads it in each branch (object compared), and a helper that takes the
#   statement by reference loads its vtable once as well, where the target loads it in each branch. So a reference to
#   the statement is taken before the test.
# - 5391 and 5390 range-check with `i32.lt_u` of 3 (after subtracting 1) and of 11 in the object, as the target's
#   `i32.ge_u` after binaryen: a switch whose cases each return their own value gives it. Measured on 5390, an `if`
#   over the range (`>= 0 && <= 10`, `<= 10 && >= 0`, a cast to uedword `< 11`, a negated `||`) and a switch whose
#   cases share one return give `i32.le_u` of 10 (each compiled, the function's rows compared). Their throws stand at
#   column 11, the function's top level, after the switch; each formats the int argument (type code 3).
# - The throws of 1548 and 708 stand at column 11, at the function's own indent, so each is the fall-through after an
#   `if` that returns; the three others of the unit in functions of this kind (3720, 2799) stand at 15 and 19, in a block.
# - 708's second compare of the iterator is a search and then a test, not a return inside the loop: a range-for that
#   returns gives 274 object rows against 277, and a hand-written loop with `break` 275.
# - 708's message takes an unsigned char: the target masks the type with 255 and packs the argument as `unsigned` (6);
#   static_cast<int> gives another row count, 275.
# - The three defaults' name string is a local: the target builds it before __cxa_allocate_exception. A temporary in the
#   throw allocates first (41 object rows against 43, measured two ways), and it is an lvalue, since the concatenation
#   calls the out-of-line operator+(const char*, const std::string&) (fn 345).
# - 2799's map and photo are std::optional members, from the flags fn 11422 stores at +32 and +16. The target reads the
#   map with no test of the flag: value() adds 8 rows to GetDedo.
#
# Chosen, no evidence names them: every data member's name, parameter and local names (comando among them), every
# getter's name but GetTituloMesarioHabilitacao, the converters being private, the enumerators' names of
# EUeComumComparecimentoMesarioError and that header's path, the
# paths of every new header (cdedo.h, celeitordecorator.h, cbiometriaeleitor.h, celeitordinamico.h, celeitordinamicodao.h,
# ieleitordinamicodao.h, ccomparecimentomesariodao.h, icomparecimentomesariodao.h, comparecimentomesario/md/
# ccomparecimentomesario.h, api/persistencia/euepersistenciaerror.h), the enumerators of EUePersistenciaError, the name
# and linkage of NOME_TABELA (anonymous namespace), api::SXYT's members and CBiometriaEleitor's +36 member, which only
# give sizes, the lines of every function but the records' throws, CriaComum being private, and the constructors' photo
# parameter being a reference: the caller passes an address for a by-value one too. The names of the
# EUeComumDadosError enumerators say only the value (that header is a blob shared with other units).
# Order in celeitordinamicodao.cpp, from ledger/ordinals.tsv, in link order: the constructor before the D0 before slot 8
# in band uses 3; Inserir before Atualizar in uses 2; ExcluirID, slot 7, Clone in uses 1. Clone last: the place of an
# inline member or of the file's last one, a choice.
#
# Other forms that give the same bytes (each compiled, the function compared row by row with wasm-objdump -d, the
# object's call indices and data offsets masked): the constructors: `m_tituloMesarioHabilitacao(std::nullopt)` or none;
# 1548: `if (m_x)`, `.has_value()`, `TemTituloMesarioHabilitacao()` or
# `!= std::nullopt` for the test, `*m_x` or `.value()` for the result. 3720: `auto` for the iterator, `(*m_dedos).find`, a
# local reference to the map, a const_iterator with cend(). 708: std::ranges::find_if, cbegin() and cend(), the
# cast through `unsigned int` as well. The defaults: a non-const local, `entidade(...)`, `entidade{...}`. Clone defined
# in the class, which gives a weak symbol and the same body. NOME_TABELA as a plain namespace-scope const or as static.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 and ecourna header.
COMUM_ELEITOR_MD_SRCS := src/app/comum/dados/md/eleitor/celeitordinamico.cpp src/app/comum/dados/md/eleitor/cbiometriaeleitor.cpp src/app/comum/dados/md/eleitor/celeitordecorator.cpp
COMUM_ELEITOR_DAO_SRCS := src/app/comum/dados/dao/celeitordinamicodao.cpp src/app/comum/comparecimentomesario/dao/ccomparecimentomesariodao.cpp
UENUX2_SRCS += $(COMUM_ELEITOR_MD_SRCS) $(COMUM_ELEITOR_DAO_SRCS)
# src/ecourna/api/sql/isqlstatement.hpp and isqlresultset.hpp include Boost, and UENUX2_CXXFLAGS has no Boost path. An
# include path is not a flag of the code (asmlift-wasm/benchmark/README.md "The compile setups").
$(addprefix $(ROOT)/$(APP)/uenux2/,$(addsuffix .o,$(COMUM_ELEITOR_DAO_SRCS))): UENUX2_CXXFLAGS += -I$(BOOST_HDR)
$(ROOT)/$(APP)/91-uenux2-app-comum-dados-eleitor-pending.o: $(ROOT)/src/units/91-uenux2-app-comum-dados-eleitor-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/91-uenux2-app-comum-dados-eleitor.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -I$(BOOST_HDR) -c src/units/91-uenux2-app-comum-dados-eleitor-pending.cpp -o $(R)
$(ROOT)/$(APP)/91-uenux2-app-comum-dados-eleitor-roots.o: $(ROOT)/src/units/91-uenux2-app-comum-dados-eleitor-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/91-uenux2-app-comum-dados-eleitor.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/91-uenux2-app-comum-dados-eleitor-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/91-uenux2-app-comum-dados-eleitor-pending.o $(APP)/91-uenux2-app-comum-dados-eleitor-roots.o
