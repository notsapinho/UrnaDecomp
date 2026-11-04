# uenux2 comum::CSubstituidorTitulo (app/comum/relatorios/csubstituidortitulo.{h,cpp}), the singleton that holds a
# report title's substitutions, and the stand-ins for unit 123's CRelUtil::ImprimeTitulos, its overload and
# ImprimeAberturaFechamento (crelutil.cpp; unit 123's fragment describes them). Paths relative to src/uenux2.
#
# Matched:
# - the destructor (target fn 5576), out of line in csubstituidortitulo.cpp: `f720(p0, load[p0+4])`, the map at +0
#   destroyed. Its two callers are the class's: the reset in CreateInst, which fn 3689 holds inlined, and fn 11175. A
#   call that stays a call in the destructor's own TU at uenux2's -fPIC is the D1 alias's
#   (docs/reference/facts/codegen.md C6), so the destructor is defined in the .cpp (a reading).
# - the statics' exit destructors: the pointer's (11175, which nulls it and destroys and frees the old value) and the
#   mutex's (11174). The two .bss words are read by 3689 and by one exit destructor each (the grep of `i32.const
#   1839140` and `i32.const 1839116` in build/out/splat/pieces/asm lists 3689 and 11175, and 3689 and 11174).
# `pnpm wasm score` against the plain link before steps 7 to 9: 5576 1 over 6 rows, 11175 3 over 15, 11174 2 over 4, all
# operand-only.
#
# What the target shows, and the forms written:
# - GetInst is SINGLETON_IMPL_GET_INST (src/ecourna/api/pattern/singleton.hpp): its record, csubstituidortitulo.cpp:21
#   column 66, is the invocation's closing parenthesis, 47 plus the class name's 19 characters, the formula
#   src/units/110-uenux2-singletons.mk gives for the +47 classes, whose .bss holds the mutex 24 bytes below the pointer
#   (1839116 and 1839140 here). As there, the statics are defined after GetInst, and the pointer's exit destructor comes
#   first in link order (11175 above 11174; in our link `__cxx_global_array_dtor`, the pointer's, has ld_index 4305 and
#   the mutex's 4306).
# - CreateInst's throw is on its record's line, 26 column 15: CUeComumRelatoriosError 9088 "Instância já criada" when
#   the pointer is set, then the pointer is reset to a new object built from the map. No mutex call is in its code.
# - The class is 12 bytes, a std::map<std::string, std::string> (CreateInst allocates 12 and copies the map into them).
# - fn 3689 holds, beside CreateInst and GetInst, three functions inlined: a lock-guarded test of the pointer (frameless:
#   the pointer read, then the mutex unlocked through fn 150), the constructor that copies the map (a frame of its
#   own), and the substitution of one line (a frame of its own: the line copied, then for each pair of the map
#   CStringUtils::Replace's copying form, fn 2677, assigned back). They are written out of line here, each with one
#   call site, which binaryen inlines. The constructor and the substitution have frames of their own, binaryen's
#   sign; the pointer test is frameless, so nothing tells binaryen's inlining from clang's there, and its being out
#   of line (not an inline member, as CThreadEleitor::Existe is) is a choice.
# Chosen: the header's path; the names Existe, Substitui and the members' names; their access; the constructor's
# explicit; s_instancia.reset(new ...) for the assignment (a std::unique_ptr assigned was not tried); the lines of
# everything but the two records. Substitui passes the line to Replace through std::as_const: with a non-const string
# our ecourna header's overloads pick `void Replace(std::string&, ...)` (src/ecourna/api/util/cstringutils.hpp), and
# the target calls the copying form.
#
# The roots (230-uenux2-csubstituidortitulo-roots.cpp) stand for target callers of unit 123's new members: 5579 for
# 3689 (1543 is in the link), 12110 for 5584 (5591 is in the link), 12105 and 12110 for 3688. Each calls twice, and each goes when
# every caller it stands for is in the link.
CSUBSTITUIDORTITULO_SRCS := src/app/comum/relatorios/csubstituidortitulo.cpp
UENUX2_SRCS += $(CSUBSTITUIDORTITULO_SRCS)
# the roots declare what they call through asm labels, so their rule needs no header
$(ROOT)/$(APP)/230-uenux2-csubstituidortitulo-roots.o: $(ROOT)/src/units/230-uenux2-csubstituidortitulo-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/230-uenux2-csubstituidortitulo.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/230-uenux2-csubstituidortitulo-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/230-uenux2-csubstituidortitulo-roots.o
