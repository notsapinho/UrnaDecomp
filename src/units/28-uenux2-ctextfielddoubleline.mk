# uenux2 api::CTextFieldDoubleLine ctor (target fn 3659) and GetTypeName (10926) in
# src/uenux2/src/api/gui/ctextfielddoubleline.cpp, the file the ctor's three std::source_location records name (lines
# 40, 43 and 46, col 15: the CUeGuiError 4967, 4968 and 4969 throws), with the class header
# (api/gui/ctextfielddoubleline.h) and the three enumerators of api/gui/eueguierror.h. Paths relative to src/uenux2;
# the generic uenux2 rule depends on the source and every uenux2 header. The layout is the ctor's stores (60 B, the
# 72 B make_shared blocks of its callers); the member and parameter names are chosen, after the messages ("maxX",
# "linha 1", "linha 2"). The implicit destructors emitted with the vtable do not match 10928/10927 (12 B thunks into
# bodies binaryen merged with CTextRectField's); the census pairs them with CTextFieldPaper's 10919/10918 instead
# (one vptr apart), so stubs.py drops those two stubs from ctextfieldpaper.cpp although they are not written.
CTEXTFIELDDOUBLELINE_SRCS := src/api/gui/ctextfielddoubleline.cpp
UENUX2_SRCS += $(CTEXTFIELDDOUBLELINE_SRCS)
# the class's members not reconstructed yet (trapping bodies the vtable needs; see the file header), and two callers of
# the ctor (28-uenux2-ctextfielddoubleline-roots.cpp) so binaryen does not inline it and drops the constant TColor
# argument as the target's wasm-opt did
$(ROOT)/$(APP)/28-uenux2-ctextfielddoubleline-pending.o: $(ROOT)/src/units/28-uenux2-ctextfielddoubleline-pending.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/28-uenux2-ctextfielddoubleline-pending.cpp -o $(R)
$(ROOT)/$(APP)/28-uenux2-ctextfielddoubleline-roots.o: $(ROOT)/src/units/28-uenux2-ctextfielddoubleline-roots.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/28-uenux2-ctextfielddoubleline-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/28-uenux2-ctextfielddoubleline-pending.o $(APP)/28-uenux2-ctextfielddoubleline-roots.o
