# ecourna CEPESC envelope classes + the ASN.1 key loader (docs/reference/facts/app-flags.md §F2:
# these bodies only reach the target's shape with -fno-strict-aliasing in ECOURNA_CXXFLAGS).
# CKeyLoader::DecipherKeyIfNeeded<EntidadeChave> (9473) calls get_chave() for each end of the range. With a local reference
# to the octet string the object loads its end before its begin, and the target loads begin first: that form scored 49
# over 383 rows (3 inserted, 3 deleted), this one matches. No record covers the statement, so the form is the one these
# bytes choose. Measured in the object to load the end first as well: the local reference with std::begin and std::end,
# with cbegin and cend, with data() and data() + size(), in braces, and declared before cifrado.
ECOURNA_SRCS += api/security/cepesc/cinfosalt.cpp api/security/cepesc/ccipheredout.cpp api/security/cepesc/ccipheredin.cpp \
                api/security/cepesc/cplaintext.cpp api/security/asn1/ckeyloader.cpp
# the units' bodies have no caller in the skeleton yet: 05-ecourna-api-security-cepesc-roots.cpp keeps them the way the target reaches them
# (address-taken / two direct callers of the CInfoSalt ctor); compiled as uenux2 code like src/app/roots_ecourna.cpp
$(ROOT)/$(APP)/05-ecourna-api-security-cepesc-roots.o: $(ROOT)/src/units/05-ecourna-api-security-cepesc-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/05-ecourna-api-security-cepesc-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/05-ecourna-api-security-cepesc-roots.o
