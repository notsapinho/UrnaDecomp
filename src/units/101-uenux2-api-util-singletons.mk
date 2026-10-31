# uenux2 singletons of api/util over unit 100's api::CPolySingleton:
# - api::ITimerScheduler::GetInst (target fn 1259, record itimerscheduler.cpp:23:12) and CreateInst<api::CTimerScheduler>
#   (5444, record itimerscheduler.h:40:19), with api::CTimerScheduler (api/util/ctimerscheduler.h, a chosen path). GetInst's
#   callers are not written: unit 100's roots call it. CreateInst returns what GetInst returns, as its record spells it; no
#   caller reads it, so binaryen dropped the result. The 7085 enumerator of EUeUtilError is new, its name chosen.
# - api::CAjusteDataHora (api/util/cajustedatahora.{h,cpp}, chosen paths): Registra (10876, a chosen name: only table slot 118
#   reaches it, so the roots take its address) and Ajusta(const time_t&) (10874). 10876 holds set<IAjusteDataHora> and
#   push<IAjusteDataHora>, which binaryen inlined (two more prologues), so unit 100's fragment reads it for push. The file
#   is placed by data order: the vtable (@1584156) and the interface's typeinfo lie between api/io/cinisection.cpp's records and
#   api/util/cdate.cpp's. api::IAjusteDataHora's header has its members now, with their slots.
# Pending, in the -pending.cpp: CTimerScheduler::CreateTimer (10846) and CAjusteDataHora's first Ajusta (10875).
# ISystemDateTime::GetInst and CreateInst (1155, records isystemdatetime.cpp:23 and .h:46) are in unit 81's source, the same
# shape; 1155 holds instance<T> because it is its only caller, and CreateInst for the same reason.
# Chosen, no byte decides: every name but GetInst's, CreateInst's and the messages'; has<T> and not a member of CPolySingleton
# in the two tests; std::unique_ptr<T>(new T) for make_unique, the same object.
API_UTIL_SINGLETONS_SRCS := src/api/util/cajustedatahora.cpp src/api/util/itimerscheduler.cpp
UENUX2_SRCS += $(API_UTIL_SINGLETONS_SRCS)

$(ROOT)/$(APP)/101-uenux2-api-util-singletons-pending.o: $(ROOT)/src/units/101-uenux2-api-util-singletons-pending.cpp $(ROOT)/src/units/101-uenux2-api-util-singletons.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/util/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/101-uenux2-api-util-singletons-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/101-uenux2-api-util-singletons-pending.o
