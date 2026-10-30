# uenux2 api::CTime and api::IsValidTime, in src/uenux2/src/api/util/ctime.cpp, the file their std::source_location
# records name. The constructor from hours, minutes and seconds (target fn 3642) inlines the file's static
# EncodeTime(uebyte, uebyte, uebyte) (line 48 col 11, the CUeUtilError 7079 throw); the constructor from a string
# (target fn 3643) inlines the file's static EncodeTime(const std::string &) (line 63 col 11, the 7080 throw), which
# calls IsValidTime (target fn 5449) and then converts the HHMM[SS] digits; operator- (target fn 3641) inlines
# operator-= (line 161 col 19, the 7082 throw), which calls operator+= (line 148 col 19, the 7081 throw). With the class
# header (api/util/ctime.h: the seconds since midnight, one size_t, and IsValidTime's declaration) and the four
# enumerators of api/util/eueutilerror.h. Both EncodeTime overloads are file-static: their records (lines 63 and 48)
# come after those of += and -= (148, 161) in the file's record order (docs/reference/facts/reading.md §R8).
# Chosen, not evidenced:
# - fn 3641's name: its records are those of the inlined -= and +=, and no RTTI, vtable slot or export holds it, so
#   operator-(int) const is read from the body's shape, a copy of *this with -= applied and returned by value; a free
#   operator-(const CTime &, int) would give the same bytes.
# - fn 5449's name, IsValidTime, and its lines (22-40, inside the unknown lines 10-41): no record, slot or RTTI names
#   it, and it throws nothing. Its stub was in src/ecourna/unplaced.cpp, the tree of its component (it calls ecourna's
#   CStringUtils::ToByte), but it is uenux2 code of this file: it calls ToByte, which can throw, while a std::string
#   temporary is alive with no landing pad (uenux2 compiles without -fexceptions, docs/reference/facts/app-flags.md
#   §F6); its callers are this file's EncodeTime(const std::string &) and the date and time check fn 5475,
#   api::CDateTime's constructor from a string (cdatetime.cpp), inlines; and its use band of ledger/ordinals.tsv puts it
#   after ctickmanager.cpp's fn 5451 in link order. It is external, declared in ctime.h, because 5475 calls it from
#   that check, which binaryen inlined (a second stack frame) beside a call of CDate's check (fn 5479), while 5475
#   calls fn 3643 itself: no ctime.cpp function inlined there could carry a call to a file-static one. A static member
#   CTime::IsValidTime would give the same bytes; a free function is chosen because it reads no member.
# - the 7080 enumerator's name (eueutilerror.h says so beside it).
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CTIME_SRCS := src/api/util/ctime.cpp
UENUX2_SRCS += $(CTIME_SRCS)
# the nine callers of 3641, 3642 and 3643 and 5449's caller 5475 are not reconstructed yet: 24-uenux2-ctime-roots.cpp
# gives each function more than one call site
$(ROOT)/$(APP)/24-uenux2-ctime-roots.o: $(ROOT)/src/units/24-uenux2-ctime-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/24-uenux2-ctime-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/24-uenux2-ctime-roots.o
