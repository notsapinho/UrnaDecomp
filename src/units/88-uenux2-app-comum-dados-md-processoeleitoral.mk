# uenux2 comum::md process-election classes and comum::CCargos, the first unit that throws comum::CUeComumDadosError
# (src/app/comum/dados/euecomumdadoserror.h, a header several units share: its enumerators are named by value).
# comum::CCargos (src/app/comum/dados/ccargos.cpp): Next, GetCurrentCargoID, GetCurrentEleicaoID (target fns 1708, 1938,
# 2835), and the free comum::NomeEleicaoCorrente (11556) in the same file. In md/processoeleitoral/: CCargo's GetDetalheCandidato (1388), GetNomeNeutro, GetNomeMasculino, GetNomeAbreviado
# (1547, 3716, 2797), GetNome (2796), GetNomeSuplente (3715), GetOrdinalEscolha (2258) and Valida (5657);
# CDetalheCandidato::GetSuplente (1545); CEleicaoPE::GetCargos (2257); CPleito::GetEleicao and GetSituacoesEleicoes (5651,
# 5648); CProcessoEleitoral::GetPleito2 (1267). comum::asn::CConversorNomesCargo::DoDesconverte (11369), with
# CNomesCargo's constructor, in asn/processoeleitoral/. Added later: CCargo::operator<=> (5655),
# CEleicaoPE::PossuiCargoCandidato (5653), and CCargos::RemoveFiltro (3784) with the std::vector range assign it
# instantiates (3783); CEleicaoPE::ValidaOrdem (3714) and GetIDsCargos (5654), once md/ built with strict aliasing.
# ccargo.cpp also holds CCargo's two constructors, which fragment 191 describes (no target index of their own: binaryen
# inlines each into fn 11373).
# Evidence, records: every file above but the converter's, each throw's line and column, and each record's spelling
# (comum::TCargoID, const TVectorCargo &, TQtdEscolha). Evidence, RTTI: the converter's class and its base. The
# converter's file is rule 3 and 4 of docs/how-to-decompile.md step 3: no record names it, its vtable (@1570164) lies
# between CConversorCargo's (@1569964) and CConversorOrigemConfiguracao's (@1570240), both recorded in
# asn/processoeleitoral/. The headers' paths are the lower-case rule, chosen; csuplencia.h and crespostaconsulta.h beside
# their records' files. Each header's comment says which of its members the bytes give. md::CSexo and md::ETipoAbrangencia
# are the ones md/candidatura/cdadoscandidato.h and asn/util.h declare, with eurnafase.h beside it.
# Who inlines what, read from the objects (wasm-objdump -d) against the target:
# - clang: GetDetalheConsulta into the four name getters, and GetDetalheCandidato into GetNomeSuplente; those objects hold
#   no call of either. GetDetalheConsulta's own body is target fn 1923, a thunk of binaryen's merge 6029, so it stays out
#   of our link and 1923 is unmatched.
# - wasm-opt: GetNomeFeminino into GetNome (ccargo.cpp.o calls it, 2796 holds a second stack prologue, and 2796 is its one
#   caller), and CNomesCargo's constructor into 11369 (another TU; 11369 holds its prologue).
# Chosen names: GetNomeNeutro, GetNomeMasculino, GetNomeFeminino, GetNomeAbreviado, read from the field each copies
# (ModuloEleicao::NomesCargo); GetNome and GetNomeSuplente, from fn 5803, whose record GetNomeCargoComGenero(const
# std::string &, md::CSexo::ESexo, uebyte) passes them the sex and the byte; SEXO_MASCULINO and SEXO_FEMININO, ccargo.cpp's
# constants for the values 1 and 2 of an enum whose enumerators are not recovered; TCargoEleicao; the enumerators and data
# members.
# Chosen types: GetNomeSuplente's suplente, size_t. It is wider than a byte, since 3715 masks it with 255 and a uebyte
# parameter drops that mask (measured); int gives the same bytes. A std::pair element in CCargos; a struct of the same two
# members gives the same bytes. CCargo's abrangencia as md::ETipoAbrangencia: a plain enum, a scoped enum and an int member
# give the same bytes at Valida's first test, since an unscoped enum of these values promotes to int.
# Forms: same bytes, compared function by function with object-local numbers masked (docs/how-to-decompile.md step 3).
# - Next: ++m_atual = m_atual++. >= gives i32.lt_u where the target has i32.ne, and size() == m_atual loads in another order.
# - GetCurrentCargoID: m_cargos[m_atual] = m_cargos.at(m_atual). size() <= m_atual loads in another order. GetCurrentEleicaoID
#   is written alike.
# - GetPleito2, GetDetalheCandidato: !x = !x.has_value(), and *x = x.value() for GetPleito2.
# - GetSuplente: suplente == 0 = suplente < 1; suplente > size() = size() < suplente; m_suplentes[n] = *(begin() + n).
# - name getters: if (m_detalheCandidato) = .has_value(); m_detalheCandidato-> = GetDetalheCandidato(). A ternary, testing
#   the consulta first and testing m_tipo each differ.
# - GetNomeSuplente: const CNomesCargo = auto. A reference (no copy) and a by-value CSuplencia::GetNomes each differ.
# - GetOrdinalEscolha: the valid path first is evidence. if (escolha > m_qtdeEscolhas) throw, then the format, gives 343 over
#   539 rows in the whole link. if {...} else { throw } gives the same bytes as a throw after the if's closing brace, and the
#   record's column 15 is an if's indent, so the else is chosen. return ""; is evidence: return {} and return std::string()
#   store otherwise. Testing m_qtdeEscolhas != 1 around the rest differs.
# - Valida: m_x < 1 || m_x > 5 = m_x == 0 || m_x > 5, and !(m_x >= 1 && m_x <= 5) differs. m_qtdeEscolhas == 0 = < 1 =
#   !m_qtdeEscolhas. > the last enumerator = static_cast<int>(x) >= 3. Listing the candidato cases first swaps the
#   two message temporaries' frame slots, so the records' order is the bytes' too.
# - GetCargos: .empty(); size() == 0 loads in another order.
# - GetEleicao: std::find_if = std::ranges::find_if, and the lambda's capture is free ([id], [&id], [=]). if (it != end)
#   return *it; throw = if (it == end) throw; return *it, and column 11 fits the first, with the throw at the body's indent.
#   A range-for and a hand-written loop each differ: the target compares the iterator with end again after the search.
#   GetSituacoesEleicoes is written alike.
# - CNomesCargo's constructor: it tests the members, and testing the parameters differs; .empty() = size() == 0.
# - DoDesconverte: four named std::string copies, const or not. Temporaries in the call, direct references and const auto
#   (the ASN.1 type) each differ.
# comum::NomeEleicaoCorrente (fn 11556), the name of the current position's election, is in ccargos.cpp: it holds
# GetInst's code (record 24), which only that TU can inline, then calls GetCurrentEleicao (2836) and copies the string at
# +12 of the CEleicaoPE it returns (md/processoeleitoral/celeicaope.h's GetNome). The target reaches it only through
# table slot 3049, which fn 5580 passes to api::CPaperFormBuilder::AddTextField (604): the roots take its address. In
# band 1 (ledger/ordinals.tsv) it follows ccargos.cpp's exit destructors (11561, 11560) and two comparators of the
# cargo pairs, 11559 and 11558, whose table slots fns 7377 (which holds code of this file's line 249) and 3782 store: so
# it is defined after the statics, and its line, after record 249, is a choice. Chosen: its name and GetNome's, its
# being a free function, ccargos.h as its header, GetNome's being inline in the class.
# - CEleicaoPE::ValidaOrdem (fn 3714) matches since comum's data classes build with strict aliasing (src/Makefile
#   UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md §F6). With -fno-strict-aliasing its one difference is three rows:
#   the object reloads __child after __insert_node_at's store of the begin node. insert, emplace and a named result all
#   keep it, and so does -O3. The caller is the constructor fn 11371 inlines.
# The later members, what the target fixes (no record names any of them, so every name and line here is chosen):
# - 5655 compares the bytes at +0 of its two arguments and gives -1, 0 or 1; its one caller, fn 11888
#   (vota::CMenuFiltrarCandidatosPorCargo's slot 2), calls it twice to place a copy of CConfiguracaoEleicao::GetCargo's
#   result in a tree of 156-byte nodes (16 + CCargo's 140) and tests the result's low byte below 0. So it orders CCargo
#   by its id, out of line since 11888 keeps the calls: a member operator<=> returning std::strong_ordering is chosen
#   (ccargo.h), after Valida in ccargo.cpp, which band 2's order fits (5657, Valida, then 5655). No other form was
#   compiled.
# - 5654 and 5653 read the vector of 140-byte elements at +28 of their argument, CEleicaoPE's m_cargos (celeicaope.h):
#   5654 inserts each element's byte at +0 into a std::set of one-byte keys it returns, and 5653 tells whether any
#   element's byte at +84 (CCargo's engaged flag of m_detalheCandidato) is set. In band 2 they follow ccargo.cpp's Valida
#   (5657, record :212) and precede CPleito's constructor (5652, record cpleito.cpp:64), so a file between the two in link
#   order; celeicaope.cpp, the file of the class they read, is chosen among those, and their place in it. Both are written as index loops over
#   size(), as the target's multiply by 140 reads; no other form was compiled.
# - 3784 is called on CCargos::GetInst()'s result by fns 12098 and 12110 (vota::CGravaResultado's and vota::CGeraBU's slot
#   2) and calls 3783 on +16 with the vector at +4: m_cargos = m_todos (ccargos.h names the two vectors). 3783 is the
#   range assign of a vector of 8-byte pairs, which 7377 (FiltraPorAbrangencia, ccargos.cpp:249) calls too. 3783 follows
#   3784 in band 3, an instance of ccargos.cpp's (both callers are its). The name RemoveFiltro, ccargos.cpp as 3784's
#   file (the class's) and its line there, after NomeEleicaoCorrente, are chosen; 3784 is written as the one assignment,
#   and no other form was compiled. The roots give 3783 its second call site, for 7377.
# - CEleicaoPE::GetIDsCargos (fn 5654) matches since comum's data classes build with strict aliasing, as ValidaOrdem
#   does. With -fno-strict-aliasing it differed from the target in the reload of __child after __insert_node_at's store
#   of the begin node (`pnpm wasm score` against the plain link: 8 over 122 rows, the reload's three rows, the local
#   numbers after it and one call operand).
# - CConfiguracaoEleicao::GetSituacoesEleicoes (fn 271, a chosen name) is f5648(this + 28, eleicao): CPleito's
#   GetSituacoesEleicoes on the pleito at +28 (cconfiguracaoeleicao.h's m_pleito). Its callers (1386,
#   3687, 5577, 5578, 5582, 11558, 11559) pass it GetInst's (187) result at every call, and 11558 and 11559 pass that to
#   GetCargo (861) as well (pnpm wasm fn), so it is the class's member, out of line in cconfiguracaoeleicao.cpp; its line
#   there, after GetCargo's, and its parameter's TEleicaoID (5648's) are chosen. Its stub was an ecourna/unplaced.cpp
#   row: the ledger's component for it is ecourna, which says which code calls it, not where it is written. The scan
#   pairs it by content. None of its callers is written, so the roots give it two call sites, and the stand-in for 5648
#   now stands for 3713 alone.
# - comum::CConfiguracaoEleicao::GetIDsEleicoes (fn 5791, 87 B) and GetCargosEleicoes (fn 3774, 389 B), in
#   cconfiguracaoeleicao.cpp after the destructor. 5791 pushes the id (+0) of each 52-byte CEleicaoPE of m_pleito into
#   a vector through push_back(const&): the target calls fn 543, matched as std::vector<long>'s, and our body's call
#   goes to that body (ours 532, roots_boost.o's, in build/out/wasm-map/vota_web/names.tsv), binaryen keeping one of
#   identical bodies for our std::vector<unsigned int>'s instance (a reading); its callers are 1269
#   (comum::CRdvVota::Comparecimento(), unit 13) and 5735. 3774 pairs each
#   election's id with the id of each of its cargos (CEleicaoPE::GetCargos, fn 2257, out of line) into a
#   std::vector<CCargos::TCargoEleicao>; its callers are 4454 (vota::CEleitorVotando's, not written) and 7787 (which
#   holds CCargos::CreateInst; ccargos.h has it). Each pair is one 8-byte store in the target: `push_back({id, cargo})`
#   gives it, 5 over 195 rows, all operand-only, where `emplace_back(id, cargo)` builds the pair in place with two stores,
#   33 over 201 rows (6 inserted, 10 deleted); 5791 scores 1 over 44, operand-only (`pnpm wasm score` before step 8).
#   The scan matched 5791 through the census's pair (`shape`) and 3774 by its content. In use band 2 the target's 5791
#   comes right after the destructor (5792) in link order, which is what puts it after the destructor here; in use band
#   3 its 3774 lies after ccargos.cpp's 3784 and 3783 and before cnomearquivo.cpp's 3773, with 3775 to 3782 between (all
#   unwritten but 3779, a std::__split_buffer instance), which this file fits (a reading). Chosen: both names, their being members (they read m_pleito), the line of
#   each and their order. The roots' IDsEleicoes stands for 5735 and CargosEleicoesDuas for 4454 and 7787.
# Not matched:
# - fn 170, CBaseError<comum::EUeComumDadosError, ...>'s constructor: the target's is a thunk of 2294, whose body makes the
#   base call through invoke; ours is a thunk of the uenux2 shape. The callers need only its name, which their call votes
#   give it. The row stays `differs`.
# - CPleito's constructor (fn 5652, records 64, 67 and 70) is not written. The target calls fn 1953, the uninitialized
#   copy of CEleicaoPE, and fn 2289 calls no __init_with_size. At -O2 clang keeps __init_with_size<CCargo> out of line
#   (-Rpass-missed=inline: cost=230, threshold=225) and inlines the copy into the constructor; at -O3, the tree's level,
#   cpleito.cpp gives the target's calls. With that object and second callers for 1953 and 3870 in a scratch link, it scores 103 over 438 rows
#   against 1150 over 1448 (3 of them the reload of -fno-strict-aliasing, which this directory no longer has: without it, 100 over 435); what is left includes the placement of its three throws, so no body here is shown right.
# - ccargos.cpp also holds GetInst, GetCurrent, GetCurrentEleicao, Reset and IsFim (fns 273, 332, 2836, 2269, 602), and
#   cconfiguracaoeleicao.cpp GetInst, GetCargo and GetEleicao (187, 861, inlined into 2836): unit 110's fragment has their
#   evidence and why that object links after ccargos.cpp. The file's other records, lines 25, 93 and 249, are not written.
# - ccargo.cpp also holds comum::md::CCargo's TemFoto and QtdSuplentes (target fns 1546 and 1157, 16 and 36 B, no
#   record), which fns 1192, 4185, 6569, 6660, 6671, 6678 and 1588, 6569, 6660, 6671, 6678, 7787, 12272 call 8 and 11
#   times, none written (those with records, 6660, 6671, 6678, 7787 and 12272, are app/vota/eleitor/comum/ctelasvota.cpp's).
#   Each reads the candidate detail's engaged flag at +84 and a field of the detail itself, the photo flag at +20 or the
#   substitutes' vector at +72 (52-byte elements), not through GetDetalheCandidato, which those screens call elsewhere
#   (fn 1388). That a caller's TU would inline a body this small is a reading, not compiled, so their TU is another
#   one: ccargo.cpp, their being members, their names, the spelling uebyte of QtdSuplentes' result (its 8-bit unsigned
#   width is the target's: 1157's `i32.const 255; i32.and` at +0x1f), CDetalheCandidato's two accessors (TemFoto,
#   GetSuplentes) and their lines after operator<=> are chosen; other forms are not measured. Both scored 0 rows over 9
#   and over 19 (byte-exact) before step 8 and matched at step 9. Their stand-ins are
#   src/units/212-uenux2-app-vota-callers-roots.cpp's.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
PROCESSOELEITORAL_SRCS := src/app/comum/dados/ccargos.cpp \
  src/app/comum/dados/cconfiguracaoeleicao.cpp \
  src/app/comum/dados/md/processoeleitoral/ccargo.cpp \
  src/app/comum/dados/md/processoeleitoral/cdetalhecandidato.cpp \
  src/app/comum/dados/md/processoeleitoral/celeicaope.cpp \
  src/app/comum/dados/md/processoeleitoral/cnomescargo.cpp \
  src/app/comum/dados/md/processoeleitoral/cpleito.cpp \
  src/app/comum/dados/md/processoeleitoral/cprocessoeleitoral.cpp \
  src/app/comum/dados/asn/processoeleitoral/cconversornomescargo.cpp
UENUX2_SRCS += $(PROCESSOELEITORAL_SRCS)
# cconfiguracaoeleicao.h holds an ecourna CConfiguracaoMunicipio, whose CHorariosUrna holds Boost ptimes, and
# UENUX2_CXXFLAGS has no Boost path. An include path is not a flag of the code (asmlift-wasm/benchmark/README.md
# "The compile setups").
$(addprefix $(ROOT)/$(APP)/uenux2/,$(addsuffix .o,src/app/comum/dados/ccargos.cpp src/app/comum/dados/cconfiguracaoeleicao.cpp)): UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# no target caller of these functions is reconstructed: the roots file gives each its call sites and keeps the vtable
$(ROOT)/$(APP)/88-uenux2-app-comum-dados-md-processoeleitoral-roots.o: $(ROOT)/src/units/88-uenux2-app-comum-dados-md-processoeleitoral-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/88-uenux2-app-comum-dados-md-processoeleitoral.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/88-uenux2-app-comum-dados-md-processoeleitoral-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/88-uenux2-app-comum-dados-md-processoeleitoral-roots.o
