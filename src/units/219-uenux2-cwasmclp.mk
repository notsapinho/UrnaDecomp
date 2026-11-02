# uenux2 api::CLp, the printer the reports print through, in mock/app/simulador/wasm/cwasmclp.cpp, with the class head in
# api/hwil/clp.h: the destructor (target fn 5978), the singleton's accessor GetInst (fn 3876, which holds the
# constructor inlined), the member fn 3875 (Imprime, a chosen name), the statics' exit-time destructors (fns 12016,
# 12015) and api::CPolySingletonList::has<api::IImpressoraRelatorios> (fn 3392), the header's instance the constructor
# calls twice.
#
# Evidence:
# - The name. Fn 12016 is the exit-time destructor of the static pointer at @1834044: it clears it and, when it held an
#   object, calls fn 5978 on it and frees it. Fn 3876, which builds a 12-byte object through the constructor whose
#   record is api::CLp::CLp() (1543108, cwasmclp.cpp 10:68), stores it in that pointer and calls fn 5978 on the object
#   the pointer held before, then frees it: the shape of std::unique_ptr<CLp>::reset with a destructor called as a
#   function. So fn 5978 is CLp's destructor (the D2, its two callers adding the free).
# - Out of line. Measured on two scratch TUs at the tree's flags (try-tu.sh --symbols --component
#   uenux2/mock/app/simulador/wasm, then wasm-objdump -d of the object) holding this head, a GetInst of unit 104's
#   shape and the static pointer: with the destructor defined in the .cpp, GetInst and the pointer's exit-time
#   destructor each call the D2 and then operator delete, the target's shape; with the destructor implicit, clang emits
#   std::default_delete<api::CLp>::operator() out of line, the destructor and the free inside it, and both call that.
# - The body: +8 is released as std::unique_ptr releases (the member cleared before the delete); the pointee's
#   destructor, inlined, destroys an ecourna::api::io::CFile at +20 (its inline destructor calls fn 336, CFile::Close,
#   when the FILE* is set, then frees the name at +24) and then frees a std::vector at +8 whose elements need no
#   destruction (no loop between the end and the free). Nothing else of the pointee is destroyed.
# - The file: the constructor's record names cwasmclp.cpp, and link order puts the destructor in that file's object
#   (docs/reference/facts/placing.md P4): in use band 1 the statics' exit destructors (12016, 12015) lie between
#   vota::CExibeAlertaDesligamento's 12017 to 12019 and api::CSubReport's 12014 to 12010, in band 3 the accessor
#   (3876) and 3875 between vota::CAplicacaoEncerrada::GetInst (3877) and CSubReport::GetTitulo (3874), and in band 2
#   the destructor (5978) lies right below CExibeAlertaDesligamento::GetInst (5979), where band 1 has this object.
# - GetInst (fn 3876): unit 104's shape, a std::lock_guard on the static std::mutex (@1834020; fn 3876's last call
#   unlocks it, f150), `s_inst.reset(new CLp())` when the pointer is empty, `*s_inst` returned. The constructor is a
#   function of its own that binaryen inlined into its one caller: a second stack prologue (16 bytes) follows the
#   allocation, and in it a third and a fourth, CPolySingleton<IImpressoraRelatorios>::instance (records
#   cpolysingleton.h:78 and cpolysingletonlist.h:99 and :105, all of fn 3876, @1543124 to @1543156) and
#   CPolySingletonList::instance<IImpressoraRelatorios>, which reads as two linkonce functions with that one caller each,
#   inlined by binaryen too (how-to step 3, "Code binaryen inlined from another function"). The constructor
#   clears +8 first, calls has<IImpressoraRelatorios> (fn 3392), and only when it is true g_polySingletonsInfo() and
#   instance() with its own record; it stores the result, or 0, at +4 and then at +0. Measured on the object
#   (try-tu.sh --symbols, the constructor's code before binaryen): two assignments in the body, the instance's member
#   first, give the +8 store first (m_saida's default initializer) and the +4 and +0 stores after the calls in source
#   order; with the instance's member declared at +0 and assigned first, the stores come +0 then +4, the other order.
#   So the member assigned first sits at +4: that order is evidence, the members' types (IImpressora* at +0,
#   IImpressoraRelatorios* at +4) are chosen, the slot 9 call of fn 3875 reaching IImpressora's slot 9 through either.
#   pnpm wasm score against the link: 84 over 845 rows, operand-only (calls, data addresses, table slots and the packed
#   format strings of the two inlined throws; none a frame offset, field or vtable slot).
# - Fn 3875: reads +4, so a member (how-to step 3's member rule). Its three target callers (2882, 3671, 11908) pass a
#   CSubReport they build and a std::function<void()> of their own lambda; it calls slot 9 of +4's object when +4 is
#   set, slots 5 and 6 of the sub-report (TemParte, ImprimeParte in api/gui/isubreport.h) and the function. 1 over 37
#   rows, operand-only. In use band 3 it follows GetInst (3876, 3875), so it is defined after it.
# - has<IImpressoraRelatorios> (fn 3392): the header's template (api/pattern/cpolysingletonlist.h), a thunk into
#   binaryen's merge of the has<T> instances (fn 3928), the typeinfo name of api::IImpressoraRelatorios its constant
#   (1583848). Its target callers are fn 3876 (twice) and fn 8302, the simulator's set-up; our link's copy comes from
#   mock/app/simulador/wasm/simulador.cpp's object, which instantiates it first (CPolySingleton<...>::set), at this
#   file's flags. 2 over 5 rows, operand-only.
# - The statics: s_inst (@1834044) is read by fns 3876 and 12016 only, s_mutex (@1834020) by fns 3876 and 12015 only
#   (/usr/bin/grep -rlE 'i32\.const <address>($|[^0-9])' build/out/splat/pieces/asm), so each name step 8 votes from
#   3876 (vote:4 and vote:1) is tied to the object by its exit-time destructor's match too. Defined below GetInst, the
#   pointer first, as unit 104's are: the target has the mutex lower in .bss and the pointer's destructor first in link
#   order (12016 before 12015).
#
# Chosen, no evidence names them: the pointee's name, SSaidaLp, and its being a struct; its two first words and their
# types, the vector's element type (uebyte), every data member's name; the types of CLp's +0 and +4 (above); the header's
# path, api/hwil/clp.h, beside the printer interfaces (no record names a header; the record's file is the simulator's
# implementation); `= default` for the destructor's body (`{}` gives the same D2: wasm-objdump -d of the two objects,
# call indices masked) and its line, below the constructor; GetInst's name (unit 104's convention), Imprime's name and
# its parameters' names and types (a reference to api::ISubReport, whose slots it calls, and a reference to the
# std::function); the constructor's spelling on line 10: the 67 characters before `CPolySingleton<` at column 68 are
# `    m_impRel = CPolySingletonList::has<IImpressoraRelatorios>() ? &`, a spelling of that length
# (docs/reference/facts/reading.md R19), with the member's name chosen to give it; the includes on lines 1 to 4.
#
# Paths relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on each source and every uenux2
# header.
CWASMCLP_SRCS := mock/app/simulador/wasm/cwasmclp.cpp
UENUX2_SRCS += $(CWASMCLP_SRCS)
# GetInst and Imprime have two of their three target callers in the link (fns 2882 and 3671, units 246 and 31):
# 219-uenux2-cwasmclp-roots.cpp stands for the third, fn 11908, not written
$(ROOT)/$(APP)/219-uenux2-cwasmclp-roots.o: $(ROOT)/src/units/219-uenux2-cwasmclp-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/219-uenux2-cwasmclp.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/219-uenux2-cwasmclp-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/219-uenux2-cwasmclp-roots.o
