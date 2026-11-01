# uenux2 simulador::CWasmCanaisLog (src/uenux2/mock/app/simulador/wasm/cwasmcanaislog.h, cwasmcanaislog.cpp), the wasm
# simulator's log lines per channel, which CWasmInit's Loga (fn 1524, unit 127) and CWasmLogd::escreve (fn 8327, unit
# 62) write to through the inline GetInst. cwasmcanaislog.h says what the target shows of the class; no record,
# symbol, string or RTTI names it, its files or a member, so every name and both paths are chosen.
# - matched, from the objects of the inline GetInst's users: the static's destructor (fn 5154, table slots 534 and
#   741: one internal copy per object, cwasminit.cpp's and cwasmlogd.cpp's, which binaryen merges, so our link holds
#   it in two slots too), and libc++'s std::deque<std::string> D2 (fn 3503), which it calls. The static's name has the
#   votes of 5154 and 8327.
# - matched since mock/app/simulador/wasm/ builds with strict aliasing: Escreve (fn 5152), with Agora and Adiciona,
#   which binaryen inlines into it as into the target's (each has one caller). At -O2 clang inlines std::string::append
#   into `Agora() + " " + texto`, where the target calls it (fn 160) twice, and the body differs (833 over 1995 rows).
#   At -O3 with -fno-strict-aliasing it was 78 over 1787 rows, all operand-only: its calls of
#   std::__split_buffer<std::string*>'s emplace_back and emplace_front went to this object's copies, matched as fns 915
#   and 1199, where the target's go to 3501 and 5150, roots_rhvoice.o's language_search_criteria instances. With strict
#   aliasing this object's two are byte-identical to those, and the lines of 915 and 1199 went to their other twins
#   (src/Makefile UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6). A generated vptr-anchor line names 5152. Its callers are 8327, named
#   by vtable alone, and 1524, which the content pass finds, and 1524's caller is 9405: with 5152's name out on both
#   sides of splat/symbol_addrs.txt's marker (docs/reference/splat.md "Reviewing a match"), 1524 and 9405 leave match.
#   Its body also casts the vote that names std::time_put<char>'s id (0x1d5e18), which only 5152 and libc++'s
#   locale::__imp::install<time_put<char>> (fn 7833) load in the target, and 7833 matches by that name.
# Forms: the target's body holds two more stack frames, the sign of functions binaryen inlined
#   (docs/reference/facts/reading.md R10), and Agora and Adiciona, out of line, give ours the same frames; that they are
#   members with external linkage is chosen. Agora's std::tm is value-initialized: the target zeroes it before
#   localtime_r. In Adiciona the vector of observers is declared before the last line: the string declared first gives
#   another object at -O2 (the disassembly, relocated operands masked), and that order was not linked at -O3.
# Paths relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on each source and every uenux2
# header.
CWASMCANAISLOG_SRCS := mock/app/simulador/wasm/cwasmcanaislog.cpp
UENUX2_SRCS += $(CWASMCANAISLOG_SRCS)
