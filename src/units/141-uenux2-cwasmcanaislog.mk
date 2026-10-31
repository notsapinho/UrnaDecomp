# uenux2 simulador::CWasmCanaisLog (src/uenux2/mock/app/simulador/wasm/cwasmcanaislog.h, cwasmcanaislog.cpp), the wasm
# simulator's log lines per channel, which CWasmInit's Loga (fn 1524, unit 127) and CWasmLogd::escreve (fn 8327, unit
# 62) write to through the inline GetInst. cwasmcanaislog.h says what the target shows of the class; no record,
# symbol, string or RTTI names it, its files or a member, so every name and both paths are chosen.
# - matched, from the objects of the inline GetInst's users: the static's destructor (fn 5154, table slots 534 and
#   741: one internal copy per object, cwasminit.cpp's and cwasmlogd.cpp's, which binaryen merges, so our link holds
#   it in two slots too), and libc++'s std::deque<std::string> D2 (fn 3503), which it calls. The static's name has the
#   votes of 5154 and 8327.
# - written and `unresolved`: Escreve (fn 5152), with Agora and Adiciona, which binaryen inlines into it as into the
#   target's (each has one caller). It needs uenux2 at -O3, the user's decision: at the tree's -O2 clang inlines
#   std::string::append into `Agora() + " " + texto`, where the target calls it (fn 160) twice, and the body differs
#   (833 over 1995 rows); with cwasmcanaislog.cpp alone at -O3 in a copy of the link (docs/reference/facts/workflow.md
#   W13), 78 over 1787 rows, all operand-only. Its callers are 8327, named by vtable alone, and 1524, which the content
#   pass finds; neither casts a vote, so a `callers+content` hand edit under splat/symbol_addrs.txt's marker names 5152
#   for them. Weighed by removal (docs/reference/splat.md "Reviewing a match"), the line carries 1524's match, and the
#   line gives what it rests on.
# Forms: the target's body holds two more stack frames, the sign of functions binaryen inlined
#   (docs/reference/facts/reading.md R10), and Agora and Adiciona, out of line, give ours the same frames; that they are
#   members with external linkage is chosen. Agora's std::tm is value-initialized: the target zeroes it before
#   localtime_r. In Adiciona the vector of observers is declared before the last line: the string declared first gives
#   another object at -O2 (the disassembly, relocated operands masked), and that order was not linked at -O3.
# Paths relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on each source and every uenux2
# header.
CWASMCANAISLOG_SRCS := mock/app/simulador/wasm/cwasmcanaislog.cpp
UENUX2_SRCS += $(CWASMCANAISLOG_SRCS)
