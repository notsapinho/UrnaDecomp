# ecourna api/security OpenSSL wrappers. The ecourna compile rule has only -Isrc; these TUs include <openssl/*.h>.
ECOURNA_CXXFLAGS += $(OPENSSL_INCLUDES)
ECOURNA_SRCS += api/security/csha.cpp api/security/csiphashmac.cpp api/security/chkdfseed.cpp api/security/ckey.cpp \
    api/security/imacalgorithm.cpp api/security/isymmetriccipher.cpp api/security/caescipher.cpp
# csha.cpp is compiled without -fPIC (docs/reference/facts/app-flags.md §F5): its records, vtables and typeinfo sit in the
# target's .rodata, where -fPIC would put them in .data, and CSha::Reset (5177) numbers its locals as the target does only
# without it. The rule is per file only because the other TUs here still build with the tree's base setting.
$(ROOT)/$(APP)/ecourna/api_security_csha.cpp.o: ECOURNA_CXXFLAGS += -fno-PIC
# CSha::Reset holds EVP_DigestInit_ex2's result in a named local before testing it: the local's lifetime-end cleanup on the
# throw path gives the landing-pad layout 5177 has, and the call in the condition does not (-Xclang
# -disable-lifetime-markers turns the local form back into the other). The local's name and type are chosen: an int, a
# bool or an if-initializer give the same bytes.
# the units' bodies have no caller in the skeleton yet: 11-ecourna-api-security-roots.cpp address-takes them (same mechanism as 05-ecourna-api-security-cepesc-roots.cpp)
$(ROOT)/$(APP)/11-ecourna-api-security-roots.o: $(ROOT)/src/units/11-ecourna-api-security-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/11-ecourna-api-security-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/11-ecourna-api-security-roots.o
