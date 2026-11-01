# uenux2 api::CApplicationContextGuard, api::CApplicationContextStack and api::CApplicationContext (api/gui/): the
# guard's constructor (record capplicationcontextstack.cpp 45:15, held inlined by target fn 676) and destructor (fn
# 675); the stack's Push (held inlined by fns 3684 and 676) and Pop (fn 5553, written and not matched, below; held
# inlined by fn 675); the context's constructor from its five members (fn 5557) and its operator== (fn 5556); the free
# functions CriaContextoAplicacao (fn 3682), CriaContextoPadrao (fn 5558) and Actions (fn 5555); and the members the
# compiler writes from the class definition, which match from api/gui/capplication.cpp's object (unit 171), the first
# on the link line that emits them, or from this unit's: the destructor (fn 1468), the copy constructor (fn 1841), the
# move assignment (fn 5552) and std::vector<CApplicationContext>'s __emplace_back_slow_path (fn 5554). Unit 171 holds
# the functions of api::CApplication that use them: PushContext (fn 3684), CriaContexto (fn 676) and InitApplication.
#
# Evidence and choices.
# - Names and paths. The record names the guard's constructor, printing the stack and the context unqualified: their
#   namespace (api, the guard's), the two headers' paths (api/gui/capplicationcontext.h, capplicationcontextstack.h),
#   capplicationcontext.cpp's path, and every other function's, member's and parameter's name are chosen. Actions is
#   chosen from the line it returns for an unknown kind, "Actions({}) - não reconhecida" (std::format of an int; the
#   target's literal, ledger/strings.tsv 231338).
# - Free functions. CriaContextoAplicacao, CriaContextoPadrao and Actions read no state of the context, and no record,
#   vtable slot or RTTI names any of them, so they are free functions in api (how-to step 3, "Names no evidence
#   gives"); which namespace is chosen. Written as static members of CApplicationContext (Cria, CriaPadrao, Actions),
#   they give the same code: the objects' functions compared with relocations as symbols differ in the symbols and the
#   objects' own type numbers alone, and that form matched all three too.
# - Layout, from the target's stores: the context is 52 bytes, three strings at +0, +12 and +24, a vector of strings at
#   +36 and a 32-bit word at +48 (fn 5557 moves its five arguments there in that order; fns 1841 and 5556 read them so);
#   the word's int type is chosen for that width (Push tests it for non-zero, operator== compares it). The guard is the
#   stack's address at +0 (fn 676 stores 1839212, CApplication::s_contextos) and the context at +4. The stack holds
#   the vector at +0, the guard's address of it being the vector's; that it holds nothing else is chosen.
# - The throw: line 45, column 15, CUeGuiError code 5013 (EUE_GUI_APPLICATIONCONTEXTGUARD_CONTEXTO_NAO_CRIADO in
#   api/gui/eueguierror.h, its name chosen from the message) with "O contexto não pôde ser criado", the target's literal
#   (ledger/strings.tsv 140145).
# - Order. In the target's use band of two uses (ledger/ordinals.tsv), where the index runs in reverse link order, 5558
#   down to 5552 are CriaContextoPadrao, the constructor, operator==, Actions, the slow path, Pop and the move
#   assignment, so that is their link order, and inside one object it is their order (how-to step 3, "The order of two
#   members"). Our two objects keep it (ld_index in build/out/wasm-map/vota_web/names.tsv): capplicationcontext.cpp.o
#   the constructor, operator== and Actions, in their definitions' order; capplicationcontextstack.cpp.o
#   CriaContextoPadrao, the slow path, Pop and the move assignment. That fixes part of this file's order: compiled with
#   the factories after the guard's destructor, the object puts CriaContextoPadrao after the slow path, Pop and the move
#   assignment; with Pop defined before Push it orders its functions as written (the objects' function lists). Across
#   our objects the order is not the target's: our link has the constructor's object first, so CriaContextoPadrao
#   follows Actions, where the band has it ahead of the constructor. Which files hold the factories, the constructor and
#   Actions, and their order on the link line, are chosen, the factories apart from Actions (below). Every other line
#   and the include order are chosen.
# - operator== is defaulted out of line in capplicationcontext.cpp, beside the constructor, as the band has it.
#   Defaulted in the class, an inline member emitted in this file's object where Pop's find calls it, gives the same
#   code for it and for its callers (the objects' functions compared, relocations as symbols) and matched too; there the
#   object puts it after the slow path (ld_index 3318 against 3315), against the band's order.
# - The factories return the context by value. Measured as constructors that delegate to the five-member one, in this
#   TU: clang inlines that constructor into both (remark cost 5); with it in another TU, the two-string constructor
#   returns its result and our fn 5557 keeps one the target's has not (`->(i32)` against `->()`). As factories, fn 5557
#   is byte-exact and fns 3682 and 5558 differ in operand rows only. They are in this file, apart from Actions: in a
#   probe of capplicationcontext.cpp holding them too (as the static members above), clang inlines Actions(1) into
#   CriaPadrao (remark cost=150, threshold=375), where the target's fn 5558 calls fn 5555, and keeps the call of the
#   five-member constructor's C1 (docs/reference/facts/codegen.md C6).
# - Push is out of line here, and clang inlines it into the guard's constructor. The target's fn 3684 (PushContext,
#   unit 171) reloads the context from its frame right after storing it, which is binaryen's inlining of a callee that
#   clang did not see (docs/reference/facts/reading.md R10): measured with Push inline in the header, clang forwards the
#   stored values and fn 3684 scores 110 over 308 rows (30 inserted, 33 deleted); out of line here, 12 over 278, all
#   operand rows.
# - The guard. Fn 676 holds three frames (two second prologues, binaryen's inlining): CApplication::CriaContexto from a
#   kind and three strings, which builds the context with CriaContextoAplicacao and calls the private CriaContexto from
#   a context, which builds the guard through its C1 (a call clang keeps at -fPIC, codegen.md C6), the record's
#   constructor, with Push inlined (unit 171 writes both CriaContexto). Measured as two delegating constructors of the
#   guard in this TU, fn 676 scores 82 over 664 rows (6 inserted, 13 deleted): the destruction of the middle step's
#   temporary loses the vector's `end = begin` store and the reload of `begin` that the target keeps; as the two
#   factories, all operand rows. Reading: clang then sees the record's constructor, and so knows that it keeps no
#   pointer to the temporary. That the factories are CApplication's is a choice.
# - The destructor pops the context when no exception is in flight (fn 675 calls __cxa_uncaught_exceptions first):
#   std::uncaught_exceptions() is the form written; std::uncaught_exception() was not measured.
# - Pop (fn 5553) is written and does not match. The target's body reads the stack at its address as a constant, and
#   its two callers (7370 and 10467, not reconstructed) pass only the context; ours is Pop with `this` folded by
#   binaryen, since the roots pass s_contextos. It scores 31 over 105 rows (4 inserted, 4 deleted): the rows that
#   differ are local.get, local.set and local.tee of other locals, the erase loop's values pairing into other locals
#   than the target's. The same 31 for: Pop inline in the header under a static wrapper in capplication.cpp, the
#   erase's first iterator written `(it + 1).base()` or `it.base() - 1`, the test written as an early return, and Pop
#   defined after the guard's destructor; a hand loop over the reverse iterators scores 53 over 110. The remainder is
#   not explained, and nothing in the link needs Pop's name.
# - Roots: 193-uenux2-capplicationcontextstack-roots.cpp stands for the callers of Pop, CriaContextoAplicacao,
#   CriaContextoPadrao and the copy constructor that are not reconstructed (its header lists them); the guard's are in
#   unit 171's.
CAPPLICATIONCONTEXTSTACK_SRCS := src/api/gui/capplicationcontext.cpp src/api/gui/capplicationcontextstack.cpp
UENUX2_SRCS += $(CAPPLICATIONCONTEXTSTACK_SRCS)
$(ROOT)/$(APP)/193-uenux2-capplicationcontextstack-roots.o: $(ROOT)/src/units/193-uenux2-capplicationcontextstack-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/193-uenux2-capplicationcontextstack.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/193-uenux2-capplicationcontextstack-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/193-uenux2-capplicationcontextstack-roots.o
