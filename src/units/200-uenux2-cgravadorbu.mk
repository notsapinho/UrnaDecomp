# uenux2 comum::CGravadorBU (app/comum/gravadores/cgravadorbu.{h,cpp}, the files its records name) and the BU's result
# data classes comum::md::CVotosCargo, md::CResultadoVotacao and md::CResultadoVotacaoPorEleicao
# (app/comum/gravadores/md/cvotoscargo.h, cresultadovotacao.{h,cpp} and cresultadovotacaoporeleicao.{h,cpp}), paths
# relative to src/uenux2. The sources are md/cresultadovotacao.cpp, then cgravadorbu.cpp: that order is the target's,
# where CResultadoVotacao's constructor (fn 3824) is ahead of AcrescentaVotoVotavel (fn 3820) in their use band, other
# objects' functions between them (fns 3821 to 3823); md/cresultadovotacaoporeleicao.cpp's and md/cvotoscargo.cpp's
# places between them are chosen (neither has a function of its own in the target).
#
# Matched:
# - CGravadorBU's implicit destructors (target fns 5857 and 11628, slots 0 and 1) and the destroy of the tree of its
#   std::map<md::TCargoID, uebyte> at +284 (fn 3814), emitted with the vtable in cgravadorbu.cpp's object, whose
#   GravaResultado (fn 11629) is the class's key function. The D2's other callees are in the link: fn 1405 (unit 155's)
#   and fn 857.
# - libc++'s uninitialized copy of a range of md::CResultadoVotacaoPorEleicao (fn 2853) and
#   std::vector<md::CResultadoVotacaoPorEleicao>'s __base_destruct_at_end (fn 5859), template instances whose one target
#   caller is fn 11629 (four calls of 2853, two of 5859): 2853 comes from md/centidadebu.cpp's object (unit 321's), whose
#   four md::CEntidadeBU constructors copy the results, and 5859 from cgravadorbu.cpp's, which destroys them. That the
#   20-byte elements are md::CResultadoVotacaoPorEleicao: MontaEntidadeBU's record (cgravadorbu.cpp:636) takes a const
#   std::vector<md::CResultadoVotacaoPorEleicao> &, and fn 2853's nested copies have the three classes' layouts.
# - CGravadorBU::AcrescentaVotoVotavel (fn 3820, record cgravadorbu.cpp:221:23, static) in cgravadorbu.cpp, and the
#   std::vector<md::CVotosVotavel>::push_back it calls three times (fn 1944, from cgravadorbu.cpp.o; 3819 below calls
#   it three times too). It returns at
#   once for a count of 0, pushes a CVotosVotavel without identification for BRANCO, NULO and
#   NULO_CARGO_SEM_CANDIDATO (the target's mask 280 over the type), one identified with the party 0 when
#   cargo.IsConsulta() (the byte at +136), and otherwise one with the party of the candidacy CCandidaturas::Busca finds,
#   or, when Busca returns null, the number of the md::CPartido that CPartidos::GetInst().Find (api::CDataMap's, the
#   cursor at +12 set) finds for the candidate, throwing CUeComumGravadoresError 8638 "Candidato {} / cargo {} não
#   existe" when there is none. CGravadorBU declares `using TVetorVotosVotaveis = std::vector<md::CVotosVotavel>;` and
#   `using TQtdEleitor = ueword;`: the record spells both names, the push_back's 24-byte elements are CVotosVotavel, and
#   with ecourna's CBaseType for the count the parameter is masked (p & 65535), which the target does not do (measured
#   in the scratch try below). Chosen: the aliases' place in the class, public for the member (it was private until
#   3819's helpers, free functions, called it), the null test of
#   Busca's result first (a scratch try that tested the found candidacy first, with a CBaseType count as well, scored
#   95 over 359; the two were not measured apart), and the locals' names.
# - md::CResultadoVotacao's constructor (fn 3824, no record) in md/cresultadovotacao.cpp, out of line in an object
#   apart from its caller's (cresultadovotacao.cpp says what places it), and the copy of a std::vector<md::CVotosCargo>
#   it calls (__init_with_size, fn 1556), from that object; and std::vector<md::CResultadoVotacao>'s
#   __emplace_back_slow_path<const md::CResultadoVotacao &> (fn 3817), the push_back of a copy, from cgravadorbu.cpp's
#   object (MontaResultadosVotacao's three push_backs). 11629 is the one target caller of 3824 and 3817 (three calls
#   each) and calls 1556 six times; 3817 and 3824 call it too. 3817's body holds CResultadoVotacao's implicit copy
#   constructor (the two words at +0 and +4 and fn 1556 over the vector at +8).
# - comum::FiltraCargos (fn 3818, no record) in cgravadorbu.cpp after AcrescentaVotoVotavel, and the relocation of a
#   std::vector<md::CCargo> it calls in its reserve and its push_back (std::__uninitialized_allocator_relocate, fn 3816,
#   from cgravadorbu.cpp's object): cgravadorbu.cpp's notes say what it does, why it reads as an external function
#   there, and what is chosen. Its one target caller, 11629, calls it three times (MontaResultadosVotacao's calls), and
#   3816's other target caller is 11371 (comum::asn::CConversorEleicaoPE::DoDesconverte, fragment 299's); 3818 calls it
#   twice. Measured in the whole link before step 8 (pnpm wasm score against the target): 3818 9
#   over 312 rows and 3816 2 over 243, operand-only, every operand a call's. It is the first form written; std::copy_if
#   with a lambda was not tried.
# - comum::MontaVotosCargos (fn 3819, no record, a chosen name) in cgravadorbu.cpp between AcrescentaVotoVotavel and
#   FiltraCargos, the use band's order (3820, 3819, 3818), with the six functions it holds inlined (cgravadorbu.cpp's
#   header says what each does and what is chosen), and md::CVotosCargo's constructor, which it holds inlined too, in
#   md/cvotoscargo.cpp (cvotoscargo.h says why it is out of line; the file's place in the list below is chosen). The
#   libc++ code it holds (the copy assignment and the range insert of a std::vector<md::CVotosVotavel>, the push_back
#   of a std::vector<md::CVotosCargo>, map::at) is its own; its one target caller, 11629, calls it three times
#   (MontaResultadoVotacao's call, inlined three times). What the bytes decided, each measured in the whole link with pnpm wasm score
#   against the target (rows over rows, structural rows, at the state of the source then):
#   - the party votes are appended with legendas.cbegin() and cend(): the target's range insert assigns through a
#     temporary copy and constructs element by element, libc++'s path for const iterators; with
#     std::make_move_iterator 653 over 2007 rows, with cbegin() and cend() 482 over 1983 (the definitions then ran
#     callers first; begin() and end() were not measured apart);
#   - the definitions run callees first (VotosRespostas, MontaVotosNominais, MontaVotosVotaveis, MontaVotosCargos):
#     with MontaVotosCargos first, four orders of the rest each gave 482 over 1983 rows (32 inserted, 33 deleted);
#     callees first, 40 over 1954 (3 and 1), the same with VotosRespostas moved last; MontaVotosVotaveis,
#     MontaVotosCargos, MontaVotosNominais, VotosRespostas gave 665 over 2025 (docs/reference/facts/codegen.md C4);
#   - VotosRespostas and VotosCandidatos both end in VotosNumeros: with the votes loop written in each, 40 over 1954
#     (3 rows inserted, 1 deleted, the destroy loop of the answers' copy), and with VotosNumeros 35 over 1951, every
#     row operand-only and every operand a call's or a data address, before step 8; step 9 matched it;
#   - VotosRespostas walks the copy of the answers by index (the target's loop multiplies the index by 28) and
#     declares the numbers' vector before the copy (the target frees the copy first); an unsigned int index, `!=` for
#     `<`, a non-const copy, and `++i` with a named local for the number each gave the same 40 over 1954 as std::size_t,
#     `<`, a const copy and `i++` with the plain push_back; an int index compared with a cast of size() gave 91 over
#     1977;
#   - the remaining forms are what the target's shape shows: MontaVotosNominais assigns its result from the branch's
#     prvalue (the target never zeroes the result before the branch moves it in), reads the cargo's id once for the
#     blank and null votes, and pushes them through AcrescentaVotosSemCandidato (with the votes pushed in place, the
#     frame's slots came out in another order: the target's put the CVotosVotavel temporaries' slot at the top);
#     MontaVotosVotaveis reads IsProporcional() into a local before it builds the party votes (with the test after
#     the vector's declaration the target's one i32.or of both bytes came out as two branches after it).
#   md/cvotoscargo.cpp after cgravadorbu.cpp in the list gave the same score as before it (482 over 1983, at the state
#   of the second bullet's first number), and cgravadorbu.cpp built with strict aliasing gave 196 over 1969 for 3819
#   (at the 40 state, a measurement only: the tree's flags stand).
#   The helpers' being free functions of comum is how-to "Names no evidence gives" (they read no class state);
#   static members of CGravadorBU are the other form that rule allows, which would leave AcrescentaVotoVotavel
#   private, and a static member compiles as a free function does but for its name (a reading, not measured).
# Measured in this link before step 8 (pnpm wasm score against the target): 3820 23 over 332 rows, 1944 4 over 137,
# 3824 1 over 30, 1556 4 over 109, 3817 9 over 388, every one operand-only; every operand of 1944, 3824, 1556 and 3817 a
# call's or a data address, and of 3820 those and the packed format string's address and two constants that are table
# slots of this link (the format buffer's and the exception's destructor's), which step 9's names resolve.
# Earlier measurements (step 9 matched 5857, 11628, 3814, 2853 and 5859 with them): 5857 9 over 101 rows, 11628 2 over
# 5, 3814 1 over 15, 2853 6 over 206 and 5859 3 over 122, every one operand-only and every operand a call's or a data
# address. The scratch try for 3820 and 1944, before cpartidos.h derived CPartidos from api::CDataMap: try-tu.sh
# --component uenux2/src/app/comum/gravadores, over variants of cpartidos.h (CPartidos derived from that CDataMap) and
# of cgravadorbu.h under -iquote, scored 3820 at 23 over 332 rows and 1944 at 4 over 137 with the form above, and 95
# over 359 with a CBaseType count and the found candidacy tested first.
#
# Measured on this unit's link as it lands (pnpm wasm score against the target, every row operand-only): 5857 8 over
# 101 rows, 11628 2 over 5, 3814 1 over 15, 2853 6 over 206, 5859 3 over 122, 3817 9 over 388, 3818 9 over 312, 3816 2
# over 243, 3819 35 over 1951, 3820 23 over 332, 3824 1 over 30, 1556 4 over 109 and 1944 4 over 137.
#
# Evidence and choices: cgravadorbu.h and the md headers say what each layout comes from and which types and names are
# chosen; the paths of the md headers, md/cresultadovotacao.cpp and md/cresultadovotacaoporeleicao.cpp are chosen
# (beside cvotosvotavel.h).
#
# - comum::CGravadorBU::GravaResultado (fn 11629, slot 7, records cgravadorbu.cpp:484 and :485), with what it holds:
#   LeChavePublica and MontaEntidadeBU (records :542 to :560 and :636), the results' helpers MontaResultadosVotacao,
#   MontaResultadosVotacaoPorEleicao and MontaResultadoVotacao (no record), md::CResultadoVotacaoPorEleicao's constructor
#   (md/cresultadovotacaoporeleicao.cpp), md::CEntidadeBU's four constructors and ValidaCriacao (unit 321's
#   md/centidadebu.cpp, records :159 to :177) and comum::asn::Codifica (unit 321's asn/cconversorentidadebu.cpp, with
#   IConversorASN's Converte and CFileASN::CodeObject for the BU's entity): cgravadorbu.cpp's header says what each does
#   and what is read, cgravadorbu.h and the md headers what each member is. As it lands, fn 11629 is 423 over 7089 rows,
#   every one operand-only: calls, data addresses, the packed format strings' addresses, and the constants 69 and 148
#   (eleven and six rows), table slots of this link (the exception's destructor's and the format buffer's), as for fn
#   3820. What the bytes decided, each measured in the whole link with pnpm wasm score against the target, with that one
#   form changed from the source as it lands:
#   - the CResultadoVotacao of each type built by MontaResultadoVotacao, so that the votes' vector is destroyed before
#     the result is moved into the one MontaResultadosVotacao keeps: built in place (the first directly, the others by
#     assigning a temporary), 1184 over 7153 rows (64 inserted, 42 deleted);
#   - md::CResultadoVotacaoPorEleicao's constructor out of line, in its own object: defined in the class, 941 over 7196
#     (107 inserted, 35 deleted); out of line, its copy of the vector calls fn 1556 per element, as the target's does;
#   - its +4 an SQtdeAptos copied whole (one 32-bit load and store, the target's): with two ueword members set from
#     the SQtdeAptos's fields, 429 over 7093 (4 inserted, 0 deleted: two 16-bit loads and stores);
#   - the election's id read into a local before CConfiguracaoEleicao::GetInst() (the target loads it first): with
#     eleicao.GetID() at each use, 456 over 7093 (4 inserted, 3 deleted);
#   - MontaResultadosVotacaoPorEleicao's parameters with the posts' order map before the voters' map: the other way
#     round, 425 over 7090 (1 inserted, 1 deleted: where fn 11629 copies `this` into the local the inlined code reads);
#   - each result kept when GetTotaisVotosCargo().size() > 0 (the target loads the end first): with !empty(), 427 over
#     7091 (2 and 2);
#   - LeChavePublica's test of the decrypted key as size() == 0: with empty(), 427 over 7091 (2 and 2, the begin
#     loaded first; CControlaArmazenamentoDeImagens::LeChavePublica, unit 293's, spells it empty(), and target fn 2725
#     loads the end first there too);
#   - the encrypted branch's copy of the coded bytes as std::vector<uebyte>(size) filled by std::copy (the begin's
#     zero set before the end's, the target's order; the vector's zero fill is dead and goes): with the iterator-pair
#     constructor, 427 over 7091 (2 and 2), the two sets the other way round; clang's output for this TU (its IR or its
#     object) set the end first for cbegin()/cend(), data() to data() + size(), braces, auto, std::begin/std::end, a non-const
#     copy and the copy declared after the table too, and the begin first for this form;
#   - md::CEntidadeBU's constructors out of line in md/centidadebu.cpp, or defined in the class: 423 over 7089 both
#     ways (the first is written, the form cenvelopegenerico.cpp has);
#   - FiltraCargos defined after the results' helpers (declared before them): defined first, the same bytes, with 3816
#     linked ahead of 3817 (cgravadorbu.cpp's header).
#   Chosen, beyond those: every name the records do not give (the helpers, Codifica, the locals, the members of
#   cgravadorbu.h), the helpers' being free functions of comum and their parameters' types and order beyond the
#   target's, the four constructors' parameter lists, the place of each function without a record, and the comment
#   lines of cgravadorbu.cpp's header. The roots file's stand-ins for fn 11629 (of fns 2853, 5859, 3817, 3818, 3819 and
#   3824) went with it; its vtable sink stays, for 12098, which holds the constructor (below).
# The constructor has no target index: vota::CGravaResultado::StartState (fn 12098) holds it inlined behind a 192-byte
# frame (line 238 of the folded readout `pnpm --silent wasm fn ../target/vota_web_wasm.wasm 12098` prints, counted from
# the line after `;; --- folded readout`). It is written in cgravadorbu.cpp ahead of AcrescentaVotoVotavel, unrooted, so
# wasm-ld drops it and it matches nothing until 12098 is written: a public constructor that delegates to a private one
# taking the vector, the map and four std::optionals by value, MontaOrdemCargos (file-local) building the map at +284
# in its initializer (cgravadorbu.cpp's header says what each reading rests on). Measured on cgravadorbu.cpp.o
# (wasm-objdump -d): the public constructor opens a 192-byte frame and stores, offset for offset, what readout lines 240
# to 283 store (the vector moved to +180, the map to +168, the optionals built at +120, +108, +96 and +88 and copied to
# +40, +24, +8 and +0), then calls the private one, which opens no frame and makes the calls of readout lines 284 to
# 384 in their order (IGravador's constructor, ConverteFase, CDadoCorrespondencia's copy, comum::CCargos's GetInst,
# RemoveFiltro, GetInst, OrdenaPorImpressao, Reset, IsFim and GetCurrent, the node's allocation,
# __tree_balance_after_insert, Next and IsFim); binaryen would inline it at its one call (a reading). check_srcloc.py
# --strict on the object: its 15 records are the target's. Chosen: the parameters' order and form, the private
# constructor and its constants (the extension 4, the SAVD file 35, 49, "bu.pk1" and true), MontaOrdemCargos's name
# and linkage, and the loop's spelling (a for over Reset, IsFim and Next; emplace with a pre-incremented byte).
CGRAVADORBU_SRCS := src/app/comum/gravadores/md/cresultadovotacao.cpp \
  src/app/comum/gravadores/md/cresultadovotacaoporeleicao.cpp src/app/comum/gravadores/md/cvotoscargo.cpp \
  src/app/comum/gravadores/cgravadorbu.cpp
UENUX2_SRCS += $(CGRAVADORBU_SRCS)
# cgravadorbu.cpp reads comum::CConfiguracaoEleicao, whose header includes Boost's ptime, and ecourna's media
# information, whose converter's header includes its ASN.1 module by its bare name
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorbu.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR) -Isrc/asn1/modules
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorbu.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
W200_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
# the constructor that stores the vtable is unrooted and its one caller, 12098, not written:
# 200-uenux2-cgravadorbu-roots.cpp stands in for 12098; it compiles with the tree's flags
$(ROOT)/$(APP)/200-uenux2-cgravadorbu-roots.o: $(ROOT)/src/units/200-uenux2-cgravadorbu-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/200-uenux2-cgravadorbu.mk $(W200_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/200-uenux2-cgravadorbu-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/200-uenux2-cgravadorbu-roots.o
