# uenux2 simulador::CWasmWebSound, the wasm build's api::ISound, in src/uenux2/mock/app/simulador/wasm/cwasmwebsound.cpp
# (+ cwasmwebsound.h), with the api::ISound interface (src/uenux2/src/api/audio/isound.h):
# - slots 0 to 8 of its vtable @1528468 (target fns 9589, 9580, 9573, 9565, 9559, 9550, 9541, 9533, 9523), under
#   ISound's names: Pause, Play(const std::string &), Play(const std::string &, EModo), Play(std::shared_ptr<CWavFile>),
#   Play(std::shared_ptr<CWavFile>, EModo), Stop, Mute, GetStatus and Wait(std::function<bool ()>). Play of a WAV
#   (slot 4) hands the CWavFile's header, samples and size to js_wasm_web_sound_play_wav with the volume as
#   m_volume * 5 + 50 and `modo != INTERROMPE`; slot 3 is slot 4 called with INTERROMPE on a copy of its shared_ptr
#   (one count increment, two releases: the copy and the parameter, which the callee owns), and slot 8 holds GetStatus:
#   both calls are devirtualized and inlined. `final` on the class gets that, and it is a choice: a class that is not
#   final with `override final` on those two members, or with both calls qualified CWasmWebSound::, compiles to the
#   same object; a bare virtual call does not. Slot 4 reads the samples and their size into locals before it stores
#   the status: read after the store, -fno-strict-aliasing (this directory's flag then) makes clang load both again for the call
#   (7 of 105 rows alone, with the accessors in the call). How the locals are spelled is a choice too: assigned inside
#   an `if (wav)`, or after one condition on the accessors, they give the same object as the two conditional
#   expressions.
# - the implicit destructors (slots 10 and 11) are binaryen's shared 174 and 144, matched already.
# - the waits the browser holds: the static map s_esperas (.bss 1832664), with its global destructor (fn 9631) and
#   std::map's __tree::destroy (fn 3530), the export uenux_wasm_web_sound_wait_cancel_requested (fn 9614) and
#   CEsperaAudioWasm::Cancelada (fn 9445, slot 3), which match; s_esperas's name is a vote of 9614 and 9631. The control
#   block's D2 and D0 (9490, 9481) match too, from this object.
# - matched at the tree's -O3 and `unresolved` at -O2 (docs/reference/facts/levels.md V2 and V3): the export
#   uenux_wasm_web_sound_wait_finished (fn 9604), CEsperaAudioWasm::Cancela (fn 2680) with the D2, the D0 and
#   __on_zero_shared that call it (9459, 9448, 9472). The target inlines std::map's erase into 9604 and 2680 (the same
#   code in two functions, so clang did), and Cancela is then too large to inline into its three callers; at -O2 erase
#   stays a call and Cancela goes into them. In a scratch link with the simulator's three objects at -O3 (the rest at
#   -O2, the tree's level then), 2680 scored 8 over 157 rows, 9604 9 over 223, 9459 1 over 5, 9448 2 over 6 and 9472 1 over 6,
#   all operand-only. WaitAsync (fn 9515) is written and `unresolved`. With -fno-strict-aliasing its insert reloads __child
#   where the target does not (45 over 464 rows, 5 inserted); with the directory's strict aliasing (src/Makefile UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6)
#   it is 19 over 459, 16 replaced, all operand-only, and 3 deleted. Those 3 are CEsperaAudio's flag store, which ours merges into the object's first i64; and a name of s_proximaEspera (.data
#   1528464, value 1 in the target's data): too little content to place, and only 9515 reads it.
# RTTI gives simulador::(anonymous namespace)::CEsperaAudioWasm, so the class is file-local (vtable @1528660, slots 9459,
# 9448, 2680, 9445). Its `final` is evidence for the class or its destructor: 9472 calls 2680 directly, which needs one of
# the two (docs/reference/facts/reading.md R4); the class form is chosen. The in-class destructor is read from the D0,
# which holds the call of 2680 and the free (R5). The layout is read from 9515, which stores the id at +4 and the flag at
# +8 of the object; m_id's type is what 2680 passes to js_wasm_web_sound_cancel_wait. Chosen: SEspera and every
# member, variable and parameter name of this block, that s_esperas and s_proximaEspera are file-local, and that the
# two exports are plain extern "C" functions here (EMSCRIPTEN_KEEPALIVE adds nothing to the bodies: src/Makefile's
# EXPORTS lists them). Their place above the class's members is read from the target's indices, 9631, 9614 and 9604
# above Pause's 9589 (higher is earlier in a band), which is weak evidence in this digit zone.
# Forms that give the same 9614: the test inverted around the call, a bool local, `== nullptr` for the function's test.
# The class, its base and the members Wait() and WaitAsync are RTTI's (isound.h says which typeinfo names them); every
# other name is chosen: the members' (Pause, Play, Stop, Mute, GetStatus, Wait(std::function<bool ()>)), the
# enumerations ISound::EModo and EStatus and the data members' (cwasmwebsound.h, isound.h). So is ISound's path:
# no record names it, and the one recorded audio directory, api/audio/alsa/, holds the ALSA implementation's
# CWavFile. The three CWavFile accessors slot 4 calls are chosen too, inline in unit 38's cwavfile.h. No record names
# cwasmwebsound.cpp either: it is the file ledger/tu-clusters.tsv gives clusters 227, 229, 230 and 232 (the
# `neighbours' file` of their unplaced.cpp stubs), in the directory where simulador's other wasm classes have records
# (cwasmthread.cpp, cwasmclp.cpp). The constructor is implicit and has no target function: clang's object has no call
# to it, fn 10384 holds its stores, and ISound's m_volume = 9 and this class's zeroed members are default member
# initializers. isound.h defines ISound's inline Play(..., EModo) defaults (target fns 8479, 8472, slots 2 and 4 of
# CWasmNullSound's vtable), which no object here emits: this class overrides both.
# Paths relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on the source and every uenux2
# header.
CWASMWEBSOUND_SRCS := mock/app/simulador/wasm/cwasmwebsound.cpp
UENUX2_SRCS += $(CWASMWEBSOUND_SRCS)
# nothing reconstructed builds the sound yet: 74-uenux2-cwasmwebsound-roots.cpp keeps the vtable, as the constructor
# inlined into fn 10384 does
$(ROOT)/$(APP)/74-uenux2-cwasmwebsound-roots.o: $(ROOT)/src/units/74-uenux2-cwasmwebsound-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/74-uenux2-cwasmwebsound.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/74-uenux2-cwasmwebsound-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/74-uenux2-cwasmwebsound-roots.o
