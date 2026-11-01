# uenux2 comum::CLocal, the comum::md locality, municipality and candidacy classes, and comum::CCandidaturas. Paths
# relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
#
# md::CLocal's two constructors are written in md/clocal.cpp, above GetSecao, and have no index of their own: the
# target inlines each into its one caller, comum::asn::CConversorLocal::DoDesconverte (fn 11452, not written), which
# copies the id, the three strings and the municipality, then the section or the contingency urn, and calls
# ValidaCriacao once in each path. Read from 11452 (md/clocal.h has the forms); unrooted, so our link drops them until
# 11452 lands, and nothing is measured on them but the object (each makes the four string copies and calls
# ValidaCriacao out of line, as 11452 does).
#
# Names and files from records: md::CLocal::GetSecao (target fn 943) and ValidaCriacao (5673); comum::CLocal::VerificaLido
# (782), GetSecaoID (1078) and VerificaEhSecao (5742); md::CInfoMunicipio::GetHorarioVerao (3725) and ValidaCriacao (5675);
# md::CComplementoMunicipio::GetHorarioVerao (2795) and ValidaCriacao (5647); md::CHorarioVeraoMunicipio::ValidaCriacao
# (5678); md::CCandidatura::GetSuplente (1389); comum::CCandidaturas::RecuperaVersaoPacote (5810); comum::GetCandidaturaAtual
# (2838, ccandidaturas.cpp:261). Each throw is on its record's line; the lines of everything else are a choice.
#
# Singletons, read from the body: comum::CLocal's accessor (401) and its static destructors (11506, 11508), and comum::CCandidaturas's
# accessor, destructor and static destructors (521, 3786, 11563, 11564) with the __tree::destroy they call (681). Each class's statics
# are members defined after the accessor; unit 109's fragment has why, the form's measurements and the same-code forms. GetInst
# is chosen, as there. 401 has 29 target callers, none written, and the roots stand in for them; 521 has 25, of which unit 129's
# 2268 is written, and holds table slot 99, so the roots take its address. GetCandidaturaAtual (2838) holds 521 inlined.
# CCandidaturas's constructor (5811) matches with the class as an api::CDataMap<uedword, md::CCandidatura> (its base, whose
# constructor takes the name as const std::string&, api/io/cdatamap.h): the target frees the temporary name before it stores the
# flag at +28 and builds the map at +32, and fns 2268 and 2838 pass the singleton's pointer to that CDataMap's GetCurrent (1200).
# A delegating constructor frees the name last (8 rows of 48). Its callers are 521 and 2838, both written, so the stand-in that
# took 2838's place went.
#
# GetCandidaturaAtual (2838) and comum::CCandidaturasDSSexo's call operator (5806). 5806 has no record; its file is a
# choice: ccandidaturas.cpp after 2838, which only the data-source classes' code calls (5806, 5807, 12641, 12742), and
# in link order the band (ledger/ordinals.tsv, uses 2) puts 5806 and 5807 after 5810 and 5811 and before ccargos.cpp's 5805. The class's header is
# ccandidaturasds.h, with the other data-source classes. 5806 builds its literal, loads the substitute's order, calls
# 2838, picks the holder or the substitute, frees the literal and only then reads the ESexo at +40: the file-static
# GetCandidatoAtual, which takes the order as its parameter and which clang inlines, gives that order (measured: 5806
# matches). Its name, its linkage and the form are chosen; a form that picks after the full expression is not tried.
# 2838's external linkage is chosen too: the roots stand in for its caller 12641 (12742 matches, from unit 102's roots
# object), and for 5806's 13101.
# CCandidaturasDSNome's call operator (5807) is 5806's shape with its literal, "CCandidaturasDSNome", and the string at +12 of
# the candidate, md::CDadosCandidato::GetNomeUrna, for the ESexo: written alike, after GetCandidatoAtual and before 5806's,
# since the band puts 5807 ahead of 5806 (ld_index 3398 against 3399 in this link). The class gets the byte 5807 reads as
# a member, with a constructor like CCandidaturasDSSexo's (chosen). Of its target callers 12649 matches (from unit 102's
# roots object) and 6076 is not written; the roots stand in for it.
#
# comum::CCandidaturas's queries, in ccandidaturas.cpp after RecuperaVersaoPacote (no record; lines and names chosen):
# GetCandidatosPartido (2272), ExisteCandidato (2271), GetCandidatos (2840) and Busca (1273), measured operand-only
# against the target in the whole link (`pnpm wasm score`: 2272 2 of 139 rows, 2271 0 of 56, 2840 1 of 77, 1273 1 of 62).
# The first three's `this` is CCandidaturas::GetInst()'s result (fn 521) at every target call, and they walk the
# base's map, as Localiza (record ccandidaturas.cpp:56, held by fn 11213) does, which also sets its
# cursor: so they are members, and api/io/cdatamap.h makes the map and cursor protected. Busca's one target body is
# also called on CRespostas::GetInst()'s result (fn 2812: by 11212, and by 11683 on one of its two calls), a CDataMap
# of the same layout giving the same bytes: CCandidaturas as its class is chosen between the two. They read three accessors added for them,
# md::CCandidatura::GetPartidoID and GetCandidatoID and md::CDadosCandidato::GetSituacao (chosen names). Their callers in
# our link are unit 77's 11215 (2271), 11214 (2840, 1273) and 11213 (2272), and unit 139's 11254 (2271) and 11255 (2272,
# 2271, 1273); the roots' Consultas stands for the rest, which its comment lists.
#
# comum::CCandidaturas::Localiza, named and typed by its record (ccandidaturas.cpp:56:15, its throw: code 7800 and the
# 42-byte message at 440373 of ledger/strings.tsv, the candidate then the post): it finds the base's key, the post times
# 1000000 plus the candidate, throws when the map holds none, and moves the base's cursor to it. Its one caller, unit
# 77's CParteCandidatosProporcionais::Imprime (fn 11213), holds it inlined by binaryen (a frame of its own) and does not
# read its result. Written with std::map::find, the end test, the throw and then the cursor's store, the order 11213's
# rows show; its being public is chosen. cpartecandidatos.cpp, unit 77's file, is in this fragment's list right after
# ccandidaturas.cpp: with its object ahead of ccandidaturas.cpp's, 11213 differs in local numbers (unit 77's fragment has
# the scores of both orders).
# comum::CLocal::GetLocalID (fn 1933; the name is its literal's, "GetLocalID", the reading of these literals below): it
# calls VerificaEhSecao with that literal and returns the place's id, the word at +16 of md::CLocal::GetSecao() (the
# CIdentificacaoSecao at +4, its TLocalID at +12). Its six callers (1543, 2725, 7787, 11188, 11242, 12098) are not
# written; the roots' LocaisID stands for them. It has no record; its line, after UrnaBiometrica, is a choice.
#
# 3473, the ASN.1 runtime's OBJECT_IDENTIFIER::decodeCommon, matches with these members in the link, and rests on the
# link order, not on a source here (docs/reference/facts/splat.md S10 item 19). ccandidaturas.cpp.o defines
# std::vector<unsigned>::push_back(&&) (273 B, at -O3) ahead of asn1.o's -Os copy (318 B) and RHVoice's document.cpp.o
# on the link line (their linking sections, wasm-objdump -x, in LINK_OBJS order: inputs 307, 706 and 877), so its
# copy is the one decodeCommon calls. That copy is the code of roots_boost.o's vector<long>::push_back(const long&),
# which binaryen merges it into (ours 553, the body that matches 543), and decodeCommon's call re-points to 543, as
# the target's does.
#
# 1709, __tree::destroy over md::CCandidatura, matches at the tree's -O3 and not at -O2:
# __destroy_at<pair<const uedword, CCandidatura>> is not inlined at cost 230 against 225, and -O3's 250 takes it, the target's frame at entry.
# 1719, vector<md::CDadosCandidato>::__destroy_vector, needed TBAA, not the level: with -fno-strict-aliasing the store of __end_
# comes ahead of the reload of __begin_, -O3 leaves that as it is, and the same compile without the flag gives the target's order.
# The copy that wins the link is cvisualizarcandidatos.cpp's (app/vota/, unit 150), ahead of ccandidaturas.cpp's, and it matches
# since app/vota/ builds with strict aliasing (src/Makefile UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6).
#
# Read from the body, no record names them:
# - The constructors of CInfoMunicipio (5674, 5676), CHorarioVeraoMunicipio (5677, 5679) and CComplementoMunicipio (3710,
#   3711): each stores the members and calls its class's ValidaCriacao, and the three pairs are that function's only
#   callers. The file is the class's. Their order is the bands': each class defines the constructor without the optional
#   first (5676, 5679, 3711), then the one with it. ValidaCriacao's place between them in the object (the band reads 5676,
#   5675, 5674) needs no definition there: the first constructor's call creates its declaration. Where the two sit among
#   the file's other lines is a choice.
# - comum::CLocal's GetMunicipio (1004), GetNomeMunicipio (1077), GetUF (1702), GetLocalData (5743), UrnaBiometrica (820):
#   each passes its own name to VerificaLido as a literal, which is the evidence for the name. The literal of fn 1003 is
#   "GetZona", so the literal is not always the whole name. 3753 passes "GetUF" as well and returns CStringUtils::ToLower of
#   it, so GetUFMinuscula is chosen. GetMunicipio's result type is chosen.
#   GetNomeMunicipio follows GetSecaoID, the order of their band, 1078 then 1077, by how-to step 3 "What a record's place
#   says". That is a judgement: a call of GetSecaoID in unwritten code earlier in the file would give the same order with
#   the definitions the other way round. Nothing read shows one: none of 1078's ten callers has a record in this file, and
#   the comum::CLocal bodies read (3752, 5738, 5741, 5743) do not call it. 4161, 11223, 11902 and 11908 have no record, so
#   they cannot be ruled out.
# - comum::CLocal's constructor and destructor (2262, 2261): the accessor (401) allocates 4 bytes and calls them, and
#   so does 5738, which holds it inlined. 2261 frees a md::CLocal through md::CLocal's destructor (5744), written by the compiler, so the member is a
#   std::unique_ptr; both are defined out of line because the target calls them.
# - md::CIndiceFoto's constructor (5659), declared by unit 36. The file is the one the record of CIndicesFotos::at names
#   (cindicesfotos.cpp:30, a function not written, whose line stays blank). md::CIndicesFotos's constructor is there
#   too, out of line by choice: comum::asn::CIndexadorFotos::DoDesconverte (11441), which
#   124-uenux2-app-comum-dados-asn.mk matches, holds it inlined and shows neither tell (that fragment says so).
# - md::CImpedido's constructors (5662, 5661, in the order of their band). The file is the record's (cimpedido.cpp:46,
#   GetImpedimentoP2, held inlined by fn 5764 and not written, so its line stays blank). The class is read from 11410, CConversorImpedido's DoDesconverte,
#   their only caller, which unit 98 writes: it calls each twice (emplace_back's two paths), so the roots' stand-ins for
#   them went with it. Why the second constructor stores 15 in the second impediment is not known: the value is the bytes'.
#
# Evidence for forms:
# - m_codigo is a plain uedword lvalue where it is formatted (5675, 5678). std::format over such a member stores the pair
#   +24 then +16, the target's order; a prvalue (.Get() over a CBaseType member, a static_cast) stores +16 then +24, and a
#   local copy of the member differs in 28 rows. Of the forms measured only the plain member gives the target's bytes, so
#   these two classes do not hold ecourna's CBaseType; CComplementoMunicipio's member follows them by choice, as no body
#   of it tells. The identification classes' four names, TMunicipioID, TZonaID, TLocalID and TSecaoID, are comum's plain
#   integers (143-uenux2-cidentificacao.mk has the measurement).
# - UrnaBiometrica tests the section as a statement of its own, so the temporary string dies before +58 is read: 820 frees
#   it between the two reads, and `return EhSecao(...) && ...`, which keeps it alive, differs in 37 rows. EhSecao is
#   defined in the class because 820, 5738 and 5741 hold the same inlined code, so clang inlined it (how-to step 3).
# - CDadosCandidato's order is a signed char: 5660 loads it with i32.load8_s and formats it as an int, which std::format
#   does for a signed char and not for a char.
# - The target reads the substitute's name in 5660 through .at() after allocating the exception, so .at() is in the throw
#   and the loop uses operator[].
# - The fuso bound of +720 and -720 is the unsigned compare the bodies hold, (word - 721) <= 64094.
#
# Chosen, no evidence names them: every data member's name, every parameter's, TemSecao, TemContingencia, EhSecao,
# GetIdentificacao, GetCodigo, GetNome, EhUrnaBiometrica, GetSiglaUF, GetOrdem, GetNomeUrna, GetZona, GetMunicipio and
# GetSecao of the identification classes; the paths of every new header (the lower-case rule, how-to step 3), under
# app/comum/md/ for the classes whose records are there; CCandidaturas::TCargoID as a member alias; which constructor
# parameter is by const reference where a pointer is all the body shows (CHorarioVerao); that
# CIdentificacaoUrnaContingencia derives from CIdentificacaoUrna with no member of its own; and CSecaoEleitoral's first
# member as a plain int, since the record gives the type's name and the bodies only its width. The code 8013 is a static_cast
# because euecomumdadoserror.h holds only the codes passed to fn 170 directly, and 3724 passes it to binaryen's merge 6029.
#
# Measured, the same code (the function's disassembly with object-local numbers masked):
# - 3786: = default or {}.
# - 943, 3724, 3725, 2795: !m_x.has_value() or !m_x; *m_x or m_x.value(), since the earlier test folds the check.
# - 5673, 5675: .empty() or .size() == 0; .size() or .length(); m_secao-> or GetSecao(). (clang folds its check); has_value()
#   or TemSecao().
# - 5673: m_secao's municipality compared directly or through a static_cast.
# - 5675, 5647, 5678: >= 100000 or > 99999.
# - 5675, 5647: x < -720 || x > 720, its operands swapped, or std::abs(x) > 720. !(x >= -720 && x <= 720) differs in 3
#   rows in each.
# - 782: !m_local, m_local == nullptr or !m_local.get(). 5743: *m_local or *m_local.get().
# - 820: if (EhSecao(...)) or the same test in a const bool first.
# - 1003, 1078: two ifs or else if. 1003: the literal or an explicit std::string. 1078: return 0 or return TSecaoID(0).
# - 5742: !TemSecao() or TemSecao() == false.
# - 2262: = default, {} or : m_local(nullptr) {}. 2261: = default or {}.
# - 5676: the scalars by mem-initializer or assigned in the body; the same for 3711 differs in 4 rows, so its mem-initializer
#   is evidence. 5679: the code by mem-initializer or assigned. Assigning the optional in the body of 5674 differs in 64
#   rows, and delegating to the other constructor in 30.
# - 5661, 5662: the flag by mem-initializer or assigned in the body. 5662's 15 assigned in the body differs in 6 rows.
# - 5659: m_indice by mem-initializer or assigned in the body.
# - 1389: ordem == 0, ordem < 1 or !ordem; [ordem - 1], .at(ordem - 1), since the test folds its check, or an iterator. The
#   two tests swapped differ in 240 rows.
# - 5810: const auto or auto. An early return of the hit differs in 256 rows, and contains() in 296.
#
# Written, not matching:
# - md::CLocal::GetContingencia (3724). The target's 3724 is a thunk into binaryen's merge 6029, whose other caller is
#   CCargo::GetDetalheConsulta (1923, record ccargo.cpp:89); unit 88 writes 1923, but clang inlines it there and the link
#   drops its body, so with no partner ours stays a whole body (`differs`). It waits for a caller that keeps 1923.
#   Measured: a try link with a stand-in of 1923 (flag at +136, member at +88, its code and literal) forms the merge,
#   and 3724, 1923, 6029 and 1003 differ from the target in operand rows only (4 of 8, 4 of 8, 5 of 33, 14 of 84).
#   comum::CLocal::GetZonaID (1003), which calls 3724, was `unresolved self-voted` on that call until unit 157 wrote
#   CConversorLocal::DoConverte (11451), the target's other caller of 3724: its two calls give the name a second voter,
#   and 1003 matches. Those three calls are the target's, so 3724 needs no stand-in.
# - md::CCandidatura's constructor (5660) needs -O3: at -O2 clang inlines vector::__init_with_size and leaves
#   __uninitialized_allocator_copy_impl out of line (cost 225 against 225), and at -O3 the threshold is 250, which keeps
#   __init_with_size (2870) out of line as the target does. Measured: a try link of this unit at -O3 with a second caller
#   of 2870, which the target has and this link does not, differs from the target in operand rows only (63 of 519 for
#   5660, 5 of 155 for 2870), against 236 of 667 rows at -O2. It stays written, and its row stays `no-candidate`: at the
#   tree's -O3 this link has no second caller of 2870, and 5660 scores 220 over 669 rows.
#
# CMunicipio's constructor (3712, unit 107) and CEleitor::ValidaCriacao (5667, unit 157), which call 1374, a copying
# wrapper of the trim body 9406 that binaryen merges into 3942 with the copying CStringUtils::ToLower, are written and
# match: 1374 is `call by:3712,5667`.
#
# 2262 is one body with ASN1::ABSTRACT_SYNTAX::info_type's constructor, and this object comes first, so its match line
# carries comum::CLocal's symbol. Its line and 2261's read C1 and D1 and not C2 and D2 since GetInst was written, and that is
# no twin: C1 and C2 are aliases of one function in clocal.cpp.o (wasm-objdump -x prints one func= for both), and GetInst mentions C1
# first, so the link map holds no C2 or D2 of this class. 3751, 3756, 5813, 2815, 2818 and 3786 read so for the same reason. 3753 is a second caller of the copying ToLower (1879), which releases unit 12's
# IndexForColumnName (1525).
CLOCAL_SRCS := src/app/comum/dados/ccandidaturas.cpp src/app/comum/relatorios/cpartecandidatos.cpp \
  src/app/comum/dados/clocal.cpp \
  src/app/comum/dados/md/chorarioveraomunicipio.cpp src/app/comum/dados/md/cinfomunicipio.cpp \
  src/app/comum/dados/md/clocal.cpp src/app/comum/dados/md/eleitor/cimpedido.cpp \
  src/app/comum/dados/md/candidatura/ccandidatura.cpp src/app/comum/dados/md/candidatura/cindicesfotos.cpp \
  src/app/comum/dados/md/municipiozona/ccomplementomunicipio.cpp
UENUX2_SRCS += $(CLOCAL_SRCS)
# the classes' users are not reconstructed yet: 89-uenux2-clocal-roots.cpp gives each function its call sites
$(ROOT)/$(APP)/89-uenux2-clocal-roots.o: $(ROOT)/src/units/89-uenux2-clocal-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/89-uenux2-clocal.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/89-uenux2-clocal-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/89-uenux2-clocal-roots.o
