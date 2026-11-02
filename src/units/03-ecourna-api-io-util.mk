# ecourna api/io (CFile + CIoError/EFileOperation), api/util (CBitArray, CSynchronizer); header-only units that go
# with them: api/pattern/cbasetype.hpp, api/asn/iconversorasn.hpp, api/io/asn/serialization.hpp.
# cbitarray.cpp includes <boost/dynamic_bitset.hpp>, which ECOURNA_CXXFLAGS alone does not find.
# CBitArray's D2 and D0 (11417, 11414) are code cbitarray.hpp defines, and match from the roots object, compiled with
# Boost's path too (its header says how): at UENUX2_CXXFLAGS both compare equal, by function with the object-local
# numbers masked; at ECOURNA_CXXFLAGS both differ (55 and 57 rows against 48 and 50, the address arithmetic). The
# target's copies are a uenux2 object's: their vtable lies among app/comum/dados/asn/eleitor/ records.
# The std::make_shared<boost::dynamic_bitset<uebyte>>() in CBitArray's constructor builds a __shared_ptr_emplace block
# whose vptr (vtable @1117736) only fn 5702 stores in the target (not written; it holds the constructor inlined). Its
# D2 and D0 (9409, 9408) match from the roots object: a builder there that the link drops instantiates the block, and
# the vtable's address in the sink stands for 5702's store (src/units/README.md "A control block"); slot 2 holds 5047,
# matched as vector<uebyte>'s block's __on_zero_shared. The two bodies store the vptr and return or
# free: compiled at UENUX2_CXXFLAGS too, the roots object's D2 and D0 give the same rows (wasm-objdump -d, function by
# function, indices masked).
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
# sync is fdatasync (3992). s_instancia is a std::unique_ptr: fn 9268, table slot 6618, is f349(p0, 1911988), the
# reset-and-free body of static unique_ptrs' destructors (CAguardaMensagem::s_inst's among them), and 1911988 is the word
# 5181 tests. A unique_ptr with reset(new ...) or with operator= gives CreateInst's object code the raw pointer gives (one
# store after operator new, no reload of the old value). The static's name waits for 5181 too: an anchor votes for a
# .bss object only when its two bodies are the same opcodes (docs/reference/splat.md section 2), which fsync's row
# breaks, so no vote names 1911988, and the census pairs 9268 at the addr tier with another static's destructor of its
# shape (cpedetitulomesario.cpp.o's), so it stays `differs` with ours, csynchronizer.cpp.o's, in the link. CFile::Close
# (336) matches: its call of 5181 has two voters, 336 and 2767.
# CBitArray::GetValor(uebyte) (1375) holds GetValor(ueqword, uebyte) inlined by binaryen, and matches. The two-argument
# member tests the bound first and throws in the else, after the loop as the target has it; the bound is `size() -
# posicao`, zeroed when it exceeds size(); the loop steps a 64-bit position of its own in the call (`test(pos++)`) under a
# signed int counter that counts down from bits. The form this unit wrote first (a ternary bound, a uebyte index added
# to posicao, the throw ahead of the loop) scored 192 rows over 496 in the whole link (pnpm wasm score). Measured then with
# try-tu.sh --single: the zeroed bound gives the target's select where the ternary gives a branch, and a position of its
# own gives the target's loop, a 32-bit counter and a 64-bit position stepped apart, where an index added to posicao
# gives one 64-bit counter.
# The counter counts down in 32 bits, which the object shows (the two-argument GetValor's code, relocations masked): one
# counting up differs, int or unsigned, and so does an 8-, 16- or 64-bit one counting down. Its signedness is chosen
# (unsigned gives the same code), and so is the order of the two locals ahead of the null test (swapped, or both after
# it: the same code).
ECOURNA_CXXFLAGS += -I$(BOOST_HDR)
ECOURNA_SRCS += api/io/cfile.cpp
ECOURNA_SRCS += api/io/cioerror.cpp
ECOURNA_SRCS += api/util/cbitarray.cpp
ECOURNA_SRCS += api/util/csynchronizer.cpp
# the units' bodies have no caller in the skeleton yet: 03-ecourna-api-io-util-roots.cpp address-takes the functions the target keeps
# (same mechanism as 06-ecourna-api-compression-roots.cpp; the single-caller functions the target inlines are deliberately not rooted)
$(ROOT)/$(APP)/03-ecourna-api-io-util-roots.o: $(ROOT)/src/units/03-ecourna-api-io-util-roots.cpp $(ROOT)/src/Makefile \
    $(ROOT)/src/units/03-ecourna-api-io-util.mk $(wildcard $(ROOT)/src/ecourna/api/*.hpp $(ROOT)/src/ecourna/api/io/*.hpp \
    $(ROOT)/src/ecourna/api/util/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -I$(BOOST_HDR) -c src/units/03-ecourna-api-io-util-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/03-ecourna-api-io-util-roots.o
