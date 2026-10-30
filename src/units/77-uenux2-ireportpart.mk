# uenux2 api::IReportPart's parts: comum::CParteCandidatos, CParteCandidatosMajoritarios, CParteCandidatosProporcionais,
# CParteCandidatosConsultas, CParteRdv, CParteEleitores and api::CFormPart (comum::CParteCargos is unit 58). Matched:
# - the implicit destructors, the compiler's code for the class definitions, emitted with the vtables in the pending
#   object: CParteCandidatos's and CParteRdv's one body (D2 2876, D0 5590), CParteCandidatosMajoritarios's and
#   CParteCandidatosConsultas's one body (5589, 5588), CParteCandidatosProporcionais's (3867, 11210), and
#   CParteEleitores's (11205, 11204) and CFormPart's (10888, 10887), four thunks into binaryen's two merged bodies 2899
#   and 6026, which match too under the byn$mgfn-shared$ names our link gives them. In the target 2899 has two more
#   callers, the D2s 3607 and 3740 of comum::servico::CComparecimentoMesarioServico and CJustificadorServico, which no
#   unit defines: the two classes here give the same shared body and the same thunks;
# - CFormPart's constructor (fn 601), in api/gui/reports/cformpart.cpp;
# - from std::make_shared, each class's control block: __shared_ptr_emplace<T>'s D2 and D0, from the roots (11950, 11949;
#   11979, 11978; 11964, 11963; 11952, 11951; 11960, 11959; 11228, 11227), except CFormPart's (11962, 11961), which
#   cparteeleitores.cpp's object emits first; and, from the roots, the final classes' __on_zero_shared: 5969 (one body
#   for CParteCandidatos and CParteRdv) and 11958 call the D2, and 5966 (one body for the two three-part classes) holds
#   it: clang inlined it there, as the roots object shows. The classes that are not final use the virtual fn 411,
#   already matched.
# Imprime, the key function of every class, is pending (the pending file's header lists what each waits for).
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
# Forms that give the same bytes, measured on this unit's pending object with variant headers passed by -iquote, each
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
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header. A header of
# api/gui/reports/ or app/comum/relatorios/ rebuilds the two companions below, whose rules name those directories.
IREPORTPART_SRCS := src/app/comum/relatorios/cpartecandidatos.cpp src/app/comum/relatorios/cparteeleitores.cpp src/app/comum/relatorios/cparterdv.cpp src/api/gui/reports/cformpart.cpp
UENUX2_SRCS += $(IREPORTPART_SRCS)
IREPORTPART_HDRS := $(wildcard $(ROOT)/src/uenux2/src/app/comum/relatorios/*.h) $(wildcard $(ROOT)/src/uenux2/src/api/gui/reports/*.h)
$(ROOT)/$(APP)/77-uenux2-ireportpart-pending.o: $(ROOT)/src/units/77-uenux2-ireportpart-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/77-uenux2-ireportpart.mk $(IREPORTPART_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/77-uenux2-ireportpart-pending.cpp -o $(R)
$(ROOT)/$(APP)/77-uenux2-ireportpart-roots.o: $(ROOT)/src/units/77-uenux2-ireportpart-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/77-uenux2-ireportpart.mk $(IREPORTPART_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/77-uenux2-ireportpart-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/77-uenux2-ireportpart-pending.o $(APP)/77-uenux2-ireportpart-roots.o
