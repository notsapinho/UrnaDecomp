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
# - from the roots' std::make_shared, each class's control block: __shared_ptr_emplace<T>'s D2 and D0 (11950, 11949;
#   11979, 11978; 11964, 11963; 11952, 11951; 11960, 11959; 11228, 11227; 11962, 11961) and the final classes'
#   __on_zero_shared: 5969 (one body for CParteCandidatos and CParteRdv) and 11958 call the D2, and 5966 (one body for
#   the two three-part classes) holds it: clang inlined it there, as the roots object shows. The classes that are not
#   final use the virtual fn 411, already matched.
# Imprime, the key function of every class, is pending (the pending file's header lists what each waits for).
#
# Evidence. RTTI names the classes and gives api::IReportPart as each one's only base. The D2s give the layouts, the
# allocations of fns 5971, 11908 and 11946 the sizes (44, 28, 88, 12 bytes), and Imprime's calls of slot 2 the
# pointees' type; fn 11213's call, slot 6 of the __base, tested, with no argument but the callable, gives the
# std::function its signature. Records name cpartecandidatos.cpp (:75:19, :174:19). 2876, 5589 and 3867 never store a
# vptr, and 5969 and 11958 call the D2 directly, so those classes are final (docs/reference/facts/reading.md R4);
# 2899 and 6026 take the vptr, and CParteEleitores's and CFormPart's control blocks use fn 411, so those two are not.
# binaryen inlined the comum constructors into their one caller each: fns 11946 and 5971 copy each pointer's two words
# from a temporary in the frame, and 11908 opens a second stack frame (R10). A constructor defined in the class leaves
# neither (a probe: clang stores into the object from i64 loads of the parameters, with no temporary and no A::A left),
# and our out-of-line ones, called once from the roots, give those same shapes. So they are out of line and take their
# pointers by value (R12). fn 11908 shows what CParteEleitores's does: std::make_shared<api::CFormPart> of its by-value
# form.
#
# Chosen. Every member name, every parameter name and order, and these paths: cpartecandidatos.h, and
# cparteeleitores.{h,cpp} and cparterdv.{h,cpp} beside the recorded file, whose vtables run Candidatos..., Cargos,
# Eleitores, Rdv at 1576388-1576620, after CGeradorRelVersaoPacoteDados's vtable and before CRelatorioTesteImpressora's,
# a run in name order; api/gui/reports/cformpart.{h,cpp}, whose vtable (@1583688) lies between api/gui/primitives.cpp's
# records and api/gui/reports/creport.cpp's, where that name sorts and api/gui/cformpart.cpp, the guess of link-order
# stretch 364, does not. CFormPart's member type: RTTI's __shared_ptr_pointer<api::IFormImpressao<api::IPaperRelatorios>*,
# std::shared_ptr<api::IForm<api::IPaper>>::...> shows forms held that way, and its constructor's two copied words show
# nothing of the pointee. The lines of cpartecandidatos.cpp's constructors are chosen, before the two records' lines.
#
# Forms that give the same bytes. Probes with uenux2's flags of classes of 3, 5 and 7 std::shared_ptr, the last with a
# std::function, each with a key function:
# - final classes: the whole object is the same for the implicit destructor (what these headers write), for
#   `~X() override = default;`, `~X() override {}`, `virtual ~X() = default;` and `inline ~X() override = default;` in
#   the class, for `~X() override;` with `inline X::~X() = default;` or `inline X::~X() {}` after it, for a class not
#   marked final with `~X() final = default;`, `~X() final {}`, `inline ~X() final = default;` or `~X() final;` with
#   `inline X::~X() = default;` after it, and for final on both. So nothing here shows that the destructor is implicit
#   or that final is on the class. A D0 calls the D2 for 5 and 7 pointers and holds it for 3, in every one of them. Not
#   the same: a destructor out of line in the .cpp (its D0 calls the D1, drops the result and frees this), and a class
#   with neither final (its D2 stores the vptr);
# - CParteEleitores and CFormPart, one pointer, not final: the whole object is the same for the implicit destructor,
#   `~X() override = default;`, `~X() override {}`, `inline ~X() override = default;`, and `~X() override;` with
#   `inline X::~X() = default;` or `inline X::~X() {}` after it. Not the same: out of line;
# - members: the D2 and D0 are the same for any element type of the pointers (CParteEleitores's as api::CFormPart gives
#   the same whole object), for a C array of the pointers in place of the named members, and for any signature of the
#   std::function. A std::array of them is not the same for 5 and 7: its destructor stays out of line;
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
