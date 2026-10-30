# uenux2 api::CMovie ctor (target fn 5526) in src/uenux2/src/api/gui/cmovie.cpp, the file its std::source_location
# record names (line 29 col 15, the CUeGuiError 4943 throw when there are no frames), with the class header
# (api/gui/cmovie.h: the std::vector<CMovieFrame>, the current frame and the SPoint, at +0, +12 and +16; no header of
# CMovie or CMovieFrame existed) and the 4943 enumerator of api/gui/eueguierror.h. Paths relative to src/uenux2; the
# generic uenux2 rule depends on the source and every uenux2 header.
CMOVIE_SRCS := src/api/gui/cmovie.cpp
UENUX2_SRCS += $(CMOVIE_SRCS)
# the ctor's two callers (fns 1593 and 8605) are not reconstructed yet: 23-uenux2-cmovie-roots.cpp gives it two call
# sites that drop its `this` return
$(ROOT)/$(APP)/23-uenux2-cmovie-roots.o: $(ROOT)/src/units/23-uenux2-cmovie-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/23-uenux2-cmovie-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/23-uenux2-cmovie-roots.o
