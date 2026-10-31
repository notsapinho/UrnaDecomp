# uenux2 comum::CFederacoes (src/app/comum/dados/cfederacoes.cpp): GetInst (target fn 2832) with the constructor it holds
# inlined, the destructor (5800), the exit destructors of the singleton's pointer and mutex (11553, 11552) and
# GetFederacao (5799). Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
#
# Evidence: the records of Load (cfederacoes.cpp:141 and :149, held inlined by fn 7787) name the class and the file. The
# rest is read from the bodies: 2832 is CPartidos::GetInst's shape (fn 819, unit 109) with the constructor inlined, a
# 28-byte object whose +0..+15 it zeroes and whose +16 it copies from a heap temporary of the literal "CFederacoes",
# freed after the copy; 5800 frees the string at +16 and calls fn 1272, std::vector<ecourna::app::dados::CFederacao>'s
# __destroy_vector, on +0; 11553 nulls the pointer at 1838748 and calls 5800, and 11552 destroys the mutex at 1838724,
# 24 bytes below the pointer, the order of CPartidos's statics (unit 110's fragment says which definition order gives
# it). 5799 compares its argument with each party number unmasked, so the parameter is a 16-bit integer type: with
# ecourna::app::dados::TPartidoID (a class of one unsigned short) the body masks it with 65535. It walks the vector by
# its 40-byte stride, copies each federation's vector of party numbers at +28, looks for its argument there, and returns
# the federation's address or null.
# Link order (ledger/ordinals.tsv): in band 2, 5800, 5799 and fn 5798 (the vector's __vdeallocate, a linkonce copy) follow
# ccargods.cpp's 5801 to 5803; in band 1, 11553 and 11552 follow ccargods.cpp's 11555 and precede
# cconfiguracaoeleicao.cpp's 11551; the records of Load lie between ccargods.cpp's and cconfiguracaoeleicao.cpp's.
#
# Forms measured (pnpm wasm score in the whole link): GetFederacao opens with the empty test and returns null there, and
# after std::find_if compares the result with a reloaded end(): the target's two returns. find_if alone, which folds the
# empty case into the final select, scored 17 over 99 rows (5 inserted, 5 deleted); with the test, 4 over 94, all
# operand-only. The vector of parties is a local copy: the target allocates, copies and frees it per federation.
# This object's linkonce copy of fn 1272 now comes ahead of the ecourna object's (uenux2 links first) and gives the same
# rows (4 over 91, operand-only).
#
# Names: the singleton's mutex has a hand edit in splat/symbol_addrs.txt (evidence:callers+content, as CPartidos's and
# CFotos's): its two readers, 2832 (the address it unlocks) and 11552, have no other name to come from. Removed with the
# match lines of 2832, 11552 and 11553, a scan run twice leaves those three out (and moves 10491, not a match, from
# differs to unresolved), and a control that removes nothing moves no row; splat-build accepts both copies. The pointer's name is generated (vote:2 by:11553); 11553's row is `unresolved
# self-voted` on it until 2832, which loads the same address, matches.
#
# Chosen, no evidence names them: GetInst and GetFederacao, the statics' and data members' names, the word at +12's type
# (size_t, which nothing written here reads), GetFederacao's parameter type beyond its 16 bits (ueword) and its result's
# constness, the private constructor from the name (a base class holding the three members is not tried), the lambda,
# and every line.
CFEDERACOES_SRCS := src/app/comum/dados/cfederacoes.cpp
UENUX2_SRCS += $(CFEDERACOES_SRCS)
# the class's users are not reconstructed yet: 162-uenux2-cfederacoes-roots.cpp gives each function its call sites
$(ROOT)/$(APP)/162-uenux2-cfederacoes-roots.o: $(ROOT)/src/units/162-uenux2-cfederacoes-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/162-uenux2-cfederacoes.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/162-uenux2-cfederacoes-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/162-uenux2-cfederacoes-roots.o
