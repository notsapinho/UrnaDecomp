# uenux2 vota eleitor classes no landed file holds, in app/vota/eleitor/ (paths relative to src/uenux2):
# vota::impl::ISincronismoVotoEleitor's destructor and GetInst with its default instance,
# vota::impl::CSincronismoVotoEleitor (csincronismovotoeleitor.{h,cpp}), and vota::CFimVotoEleitor's constructor,
# GetInst and statics (cfimvotoeleitor.{h,cpp}). Both GetInsts are held inlined by vota::CSincronismoEleitor::ProcessKey
# (fn 7181, unit 192's csincronismoeleitor.cpp), which matches with them.
#
# Target functions matched:
# - 7175, the exit destructor of ISincronismoVotoEleitor::GetInst's mutex (f150(1833164)), and 7212 and 7202, those of
#   CFimVotoEleitor's s_inst (f349(p0, 1833132)) and s_mutex (f150(1833108)). The scan's content pass found the three
#   (their match lines' symbols have no line in splat/symbol_addrs.txt; a rescan writes `symbol` in their source
#   column). Each is right by what it destroys: ours, the __cxx_global_array_dtor (and .2) of
#   csincronismovotoeleitor.cpp.o and cfimvotoeleitor.cpp.o (pnpm wasm fn on our link), destroy the mutex, s_inst and
#   s_mutex, and splat/symbol_addrs.txt places those three names at 1833164, 1833132 and 1833108. The names have
#   7181's votes and hold through these second matches (docs/reference/splat.md section 3).
# - Rows this unit's sources release in other units: 7181 (unit 192), with the executable TU's has<T> and push<T> thunks
#   2741 and 5398 that it calls and the TU's set<ISincronismoVotoEleitor>, 9437, over them (unit 170's paragraph).
#
# Pending, trapped in 241-uenux2-app-vota-eleitor-pending.cpp (its header says what it waits for):
# CSincronismoVotoEleitor::Sincroniza (7174), the class's key function, so the pending object emits its vtable.
#
# Written since: CFimVotoEleitor::StartState (7198, slot 2, record cfimvotoeleitor.cpp:42), the class's key function,
# so cfimvotoeleitor.cpp.o emits the vtable. It shows the form at +156 of vota::CTelasVota (slot 2, through a getter
# ctelasvota.h has now), beeps through IBeep's slot 2 with 4 (its instance() call at :42), says "fim" (the 3 bytes
# at 150256) through CVotacaoStateAudio::PlayMessage (1204, unit 97's) when CEstadoAudio is active, posts a message
# of type 1 to CThreadOperador's queue (api::SMessage{1, &fila} at priority 1, as cverificaeleicaopassou.cpp posts
# its own) and goes to CAguardaMensagem. It waited for 1204 alone, and matched as written (pnpm wasm score before
# step 8: operand rows only). Its lines and the includes' are a choice, StartState's above :42.
#
# What the target shows:
# - ISincronismoVotoEleitor's destructor is out of line in csincronismovotoeleitor.cpp, its key function
#   (isincronismovotoeleitor.h has the evidence: where its typeinfo lies, and the executable TU's has<T> loading the
#   type name from it). Which member is the key function, and `= default`, are chosen.
# - GetInst's record, csincronismovotoeleitor.cpp:67 column 98, is the closing parenthesis of
#   POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(ISincronismoVotoEleitor, CSincronismoVotoEleitor) (unit 50's
#   macro, whose column reading this record fits: 52 plus the two names' lengths). CSincronismoVotoEleitor is 4 bytes:
#   7181 allocates 4 and stores only the vptr (@1534164).
# - CFimVotoEleitor: cfimvotoeleitor.h has the layout, the constructor out of line (measured on 7181: an in-class
#   constructor leaves one row inserted and one deleted) and the statics' order. The constructor, GetInst and the
#   statics are above StartState in cfimvotoeleitor.cpp, as the exit destructors' order puts them (ld_index 4911,
#   4912, 4913 for 7212, 7202 and 7198).
# - Link order: in the target's use band 1 cfimvotoeleitor.cpp's functions (7212, 7202, 7198) link before
#   csincronismoeleitor.cpp's (7195, 7187, 7181, 7178), which link before csincronismovotoeleitor.cpp's (7175, 7174):
#   the directory's name order. This fragment lists cfimvotoeleitor.cpp after unit 192's csincronismoeleitor.cpp.
#   Every row of the three objects this branch matches is `match` with that order, and inside each object the matched
#   rows keep the target's order (ld_index 4592 < 4593 for 7212, 7202; 4361 < 4362 for 7181, 7178).
# - Data: csincronismovotoeleitor.cpp's data in the target holds GetInst's record (@1534132), the interface's typeinfo
#   (@1534148), CSincronismoVotoEleitor's vtable (@1534156) and typeinfo (@1534176), then instance<T>'s records; ours
#   holds the class's vtable and typeinfo in the pending object, Sincroniza's, until 7174 is written.
#
# Chosen, no evidence names them: the paths of both headers, the files' lines other than the two records', GetInst's
# place in cfimvotoeleitor.cpp, the statics' names, EVENTO_NENHUM for the base constructor's 0, and this fragment's
# order against unit 192 (above).
APP_VOTA_ELEITOR_SRCS := src/app/vota/eleitor/cfimvotoeleitor.cpp src/app/vota/eleitor/csincronismovotoeleitor.cpp
UENUX2_SRCS += $(APP_VOTA_ELEITOR_SRCS)
APP_VOTA_ELEITOR_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/241-uenux2-app-vota-eleitor-pending.o: $(ROOT)/src/units/241-uenux2-app-vota-eleitor-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/241-uenux2-app-vota-eleitor.mk $(APP_VOTA_ELEITOR_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/241-uenux2-app-vota-eleitor-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/241-uenux2-app-vota-eleitor-pending.o
