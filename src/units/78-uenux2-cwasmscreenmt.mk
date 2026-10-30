# DRAFT
CWASMSCREENMT_SRCS := mock/app/simulador/wasm/cwasmscreenmt.cpp src/api/gui/cbeepfieldmt.cpp src/api/gui/cbuzzfieldmt.cpp src/api/gui/cclockfieldmt.cpp
UENUX2_SRCS += $(CWASMSCREENMT_SRCS)
$(ROOT)/$(APP)/78-uenux2-cwasmscreenmt-pending.o: $(ROOT)/src/units/78-uenux2-cwasmscreenmt-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/78-uenux2-cwasmscreenmt.mk $(ROOT)/src/uenux2/mock/app/simulador/wasm/cwasmscreenmt.h $(ROOT)/src/uenux2/src/api/gui/iscreenmt.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/78-uenux2-cwasmscreenmt-pending.cpp -o $(R)
$(ROOT)/$(APP)/78-uenux2-cwasmscreenmt-roots.o: $(ROOT)/src/units/78-uenux2-cwasmscreenmt-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/78-uenux2-cwasmscreenmt.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/78-uenux2-cwasmscreenmt-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/78-uenux2-cwasmscreenmt-pending.o $(APP)/78-uenux2-cwasmscreenmt-roots.o
