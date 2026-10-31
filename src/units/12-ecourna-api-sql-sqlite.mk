# ecourna::api::sql::sqlite DAO (csqlconnection / csqlresultset / csqlstatement) + the shared sqlite error helper.
# CSqlStatement::Close (fn 9429) and s_mutex's destructor (fn 9431) match. Close keeps sqlite3_finalize's result in a local
# as Reset does. Evidence: with the call in the `if`, wherever the two statements after it sit, clang puts the success
# path after the handler, with one __cxa_free_exception; with the local it comes before, with two, as in 9429 (measured on
# the object). `const int` and `int` give the same rows, and the `const` is chosen, from Reset. s_mutex's name is a vote of
# 9429, which a vtable slot names, and 9431 holds it as the second user.
# (sqlite3.h and boost come from the include dirs src/mk/ecourna-flags.mk adds)
#
# What matches (target fns): CSqlConnection's constructor 3515, D2 5167, D0 9456, BeginTransaction 9455,
# CommitTransaction 9454, RollbackTransaction 9453, Prepare 9460, IsClosed 9457, Close 9458, CheckIntegrity 9452 and
# GetCaminho 5322 (a twin of an RHVoice getter, whose line now carries this name); CSqlStatement's constructor 9430, D2
# 3513, D0 9426, SetInt 5160, SetInt64 9425, SetDouble 9424, SetText 9423, SetBool 9421, SetBlob 9420, SetNull 9419,
# Execute 9417, Reset 9416, IsClosed 9428 and VerifyParameterIndex 1882; CSqlResultSet's constructor 9449, D2 9443, D0
# 9442, the GetInt/GetInt64/GetDouble/GetText/IsNull/GetBool pairs (2679 9441, 5165 9440, 5164 9439, 3514 9438, 5163
# 9435, 9446 9433), GetDateTime(const std::string &) 9434, GetBlob(const std::string &) 9432, Next 9444 and
# VerifyColumnIndex 1883; ObterMensagemErro 9411; the __shared_ptr_pointer control blocks' __get_deleter and
# __on_zero_shared (statement 9450 9451, result set 9412 9413 from the unit's objects; connection 11538 11539 from
# celeitordinamicodao.cpp.o, as the target's copy is a uenux2 caller's: its vtable 1559000 lies in uenux2's data band); the
# externs' Replace 9398; and library code these bodies call: std::map<std::string, int>'s tree members 1677, 2678,
# 9447, std::set<int>'s __find_equal 2676 and string::replace 4667.
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
#   constructor's own code (stores and sqlite3_bind_parameter_count) cannot: std::mutex::lock can, and its code goes
#   once pthread_mutex_lock, a stub in this single-threaded build, is inlined. Without the lock the call is direct and
#   neither 9430 nor 9460 matches. The body places the lock too: 9430 stores m_stmt and then reloads it from +8 for
#   sqlite3_bind_parameter_count, which LLVM does only with an opaque call between the store and the count. Compiled
#   with ecourna's flags, the object of this form (member stores, lock, then the count) reloads `i32.load 2 8` after
#   `call std::mutex::lock`; the base's form (the count in the initializer list, no lock) and the same with the lock in
#   the body both pass the parameter (`local.get 2`). A std::lock_guard, or the count before the lock, does not match
#   in the whole link either (measured by this unit's verification). That Close does not take the lock again is
#   chosen: a second lock there gives the same bytes.
# - GetBlob returns an empty vector before building one when the column has no bytes: the target tests the size
#   before the vector's exception guard is set up.
#
# Choices, each with the forms that give the same object code (`em++` with ecourna's flags, the function's
# disassembly compared): the local's name and type (`const int resultado`; `int`, `const bool ok = ... == SQLITE_OK`
# and an if-initializer give the same bytes); the destructors test `m_fechada`/`m_fechado` (`IsClosed()` gives the same
# bytes) and sit right after the constructors, a place no record gives; GetBlob's `return std::vector<uebyte>();`
# (`return {};` gives the same bytes; `if (tamanho > 0)` around the copy does not).
#
# Not matched, each with what blocks it:
# - CSqlStatement::Close (9429): the scan finds no target name for the file-static std::mutex it unlocks (our .bss
#   `s_mutex`; the target's is at 1911796). Every byte before that operand is the target's. A .bss object gets a name
#   only from a vote of a census-paired function, and the census pairs neither 9429 nor 9431, the mutex's exit-time
#   destructor.
# - CSqlStatement::SetDateTime (9422): its callees boost::date_time's from_day_number (1376) and ymd_to_string are
#   linkonce copies the link takes from src/app/roots_boost.o, which comes first and compiles at -O2 without
#   -fexceptions; the target's 1376 is an -fexceptions copy, and its ymd_to_string has this one caller.
# - CSqlResultSet::GetDateTime (5162): its callee boost::date_time::parse_iso_time<ptime> (5851, 9824 B) is the copy of
#   app/dados/asn/datahoraasn.cpp in our link, a different body (fn 6004, whose folded readout is 290 lines against the target's 1568).
# - CSqlResultSet::GetBlob (5161): the vector's exception guard destructor is the separate 306 in the target, inlined
#   into ours (`call 306 | call 2671`), the blocker of 5111, 9226, 9467, 3521 and 5169 too.
# - CSqlResultSet::StepStatement (5166): no evidence names std::piecewise_construct, a one-byte object the map's
#   operator[] passes (target 463337): content cannot place one byte, and the census pairs no function that loads it.
#   The rest of the body is the target's up to operands (64 rows, all operand-only).
# - The copying ToLower (1879) is a thunk into binaryen's merge 3942 in the target, with fns 1374 and 5156, copying
#   wrappers of other functions not reconstructed (5156 of 3509, a ToUpper-like body); with no partner ours stays a whole
#   body. CSqlResultSet::IndexForColumnName (1525), which calls it, matches since unit 89's comum::CLocal::GetUFMinuscula
#   (3753) is a second holding caller.
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
