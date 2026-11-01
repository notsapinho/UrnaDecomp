# uenux2 comum::CGeradorResultados's constructor (target fn 5824) in src/uenux2/src/app/comum/gravadores/
# cgeradorresultados.cpp, with the class header beside it.
#
# Evidence. fn 5824 is called only by vota::CGravaResultado::StartState (fn 12098), twice (ledger/callgraph.tsv), and
# builds an 84-byte object (cgeradorresultados.h has what it stores where). Its last argument is a std::shared_ptr that
# it copies to +76 and then releases: this toolchain passes std::shared_ptr by value as a pointer the callee destroys,
# and a by-value parameter copied into a member gives that release (`m_p(p)`), where one moved into it gives none
# (measured on a probe TU at uenux2's flags, wasm-objdump -d). The two vectors are of two element types: the target's
# body holds two calls of fn 158 (vector<unsigned char>::__throw_length_error, binaryen's one body for every vector's
# member), one per copy; with one element type for both, our body ran both copies' throws through one call (4 rows
# deleted, pnpm wasm score against 5824), and with two it scores 8 over 266 rows, all operand-only. The byte at +72 is a
# bool: fn 12098 passes a condition xor-ed with 1 and tests the byte against 1.
#
# Choices. No record, vtable slot or RTTI names the class, its file, its members or the types of its elements and of
# +76: the class name is chosen from the log fn 12098 writes around the first vector (CLogComum::
# LogaGerandoResultados), the flag's from the text it gates ("Copiando resultados para a MV"); the first vector holds
# IGravador (fn 12098 calls slot 4, which IGravador adds, on its elements), the second IResultado (fn 12098 uses only
# IResultado's slot 2 and its +32 and +36), and +76 IGravador (slots 2 and 4); the namespace, the directory (beside the
# recorders it holds) and the file name are chosen, as is the constructor's place in its own TU. The vectors and the
# CAssinador are taken by const reference, a choice: the body only copies from them.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CGERADORRESULTADOS_SRCS := src/app/comum/gravadores/cgeradorresultados.cpp
UENUX2_SRCS += $(CGERADORRESULTADOS_SRCS)
# the constructor's one caller, vota::CGravaResultado::StartState (fn 12098), is not reconstructed:
# 195-uenux2-cgeradorresultados-roots.cpp stands for it
$(ROOT)/$(APP)/195-uenux2-cgeradorresultados-roots.o: $(ROOT)/src/units/195-uenux2-cgeradorresultados-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/195-uenux2-cgeradorresultados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/195-uenux2-cgeradorresultados-roots.o
