# uenux2 simulador::CWasmWebSound, the wasm build's api::ISound, in src/uenux2/mock/app/simulador/wasm/cwasmwebsound.cpp
# (+ cwasmwebsound.h), with the api::ISound interface (src/uenux2/src/api/audio/isound.h):
# - slots 0 to 8 of its vtable @1528468 (target fns 9589, 9580, 9573, 9565, 9559, 9550, 9541, 9533, 9523), under
#   ISound's names: Pause, Play(const std::string &), Play(const std::string &, EModo), Play(std::shared_ptr<CWavFile>),
#   Play(std::shared_ptr<CWavFile>, EModo), Stop, Mute, GetStatus and Wait(std::function<bool ()>). Play of a WAV
#   (slot 4) hands the CWavFile's header, samples and size to js_wasm_web_sound_play_wav with the volume as
#   m_volume * 5 + 50 and `modo != INTERROMPE`; slot 3 is slot 4 called with INTERROMPE on a copy of its shared_ptr
#   (one count increment, two releases: the copy and the parameter, which the callee owns), and slot 8 holds GetStatus,
#   both inlined because the class is final. Slot 4 reads the samples and their size into locals before it stores
#   the status: written as one condition on wav->GetDados() and wav->GetTamanhoDados(), with the uenux2 tree's
#   -fno-strict-aliasing the store to m_status would make clang load both again for the call (7 of 105 rows alone).
#   Assigning the two locals inside an `if (wav)` gives the same body alone (try-tu --single, 0 of 103 rows).
# - the implicit destructors (slots 10 and 11) are binaryen's shared 174 and 144, matched already.
# The class, its base and the members Wait() and WaitAsync are RTTI's (isound.h says which typeinfo names them); every
# other name is chosen: the members' (Pause, Play, Stop, Mute, GetStatus, Wait(std::function<bool ()>)), the
# enumerations ISound::EModo and EStatus and the data members' (cwasmwebsound.h, isound.h). So is ISound's path:
# no record names it, and the one recorded audio directory, api/audio/alsa/, holds the ALSA implementation's
# CWavFile. The three CWavFile accessors slot 4 calls are chosen too, inline in unit 38's cwavfile.h. No record names
# cwasmwebsound.cpp either: it is the file ledger/tu-clusters.tsv gives clusters 227, 229, 230 and 232 (the
# `neighbours' file` of their unplaced.cpp stubs), in the directory where simulador's other wasm classes have records
# (cwasmthread.cpp, cwasmclp.cpp). The constructor has no target function (binaryen inlined it into fn 10384) and
# stays implicit, with ISound's m_volume = 9 and this class's zeroed members as default member initializers.
# WaitAsync (target fn 9515, slot 9) is pending: 74-uenux2-cwasmwebsound-pending.cpp says what it waits for. Paths
# relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on the source and every uenux2 header.
CWASMWEBSOUND_SRCS := mock/app/simulador/wasm/cwasmwebsound.cpp
UENUX2_SRCS += $(CWASMWEBSOUND_SRCS)
# WaitAsync (target fn 9515) is not reconstructed: 74-uenux2-cwasmwebsound-pending.cpp gives the vtable a trapping
# body, compiled with the unit's flags
$(ROOT)/$(APP)/74-uenux2-cwasmwebsound-pending.o: $(ROOT)/src/units/74-uenux2-cwasmwebsound-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/74-uenux2-cwasmwebsound.mk $(ROOT)/src/uenux2/mock/app/simulador/wasm/cwasmwebsound.h $(ROOT)/src/uenux2/src/api/audio/isound.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/74-uenux2-cwasmwebsound-pending.cpp -o $(R)
# nothing reconstructed builds the sound yet: 74-uenux2-cwasmwebsound-roots.cpp keeps the vtable, as the constructor
# inlined into fn 10384 does
$(ROOT)/$(APP)/74-uenux2-cwasmwebsound-roots.o: $(ROOT)/src/units/74-uenux2-cwasmwebsound-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/74-uenux2-cwasmwebsound.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/74-uenux2-cwasmwebsound-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/74-uenux2-cwasmwebsound-pending.o $(APP)/74-uenux2-cwasmwebsound-roots.o
