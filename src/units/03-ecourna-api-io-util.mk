# ecourna api/io (CFile + CIoError/EFileOperation), api/util (CBitArray, CSynchronizer); header-only units that go
# with them: api/pattern/cbasetype.hpp, api/asn/iconversorasn.hpp, api/io/asn/serialization.hpp.
# cbitarray.cpp includes <boost/dynamic_bitset.hpp>, which ECOURNA_CXXFLAGS alone does not find.
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
