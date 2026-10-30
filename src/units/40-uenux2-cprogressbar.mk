# uenux2 api::CProgressBar::~CProgressBar (target fn 5509, the base-object destructor in slot 0 of the CProgressBar
# vtable @1581760, and fn 10978, the deleting one in slot 1) and Rect (fn 10974, slot 8) in
# src/uenux2/src/api/gui/cprogressbar.cpp, the file the constructor's three std::source_location records name
# (cprogressbar.cpp:52, 58 and 67, column 15: api::CProgressBar::CProgressBar(const uedword, const uedword, const
# uedword, const SRect &, TColor, TColor, TColor, TColor, const std::string &, TFontSize, uebyte, const TColor)). The
# constructor is not reconstructed: binaryen inlined it into std::make_shared's fn 5545 (component libc++, no stub), so
# lines 4-77 stay blank for it, its records' lines among them; no record falls in the destructor or Rect, so their
# lines (78 on) are a choice. The class header (api/gui/cprogressbar.h) has the layout that constructor stores: the
# destructor destroys the std::string at +68, then IFormFieldBase<IScreen>'s part (its vptr, m_nome at +12). The
# destructor is out of line (the deleting one calls it), declared first, so it is the key function and cprogressbar.o
# emits the vtable. Draw (10977), Move (10976) and GetTypeName (10975) are pending (40-uenux2-cprogressbar-pending.cpp
# says why each). Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CPROGRESSBAR_SRCS := src/api/gui/cprogressbar.cpp
UENUX2_SRCS += $(CPROGRESSBAR_SRCS)
# Draw, Move and GetTypeName are not reconstructed: 40-uenux2-cprogressbar-pending.cpp gives the vtable trapping bodies,
# compiled with the unit's flags. Its prerequisites are every header the compile reads (cprogressbar.h includes
# api/gui/iformfield.h, which includes api/gui/primitives.h, and ecourna/api/uetypes.hpp); $(UENUX2_HDRS) is not set
# yet when src/Makefile reads the fragments
$(ROOT)/$(APP)/40-uenux2-cprogressbar-pending.o: $(ROOT)/src/units/40-uenux2-cprogressbar-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/40-uenux2-cprogressbar.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/40-uenux2-cprogressbar-pending.cpp -o $(R)
# nothing reconstructed references the vtable yet: 40-uenux2-cprogressbar-roots.cpp takes its address, which keeps
# every slot in the table as the target has them
$(ROOT)/$(APP)/40-uenux2-cprogressbar-roots.o: $(ROOT)/src/units/40-uenux2-cprogressbar-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/40-uenux2-cprogressbar.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/40-uenux2-cprogressbar-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/40-uenux2-cprogressbar-pending.o $(APP)/40-uenux2-cprogressbar-roots.o
