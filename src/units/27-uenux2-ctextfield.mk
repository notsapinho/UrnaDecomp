# uenux2 api::CTextField ctor (target fn 1918), GetTypeName (10947) and its implicit destructors (10950, 10948, emitted
# with the vtable) in src/uenux2/src/api/gui/ctextfield.cpp, with the class header ctextfield.h and the 4964 enumerator
# of eueguierror.h; paths relative to src/uenux2.
# Move (target fn 2241, slot 9) is binaryen's one body for five functions, each written in its class's file: the Move of
# this class, CImageField, CImageFieldUpdate, CTextFieldBlinking and CTextFieldUpdate (the vtables of six classes hold it:
# api::CDSImageField inherits CImageField's). Binaryen keeps the first in link order, this one, so the match line names
# it. It reads api::IForm<IScreen> through IsVisible and Refresh. Its place below Rect's line 55 is a choice: a shared
# body has no place in a band. Forms that give Move's object code, by the function's disassembly in a compile with the
# unit's flags: the body in an `if (posicao.x != m_posicao.x || posicao.y != m_posicao.y)` instead of the early return, x
# and y read into locals before the test, and `if (m_form == nullptr || !m_form->IsVisible()) return;` before the
# notification. So the early return and the test's spelling are choices. A SPoint operator== changes the object: it adds
# a mask on the second compare, as 65-uenux2-ctextbox.mk says, and primitives.h declares none.
UENUX2_SRCS += src/api/gui/ctextfield.cpp
# the class's members not reconstructed yet (trapping bodies the vtable needs; see the file header), and two callers of
# the ctor (27-uenux2-ctextfield-roots.cpp) so binaryen does not inline it and keeps both TColor parameters, as the
# target's six callers do
$(ROOT)/$(APP)/27-uenux2-ctextfield-pending.o: $(ROOT)/src/units/27-uenux2-ctextfield-pending.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/27-uenux2-ctextfield-pending.cpp -o $(R)
$(ROOT)/$(APP)/27-uenux2-ctextfield-roots.o: $(ROOT)/src/units/27-uenux2-ctextfield-roots.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/27-uenux2-ctextfield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/27-uenux2-ctextfield-pending.o $(APP)/27-uenux2-ctextfield-roots.o
