# uenux2 api::CMovie ctor (target fn 5526) in src/uenux2/src/api/gui/cmovie.cpp, the file its std::source_location
# record names (line 29 col 15, the CUeGuiError 4943 throw when there are no frames), with the class header
# (api/gui/cmovie.h: the std::vector<CMovieFrame>, the current frame and the SPoint, at +0, +12 and +16; no header of
# CMovie or CMovieFrame existed) and the 4943 enumerator of api/gui/eueguierror.h. CMovieFrame's constructor is in
# cmovie.cpp too: it has no target function (binaryen inlines it into its one caller, simulador::CWasmResource's slot
# 4, fn 8605, unit 127's), so it is compared with nothing but through 8605, which matches (unit 127's fragment).
# CMovie::ProximoFrame (fn 5525, declared in cmovie.h), the frame advance that the timer callback of api::CMovieField
# calls twice (fn 11056 holds both calls, so binaryen keeps it out of line), is written last in cmovie.cpp, a choice,
# as a select of the next index or 0 (an if storing 0 after the increment's store gave 8 over 24 rows, 4 inserted); its
# name is chosen (src/units/378-uenux2-ctelasvota-criatela.mk). The constructor's two callers, 1593 and 8605, are in
# the link (1593, unit 378's, calls it from the std::make_shared of a one-frame movie), so the roots file that stood for
# 1593 went.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CMOVIE_SRCS := src/api/gui/cmovie.cpp
UENUX2_SRCS += $(CMOVIE_SRCS)
