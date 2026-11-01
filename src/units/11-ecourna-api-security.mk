# ecourna api/security OpenSSL wrappers. The ecourna compile rule has only -Isrc; these TUs include <openssl/*.h>.
ECOURNA_CXXFLAGS += $(OPENSSL_INCLUDES)
ECOURNA_SRCS += api/security/csha.cpp api/security/csiphashmac.cpp api/security/chkdfseed.cpp api/security/ckey.cpp \
    api/security/imacalgorithm.cpp api/security/isymmetriccipher.cpp api/security/caescipher.cpp
# CSha::Reset holds EVP_DigestInit_ex2's result in a named local before testing it: the local's lifetime-end cleanup on the
# throw path gives the landing-pad layout 5177 has, and the call in the condition does not (-Xclang
# -disable-lifetime-markers turns the local form back into the other). The local's name and type are chosen: an int, a
# bool or an if-initializer give the same bytes.
# CSha::Finish (3518) holds EVP_DigestFinal_ex's result in a named local the same way. Measured in the link: with the call
# in the condition it is `differs` (59 over 240 rows, 10 inserted and 9 deleted; first at +0x3d, a `block` of the
# target's where ours has `local.get 2`), with the local 33 over 230, all operand rows, and a match. Its name and type are chosen: `const int`, `int`,
# `const auto`, `const bool` and an if-initializer give the same object code for Finish (compiled at ECOURNA_CXXFLAGS,
# its disassembly compared with call and global indices masked), and the call in the condition does not. Its line, 43,
# is one of the two the base left blank before the test (the record is 45:15): chosen.
# CSha512's constructor (2684) holds CSha's inlined, and its call of Reset is direct (invoke_vi through Reset's slot
# 6236): CSha's constructor calls it qualified, `CSha::Reset()`. The unqualified call loads the slot from the vtable
# (lone, try-tu --single: 19 over 112 rows, 3 inserted and 1 deleted; qualified: 16 over 109, operand rows only, and a
# match in the link); -fstrict-vtable-pointers, a flag this tree does not have, gives the same lone rows as the
# qualified call.
# CAesKey's three-argument constructor is declared `inline`: CSymmetricCipherFactory::Create(const std::string&) (1884)
# holds it inlined (the key's 32 bytes copied straight from the digest), and without the keyword clang keeps it out of
# line there (-Rpass-missed=inline: cost 320, threshold 250; with it, cost 320 and threshold 325). Two constructors
# without the default argument are inlined too (object); not compared further.
# CAesCipher (9495, 9494, 9493, 9491; records caescipher.cpp:54, 70, 79, 119) is written and not matched:
# - SetKey compares the key's size before calling EVP_CIPHER_get_key_length, and Encrypt and Decrypt declare their two
#   ints after the buffer: the target reloads the key's bounds for the copy and stores the two ints after the buffer's
#   allocation. Measured in the link: 9494 from 42 over 164 rows to 29 over 161, 9493 from 226 over 858 to 214 over
#   852, 9491 from 238 over 975 to 226 over 969.
# - 9494, 9493 and 9491 call std::vector<uebyte>::__assign_with_size (1681, table slot 6264), which no name reaches:
#   ours is ckey.cpp's copy, which inlines what the target's calls (5493, 3656, 2769): 68 over 162 rows, 47 inserted.
#   Which level keeps those three calls: `std::vector<unsigned char>::assign(unsigned char*, unsigned char*)` alone in a
#   TU, compiled at -O3 with uenux2's and with ecourna's other flags, calls operator new and delete in
#   __assign_with_size; at -Oz -fexceptions, with -fPIC and without, it calls __vdeallocate, __recommend and __vallocate,
#   three calls as the target's 1681 makes them (5493, then 2769 over 3656's result). -O2 (with -fexceptions, and with
#   -fPIC without it) calls operator new and delete as -O3 does, and -Os keeps __vdeallocate and __vallocate but not
#   __recommend. -Oz is the executable TU's level (docs/reference/facts/levels.md V1), so the target's 1681 reads
#   as that TU's copy: a reading, from the first object's linkonce copy winning the link.
# - 9495 is 35 over 277 rows, all operand rows but the two `drop`s the target has after its unwind path's calls of fn
#   388, a ~shared_ptr copy whose result one target caller reads (fn 11530, not written); ours drops that result
#   (docs/reference/facts/reading.md R18). Unit 100's fragment lists 388 among the executable TU's -Oz copies.
# - 9493's and 9491's names reach CBlockCipher's Encrypt and Decrypt (9487, 9485, unit 137) by two hand lines in
#   splat/symbol_addrs.txt (callers+content): each loads the records of its own name that no other target function
#   loads, and each fills one table slot (6284, 6285) whose number only its thunk holds. The generated
#   `table by:9487` and `by:9485` lines are those thunks' own votes, which hold nothing (docs/reference/splat.md
#   "No circular evidence"). Without either hand line its thunk is `unresolved` again, and the splat build passes
#   without that match (a scan, run twice, and splat-build on copies of the symbol file and the match list).
# CHKDFSeed's D2 and D0 (11498, 11497) are code chkdfseed.hpp defines, and match from the roots object (its header).
# At ECOURNA_CXXFLAGS both differ (66 and 68 rows against 56 and 58, the address arithmetic): the target's copies are
# crdv.cpp's, a uenux2 object (their vtable lies among that file's records).
# the units' bodies have no caller in the skeleton yet: 11-ecourna-api-security-roots.cpp address-takes them (same mechanism as 05-ecourna-api-security-cepesc-roots.cpp)
$(ROOT)/$(APP)/11-ecourna-api-security-roots.o: $(ROOT)/src/units/11-ecourna-api-security-roots.cpp $(ROOT)/src/Makefile \
    $(ROOT)/src/units/11-ecourna-api-security.mk $(wildcard $(ROOT)/src/ecourna/api/*.hpp $(ROOT)/src/ecourna/api/security/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/11-ecourna-api-security-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/11-ecourna-api-security-roots.o
