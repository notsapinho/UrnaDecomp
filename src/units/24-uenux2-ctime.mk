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
#   it, and it throws nothing. Its stub was in src/ecourna/unplaced.cpp, the tree of its component (a component records
#   who calls a function: ledger/func-attribution.tsv reads `5449 ecourna callers`), but it is uenux2 code of this
#   file: it calls ecourna's CStringUtils::ToByte, which can throw, while a std::string
#   temporary is alive with no landing pad (uenux2 compiles without -fexceptions, docs/reference/facts/app-flags.md
#   §F6); its callers are this file's EncodeTime(const std::string &) and the date and time check fn 5475,
#   api::CDateTime's constructor from a string (cdatetime.cpp), inlines; and, inside one digit zone, its use band of
#   ledger/ordinals.tsv puts it after ctickmanager.cpp's fn 5451 in link order. Its linkage is chosen too: external,
#   declared in ctime.h, because 5475 calls it from a check binaryen inlined (a second stack frame) beside CDate's
#   check (fn 5479), which reads as cdatetime.cpp's. No record or band places that check: defined in ctime.cpp, with
#   IsValidTime file-static, it gives the same bytes. A static member CTime::IsValidTime would too; a free function
#   is chosen because it reads no member.
# - the 7080 enumerator's name (eueutilerror.h says so beside it).
# Added with unit 125 (api::CDate and api::CDateTime): CTime's default constructor (target fn 2230, matched), now from
# ISystemDateTime's clock, at lines 13-19, a choice (it has no record); Format (fn 779) at lines 76-135 and operator<=>
# at the end of the file, both places chosen, with operator<=>'s name and std::strong_ordering result; and the inline
# getters ctime.h describes.
# operator<=>'s body is fn 5448's, the one the target keeps for OpenSSL's err_string_data_cmp as well, so that match line
# now names ours (ctime.cpp.o links ahead of libcrypto). Format matches at the tree's -O3: its appends call
# std::string::append (fn 160) in the target, which -O2 inlines (unit 125's fragment has the -O2 measurement).
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CTIME_SRCS := src/api/util/ctime.cpp
UENUX2_SRCS += $(CTIME_SRCS)
# the callers of 3641 and 3643 outside the tree's sources are not reconstructed yet: 24-uenux2-ctime-roots.cpp gives each
# more than one call site, with cdatetime.cpp's (unit 125), which also calls 3642 and 5449 enough
$(ROOT)/$(APP)/24-uenux2-ctime-roots.o: $(ROOT)/src/units/24-uenux2-ctime-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/24-uenux2-ctime-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/24-uenux2-ctime-roots.o
