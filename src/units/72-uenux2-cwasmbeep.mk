# uenux2 simulador::CWasmBeep, the wasm build's api::IBeep, in src/uenux2/mock/app/simulador/wasm/cwasmbeep.cpp
# (+ cwasmbeep.h), with the api::IBeep interface (src/uenux2/src/api/hwil/ibeep.h) and the tone sequences its members
# play (src/uenux2/src/api/hwil/ibeep.cpp):
# - every member of the vtable (@1530304): SetVolume (target fn 8541, slot 0), Beep (8538, slot 1), BeepConfirm
#   (8533, slot 2), BeepError (8523, slot 3), BeepAlert (8514, slot 4), BeepDiscard (8505, slot 5) and BeepKey
#   (8494, slot 6). SetVolume, the first, is the key function, so cwasmbeep.cpp emits the vtable. The destructors
#   (slots 7 and 8) are the shared empty bodies 174 and 144, so CWasmBeep's destructor is implicit; its constructor
#   (inlined into simulador's init, fn 8302) has no target function, and nothing here calls it.
# - the tone sequences of slots 2 to 5: each target function keeps its std::vector in the frame and loads its begin
#   and end again right after the vector is filled and on every pass, which clang does only when the vector was
#   filled by a call it cannot see into. Defined in the same TU, such a function is inlined by clang and the vector
#   is gone (no operator new). So each sequence is a static member of api::IBeep in ibeep.cpp with one caller in
#   cwasmbeep.cpp, into which binaryen inlines it as it did in the target (none has a target function of its own;
#   none is rooted). BeepError's sequence calls vector::push_back, which our link merges into the matched
#   std::vector<std::pair<unsigned long, unsigned long>>::push_back (fn 760).
# Other forms that give the same bytes: BeepConfirm's guard written `if (times > 0 && !tones.empty())` around the
# loops; ErrorTones' twelve vibrato tones as twelve push_back calls instead of the loop (identical object).
# No record names any of it. The file is the one ledger/tu-clusters.tsv gives clusters 69, 72, 75, 78, 79 and 81 (the
# `neighbours' file` of their unplaced.cpp stubs), in the directory where simulador's other wasm classes have records
# (cwasmthread.cpp, cwasmclp.cpp). The member names, the sequences' names, their being IBeep's static members, and the
# paths of ibeep.h and ibeep.cpp are chosen (ibeep.h says from what); the class and the base are RTTI's. Paths
# relative to src/uenux2; the generic uenux2 rule compiles both and depends on each source and every uenux2 header.
CWASMBEEP_SRCS := mock/app/simulador/wasm/cwasmbeep.cpp src/api/hwil/ibeep.cpp
UENUX2_SRCS += $(CWASMBEEP_SRCS)
# nothing reconstructed creates the beeper yet: 72-uenux2-cwasmbeep-roots.cpp keeps its vtable the way the target
# reaches it
$(ROOT)/$(APP)/72-uenux2-cwasmbeep-roots.o: $(ROOT)/src/units/72-uenux2-cwasmbeep-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/72-uenux2-cwasmbeep.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/72-uenux2-cwasmbeep-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/72-uenux2-cwasmbeep-roots.o
