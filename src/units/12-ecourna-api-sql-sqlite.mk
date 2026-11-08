# ecourna::api::sql::sqlite DAO (csqlconnection / csqlresultset / csqlstatement) + the shared sqlite error helper.
# CSqlStatement::Close (fn 9429) and s_mutex's destructor (fn 9431) match. Close keeps sqlite3_finalize's result in a local
# as Reset does. Evidence: with the call in the `if`, wherever the two statements after it sit, clang puts the success
# path after the handler, with one __cxa_free_exception; with the local it comes before, with two, as in 9429 (measured on
# the object). `const int`, `int` and `auto` give the same rows, and `const int` is chosen, from Reset. s_mutex's name is a
# vote of 9429, a `srcloc-anchor`, and 9431 holds it as the second user.
# (sqlite3.h and boost come from the include dirs src/mk/ecourna-flags.mk adds)
#
# What matches (target fns): CSqlConnection's constructor 3515, D2 5167, D0 9456, BeginTransaction 9455,
# CommitTransaction 9454, RollbackTransaction 9453, Prepare 9460, IsClosed 9457, Close 9458, CheckIntegrity 9452 and
# GetCaminho 5322 (a twin of an RHVoice getter, whose line now carries this name); CSqlStatement's constructor 9430, D2
# 3513, D0 9426, SetInt 5160, SetInt64 9425, SetDouble 9424, SetText 9423, SetBool 9421, SetBlob 9420, SetNull 9419,
# SetDateTime 9422, Execute 9417, Reset 9416, IsClosed 9428 and VerifyParameterIndex 1882; CSqlResultSet's constructor 9449, D2 9443, D0
# 9442, the GetInt/GetInt64/GetDouble/GetText/IsNull/GetBool pairs (2679 9441, 5165 9440, 5164 9439, 3514 9438, 5163
# 9435, 9446 9433), GetDateTime(const std::string &) 9434 and GetDateTime(int) 5162, the GetBlob pair (5161 9432),
# IndexForColumnName 1525, Next 9444 and VerifyColumnIndex 1883; ObterMensagemErro 9411; the __shared_ptr_pointer
# control blocks' __get_deleter and
# __on_zero_shared (statement 9450 9451, result set 9412 9413 from the unit's objects; connection 11538 11539 from
# celeitordinamicodao.cpp.o, as the target's copy is a uenux2 caller's: its vtable 1559000 lies in uenux2's data band); the
# externs' ToLower in place 5158, copying ToLower 1879 and Replace 9398; and library code these bodies call:
# std::map<std::string, int>'s tree members 1677, 2678, 9447, std::set<int>'s __find_equal 2676 and string::replace 4667,
# and Boost date_time's format_month in iso_extended_format 9414 and to_simple_string_type over a time_duration 9415.
#
# Names: records name the connection's constructor, Prepare and Close; the statement's SetInt, SetInt64, SetDouble,
# SetText, SetBlob, SetNull, Reset, Close and VerifyParameterIndex; the result set's GetInt(int), GetInt64(int),
# GetDouble(int), GetText(int), IsNull(int), GetBlob(int), VerifyColumnIndex, IndexForColumnName and StepStatement.
# RTTI names the classes and their interfaces, and the vtables place each slot. Every other member name is chosen, from
# what its body does: BeginTransaction, CommitTransaction and RollbackTransaction (they run "begin transaction",
# "commit transaction", "rollback transaction"), CheckIntegrity ("PRAGMA integrity_check(1)"), IsClosed (the closed
# flag), GetCaminho (the path member), Execute (builds the result set), SetDateTime and SetBool (format a ptime and pass
# a bool to SetText and SetInt), Next (the first-row flag, else StepStatement), GetBool and GetDateTime, and the
# `const std::string &` overloads, which call IndexForColumnName and then the int form. The constructors are named by
# their role (a fresh object's vptr store), ObterMensagemErro and its file sqliteutils.{hpp,cpp} by choice. All of these
# names are the base's, in the headers before this unit was reached; the one name this unit's matching adds is the
# helper ObterSql (below).
#
# What the target shows, and the source follows (evidence):
# - The destructors of CSqlConnection and CSqlStatement are out of line, defined in the .cpp: the control blocks'
#   __on_zero_shared (11539, 9451) call the D2 (5167, 3513) where an in-class destructor is inlined into them. Both
#   classes are final: those calls are direct, not through the vtable.
# - CSqlConnection closes with sqlite3_close, not sqlite3_close_v2: the constructor reaches it through table slot 6335,
#   fn 6521, sqlite3_close (`wasm-objdump -x -j Elem target/vota_web_wasm.wasm`), and Close (9458) calls f6521
#   directly.
# - Each sqlite3_bind_*, sqlite3_reset and sqlite3_close result is held in a named local before the test: in ecourna's
#   -fexceptions code the local's lifetime end on the throw path gives the landing-pad layout the target has; the call
#   in the condition gives another (first difference `block` at +0x19 in 5160). Unit 11's fragment
#   (11-ecourna-api-security.mk) has the same case for CSha::Reset.
# - StepStatement tests SQLITE_ROW first, then SQLITE_OK or SQLITE_DONE, and builds the operation's text in a helper
#   that returns either string: the `temLinha` form and an in-place ternary of two strings each give other code (184 and
#   180 rows against the target, against 64 operand-only rows for this one). The helper's name, its file-static
#   linkage and its place are chosen: it sits at csqlresultset.cpp lines 14-25, in lines the base kept blank as not
#   recovered, which moves the constructor (no record) to line 27. binaryen inlines it into its one caller.
# - CSqlStatement's constructor takes the file's mutex and Close releases it. Prepare calls the constructor through
#   an invoke_ thunk (slot 6338), which emscripten keeps only for a callee that may throw when it runs, and the
#   constructor's own code (stores and sqlite3_bind_parameter_count) cannot: the mutex's lock can, and its code goes
#   once pthread_mutex_lock, a stub in this single-threaded build, is inlined. Without the lock the call is direct and
#   neither 9430 nor 9460 matches. The body places the lock too: 9430 stores m_stmt and then reloads it from +8 for
#   sqlite3_bind_parameter_count, which LLVM does only with an opaque call between the store and the count. Compiled
#   with ecourna's flags, the object of this form (member stores, lock, then the count) reloads `i32.load 2 8` after
#   the lock's call (std::mutex::lock, and std::recursive_mutex::lock since); the base's form (the count in the
#   initializer list, no lock) and the same with the lock in
#   the body both pass the parameter (`local.get 2`). A std::lock_guard, or the count before the lock, does not match
#   in the whole link either (measured by this unit's verification). That Close does not take the lock again is
#   chosen: a second lock there gives the same bytes.
# - The file's mutex (s_mutex) is read as a std::recursive_mutex. Evidence: the target's static initializers (fn
#   14478, __wasm_call_ctors) hold libc++'s recursive_mutex constructor inlined at +0x13b9, after CTrng's DISPOSITIVO
#   (1911784) is built and before the CBaseType names (1911992 on): it tests the results of libc's
#   pthread_mutexattr_init (3977) and pthread_mutexattr_settype (3976) and calls __throw_system_error (1223) with
#   "recursive_mutex constructor failed" (202274); a std::mutex is constant-initialized, with no such code. That code
#   addresses nothing but its frame, so which static it builds is a reading. The init and .bss orders allow two:
#   this file's s_mutex (1911796, 24 bytes) and the 24-byte object at 1911964, whose exit destructor is 9267, beside
#   CSynchronizer::s_instancia (1911988, 9268), read by that place and that adjacency as a static of csynchronizer.cpp's
#   TU (a reading) our source does not declare. What
#   favours s_mutex: the target keeps "recursive_mutex lock failed" (202681), so code the link kept locked the one
#   recursive mutex, and s_mutex is locked (9430) and unlocked (9429), while no target body but 9267 refers to 1911964.
#   Measured in the whole link against 21a541d4: with the recursive mutex, 3977 keeps its i32 result, and 3977,
#   SQLite's pthreadMutexAlloc (12936), api::CPosixMutex's constructor (10254, unit 01) and
#   CDefaultGenericFactory<ISyncCtl, CPosixMutex>::Create (10869, unit 170) match, none lost; 9429, 9430, 9431 and
#   9460 still match. A static recursive_mutex in csynchronizer.cpp's TU would give the four the same 3977 (reasoned,
#   not measured). Merged onto 93c63667, 12936's pair took SQLite's 962 and 2352 out until sqlite3.o linked after
#   libcrypto (docs/reference/facts/link-order.md §L3). Our link puts this unit's objects ahead of ctrng.cpp's (unit
#   137), the reverse of the target's data; 14478 is `unresolved` before and after.
# - GetBlob returns an empty vector before building one when the column has no bytes: the target tests the size
#   before the vector's exception guard is set up.
#
# Choices, each with the forms that give the same object code (`em++` with ecourna's flags, the function's
# disassembly compared): the local's name and type (`const int resultado`; `int`, `const bool ok = ... == SQLITE_OK`
# and an if-initializer give the same bytes); the destructors test `m_fechada`/`m_fechado` (`IsClosed()` gives the same
# bytes) and sit right after the constructors, a place no record gives; GetBlob's `return std::vector<uebyte>();`
# (`return {};` gives the same bytes; `if (tamanho > 0)` around the copy does not).
#
# Matched later, with what held each:
# - CSqlResultSet::StepStatement (5166): no evidence named std::piecewise_construct, a one-byte object the map's
#   operator[] passes (target 463337): content cannot place one byte, and the census paired no function that loads
#   it. The rest of the body was the target's up to operands (64 rows, all operand-only). Since the executable TU's
#   votaInit 9384's vote names it (`vote:1 by:9384`), and 5166 matches (docs/reference/facts/splat.md S10 item 33's
#   rows are its neighbours; why the vote formed is not traced).
# - CSqlResultSet::GetDateTime (5162) waited for its callee boost::date_time::parse_iso_time<ptime> (5851, 9824 B),
#   which it reaches through an invoke_ table slot: that was the copy of app/dados/asn/datahoraasn.cpp in our link, a
#   different body (fn 6004, whose folded readout is 290 lines against the target's 1568), then uenux2's
#   cgravadorrcsecao.cpp's (unit 122), which is the target's since the Boost tree root's probe dropped its date
#   parsing, clock and lexical_cast calls (unit 122's fragment has the measurements). 5162's body is unchanged; with
#   5851 named it matches (25 over 230 rows, all operand-only, pnpm wasm score).
# - CSqlStatement::SetDateTime (9422) waited for its inlined ymd_to_string in iso_extended_format: the target holds it
#   inlined here, its one caller, and the probe that src/app/roots_boost.o compiles (-O2, no -fexceptions, ahead of both
#   trees) gave it a second call site. 9422 matches since that call left tools/libs/boost/probe.cpp (fragment 265 has
#   the measurements). Its callees from_day_number (1376) and to_simple_string_type over a time_duration (9415, which
#   it calls through invoke_vij) come from ecourna's objects too since the root stopped giving its own (its `extern
#   template` lines, until the probe's date parsing and clocks went: fragment 265), and
#   this unit's object gives 9415 and month_formatter's format_month in iso_extended_format (9414); 9422 reaches 1376
#   and 9415 through their table slots, which re-point by name whichever copy fills them, so its bytes do not rest on
#   those two lines (measured: a whole link without either line keeps 9422 verified).
# - CSqlStatement::Close (9429) waited for a target name of the file-static mutex it unlocks (our .bss `s_mutex`;
#   the target's is at 1911796): a .bss object gets a name only from a vote of a census-paired function, and the census
#   paired neither 9429 nor 9431, the mutex's exit-time destructor. 9429 is a `srcloc-anchor` now, and its vote names
#   the mutex (above).
# - CSqlResultSet::GetBlob (5161) stopped at `call 306 | call 2671`: the target's vector exception guard destructor
#   calls __destroy_vector out of line, and ours inlined it and merged with 2671. It matches since
#   src/app/roots_vector.cpp holds the target's copy.
# - The copying ToLower (1879) is a thunk into binaryen's merge 3942 in the target, with fns 1374 and 5156, copying
#   wrappers of Trim and of ToUpper in place (3509, unit 00). It matches since unit 112 brought 1374. CSqlResultSet::IndexForColumnName
#   (1525), which calls it, matches since unit 89's comum::CLocal::GetUFMinuscula (3753) is a second holding caller.
# - ToLower in place (5158) was `unresolved`, self-voted on acentuadas's guard, which only its own pair votes for. It
#   matches since the self-vote rule places a guard by its object at our link's distance (the externs file's header).
ECOURNA_SRCS += api/sql/sqlite/csqlconnection.cpp
ECOURNA_SRCS += api/sql/sqlite/csqlresultset.cpp
ECOURNA_SRCS += api/sql/sqlite/csqlstatement.cpp
ECOURNA_SRCS += api/sql/sqlite/sqliteutils.cpp
# definitions of CStringUtils::ToLower/Replace until api/util/cstringutils.cpp holds them (see the file header); path is
# relative to src/ecourna
ECOURNA_SRCS += ../units/12-ecourna-api-sql-sqlite-externs.cpp
# nothing in the skeleton reaches the unit: 12-ecourna-api-sql-sqlite-roots.cpp builds the connection as the target's
# callers do (its header says how), and the class header it includes needs Boost's
$(ROOT)/$(APP)/12-ecourna-api-sql-sqlite-roots.o: $(ROOT)/src/units/12-ecourna-api-sql-sqlite-roots.cpp $(ROOT)/src/Makefile \
    $(ROOT)/src/units/12-ecourna-api-sql-sqlite.mk $(shell find $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -I$(BOOST_HDR) -c src/units/12-ecourna-api-sql-sqlite-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/12-ecourna-api-sql-sqlite-roots.o
