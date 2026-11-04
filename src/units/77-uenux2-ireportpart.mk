# uenux2 api::IReportPart's parts: comum::CParteCandidatos, CParteCandidatosMajoritarios, CParteCandidatosProporcionais,
# CParteCandidatosConsultas, CParteRdv, CParteEleitores and api::CFormPart (comum::CParteCargos is unit 58). Matched:
# - the implicit destructors, the compiler's code for the class definitions, emitted with the vtables in each class's
#   Imprime's .cpp (CFormPart's, CParteRdv's and CParteEleitores's own, and cpartecandidatos.cpp for its four
#   classes): CParteCandidatos's and CParteRdv's one body (D2 2876, D0 5590; the match lines name
#   CParteRdv's since cpartecandidatos.cpp links after cparterdv.cpp, below: step 9 renamed them), CParteCandidatosMajoritarios's and
#   CParteCandidatosConsultas's one body (5589, 5588), CParteCandidatosProporcionais's (3867, 11210), and
#   CParteEleitores's (11205, 11204) and CFormPart's (10888, 10887), four thunks into binaryen's two merged bodies 2899
#   and 6026, which match too under the byn$mgfn-shared$ names our link gives them: CParteEleitores's D2 and D0 since its
#   Imprime is written in cparteeleitores.cpp, which this fragment lists ahead of cformpart.cpp (step 9 renamed the two
#   match lines from CFormPart's). In the target 2899 has two more
#   callers, the D2s 3607 and 3740 of comum::servico::CComparecimentoMesarioServico and CJustificadorServico, which no
#   unit defines: the two classes here give the same shared body and the same thunks;
# - CFormPart's constructor (fn 601), in api/gui/reports/cformpart.cpp;
# - from std::make_shared, each class's control block: __shared_ptr_emplace<T>'s D2 and D0, from the roots (11950,
#   11949; 11979, 11978; 11964, 11963; 11952, 11951; 11960, 11959), except CParteEleitores's (11228, 11227) and
#   CFormPart's (11962, 11961), which fragment 317's cgeradorrellistaeleitores.cpp's object emits first (it builds both,
#   for 11908, and links ahead of cparteeleitores.cpp and the roots); and, from the roots, the final classes'
#   __on_zero_shared: 5969 (one body for CParteCandidatos and CParteRdv) and 11958 call the D2, and 5966 (one body for
#   the two three-part classes) holds it: clang inlined it there, as the roots object shows. The classes that are not
#   final use the virtual fn 411, already matched.
# Imprime, the key function of every class, is written: api::CFormPart's (10889, a call of its form's slot 2) in
# cformpart.cpp, which brings that class's vtable and destructors, CParteRdv's (11203) in cparterdv.cpp, CParteEleitores's
# (11206) in cparteeleitores.cpp, and CParteCandidatos's (11215), CParteCandidatosMajoritarios's (11214),
# CParteCandidatosProporcionais's (11213) and CParteCandidatosConsultas's (11212) in cpartecandidatos.cpp, whose objects
# emit those classes' vtables and destructors. The unit has no pending file since 11212, the last trapped member, was
# written. 11214's throw is on its record's line (cpartecandidatos.cpp:75:19), with the target's code 9081 and message,
# and 11212's on its own (:174:19), with code 9083 and its message; the lines of 11215, of the constructors, which follow
# 11214, and where 11212 starts above its record are a choice. CParteEleitores::Imprime calls its part's slot 2 once per record of
# comum::CEleitores: the target moves the base CDataMap's cursor to the map's first record inline (CDataMap::Reset in
# api/io/cdatamap.h, a chosen name), tests it against the map's end inline (IsFim) and calls Next (fn 5601).
#
# 11215 and 11214, measured in the whole link with `pnpm wasm score` against our plain link's body:
# - 11215's first test, whether the post has candidates' details and no candidacy to print, is a value in the target
#   (`hv ? !ExisteCandidato(...) : false`, then one branch), which reads as code binaryen inlined from a function of its
#   own with no frame (docs/how-to-decompile.md step 3); the measurements agree. Written in place, `score 24 over 74 rows` (4 inserted, 7 deleted); as an
#   out-of-line CargoSemCandidatos in ccandidaturas.cpp, clang inlines ExisteCandidato into it and 11215 scores `100 over
#   150 rows` (80 inserted); in cparterdv.cpp, `3 over 70 rows`, all operand-only. So it is in another object than both,
#   cparterdv.cpp by choice. Its name and its being a free function are chosen.
# - 11214 reads the candidate again after Busca returns on its throw's path: the loop variable is a reference.
#   `const TCandidatoID&` scores `22 over 267 rows`, all operand-only; by value, `44 over 274 rows` (7 inserted, 7
#   deleted).
# - 11213 walks comum::CPartidos as its base api::CDataMap (Reset and IsFim inline, GetCurrent 1283 and Next 3697) and holds
#   CCandidaturas::Localiza (record ccandidaturas.cpp:56, unit 89's file) inlined by binaryen, in a frame of its own. With
#   cpartecandidatos.cpp in this fragment's list, its object ahead of ccandidaturas.cpp's, it scored `46 over 406 rows`
#   (3 inserted, 3 deleted), every differing row that is not a callee, an address or a table slot a local's number; in
#   scratch links of the same objects with ccandidaturas.cpp's object moved right before cpartecandidatos.cpp's, or
#   cpartecandidatos.cpp's right after ccandidaturas.cpp's, `24 over 403 rows`, all operand-only, callees, addresses
#   and table slots.
#   The callee first is the target's order for this pair: ccandidaturas.cpp's record (1558224) precedes
#   cpartecandidatos.cpp's (1576428). The same data put cpartecandidatos.cpp before cparteeleitores.cpp and
#   cparterdv.cpp (vtables 1576388, 1576588, 1576620), which this list inverts; the other form, ccandidaturas.cpp
#   listed before it in this fragment, keeps both and moves the object 3473 rests on (fragment 89), and was not
#   measured in the whole link. So
#   cpartecandidatos.cpp is listed in fragment 89, right after ccandidaturas.cpp (the second form, measured), and
#   this unit keeps its other files; docs/reference/facts/codegen.md C4 has the effect.
#
# 11212, CParteCandidatosConsultas::Imprime, prints m_cabecalho, then m_candidato per answer number of the current post,
# after checking that CRespostas::Busca finds it (else code 9083, "Resposta não encontrada: {}/{}", the post and the
# number, both formatted as unsigned: the argument word 198), and m_rodape. What shows each part:
# - The numbers come from a function binaryen inlined: a 16-byte frame of its own inside 11212's
#   (docs/reference/facts/reading.md R10, the first sign). It walks the map at +0 of CRespostas::GetInst()'s result
#   (fn 2812) and keeps the number at +0 of each CRespostaConsulta (node +20) whose key lies from post * 1000000 to below
#   (post + 1, narrowed to a byte) * 1000000. It reads the class's map; that it is a CRespostas member, and in
#   crespostas.cpp, is a choice (unit 110's fragment has its forms): the second frame shows only that it is in a TU
#   other than 11212's. Defined in cpartecandidatos.cpp instead, clang inlines it into 11212: the object's 11212 has
#   486 rows and one frame, against 309 rows and a call.
# - std::sort over the numbers calls libc++'s own __sort<__less<unsigned>&, unsigned*>, the extern template the
#   header's __sort_dispatch routes an unsigned* sort to, which the pinned emsdk's libc++.a defines in algorithm.o
#   (system/lib/libcxx/src/algorithm.cpp). binaryen inlines it into 11212, its one caller, as the target's 11212 shows:
#   the first == last test and the 2 * log2 depth limit before the call of 4816. It brings 4816,
#   std::__introsort<_ClassicAlgPolicy, ranges::less, unsigned int*, true>, and its callees 4809 (__sift_down), 4810
#   (__swap_bitmap_pos), 4813 (__insertion_sort_incomplete), 4814 (__sort5), 4815 (__sort4), 1506 (__sort3) and 2578
#   (__partially_sorted_swap), which match from libc++.a(algorithm.o) with no source of ours.
# - The loop variable is a reference: on the throw's path the target reads the number again after Busca returns, as
#   11214 does. By value, the object's 11212 differs (32 lines of diff over 309 rows). The one call of CRespostas::GetInst serves both the walk
#   and Busca; a second call for the walk adds a call to the object's 11212.
# - CRespostas::Busca has the bytes of 1273, CCandidaturas::Busca (unit 89's fragment): binaryen keeps one body.
# Same code for 11212 in the object, compiled at the tree's flags and compared with call and global numbers read as
# symbols and __memory_base offsets masked (none linked): std::ranges::sort(numeros), and std::sort with
# std::less<TCandidatoID>(). Chosen: the names CRespostas::GetNumeros and Busca, their being members, and the locals'
# names. Before step 8, `pnpm wasm score` against our plain link: 11212 `23 over 378 rows`, all operand-only (callees,
# data addresses, the packed format string and two table slots); 4816, 4809, 4810, 4813, 4814, 4815, 1506 and 2578 `0`.
#
# Evidence. RTTI names the classes and gives api::IReportPart as each one's only base. The D2s give the layouts, and the
# allocations of fns 5971, 11908 and 11946 the sizes (44, 28, 88, 12 bytes). RTTI gives the std::function's signature:
# fn 11946 stores vptr 1544192, __func<bool (*)(), bool ()>, with table slot 1631 as its function pointer, in the frame
# the constructor moves from, and fn 11213 calls slot 6 of the __base with no argument but the callable and tests the
# result. CFormPart's member type: fn 11908 passes fn 357's result to the constructor, and 357's callee 5515 stores vptr
# 1581324, __shared_ptr_pointer<api::IFormImpressao<api::IPaperRelatorios>*, shared_ptr<api::IForm<api::IPaper>>::...>,
# in that result. Records name cpartecandidatos.cpp (:75:19, :174:19), for CParteCandidatosMajoritarios and
# CParteCandidatosConsultas only. 2876, 5589 and 3867 never store a vptr, and 5969 and 11958 call the D2 directly, so
# nothing derives from those classes: final is confirmed (docs/reference/facts/reading.md R4), and where it is written
# stays open (below). 2899 and 6026 take the vptr, and CParteEleitores's and CFormPart's control blocks use fn 411, so
# those two are not final.
# binaryen inlined the comum constructors into their one caller each: fns 11946 and 5971 copy each pointer's two words
# from a temporary in the frame, and 11908 opens a second stack frame (R10). A constructor defined in the class leaves
# neither (a probe: clang stores into the object from i64 loads of the parameters, with no temporary and no A::A left),
# and our out-of-line ones, called once from the roots, give those same shapes. So they are out of line and take their
# pointers by value (R12). fn 11908 shows what CParteEleitores's does: std::make_shared<api::CFormPart> of its by-value
# form.
#
# Chosen. Every member name, every parameter name and order, the comum pointers' element type, api::IReportPart, and
# these paths: that cpartecandidatos.cpp holds CParteCandidatos and CParteCandidatosProporcionais too, because the
# vtables interleave with the two records: Candidatos @1576388, Majoritarios @1576408, record :75 @1576428, Proporcionais
# @1576444, Consultas @1576464, record :174 @1576484; cpartecandidatos.h; cparteeleitores.{h,cpp} and cparterdv.{h,cpp}
# beside it, whose vtables run on with Cargos, Eleitores and Rdv to 1576620, after CGeradorRelVersaoPacoteDados's vtable
# and before CRelatorioTesteImpressora's, a run in name order; api/gui/reports/cformpart.{h,cpp}, whose vtable (@1583688)
# lies between api/gui/primitives.cpp's records and api/gui/reports/creport.cpp's, where that name sorts and
# api/gui/cformpart.cpp, the guess of link-order stretch 364, does not. The lines of cpartecandidatos.cpp's constructors
# are chosen, before the two records' lines.
#
# Forms that give the same bytes, measured on this unit's pending object (which held CParteCandidatosConsultas::Imprime's
# trap until 11212 was written) with variant headers passed by -iquote, each
# form on all the classes of its kind at once, comparing the whole object and each function's body with its call and GOT
# numbers read as symbols. None was linked. A function's body is what the target can show:
# - final classes: every body is the same for the implicit destructor (what these headers write), for
#   `~X() override = default;`, `~X() override {}`, `virtual ~X() = default;` and `inline ~X() override = default;` in
#   the class, for `~X() override;` with `inline X::~X() = default;` or `inline X::~X() {}` after it, for a class not
#   marked final with `~X() final = default;`, `~X() final {}`, `inline ~X() final = default;` or `~X() final;` with
#   `inline X::~X() = default;` after it, and for final on both. So nothing here shows that the destructor is implicit,
#   or where final is written. A D0 calls the D2 for 5 and 7 pointers and holds it for 3, in every one of them;
# - CParteEleitores and CFormPart, one pointer, not final: every body is the same for the implicit destructor,
#   `~X() override = default;`, `~X() override {}`, `virtual ~X() = default;`, `inline ~X() override = default;`, and
#   `~X() override;` with `inline X::~X() = default;` or `inline X::~X() {}` after it;
# - in both lists `{}` and the after-class forms reorder the object's functions and renumber its GOT entries, so the
#   whole object differs, unless the form is on CParteCandidatos alone, the first class; the other forms leave the whole
#   object as it is;
# - not the same, by the probes of classes of 1, 3, 5 and 7 pointers: a destructor out of line in the .cpp (its D0 calls
#   the D1, drops the result and frees this). On the pending object, a class with neither final: the D2s store the vptr;
# - members: the D2 and D0 are the same for any element type of the pointers (CParteEleitores's as api::CFormPart gives
#   the same pending and cparteeleitores.cpp objects), for a C array of the pointers in place of the named members, and
#   for any signature of the std::function. A std::array of them is not the same for 5 and 7: its destructor stays out
#   of line;
# - fn 601: a by-value parameter moved in is its only form among those R12 measures, and one defined in the class
#   leaves no body (the probe above), where the target has one.
#
# Paths relative to src/uenux2 (cpartecandidatos.cpp is compiled through fragment 89's list, above); the generic uenux2
# rule depends on the sources and every uenux2 header. A header of
# api/gui/reports/ or app/comum/relatorios/ rebuilds the two companions below, whose rules name those directories.
IREPORTPART_SRCS := src/app/comum/relatorios/cparteeleitores.cpp src/app/comum/relatorios/cparterdv.cpp src/api/gui/reports/cformpart.cpp
UENUX2_SRCS += $(IREPORTPART_SRCS)
IREPORTPART_HDRS := $(wildcard $(ROOT)/src/uenux2/src/app/comum/relatorios/*.h) $(wildcard $(ROOT)/src/uenux2/src/api/gui/reports/*.h)
$(ROOT)/$(APP)/77-uenux2-ireportpart-roots.o: $(ROOT)/src/units/77-uenux2-ireportpart-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/77-uenux2-ireportpart.mk $(IREPORTPART_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/77-uenux2-ireportpart-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/77-uenux2-ireportpart-roots.o
