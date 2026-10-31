# uenux2 comum::CLocal, the comum::md locality, municipality and candidacy classes, and comum::CCandidaturas. Paths
# relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
#
# Names and files from records: md::CLocal::GetSecao (target fn 943) and ValidaCriacao (5673); comum::CLocal::VerificaLido
# (782), GetSecaoID (1078) and VerificaEhSecao (5742); md::CInfoMunicipio::GetHorarioVerao (3725) and ValidaCriacao (5675);
# md::CComplementoMunicipio::GetHorarioVerao (2795) and ValidaCriacao (5647); md::CHorarioVeraoMunicipio::ValidaCriacao
# (5678); md::CCandidatura::GetSuplente (1389); comum::CCandidaturas::RecuperaVersaoPacote (5810). Each throw is on its
# record's line; the lines of everything else are a choice.
#
# Singletons, read from the body: comum::CLocal's accessor (401) and its static destructors (11506, 11508), and comum::CCandidaturas's
# accessor, destructor and static destructors (521, 3786, 11563, 11564) with the __tree::destroy they call (681). Each class's statics
# are members defined after the accessor; unit 109's fragment has why, the form's measurements and the same-code forms. GetInst
# is chosen, as there. 89's roots stand in for callers none of which are written: 401 has 29, 521 has 25.
# CCandidaturas's constructor (5811) stays `differs`: the target frees the temporary name before it stores the flag at +28 and builds
# the map at +32, so the name's owner is a base class or member object at +0, and the records name api::CDataMap<K, V>
# there. A delegating constructor frees it last (8 rows of 48). A scratch class with a base taking const std::string& gives the
# target's order of calls and stores exactly. 1709, __tree::destroy over md::CCandidatura, stays `differs` at -O2:
# __destroy_at<pair<const uedword, CCandidatura>> is not inlined at cost 230 against 225, and -O3's 250 takes it, the target's frame at entry.
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
#   (cindicesfotos.cpp:30, a function not written, whose line stays blank).
# - md::CImpedido's constructors (5662, 5661, in the order of their band). The file is the record's (cimpedido.cpp:46,
#   GetImpedimentoP2, held inlined by fn 5764 and not written, so its line stays blank). The class is read from 11410, CConversorImpedido's DoDesconverte,
#   their only caller. Why the second constructor stores 15 in the second impediment is not known: the value is the bytes'.
#
# Evidence for forms:
# - m_codigo is a plain uedword lvalue where it is formatted (5675, 5678). std::format over such a member stores the pair
#   +24 then +16, the target's order; a prvalue (.Get() over a CBaseType member, a static_cast) stores +16 then +24, and a
#   local copy of the member differs in 28 rows. Of the forms measured only the plain member gives the target's bytes, so
#   these two classes do not hold ecourna's CBaseType, the type the using-declaration in iresultado.h gives
#   comum::TMunicipioID; CComplementoMunicipio's member follows them by choice, as no body of it tells. The identification
#   classes keep all four of iresultado.h's using-declarations, TMunicipioID, TZonaID, TLocalID and TSecaoID, by choice:
#   the records spell the names, these bodies read only widths, and another declaration would not compile beside those.
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
# - comum::CLocal::GetZonaID (1003) is `unresolved self-voted` on its call of md::CLocal::GetContingencia (3724), and nothing
#   else that holds calls 3724. The target's 3724 is a thunk into binaryen's merge 6029, whose other caller is
#   CCargo::GetDetalheConsulta (1923, record ccargo.cpp:89); unit 88 writes 1923, but clang inlines it there and the link
#   drops its body, so with no partner ours stays a whole body (`differs`). It waits for a caller that keeps 1923, or for
#   11451, CConversorLocal::DoConverte, the other caller. Measured: a try link with a stand-in
#   of 1923 (flag at +136, member at +88, its code and literal) forms the merge, and 3724, 1923, 6029 and 1003 differ from
#   the target in operand rows only (4 of 8, 4 of 8, 5 of 33, 14 of 84).
# - md::CCandidatura's constructor (5660) needs -O3: at -O2 clang inlines vector::__init_with_size and leaves
#   __uninitialized_allocator_copy_impl out of line (cost 225 against 225), and at -O3 the threshold is 250, which keeps
#   __init_with_size (2870) out of line as the target does. Measured: a try link of this unit at -O3 with a second caller
#   of 2870, which the target has and this link does not, differs from the target in operand rows only (63 of 519 for
#   5660, 5 of 155 for 2870), against 236 of 667 rows at -O2. It stays written, and its row stays `no-candidate`
#   (docs/how-to-decompile.md step 4, "When only a flag closes the gap").
#
# Not written:
# - CMunicipio's constructor (3712) and CEleitor::ValidaCriacao (5667) call 1374, a copying wrapper of the trim body 9406
#   that binaryen merges into 3942 with the copying CStringUtils::ToLower; no source defines it yet, and either alone
#   would be self-voted on it.
#
# 2262 is one body with ASN1::ABSTRACT_SYNTAX::info_type's constructor, and this object comes first, so its match line
# carries comum::CLocal's symbol. 3753 is a second caller of the copying ToLower (1879), which releases unit 12's
# IndexForColumnName (1525).
CLOCAL_SRCS := src/app/comum/dados/ccandidaturas.cpp src/app/comum/dados/clocal.cpp \
  src/app/comum/dados/md/chorarioveraomunicipio.cpp src/app/comum/dados/md/cinfomunicipio.cpp \
  src/app/comum/dados/md/clocal.cpp src/app/comum/dados/md/eleitor/cimpedido.cpp \
  src/app/comum/dados/md/candidatura/ccandidatura.cpp src/app/comum/dados/md/candidatura/cindicesfotos.cpp \
  src/app/comum/dados/md/municipiozona/ccomplementomunicipio.cpp
UENUX2_SRCS += $(CLOCAL_SRCS)
# the classes' users are not reconstructed yet: 89-uenux2-clocal-roots.cpp gives each function its call sites
$(ROOT)/$(APP)/89-uenux2-clocal-roots.o: $(ROOT)/src/units/89-uenux2-clocal-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/89-uenux2-clocal.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/89-uenux2-clocal-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/89-uenux2-clocal-roots.o
