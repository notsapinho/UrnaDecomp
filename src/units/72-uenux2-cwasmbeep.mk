# uenux2 simulador::CWasmBeep, the wasm build's api::IBeep, in src/uenux2/mock/app/simulador/wasm/cwasmbeep.cpp
# (+ cwasmbeep.h), with the api::IBeep interface (src/uenux2/src/api/hwil/ibeep.h) and the tone sequences its members
# play (src/uenux2/src/api/hwil/ibeep.cpp):
# - every member of the vtable (@1530304): SetVolume (target fn 8541, slot 0), Beep (8538, slot 1), BeepConfirm
#   (8533, slot 2), BeepError (8523, slot 3), BeepAlert (8514, slot 4), BeepDiscard (8505, slot 5) and BeepKey
#   (8494, slot 6). SetVolume, the first, is the key function, so cwasmbeep.cpp emits the vtable. The destructors
#   (slots 7 and 8) are the shared empty bodies 174 and 144: an implicit destructor or one defined in the class, left
#   implicit here. The constructor (inlined into simulador's init, fn 8302) has no target function, and nothing here
#   calls it.
# - the tone sequences of slots 2 to 5. The evidence is that each is built in another TU and returned by value: each
#   target function keeps its std::vector in the frame and loads its begin and end right after the code that stored
#   them, with no call between, which a function boundary alone gives, and fn 8523 zeroes the vector after a second
#   stack prologue, so the callee builds it. Defined in the caller's TU, such a function is inlined by clang and the
#   vector is gone (no operator new); forced out of line there, its loads are hoisted. Each has one caller, into which
#   binaryen inlines it as in the target (none has a target function of its own; none is rooted). That they are free
#   functions of namespace api (they read no state), and that the file is ibeep.cpp, is our choice: no evidence names
#   the class or the file. BeepError's sequence calls vector::push_back, which our link merges into the matched
#   std::vector<std::pair<unsigned long, unsigned long>>::push_back (fn 760).
# - the element is std::pair<int, int>: it gives the target's immediate stores, highest offset first, while one plain
#   aggregate, `struct { int; int; }`, the only other element tried, puts the tones in .rodata and copies them with
#   memory.copy.
# - BeepConfirm's guard: 8533 tests the count and emptiness before its outer loop, with the range-for's own test still
#   inside it, so the source holds a redundant emptiness test. The operand order of the `||` is not evidence.
# Other forms that give the same bytes: each sequence as a static member of api::IBeep; the guard as
# `if (tones.empty() || times <= 0) return;` or as `if (times > 0 && !tones.empty())` around the loops; ErrorTones'
# twelve vibrato tones as twelve push_back calls instead of the loop (identical object).
# No record names any of it. cwasmbeep.cpp is the probable_file ledger/tu-clusters.tsv gives clusters 69, 72, 75, 78, 79
# and 81, which hold the seven members (class-convention labels); the unplaced.cpp stubs said the same except 8523's,
# which sat under cluster 77's comment (carchiveopencallback_offset.cpp). The directory is where simulador's other wasm
# classes have records (cwasmthread.cpp, cwasmclp.cpp). The member names, the sequences' names and form, and the paths
# of ibeep.h and ibeep.cpp are chosen (ibeep.h says from what); the class and the base are RTTI's. Paths relative to
# src/uenux2; the generic uenux2 rule compiles both and depends on each source and every uenux2 header.
CWASMBEEP_SRCS := mock/app/simulador/wasm/cwasmbeep.cpp src/api/hwil/ibeep.cpp
UENUX2_SRCS += $(CWASMBEEP_SRCS)
# nothing reconstructed creates the beeper yet: 72-uenux2-cwasmbeep-roots.cpp keeps its vtable the way the target
# reaches it
$(ROOT)/$(APP)/72-uenux2-cwasmbeep-roots.o: $(ROOT)/src/units/72-uenux2-cwasmbeep-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/72-uenux2-cwasmbeep.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/72-uenux2-cwasmbeep-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/72-uenux2-cwasmbeep-roots.o
