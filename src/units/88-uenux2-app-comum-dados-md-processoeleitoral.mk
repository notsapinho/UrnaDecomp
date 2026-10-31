# uenux2 comum::md process-election classes and comum::CCargos, the first unit that throws comum::CUeComumDadosError
# (src/app/comum/dados/euecomumdadoserror.h, a header several units share: its enumerators are named by value).
# comum::CCargos (src/app/comum/dados/ccargos.cpp): Next, GetCurrentCargoID, GetCurrentEleicaoID (target fns 1708, 1938,
# 2835). In md/processoeleitoral/: CCargo's GetDetalheCandidato (1388), GetNomeNeutro, GetNomeMasculino, GetNomeAbreviado
# (1547, 3716, 2797), GetNome (2796), GetNomeSuplente (3715), GetOrdinalEscolha (2258) and Valida (5657);
# CDetalheCandidato::GetSuplente (1545); CEleicaoPE::GetCargos (2257); CPleito::GetEleicao and GetSituacoesEleicoes (5651,
# 5648); CProcessoEleitoral::GetPleito2 (1267). comum::asn::CConversorNomesCargo::DoDesconverte (11369), with
# CNomesCargo's constructor, in asn/processoeleitoral/.
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
# Not matched:
# - CEleicaoPE::ValidaOrdem (fn 3714, written, no-candidate). Its one difference is three rows: at this tree's
#   -fno-strict-aliasing the object reloads __child after __insert_node_at's store of the begin node. insert, emplace and a
#   named result all keep it, and so does -O3. In a whole link with celeicaope.cpp.o alone compiled without the flag,
#   splat-remap prints target 3714: IDENTICAL. docs/reference/facts/app-flags.md §F6 states the flag for the tree, and a flag
#   is a tree's, so the body stays and the row waits for that decision. The caller is the constructor fn 11371 inlines.
# - fn 170, CBaseError<comum::EUeComumDadosError, ...>'s constructor: the target's is a thunk of 2294, whose body makes the
#   base call through invoke; ours is a thunk of the uenux2 shape. The callers need only its name, which their call votes
#   give it. The row stays unresolved.
# - CPleito's constructor (fn 5652, records 64, 67 and 70) is not written. The target calls fn 1953, the uninitialized
#   copy of CEleicaoPE, and fn 2289 calls no __init_with_size. At -O2 clang keeps __init_with_size<CCargo> out of line
#   (-Rpass-missed=inline: cost=230, threshold=225) and inlines the copy into the constructor; at -O3 cpleito.cpp gives the
#   target's calls. With that object and second callers for 1953 and 3870 in a scratch link, it scores 103 over 438 rows
#   against 1150 over 1448 (3 of them the tree's reload: without -fno-strict-aliasing, 100 over 435); what is left includes the placement of its three throws, so no body here is shown right.
# - ccargos.cpp also holds GetInst, GetCurrent, GetCurrentEleicao, Reset and IsFim (fns 273, 332, 2836, 2269, 602), and
#   cconfiguracaoeleicao.cpp GetInst, GetCargo and GetEleicao (187, 861, inlined into 2836): unit 110's fragment has their
#   evidence and why that object links after ccargos.cpp. The file's other records, lines 25 and 93, are not written.
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
# slot 2 of CConversorNomesCargo is the base's default DoConverte (target fn 11368), which iconversorasn.h does not
# define yet: the pending file gives the vtable a trapping explicit specialization of it, compiled with the unit's flags
$(ROOT)/$(APP)/88-uenux2-app-comum-dados-md-processoeleitoral-pending.o: $(ROOT)/src/units/88-uenux2-app-comum-dados-md-processoeleitoral-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/88-uenux2-app-comum-dados-md-processoeleitoral.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/asn/*.h $(ROOT)/src/uenux2/src/app/comum/dados/asn/processoeleitoral/*.h $(ROOT)/src/uenux2/src/app/comum/dados/md/processoeleitoral/*.h $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/ModuloEleicao.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/88-uenux2-app-comum-dados-md-processoeleitoral-pending.cpp -o $(R)
# no target caller of these functions is reconstructed: the roots file gives each its call sites and keeps the vtable
$(ROOT)/$(APP)/88-uenux2-app-comum-dados-md-processoeleitoral-roots.o: $(ROOT)/src/units/88-uenux2-app-comum-dados-md-processoeleitoral-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/88-uenux2-app-comum-dados-md-processoeleitoral.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/88-uenux2-app-comum-dados-md-processoeleitoral-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/88-uenux2-app-comum-dados-md-processoeleitoral-pending.o $(APP)/88-uenux2-app-comum-dados-md-processoeleitoral-roots.o
