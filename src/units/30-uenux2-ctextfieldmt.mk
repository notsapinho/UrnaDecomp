# uenux2 api::CTextFieldMT ctor (target fn 1262) and Draw (10934) in src/uenux2/src/api/gui/ctextfieldmt.cpp, the file the
# ctor's std::source_location record names (line 25 col 15, the CUeGuiError 4970 throw), with the class header
# (api/gui/ctextfieldmt.h), the 4970 enumerator of api/gui/eueguierror.h and the IFormField<IScreenMT> specialization of
# api/gui/iformfield.h (8 slots; its inline GetTypeName is target fn 11051). Paths relative to src/uenux2; the generic
# uenux2 rule depends on the source and every uenux2 header.
CTEXTFIELDMT_SRCS := src/api/gui/ctextfieldmt.cpp
UENUX2_SRCS += $(CTEXTFIELDMT_SRCS)
# Draw is the class's only virtual member defined out of line, its key function, so ctextfieldmt.cpp's object emits the
# vtable with the implicit destructors (fns 10933, 10932) and GetTypeName; the destructor's base vtable brings
# IFormFieldBase<IScreenMT>'s destructor (11052), which binaryen merges with IFormFieldBase<IScreen>'s (12658, unit 14)
# into one body taking the vptr (1566), as the target's link did; the ctor's eight callers are not reconstructed either:
# 30-uenux2-ctextfieldmt-roots.cpp gives it two
$(ROOT)/$(APP)/30-uenux2-ctextfieldmt-roots.o: $(ROOT)/src/units/30-uenux2-ctextfieldmt-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/30-uenux2-ctextfieldmt-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/30-uenux2-ctextfieldmt-roots.o
