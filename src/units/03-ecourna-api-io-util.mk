# ecourna api/io (CFile + CIoError/EFileOperation), api/util (CBitArray, CSynchronizer); header-only units that go
# with them: api/pattern/cbasetype.hpp, api/asn/iconversorasn.hpp, api/io/asn/serialization.hpp.
# cbitarray.cpp includes <boost/dynamic_bitset.hpp>, which ECOURNA_CXXFLAGS alone does not find.
# CSynchronizer::Sync is out of line in csynchronizer.cpp. Evidence: CFile::Sync (fn 5181) keeps `if (result i32) ... else
# 0 end` and tests it, which is a callee binaryen inlined; inline in the header, clang folds the two tests into a branch.
# Its place in the file is chosen, after CreateInst's record. `?:` and an `if` give the same rows on the object.
# 5181 is written and `unresolved`, one row from the target: `call 12310`, libc's fsync, where our link inlines fsync.
# Why the target keeps fsync with one direct caller is not known: 12310 is in no table slot and no export, and SQLite's
# sync is fdatasync (3992). And s_instancia needs a second holder (docs/reference/splat.md "No circular evidence"): fn
# 9268, table slot 6618, is f349(p0, 1911988), a static std::unique_ptr's destructor, so the original's static is a
# unique_ptr where csynchronizer.hpp declares a raw pointer. That is read from 9268, not measured. CFile::Close (fn 336)
# waits for 5181.
ECOURNA_CXXFLAGS += -I$(BOOST_HDR)
ECOURNA_SRCS += api/io/cfile.cpp
ECOURNA_SRCS += api/io/cioerror.cpp
ECOURNA_SRCS += api/util/cbitarray.cpp
ECOURNA_SRCS += api/util/csynchronizer.cpp
# the units' bodies have no caller in the skeleton yet: 03-ecourna-api-io-util-roots.cpp address-takes the functions the target keeps
# (same mechanism as 06-ecourna-api-compression-roots.cpp; the single-caller functions the target inlines are deliberately not rooted)
$(ROOT)/$(APP)/03-ecourna-api-io-util-roots.o: $(ROOT)/src/units/03-ecourna-api-io-util-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/03-ecourna-api-io-util-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/03-ecourna-api-io-util-roots.o
