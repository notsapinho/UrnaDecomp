# ecourna api/io (CFile + CIoError/EFileOperation), api/util (CBitArray, CSynchronizer); header-only units that go
# with them: api/pattern/cbasetype.hpp, api/asn/iconversorasn.hpp, api/io/asn/serialization.hpp.
# cbitarray.cpp includes <boost/dynamic_bitset.hpp>, which ECOURNA_CXXFLAGS alone does not find.
# CFile's constructor (fn 517) is out of line in cfile.cpp: its target body has an -fexceptions object's landing pad
# around the call of Open (invoke_iiiii through Open's slot, 6209, and m_nome destroyed inline), and uenux2 callers such
# as api::CEncryptedFile::Save (2767, unit 128) call it, where an inline constructor is inlined into them; compiled in
# fragment 03's roots at APP_CXXFLAGS, it had no landing pad. Its test is `nome != ""`: `!nome.empty()`, `size() > 0`,
# `length() != 0` and an early return each give a select over the two size words where 517 branches (objects compiled at
# ECOURNA_CXXFLAGS and compared). Its place before Open is chosen; no record holds it.
# Open (9508) holds SetFileMode inlined. SetFileMode's throw passes errno: the target loads it (1931660) as the call's fifth
# argument, where the default gives 0. Flush has no index of its own: binaryen inlines it into its one caller, 2767.
# CSynchronizer::Sync is out of line in csynchronizer.cpp. Evidence: CFile::Sync (fn 5181) keeps `if (result i32) ... else
# 0 end` and tests it, which is a callee binaryen inlined; inline in the header, clang folds the two tests into a branch.
# Its place in the file is chosen, after CreateInst's record. `?:` and an `if` give the same rows on the object.
# 5181 is written and `unresolved`, one row from the target: `call 12310`, libc's fsync, where our link inlines fsync.
# Why the target keeps fsync with one direct caller is not known: 12310 is in no table slot and no export, and SQLite's
# sync is fdatasync (3992). And s_instancia needs a second holder (docs/reference/splat.md "No circular evidence"): fn
# 9268, table slot 6618, is f349(p0, 1911988), a static std::unique_ptr's destructor, so the original's static is a
# unique_ptr where csynchronizer.hpp declares a raw pointer. A unique_ptr with reset(new ...) or with operator= gives
# CreateInst's object code the raw pointer gives (one store after operator new, no reload of the old value), so the
# change costs nothing; it is not made while fsync keeps 5181 from matching. CFile::Close (336) matches: its call of
# 5181 has two voters, 336 and 2767.
# CBitArray::GetValor(uebyte) (1375) holds GetValor(ueqword, uebyte) inlined by binaryen and does not match: 192 rows over
# 496 as written (pnpm wasm score, the whole link). Its loop has a 32-bit counter and a 64-bit position stepped apart.
# Measured with try-tu.sh --single, where the as-written body scores the same 192: the bound written as `size() - posicao`,
# zeroed when it exceeds size(), gives the target's select where the ternary gives a branch (189 with the uebyte index
# kept), but a uebyte index added to posicao gives one 64-bit counter; stepping a position of its own (`++pos` in the for,
# `pos++` in the call, 258) gives the target's loop and puts the bounds throw ahead of the loop in the object (wasm-objdump),
# where the target has it after; an int index (279), counting down (257, 227 as a while) and, with ++pos, the bound computed
# before the test, an early return for bits == 0 or `restantes < bits` do not move it. The body stays as it was.
ECOURNA_CXXFLAGS += -I$(BOOST_HDR)
ECOURNA_SRCS += api/io/cfile.cpp
ECOURNA_SRCS += api/io/cioerror.cpp
ECOURNA_SRCS += api/util/cbitarray.cpp
ECOURNA_SRCS += api/util/csynchronizer.cpp
# the units' bodies have no caller in the skeleton yet: 03-ecourna-api-io-util-roots.cpp address-takes the functions the target keeps
# (same mechanism as 06-ecourna-api-compression-roots.cpp; the single-caller functions the target inlines are deliberately not rooted)
$(ROOT)/$(APP)/03-ecourna-api-io-util-roots.o: $(ROOT)/src/units/03-ecourna-api-io-util-roots.cpp $(ROOT)/src/Makefile \
    $(ROOT)/src/units/03-ecourna-api-io-util.mk $(wildcard $(ROOT)/src/ecourna/api/*.hpp $(ROOT)/src/ecourna/api/io/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/03-ecourna-api-io-util-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/03-ecourna-api-io-util-roots.o
