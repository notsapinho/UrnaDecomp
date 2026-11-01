# uenux2 api::CDataMap<KeyType, RecordType>, a class template in api/io/cdatamap.h, the only file its records name
# (lines 98, 117, 143 and 158), with what its instantiations need: comum::CRegistradorMesario, a real user compiled here
# at the tree's flags; comum::CJustificadorDetalhe; the ordering of its key types; and the 5976 to 5979 enumerators of
# EUeIoError. The roots file instantiates what no landed TU uses (see its header).
#
# Target functions matched:
# - GetCurrent (line 98): 656, 1200, 1283 and 3125, 14-B thunks into 2919, which binaryen's merge-similar-functions forms
#   from these four instantiations, with the pair's second-member offset (32 or 20) and the record as parameters.
# - Next (line 117): 3697, 5601 and 5611, 12-B thunks into 3892, which the same pass forms from these three. The record
#   of the instantiation over CNumeroInscricaoEleitoral is held by 12105, which has it inlined.
# - Add(KeyType, RecordType): 5377 for <CComparecimentoMesarioPK, CComparecimentoMesario>, which holds that Add(value_type)
#   inlined and so its record. No record names 5377 itself.
# - CRegistradorMesario::Registra, a chosen name: 5378, which holds Update (line 158) inlined.
# - std::__tree members: 2222 (find<PK>), 3741 (find<CNumeroInscricaoEleitoral>), 5379
#   (__emplace_unique_key_args<CEleitorIdentidade>), 1703 (find<CEleitorIdentidade>), 860 (__find_equal<CEleitorIdentidade>).
#   1703 and 860 do not depend on the mapped type: in the target each is one body for every map of this key, and the
#   match line names this unit's instance (docs/how-to-decompile.md step 3, "A callee can be a twin").
# - 3743, an out-of-line 2-byte copy of the map's pair's second member, read as CJustificadorDetalhe's copy constructor.
# - comum::CJustificador's constructor, 3742 (app/comum/justificativa/cjustificador.cpp; the class in cjustificador.h
#   beside it): CDataMap's constructor from the name "CJustificador", then the comum::servico::CJustificadorServico
#   member's, which binaryen inlines from cjustificadorservico.cpp with api::persistencia::CDAORepositorio::Entregar
#   (the second stack prologue; Entregar's record, cdaorepositorio.hpp:79, is held by 3742, and the symbol file names
#   3742 by that anchor). Fragment 163
#   has the servico and the registry. 1391 allocates 40 bytes before it calls 3742, and the destructor (2810) calls the
#   servico's (3740) on +28: the class's size and the member's offset. A stand-in in the roots calls the constructor
#   twice for its three callers, 1391, 11474 and 11475, which build the class's singleton and are not reconstructed.
# - comum::CRegistradorMesario's singleton (cregistradormesario.h says what is evidence and what is chosen):
#   - GetInst, 815, under a std::lock_guard of the static std::mutex: when the static std::unique_ptr is empty it resets
#     it to a new object (52 bytes), whose constructor, in the class, passes the name "CRegistradorMesario" to CDataMap's
#     and builds the servico member, whose constructor binaryen inlines from ccomparecimentomesarioservico.cpp with
#     Entregar<IComparecimentoMesarioDAO> (the second stack prologue; the record cdaorepositorio.hpp:79, 1595692, anchors
#     815). The other object a reset would free goes through 5380 and free.
#   - the destructor, 5380, `= default` in the .cpp; the two trees it destroys, 1902 (the +28 map,
#     std::map<CEleitorIdentidade, CComparecimentoMesario>) and 2728 (the CDataMap's, <CComparecimentoMesarioPK,
#     CComparecimentoMesario>): recursive bodies, whose self-calls re-point once the symbol file names them (1902 by
#     5380's call, 2728 by its census pair); 1902 was `differs` against the twin of another map's tree, 2265, whose node
#     has its strings at the same offsets.
#   - HasInst, 2221: the unique_ptr tested under the same lock. Its callers, 11616 and 12105, are not written.
#   - the statics' exit destructors, 10310 (the unique_ptr's) and 10309 (the mutex's). The symbol file names the mutex
#     at 1909908 by 815's vote alone; 2221 and 10309 read that address as well, and 10309 is the mutex's destructor.
#   - QuantidadeMesariosInicio and QuantidadeMesariosFim, 3606 and 2727: each counts the map's records of one period, 1
#     or 2, with std::count_if. binaryen merges the two into 6007, `byn$mgfn-shared$` of the first, called with 1 and 2,
#     in our link as in the target (`pnpm wasm score ../target/vota_web_wasm.wasm 6007 ../build/out/wasm/vota_web/vota_web_wasm.wasm <our index of
#     byn$mgfn-shared$_ZNK5comum19CRegistradorMesario24QuantidadeMesariosInicioEv in names.tsv>`: BYTE-EXACT).
#   vota::CControladorRegistraMesariosVota's slot 7, 10795 (unit 119), calls GetInst and both counts. The roots'
#   ConsultaRegistrador gives GetInst, the two counts and HasInst their second call site (its comment names the callers
#   it stands for).
#
#   Measured in the link (pnpm wasm score against the target, after make -C src link-map):
#   - the order of the objects: ccomparecimentomesarioservico.cpp is in this unit's list ahead of
#     cregistradormesario.cpp, moved from unit 163's. In the target's data the servico's vtable (1595668), Entregar's
#     record (1595692) and the control block's vtable lie between ipedetitulomesario.cpp's records (1595636, 1595652)
#     and cregistradormesario.cpp's first (1595748): the servico's object comes right before cregistradormesario.cpp's.
#     The move also puts it ahead of objects whose records lie before its data (cjustificador.cpp's, 1560664); no row
#     moves for that. With unit 163's order, the servico after, 815 scored `125 over 521 rows (same 396,
#     replaced 121 [121 operand-only], inserted 2, deleted 2)`, its locals permuted; with this order `55 over 519 rows
#     (same 464, replaced 55 [55 operand-only], inserted 0, deleted 0)`, operands that names resolve.
#   - the destructor's place: the first function of the .cpp. In use band 2 the target runs 5380, 5379, 5378, 5377
#     downwards, so the destructor is defined (or first mentioned) above AtualizaMesarioSecao, which first mentions 5379
#     (how-to step 3, "The order of two members"). Defined below Registra, the bodies were the same (5380 `4 over 29
#     rows`, operand-only) and its ld_index came after those three.
#   - s_inst is defined before s_mutex: their exit destructors take the target's order in band 1, 10310 above 10309
#     (ld_index 2023 and 2024); the other order is not tried. In the object the mutex has the first .bss segment
#     (wasm-objdump -x), as 1909908 comes before 1909932 in the target.
#
# Not matched: Add(const value_type &) (line 143) for <CNumeroInscricaoEleitoral, CJustificadorDetalhe>, 5725. The member
# is written in the header and nothing in the link instantiates it over this key, so its row is no-candidate, with no
# stub, since its record falls on the written Add: this comment is its only note. It waits for a real caller, 6734
# (CEleitores::CompleteLoad) or 10590 (CJustificador::Justifica), in a uenux2 object. Even then the row is not expected
# to match at the tree's flags: see "Aliasing" below.
#
# Which inliner: the object keeps Add(value_type), Update, AtualizaMesarioSecao, and __emplace_unique_key_args and
# __find_equal over the key CComparecimentoMesarioPK, as functions of their own (wasm-objdump -x on the object), and
# binaryen inlines each of those into its one caller in the link, which is why 5377 and 5378 show second prologues (480
# and 16 B; 80 and 480 B). __emplace_unique_key_args and __find_equal over CEleitorIdentidade are functions of the object
# too and stay out of line: they are 5379 and 860, with two callers or more in the target and in our link. clang inlines
# Find, which is no function of the object, insert and __insert_node_at.
#
# Aliasing, measured. 5377, 5378 and 5379 reload *__child after the begin-node store in __insert_node_at, and 5725 does
# not: docs/reference/facts/app-flags.md F6 records that split. The roots object compiles at the tree's flags, as every
# object of this unit does, so that no match rests on a flag its tree lacks. A stand-in that reached Add over this key
# gave 5725 112 over 513 rows at the tree's flags, with 12 inserted and 8 deleted, against 21 over 501, all operand-only,
# at APP_CXXFLAGS: only a copy without -fno-strict-aliasing gives the target's rows, the flag is not this unit's to change
# (how-to step 4, "When only a flag closes the gap"), and so nothing here reaches that instance. When a real caller lands
# the body stays written and the row stays differs, as evidence for F6's open question. The instances over the key and
# over CEleitorIdentidade are the tree's too: from an object without the flag 5377 scored 32 over 695 rows with 5 deleted.
# GetCurrent, Next and 3741 are the same at both flag sets (the rows compared with local numbers and literal offsets
# masked), so the flags of the roots object decide nothing for them.
#
# Evidence for the forms, each by its measured alternative (object functions compared with local numbers and literal
# offsets masked; "differs" is at that level, 5378's order in a whole link):
# - In Update the record's assignment comes before the cursor's store: the other order differs in Update.
# - Add(KeyType, RecordType) builds value_type from both references: std::make_pair differs (228 rows against 130).
# - m_mesariosSecao.insert takes a value_type built in place, so the key is copied and the record moved, as in 5379:
#   std::make_pair and emplace(key, record) differ.
# - Registra tests Find first and Update is the true branch, and AtualizaMesarioSecao tests found first: the negated
#   forms differ. The body of AtualizaMesarioSecao written in Registra differs (271 rows against 35): the 80-B prologue
#   inside the test is that function's.
# - AtualizaMesarioSecao above Registra: below it 5378 and 5379 give the same rows, and the object's order then inverts
#   5378 against 5377 and 5379 in their use band (how-to step 3, "The order of two members").
# - IIdentificadorEleitor's m_tipo is unsigned: with the int the header had, find compares signed.
#   Its ordering: an operator< written out differs; one over std::tie gives the same object.
# - CEleitorIdentidade's ordering: an operator< that tests compare()'s result differs.
# - 3743 is out of line: an implicit copy constructor leaves no such function, and the pair's construction then has no
#   call.
# - Next's ++ is no std::next (differs); Add's duplicate test is no count() (differs).
#
# Forms that give the same bytes, so what is written is a choice:
# - GetCurrent's test written with an early return of the record; m_corrente++ for ++m_corrente; `auto it` for the
#   spelled iterator; emplace(registro) for insert(registro); Add({chave, registro}) for the value_type; Find's result
#   tested as a bool; insert(value_type(...)) for insert({...});
# - contains() for find() != end() in Add gives the same Add and a const find, another symbol of find's bytes. That one
#   is measured in the object only;
# - CDataMap as a member at +0 of CRegistradorMesario for the base (comum::CEleitores derives from it, by RTTI);
# - the key as a member at +0 of CComparecimentoMesario for the base;
# - a hand-written <=> for the defaulted one, and a < over std::tie, in CEleitorIdentidade and in the key;
# - m_tipo as unsigned int for the enum in IIdentificadorEleitor;
# - 3743 as the copy constructor of a 2-byte member of CJustificadorDetalhe, whose own copy is then implicit;
# - `: m_ano(outro.m_ano) {}` for the copy constructor's `= default`;
# - a typedef for `using Container` (no code).
# The members in the class are a choice as well: column 19 fits them, and a definition after the class with one more
# nested block would too (not measured here; unit 64's fragment measures that for its template).
#
# Chosen, no evidence names them: Find, Registra, AtualizaMesarioSecao, GetInst, HasInst, QuantidadeMesariosInicio,
# QuantidadeMesariosFim, s_inst, s_mutex, the CRegistradorMesario m_servico, GetMesario, PertenceSecao, m_registros,
# m_corrente, m_nome, m_mesariosSecao, m_mesario and m_periodoPresente (the columns of fn 10403 name their roles), m_ano,
# the four enumerators (from their messages), the paths of cregistradormesario.h and
# cjustificadordetalhe.h, and cjustificador.cpp as the file of 3743: its use band puts it beside 3741 and 3742, whose
# callers are in that file, and the band is the only evidence. Find returns the record because 3614 uses that result.
# For CJustificador: the path of cjustificador.h, m_servico, and the CDataMap as a base, not a member at +0 (the same
# choice as CRegistradorMesario's). The constructor follows 3743 in the file: band uses 3 runs 3743, 3742 downwards.
# The lines in cregistradormesario.cpp and cjustificador.cpp are a choice, and each file's records (85; 55, 83 and 104)
# belong to functions not written; in cregistradormesario.cpp the order is the use bands' where they say (the destructor
# first, above) and a choice elsewhere.
#
# CDataMap's constructor from a name, IsFim and Reset are written for their users in units 89, 129 and 77
# (comum::CCandidaturas's constructor 5811; fn 2268, which holds IsFim inline; comum::CParteEleitores::Imprime, fn 11206,
# which holds Reset and IsFim inline); cdatamap.h's comment says which parts are chosen.
#
# Not reconstructed: CRegistradorMesario::SaveCurrentInternal (record 85), which only fn 10337 holds, inlined
# (IGestorDadoMesario::StartState, unit 135's trap: its callees 395, 1149, 1255, 2730 and 2731 have no name), and
# CJustificador's other members (Justifica, SaveCurrentInternal, the functions that build its singleton, 1391, 11474 and
# 11475, and the destructor 2810). 5378 and 5379's other callers are 10337 and 6734.
CDATAMAP_SRCS := src/app/comum/comparecimentomesario/servico/ccomparecimentomesarioservico.cpp src/app/comum/comparecimentomesario/cregistradormesario.cpp src/app/comum/justificativa/cjustificador.cpp
UENUX2_SRCS += $(CDATAMAP_SRCS)

$(ROOT)/$(APP)/113-uenux2-cdatamap-roots.o: $(ROOT)/src/units/113-uenux2-cdatamap-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/113-uenux2-cdatamap.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/113-uenux2-cdatamap-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/113-uenux2-cdatamap-roots.o
