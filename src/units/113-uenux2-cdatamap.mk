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
# Chosen, no evidence names them: Find, Registra, AtualizaMesarioSecao, GetMesario, PertenceSecao, m_registros,
# m_corrente, m_nome, m_mesariosSecao, m_mesario and m_periodoPresente (the columns of fn 10403 name their roles), m_ano,
# the four enumerators (from their messages), the paths of cregistradormesario.h and
# cjustificadordetalhe.h, and cjustificador.cpp as the file of 3743: its use band puts it beside 3741 and 3742, whose
# callers are in that file, and the band is the only evidence. Find returns the record because 3614 uses that result.
# The lines in cregistradormesario.cpp and cjustificador.cpp are a choice, and each file's records (85; 55, 83 and 104)
# belong to functions not written.
#
# Not reconstructed: CDataMap's constructor and CRegistradorMesario's (inlined into 815, GetInst, which gives the map
# the literal "CRegistradorMesario"), its destructor 5380, CRegistradorMesario::SaveCurrentInternal (record 85, held by
# 10337) and CJustificador's members. 5378 and 5379's other callers are 10337 and 6734.
CDATAMAP_SRCS := src/app/comum/comparecimentomesario/cregistradormesario.cpp src/app/comum/justificativa/cjustificador.cpp
UENUX2_SRCS += $(CDATAMAP_SRCS)

$(ROOT)/$(APP)/113-uenux2-cdatamap-roots.o: $(ROOT)/src/units/113-uenux2-cdatamap-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/113-uenux2-cdatamap.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/113-uenux2-cdatamap-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/113-uenux2-cdatamap-roots.o
