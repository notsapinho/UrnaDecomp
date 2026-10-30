# uenux2 thin devices of the wasm simulator in src/uenux2/mock/app/simulador/wasm/, each a .cpp and a .h, with the
# interfaces they implement. By class:
# - simulador::CWasmInputKbd and CWasmInputMT over api::IInput, IInputKbd and IInputMT (src/api/hwil/iinput.h): ReadKey,
#   HasKey and Clear (target fns 5015, 5014, 5013, slots 2 to 4 of both vtables). Each pair is one function in the target,
#   so the two classes' bodies are written twice and binaryen merges them in our link too, under CWasmInputKbd's symbols,
#   the first in link order.
# - simulador::CWasmSystemDateTime over api::ISystemDateTime (src/api/util/isystemdatetime.h): GetTime and SetTime (7954,
#   7945), and api::CSystemDateTime (src/api/util/isystemdatetime.cpp): GetTime and SetTime (10855, 10853).
# - simulador::CWasmNullSound, the whole vtable: Play(std::shared_ptr<CWavFile>) (8487) is its own, its other members are
#   the shared empty bodies, and slots 2, 4, 8 and 9 are api::ISound's defaults (src/api/audio/isound.h), emitted with its
#   vtable: Play(const std::string &, EModo) 8479, Play(std::shared_ptr<CWavFile>, EModo) 8472, Wait 8461, WaitAsync 8450.
#   They bring the __func members of ISound::Wait()'s lambda (8440, 8435, 8429, 8427) and of ISound::WaitAsync's (8422,
#   8413, 8403, 8393, 8384, 8382, 8380, 8377), api::CEsperaAudio (src/api/audio/cesperaaudio.h; 9509 and 2683, the body
#   matched until now as sqlite's rtreeEof, which binaryen merges under this earlier symbol) and
#   __shared_ptr_emplace<api::CEsperaAudio> (9506, 9501). clang inlines ISound::Wait(), std::make_shared and
#   CSystem::Dorme into these bodies: the object calls none of them.
# - CSystem::Dorme and the flag CSystem::s_dorme, added to unit 32's csystem.h and csystem.cpp for ISound::Wait. The
#   flag is the word of .data at 1584624: the census pair of fn 8461 votes for it, its one vote, and our byte agrees with
#   the target's. Besides that, 24 target functions read that address the same way, before emscripten_sleep.
# Evidence. RTTI gives every class and base; records give iinput.h and isystemdatetime.{h,cpp} their paths, and each keeps
# its record lines blank (the headers say which, and that the lines of what they hold are a choice). What the target
# says of each header's members is in the header. The imports' types are the target's (src/web/wasm_shim.cpp): ReadKey
# has to narrow an int, HasKey to compare one. Key functions, read from data and band order, which support them and do
# not prove them: CWasmInputKbd's and CWasmInputMT's typeinfos are not followed by their bases', which lie later beside
# fn 8302's records, and a probe gives that shape for an object pulled from an archive by the TU that keeps the base's
# typeinfo; 8487 comes before ISound's four bodies in reverse link order, where a member inline in CWasmNullSound would
# sit among them in slot order. CWasmSystemDateTime's and CSystemDateTime's are not determined; CSystemDateTime's place
# is the reading of data order isystemdatetime.cpp's header gives.
# Chosen. No record names the four cwasm*.cpp files. cwasminputmt.cpp, cwasmsystemdatetime.cpp and cwasmnullsound.cpp are
# ledger/tu-clusters.tsv's class-convention labels of stretches 716, 39 and 63 to 68, and cwasminputkbd.cpp is the
# class's name in lower case, which no stretch gives; the directory is where simulador's other wasm classes have records
# (cwasmthread.cpp, cwasmclp.cpp). Every member name is chosen but ISound's Wait and WaitAsync: the headers say which and
# from what. So are the first out-of-line member of each class, which makes it the key function, and that no class but
# CEsperaAudio is final.
# Other forms that give the same bytes, compiled with the tree's flags and compared function by function: no static_cast
# in ReadKey, an implicit conversion in HasKey; final on CWasmInputKbd, CWasmSystemDateTime, CSystemDateTime or
# CWasmNullSound; slots 5 to 7 as IInputKbd's defaults; HasKey and Clear in the class; GetTime as
# static_cast<time_t>(js_...()) + m_diferenca, or through a local time_t, and a long long cast; SetTime through a local;
# time(0) or std::time(nullptr); CSystemDateTime's SetTime in the class, or both members in it with a function of this
# file that news one; every CWasmNullSound member in the class but Play(std::shared_ptr<CWavFile>), then the key function;
# in WaitAsync, an explicit type for espera, a non-const bool, the lambda as two ifs with a conditional, nested ifs around
# fim; in Wait, an if with a do-while, nested ifs, a comparison as int, and the flag's test written in place, with a
# free global instead of a member; s_dorme == true; a final destructor instead of a final CEsperaAudio. Forms that do
# not: the imports declared char or bool, m_diferenca + static_cast<time_t>(js_...()) (the load comes before the call),
# WaitAsync's captures swapped, CEsperaAudio without either final, or with final or a qualified call only on the
# read (__on_zero_shared then calls the destructor through the vtable, where the target's slot holds an empty body).
# Paths relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on each source and every uenux2 header.
SIMULADOR_DEVICES_SRCS := mock/app/simulador/wasm/cwasminputkbd.cpp mock/app/simulador/wasm/cwasminputmt.cpp \
	mock/app/simulador/wasm/cwasmnullsound.cpp mock/app/simulador/wasm/cwasmsystemdatetime.cpp \
	src/api/util/isystemdatetime.cpp
UENUX2_SRCS += $(SIMULADOR_DEVICES_SRCS)
# nothing reconstructed creates these devices yet: 81-uenux2-simulador-wasm-devices-roots.cpp keeps their vtables, the
# reference the target's vptr stores give
$(ROOT)/$(APP)/81-uenux2-simulador-wasm-devices-roots.o: $(ROOT)/src/units/81-uenux2-simulador-wasm-devices-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/81-uenux2-simulador-wasm-devices.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/81-uenux2-simulador-wasm-devices-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/81-uenux2-simulador-wasm-devices-roots.o
