# uenux2 api::CTime: the constructor from hours, minutes and seconds (target fn 3642) and operator-(int) const (target
# fn 3641), in src/uenux2/src/api/util/ctime.cpp, the file their std::source_location records name: the constructor
# inlines the file's static EncodeTime(uebyte, uebyte, uebyte) (line 48 col 11, the CUeUtilError 7079 throw), and
# operator- inlines operator-= (line 161 col 19, the 7082 throw), which calls operator+= (line 148 col 19, the 7081
# throw), with the class header (api/util/ctime.h: the seconds since midnight, one size_t) and the three enumerators
# of api/util/eueutilerror.h. No evidence names fn 3641 (its records are those of the inlined -= and +=, and no RTTI,
# vtable slot or export holds it): the name operator-(int) const is read from the body's shape, a copy of *this with
# -= applied and returned by value; a free operator-(const CTime &, int) would give the same bytes. The constructor
# from a string (fn 3643) is not reconstructed yet. Paths relative to src/uenux2; the generic uenux2 rule depends on
# the source and every uenux2 header.
CTIME_SRCS := src/api/util/ctime.cpp
UENUX2_SRCS += $(CTIME_SRCS)
# the six callers of both are not reconstructed yet: 24-uenux2-ctime-roots.cpp gives each two call sites
$(ROOT)/$(APP)/24-uenux2-ctime-roots.o: $(ROOT)/src/units/24-uenux2-ctime-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/24-uenux2-ctime-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/24-uenux2-ctime-roots.o
