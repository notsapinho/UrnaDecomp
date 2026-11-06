# uenux2 comum::asn converters of app/comum/dados/asn/ and the comum::md data they build. The unit's other members are in
# landed units' files: comum::asn::Utils's dates in unit 96 (util.cpp), md::CVotosCargos::SCargoInfo, md::CVotos's
# constructor, CVotosCargos::GetVotos and comum::CRdvVota's converter in unit 13; each fragment says what it holds.
#
# Matched:
# - CConversorPleito::DoDesconverte (target fn 11365, slot 3 of the vtable @1570332), in
#   app/comum/dados/asn/processoeleitoral/cconversorpleito.{h,cpp}, over Utils::DesconverteDataJE (fn 2276, unit 96),
#   and md::CPleitoDTO's constructor, out of line in app/comum/dados/md/processoeleitoral/cpleitodto.cpp: 11365 copies
#   the date with the 2-byte alignment of a const api::CDate& (i64.load align=1), so binaryen inlined the constructor
#   from another function. Defined in the class, 11365 is 16 over 104 rows (5 inserted, 2 deleted); out of line in
#   another TU, 4 over 99, operand-only (pnpm wasm score).
# - CConversorVotosCargo's constructor (fn 5683), in app/comum/dados/asn/rdv/cconversorvotoscargo.{h,cpp}: the
#   SCargoInfo at +4 and a CConversorVoto at +16 (that class's vptr, @1570816).
# - CConversorEleicoesVota's D2 and D0 (fns 11348, 11347), in app/comum/dados/asn/rdv/cconversoreleicoesvota.{h,cpp}:
#   implicit, the class final (the D2 does not begin with its vptr store), and fn 1160, the destroy of its map from each
#   election to a vector of md::CCargo. Five functions call 1160 in our link: those two destructors, the
#   CConversorRegistroDigitalVoto<CConversorEleicoesVota> ones (11484, 11485) and ~CRdvVota (5734, unit 13); 5734, named
#   by `call`, casts the vote that names 1160 in the generated part of splat/symbol_addrs.txt, so it has no hand line.
# - CConversorRegistroDigitalVoto<CConversorEleicoesVota>'s D2 and D0 (fns 11485, 11484), implicit, emitted with
#   comum::CRdvVota's destructor (unit 13, fn 5734), whose member at +44 the class is, in
#   app/comum/dados/asn/rdv/cconversorregistrodigitalvoto.h.
# - std::__tree<md::TCargoID, md::CVotos>::destroy (fn 2877), from this unit's roots until its target caller 5971 was
#   written (fragment 325): it comes from 5971's object now, and the roots' stand-in for 5971 went.
# - Copies of library and ecourna template code this unit's objects bring first: 858, 1074 and 1075 (the error path of
#   ecourna's IConversorASN, basic_stringstream and CBaseError<EApiAsnError>) from cconversorvotoscargo.cpp.o.
#
# Matched with fragment 299 (its unit list does not change):
# - 11363, CConversorProcessoEleitoral::DoDesconverte, in cconversorprocessoeleitoral.{h,cpp} (record line 50), with
#   md::CProcessoEleitoralDTO's two constructors out of line in cprocessoeleitoraldto.{h,cpp}. The identifiers are
#   converted by std::transform into a std::back_inserter, the lambda capturing the converter by reference: 59 over 1078
#   rows, all operand-only, against the range-for with emplace_back written before, 80 over 1088 (10 inserted, 7
#   deleted: the target ends the function with the vector's __throw_length_error and then __throw_bad_array_new_length,
#   that form puts the second right after the loop), both `pnpm wasm score` in the whole link at fragment 299's base. An
#   earlier link of this unit had std::transform with a back_inserter among the forms that kept the second throw after
#   the loop; which lambda it held is not recorded here. The form is the one fragment 299's CConversorEleicaoPE
#   (11371) showed, from the frame its inlined lambda gives. The lambda's own form (the converter captured by name and
#   by reference, a `const auto&` parameter) is chosen.
#
# Matched since, each once one form changed (pnpm wasm score against the target in the whole link, before steps 7 to 9;
# "operand rows" are calls, data addresses, the std::format pieces' packed addresses and table slots):
# - 11352, CConversorVotosCargo::DoConverte, once uenux2 built at -O3 (what -O2 gave is below).
# - 11351, CConversorVotosCargo::DoDesconverte: the entity's votes bound to a const reference before the result's vector
#   is constructed, as the target loads the field's object (the third field's pointer) before the vector's zeroing
#   stores: 82 over 1233 rows, operand rows only, against 87 over 1235 (2 inserted, 3 deleted) with the range-for over
#   entidade.get_votos() after the vector, as written before. The reference's spelling (TEntidade::votos::value_type)
#   is chosen.
# - 11350, CConversorEleicoesVota::DoConverte: GetVotos called with the SCargoInfo's cargo, which the target reads again
#   from the info after CConversorVotosCargo's constructor (ours read it from the md::CCargo), and the pair built by
#   CConversorVotosCargo::TDado's constructor, whose copy of the CVotos keeps the vector's first end store (+24 of the
#   frame, before its copy loop) where std::make_pair's lets clang drop it: 71 over 870 rows, operand rows only, against
#   94 over 870 (3 deleted) as written before and 74 over 870 (the same 3 deleted) with the info's cargo and
#   std::make_pair.
# - 11483, CConversorRegistroDigitalVoto<CConversorEleicoesVota>::DoConverte, the class template's member in
#   rdv/cconversorregistrodigitalvoto.h (its comment says what the body holds), which unit 13's crdvvota.cpp.o emits;
#   ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto::set_pleito takes const_reference (src/asn1/modules, the
#   per-field form units 93 and 124 measured: the target builds a Constrained_INTEGER temporary for pleito, INTEGER's
#   constructor with the info 1556824 and the vptr 1560492). Its code history, the rest as written:
#   std::ranges::transform into std::back_inserter(historico) with a lambda that takes the string by const reference and
#   returns it by value, 53 over 502 rows, operand rows only; std::ranges::for_each with a lambda that takes the string
#   by value and pushes a GeneralString of it, 156 over 521 (19 inserted, 29 deleted: the loop inline here and the
#   lambda's call out of line, inlined by binaryen per iteration); the same through for_each's iterator-pair overload,
#   168 over 526, where -Rpass=inline gives that call (std::__invoke of the lambda) cost 325 against 250;
#   std::ranges::transform with a lambda that takes the string by value and returns the GeneralString, 84 over 514 (12
#   inserted, 7 deleted: the copy is destroyed before the push, and clone goes through the vtable). The lambda's
#   parameter type is the bytes': taking the string by value and returning it gives 64 over 510 (8 inserted), the
#   written const reference 53 over 502, every row an operand; the local names are chosen. What the earlier forms gave (the -pending.cpp's note before this
#   landing): std::copy into a back_inserter 253 over 588, the transform with a by-value lambda 279 over 625,
#   ranges::for_each 273 over 620, each then with clone through the vtable, the vector's growth inlined and
#   HistoricoCodigosCarga a class of the module's.
# What was measured at -O2 and -O3 for 11352 and 11351: ecourna's IConversorASN Converte and Deconverte, which they hold
# for CConversorCargoID, append ": " with std::string::operator+=(const char*), which clang leaves out of line in that
# cold path at both levels; at -O2 it inlines append into it, and binaryen folds the literal into our copy, which no
# target function holds (the rows are `unresolved` on that call); at -O3 operator+= is the append the target calls (fn
# 678). 11350's inner loop pushes each converted VotosCargo into the SEQUENCE_OF: the target holds that
# vector<AbstractData*>::push_back inlined and the outer loop's called; -Rpass=inline gives both cost 260 against 225
# at -O2, and at -O3 the inner one inlined (threshold 787) and the outer not (250).
#
# The base's default DoConverte of CConversorPleito and CConversorProcessoEleitoral (11364, 11362) is emitted with
# their vtables in their objects and matches: fragment 159's row.
# 11349, CConversorEleicoesVota::DoDesconverte (slot 3), matches since, in cconversoreleicoesvota.cpp at its records
# (:69 EUE_COMUM_DADOS_7967 "Dado não é do Vota", :74 7968 "Eleições incompatíveis", :94 7969 and :104 7970, the two
# std::format messages, each argument an unsigned, type code 6). What the target's body holds, read from its rows: the
# entity's choice tested for eleicoesVota (selection 0), the elections' count against m_cargos' size, an
# ecourna::app::dados::asn::CConversorCargoID on the stack (its vptr, 1122576, stored once, before the loop) and a map
# from each election to its md::CVotosCargos; per election a local map of SCargoInfo to md::CVotos, the election's id,
# its post list found in m_cargos, and per VotosCargo the post's id through the CConversorCargoID's Deconverte
# (ecourna's IConversorASN::Deconverte, record iconversorasn.hpp:66, inlined), compared with each 140-byte md::CCargo's
# id byte after a mask to 8 bits (so the converted id is held in a md::TCargoID, a uebyte), a CConversorVotosCargo built
# on the post's SCargoInfo (fn 5683) and its Desconverte (comum's IConversorASN::Desconverte, record iconversorasn.h:71,
# which binaryen inlines: its 640-byte frame) inserted into the local map; then md::CVotosCargos built from a copy of
# that map (fn 5643, a by-value parameter) is moved into a pair and the pair into the elections' map, and the result is
# md::CVotosEleicoesVota built from a copy of that map (fn 5640). Measured with pnpm wasm score in the whole link,
# before steps 7 to 9: the SCargoInfo a temporary of the converter's construction, 98 over 2277 rows, operand rows only
# (calls, data addresses, the std::format pieces' packed addresses and table slots), against 106 over 2279 (2 inserted,
# 1 deleted) with it a named local as DoConverte has it: the target keeps it in the frame slot of Desconverte's result
# (+232), and a temporary's slot is free again once its full-expression ends (a reading of why the temporary gives it).
# Compared on the objects (the function's disassembly with call indices, types and env. stripped, against the written
# form; docs/how-to-decompile.md step 3), the same bytes: the elections' insert spelled insert({eleicao, ...}),
# emplace(std::make_pair(...)) or insert(TMapa::value_type(...)); the post's emplace for its insert; the lambda
# capturing [&]; `const auto&` loop variables; currentSelection() != eid for the choice's test. Other code:
# emplace(eleicao, md::CVotosCargos(...)) (no pair, where the target moves the CVotosCargos into one at +232),
# std::ranges::find_if, std::ranges::find with &md::CCargo::GetID as projection, the local map declared after the
# election's find or after its id, the count test's operands swapped, the converter a temporary of its Desconverte call,
# and Desconverte's result in a named local. Chosen: the local names, std::find_if with a lambda (no loop written out
# was tried) and the lines between the records.
# The object is compiled through unit 13's list, between crdvvota.cpp and md/rdv/cvoto.cpp, where its records (1571240
# on) lie in the target's data between crdvvota.cpp's and md/rdv/'s: our link keeps the first object's copy of a
# linkonce function, and 5681 (the map copy's __emplace_hint_unique_key_args, unit 13's fragment) matches with this
# object's copy, built without strict aliasing (4 over 167 rows before step 8, operand rows only, where
# md/rdv/cvotoscargos.cpp.o's copy, first before the move, is 15 over 167 with 5 deleted); 11349 scores the same in both
# places. The move puts 22 objects that our link held ahead of it into the data's order: 19 by their records (md/rdv/'s
# four, md/eleitor/celeitordadoshabilitacaobiometrica.cpp, nine of comparecimentomesario/estados/, ctipoapuracaosa.cpp,
# correspondencia/ccorrespondenciaresultado.cpp, cconversortipoapuracaosa.cpp, cgeradorbu.cpp, ctextfieldmultiline.cpp)
# and three by their vtables (comparecimentomesario/estados/cgestordadomesarioinicial.cpp, cgestordadomesariovotacao.cpp
# and cgestordadomesariofinal.cpp, @1594988, @1595048, @1595108). It inverts eleven whose units' lists link after unit
# 13's: six whose records lie before 1571240 (nomearquivo/cnomearquivo.cpp, gravadores/md/curna.cpp,
# cenvelopegenerico.cpp and centidadehashes.cpp, iniciovotacao/cverificahorariozeresima.cpp and
# testeteclado/cprezeresima.cpp) and five whose vtables do (fimvotacao/caplicacaoencerrada.cpp @1542024,
# testeteclado/cbase.cpp @1545768, iniciovotacao/creiniciovotacao.cpp @1546628, testeteclado/cretomada.cpp @1546700
# and testeteclado/cesperaretestar.cpp @1546772). cconversorvotoscargo.cpp (vtable
# @1570996) stays after it, inverted as before. Steps 7 to 9 on the moved link added 11349, 5681 and 4454 and moved one
# other row, 11445 (then unit 159's trap of CConversorCandidaturas::DoDesconverte, written since), from no-candidate
# to differs: with this unit's trap gone, our link no longer holds the two traps as one body under this unit's name
# (names.tsv at the base
# names 5369 from 140-uenux2-app-comum-converters-pending.o and nothing from 159's), so the vtable slot names 159's.
# Matched: 11482, CConversorRegistroDigitalVoto<CConversorEleicoesVota>::DoDesconverte, the class template's member in
# rdv/cconversorregistrodigitalvoto.h, which unit 13's crdvvota.cpp.o emits with the vtable: m_conversor.Desconverte
# over the entity's elections, an instance binaryen inlines (its 640-byte frame opens in the frameless 11482), and that
# instance's slot 3 through the vtable.
#
# 11437 and 11438, the DoDesconverte and DoConverte of comum::asn::CConversorCabecalhoPacote (RTTI at the typeinfo
# 1562760; vtable @1562736, slots 3 and 2, table slots 2546 and 2545), match since: unit 245's file, which unit 96 lists,
# with util.cpp's members they hold (unit 96) and the md::CIDEleitoral, CIDPacote and CCabecalhoPacote members
# (fragment 273).
#
# Where no record names a file (docs/how-to-decompile.md step 3): cconversorpleito.* by rule 3, the directory of
# md::CPleitoDTO's, and its vtable lies between cconversororigemconfiguracao.cpp's objects (@1570224 to @1570320) and
# cconversorprocessoeleitoral.cpp's record (@1570392), where a file of its own sorts; cconversorregistrodigitalvoto.h by
# rule 3; cpleitodto.cpp beside its header, chosen. The records name cconversorvotoscargo.cpp,
# cconversoreleicoesvota.cpp, cconversorprocessoeleitoral.cpp and cprocessoeleitoraldto.cpp.
#
# Evidence for forms:
# - each throw's line and column, and each definition's return type spelled as its record (md::CProcessoEleitoralDTO,
#   ModuloRegistroDigitalVoto::VotosCargo, std::pair<md::CVotosCargos::SCargoInfo, md::CVotos>); written as TDado,
#   11363's row was `unresolved` on its record (`an address of ours: source_location not in the target`);
# - 11352 builds each entity Voto into a local before set_votos() is read: in one expression the field's address is
#   read first, 62 over 424 rows (3 inserted, 5 deleted), against 55 over 421 (2 deleted, the append above), both at
#   -O2; as written it matches at the tree's -O3;
# - ModuloRegistroDigitalVoto::EleicaoVota::set_idEleicao takes const_reference (src/asn1/modules, a hand edit, the
#   per-field form units 93 and 124 measured): the target's 11350 builds the field's temporary, ASN1::INTEGER's
#   constructor (call 553 with the info 1556824), the vptr 1560492 and the value at +40, then stores the value
#   (build/out/splat/pieces/asm/comum/11350.wat, offsets 0x8c to 0xae);
# - read from the target's rows, not measured against another form: 11363 copies the name with a 4-byte alignment
#   (i64.load align=2), a reference's, where its own copy into a local is 8-byte aligned, so the DTO's constructors are
#   out of line in another TU; two constructors, since the branch with the second pleito copies the result of
#   Desconverte into the optional directly; the vector is taken by value (copied, then moved in); 11351 copies each
#   CVoto's string and then destroys the temporary (a const local pushed with push_back), and builds md::CVotos from a
#   copy of the vector (CVotos(votos), a by-value parameter).
# Chosen, no evidence names them: every member's name in the new heads, md::CProcessoEleitoralDTO's id type
# (uedword), the format casts (static_cast<int> in 11363, which formats an int, type code 3; cargo.Get() in 11351, an
# unsigned, code 6), CConversorEleicoesVota's map alias and the lines of every function no throw of which has a record.
#
# md::CProcessoEleitoralDTO::GetPleito2 (record cprocessoeleitoraldto.cpp:57:15, EUE_COMUM_DADOS_8166 "Não há pleito
# 2.") is written on that line, out of line in cprocessoeleitoraldto.cpp: unit 280's comum load (fn 3771) holds its
# throw behind a 16-byte frame of its own, binaryen's inlining of its one caller. It has no index. The DTO's inline
# getters (GetID, GetNome, GetUtilizaBiometria, GetOrigem, GetPleito1, TemPleito2, GetIdentificadorPrincipal,
# GetIdentificadores; chosen names, no layout changed) are what 3771 reads.
#
# The converters include generated ASN.1 modules; paths relative to src/uenux2; the generic uenux2 rule depends on the
# sources and every uenux2 header.
CONVERSORES_140_SRCS := src/app/comum/dados/asn/rdv/cconversorvotoscargo.cpp \
  src/app/comum/dados/asn/processoeleitoral/cconversorpleito.cpp \
  src/app/comum/dados/asn/processoeleitoral/cconversorprocessoeleitoral.cpp \
  src/app/comum/dados/md/processoeleitoral/cpleitodto.cpp \
  src/app/comum/dados/md/processoeleitoral/cprocessoeleitoraldto.cpp
UENUX2_SRCS += $(CONVERSORES_140_SRCS)
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(CONVERSORES_140_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# cconversoreleicoesvota.cpp is compiled through unit 13's list, ahead of md/rdv/ (this fragment's header says why)
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/asn/rdv/cconversoreleicoesvota.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
# cconversorvotoscargo.cpp includes ecourna's app/dados/asn/cconversorcargoid.hpp, which includes its ASN.1 module by
# its bare name, as the ecourna objects' include path finds it
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/asn/rdv/cconversorvotoscargo.cpp.o: UENUX2_CXXFLAGS += -Isrc/asn1/modules
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/asn/rdv/cconversoreleicoesvota.cpp.o: UENUX2_CXXFLAGS += -Isrc/asn1/modules
# the converters' users are not reconstructed yet: 140-uenux2-app-comum-converters-roots.cpp reaches them the way the
# target does. It compiles at the tree's flags: it holds the link's copy of a std::map instance (the file says which)
$(ROOT)/$(APP)/140-uenux2-app-comum-converters-roots.o: $(ROOT)/src/units/140-uenux2-app-comum-converters-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/140-uenux2-app-comum-converters.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/140-uenux2-app-comum-converters-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/140-uenux2-app-comum-converters-roots.o
