# uenux2 api::CMovie ctor (target fn 5526) in src/uenux2/src/api/gui/cmovie.cpp, the file its std::source_location
# record names (line 29 col 15, the CUeGuiError 4943 throw when there are no frames), with the class header
# (api/gui/cmovie.h: the std::vector<CMovieFrame>, the current frame and the SPoint, at +0, +12 and +16; no header of
# CMovie or CMovieFrame existed) and the 4943 enumerator of api/gui/eueguierror.h. CMovieFrame's constructor is in
# cmovie.cpp too: it has no target function (binaryen inlines it into its one caller, simulador::CWasmResource's slot
# 4, fn 8605, unit 127's), so it is compared with nothing but through 8605, which waits for -O3 (unit 127's fragment).
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CMOVIE_SRCS := src/api/gui/cmovie.cpp
UENUX2_SRCS += $(CMOVIE_SRCS)
# the ctor's two callers are fns 1593 and 8605; 8605 is written (unit 127), and 23-uenux2-cmovie-roots.cpp stands for
# 1593, which is not, so the ctor keeps two call sites that drop its `this` return
$(ROOT)/$(APP)/23-uenux2-cmovie-roots.o: $(ROOT)/src/units/23-uenux2-cmovie-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/23-uenux2-cmovie-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/23-uenux2-cmovie-roots.o
