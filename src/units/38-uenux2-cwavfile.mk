# uenux2 api::CWavFile::~CWavFile (target fn 5345, the base-object destructor in slot 0 of the CWavFile vtable
# @1600476, and fn 10238, the deleting one in slot 1) in src/uenux2/src/api/audio/alsa/cwavfile.cpp, the file the
# constructor's std::source_location record names (cwavfile.cpp:47:19 api::CWavFile::CWavFile(const CWavAudio &,
# const void *)). The constructor is not reconstructed: binaryen inlined it into fn 10841 (slot 11 of
# api::CRHVoiceTextToSpeech), so line 47 stays free for it. 10841 is left to do although it has no stub any more:
# tools/round/stubs.py matches a record to a definition by name, and its `\bCWavFile\s*\(` reads the destructor's
# `CWavFile::~CWavFile()` as the constructor. No record falls in the destructor, so its line (55, after
# the constructor's) is a choice, not evidence. The class header (api/audio/alsa/cwavfile.h) has the layout the
# inlined constructor stores (vptr, the 44-byte CWavAudio WAV header at +4, the malloc'd copy of the samples at +48,
# +52 and +56 zeroed, the samples' size at +60, +64 zeroed after the copy) and simulador::CWasmWebSound reads (+4 with
# sizeof 44, +48, +60: fns 9559, 9565); the destructor frees +48 and nulls it, then frees +52. The names of the
# members, and the roles of +52, +56 and +64, are not evidenced. CWavFile has no base (RTTI kind `class`) and a vtable
# of the two destructors only; the destructor is its key function, so cwavfile.o emits the vtable. The deleting
# destructor calls the base-object one, as clang's D0 does through the D1 alias. Paths relative to src/uenux2; the
# generic uenux2 rule depends on the source and every uenux2 header.
CWAVFILE_SRCS := src/api/audio/alsa/cwavfile.cpp
UENUX2_SRCS += $(CWAVFILE_SRCS)
# nothing reconstructed references the vtable yet: 38-uenux2-cwavfile-roots.cpp takes its address, which keeps both
# destructors in the table as the target has them
$(ROOT)/$(APP)/38-uenux2-cwavfile-roots.o: $(ROOT)/src/units/38-uenux2-cwavfile-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/38-uenux2-cwavfile-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/38-uenux2-cwavfile-roots.o
