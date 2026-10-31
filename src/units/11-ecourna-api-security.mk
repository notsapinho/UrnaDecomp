# ecourna api/security OpenSSL wrappers. The ecourna compile rule has only -Isrc; these TUs include <openssl/*.h>.
ECOURNA_CXXFLAGS += $(OPENSSL_INCLUDES)
ECOURNA_SRCS += api/security/csha.cpp api/security/csiphashmac.cpp api/security/chkdfseed.cpp api/security/ckey.cpp \
    api/security/imacalgorithm.cpp api/security/isymmetriccipher.cpp api/security/caescipher.cpp
# CSha::Reset holds EVP_DigestInit_ex2's result in a named local before testing it: the local's lifetime-end cleanup on the
# throw path gives the landing-pad layout 5177 has, and the call in the condition does not (-Xclang
# -disable-lifetime-markers turns the local form back into the other). The local's name and type are chosen: an int, a
# bool or an if-initializer give the same bytes.
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
#   That the target's copy is another TU's is a reading; which TU is not found.
# - 9495 is 35 over 277 rows, all operand rows but the two `drop`s the target has after its unwind path's calls of fn
#   388, a ~shared_ptr copy whose result one target caller reads (fn 11530, not written); ours drops that result
#   (docs/reference/facts/reading.md R18).
# CHKDFSeed's D2 and D0 (11498, 11497) are code chkdfseed.hpp defines, and match from the roots object (its header).
# At ECOURNA_CXXFLAGS both differ (66 and 68 rows against 56 and 58, the address arithmetic): the target's copies are
# crdv.cpp's, a uenux2 object (their vtable lies among that file's records).
# the units' bodies have no caller in the skeleton yet: 11-ecourna-api-security-roots.cpp address-takes them (same mechanism as 05-ecourna-api-security-cepesc-roots.cpp)
$(ROOT)/$(APP)/11-ecourna-api-security-roots.o: $(ROOT)/src/units/11-ecourna-api-security-roots.cpp $(ROOT)/src/Makefile \
    $(ROOT)/src/units/11-ecourna-api-security.mk $(wildcard $(ROOT)/src/ecourna/api/*.hpp $(ROOT)/src/ecourna/api/security/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/11-ecourna-api-security-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/11-ecourna-api-security-roots.o
