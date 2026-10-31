# uenux2 api::CDate and api::CDateTime, in src/uenux2/src/api/util/cdate.cpp and cdatetime.cpp, the files their
# std::source_location records name (cdate.cpp:94 and :104 for CDate(const std::string &), :130 for Format; cdatetime.cpp:31,
# :61 and :206 for CDateTime(const std::string &), ConvertFromLocalTime and ConvertFromTimestamp), with the class headers
# (cdate.h and cdatetime.h, which held the layouts only, say what each member rests on) and the 7001, 7002, 7003, 7005,
# 7006 and 7008 enumerators of api/util/eueutilerror.h, named from their messages and what their throws test.
# api::CTime's new members are unit 24's (ctime.cpp), and CAjusteDataHora's Ajusta(const CDateTime &) unit 101's.
# Target functions:
#   matched    706 Format, 3649 CDate(const std::string &), 2764 ConvertFromTimestamp (and unit 24's 779 CTime::Format),
#              at the tree's -O3 (below);
#              5479 IsValidDate, 1382 CDate(), 2765 CDate(dia, mes, ano), 1261 CDate::operator<=>;
#              479 CDateTime::Now, 1000 CDateTime(time_t), 5475 CDateTime(const std::string &), 1381 ConvertToLocalTime,
#              2233 operator+=(int), 759 CDateTime::operator<=>; libc's timegm (2961), which 1381 and 2233 call; and,
#              with units 24 and 101, 2230 CTime() and 10875 Ajusta(const CDateTime &)
#              Those four append to a std::string outside a throw, a call to std::string::append (fn 160) in the
#              target, which clang inlines at -O2. Before the tree took -O3, with -O3 for the three files
#              (tools/round/try-tu.sh cdate.cpp cdatetime.cpp ctime.cpp --flags -O3 --skip-units 24-uenux2-ctime.mk, the
#              two roots files as one --roots) each scored operand-only: 706 38 over 923 rows, 3649 33 over 363, 2764 28
#              over 576, 779 16 over 596 (pnpm wasm score against the try's link-map names); at -O2 985 over 1772, 191 over
#              469, 328 over 698 and 938 over 1355. 3649 is named by the call votes of 2765 and 5475.
#              5472 FormatCurrentDate and 5473 FormatCurrentTime, the callbacks cdatetime.h describes, match at the
#              tree's -O3 with 706 and 779, which they call; at -O2 they were operand-only (3 over 32 and 3 over 30 rows,
#              the callee rows) and `unresolved`. Each is named by a pair-depth0 hand line of splat/symbol_addrs.txt (its
#              depth-0 fingerprint is unique on both sides, and no vote reaches it: its one direct caller, 11216, has
#              its name by vtable evidence, and 5343 and 7787 are not written); the lines hold 11216's match (taking
#              either out takes 11216 out of match and the callback to no-candidate). They sit in band 2 of
#              ledger/ordinals.tsv between 5475 and 5471 (cluster 765, labelled cdatetime.cpp), and are defined after
#              ConvertFromLocalTime, 5473 first (names.tsv's ld_index); their lines are chosen. The forms, each object
#              against the target's frame offsets: a named CDateTime and a copy of its date
#              (`const CDateTime agora = Now(); const CDate data = agora.GetData(); return data.Format(formato);`) puts
#              the CDateTime at +16 and the copy at +8 in 5472, +4 and +0 in 5473, as the target does;
#              `return Now().GetData().Format(formato)` with a GetData that returns by value, and
#              `const CDate data = Now().GetData();`, put the CDateTime at +8 and the copy at +24 (5472), +0 and +12
#              (5473). GetData's and GetHora's return by reference is 11198's (cdatetime.h).
#   written    the rest below.
#              5476 ConvertFromLocalTime is operand-only (14 over 90 rows) and `unresolved self-voted`: it calls
#              std::to_string(long long) (fn 4658), whose other target caller, 3612, is not written, so the name has 5476
#              alone as voter. The roots' TempoEmTexto keeps to_string out of line for it, standing in for 3612.
#              3648 CDate::operator- is operand-only (1 over 9) and `no-candidate`: nothing names it, and its callee
#              operator-= (5477) is not matched.
#              5478 operator+= and 5477 operator-= do not match at -O2 (291 over 558, 271 over 543 rows) nor at the tree's
#              -O3 (86 over 550, 30 over 530): the target splits the day-of-the-year loop on `ano % 4` (two copies, one over a
#              lookup table), which our -O3 build gives and our -O2 build does not, and keeps the month's store inside
#              the month loop, where ours sinks it after the loop (and in += nests the month loop in the year loop's
#              exit). The rest of that remainder is not explained. They stay written: operator- (3648) calls
#              operator-=, and they call each other.
#              Their stubs stay in src/ecourna/unplaced.cpp, since nothing names their bodies.
# The 16-bit static 2000 that IsValidDate and CDate(const std::string &) add to a two-digit year is an object of
# namespace api, named g_seculo here (a chosen name), at the head of cdate.cpp's data (1584256, before its first record at
# 1584260). Its external linkage is the bytes': a const or file-static object nothing writes would fold into the code;
# that it is a namespace global and not a static member is chosen. Its name is a hand edit of splat/symbol_addrs.txt
# (callers+content): 3649, CDate's constructor by its records, and 5479 are the only target functions that read the word
# (`grep -rlE 'i32\.const 1584256($|[^0-9])' build/out/splat/pieces/asm`), each as an i32.load16_u added to the year when
# the string has 6 characters. Without it 5479 is `unresolved` on that operand, and 5475 is `unresolved self-voted` on 5479.
# The weekday names are a table of seven pointers at 1584308, in cdate.cpp's data after its records.
# Forms measured against another: Bissexto is `ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)`, where the target tests
# %4 with a branch first (5479 at 11 over 378 rows; grouped `(%4 && %100) || %400` it has no branch, 30 over 386);
# operator-= and operator+= take a month's day count once per iteration, from a variable assigned in the loop's condition
# (computed again in the body, -O3 keeps two copies: 5477 at 120 over 578), and += its year length the same way (5478 at
# 124 over 568 without). Written in the target's order and not compared with another: CDate(const std::string &) stores
# the year, the month, the day and the weekday, CDate() the day, the month, the year and the weekday; ConvertFromLocalTime
# builds the time before the date and stores the date first (two locals, then two assignments); the weekday takes
# `+= dias % 7` (`+= 7 - dias % 7` in -=) and then `%= 7`, as the target wraps the sum to 16 bits before the remainder.
# Chosen, no byte decides: every name but the records' (Format, CDate(const std::string &), the three CDateTime functions
# with records) and the messages': IsValidDate, IsValidDateTime, Now, ConvertToLocalTime, operator+= and operator<=> of
# CDateTime, FormatCurrentDate, FormatCurrentTime (and that they are static members), GetData and GetHora, CDate's
# operators and getters, g_seculo, DIAS_SEMANA and the file-static helpers Bissexto, DiasNoMes,
# DiasNoAno and DiaDoAno, which clang inlines, and that they are file-static functions and not members; IsValidDate
# and IsValidDateTime free functions in api, declared in the headers, as unit 24's IsValidTime is (5475 holds
# IsValidDateTime with a stack prologue of its own, binaryen's inlining, so it is a function of the object, left unrooted;
# that it is external rather than file-static is not measured); g_seculo's type, a short; every line but
# the records'; and the order of the functions without a record, inside the order the bands give (ledger/ordinals.tsv,
# reverse link order inside a band, read against build/out/wasm-map/vota_web/names.tsv's ld_index): in cdate.cpp
# IsValidDate, operator+=, operator-= (band 2) and CDate(const std::string &) before operator- (band 3); in cdatetime.cpp
# ConvertFromLocalTime before CDateTime(const std::string &) (band 2), as CDateTime(time_t), defined above both, calls
# it first (docs/reference/facts/reading.md R9). CDate's constructor from three numbers delegates to the one from a
# string through std::format("{:02}{:02}{:04}", ...), the string at 8593.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CDATETIME_SRCS := src/api/util/cdate.cpp src/api/util/cdatetime.cpp
UENUX2_SRCS += $(CDATETIME_SRCS)
# the callers of these members outside the two files are not reconstructed yet: 125-uenux2-cdatetime-roots.cpp reaches
# each function the way the target does (its header lists them); it includes no tree header
$(ROOT)/$(APP)/125-uenux2-cdatetime-roots.o: $(ROOT)/src/units/125-uenux2-cdatetime-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/125-uenux2-cdatetime.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/125-uenux2-cdatetime-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/125-uenux2-cdatetime-roots.o
