# ecourna api/compression (ICompressor, CZip over zlib/minizip, CLzmaCompress over the 7-Zip wrapper).
# CZip::Close (2691) is unresolved on its call of zipCloseFileInZipRaw64, which no name gives a target function: the
# target's is 3379, 14 operand rows over 712 from ours, and splat-remap's one unresolved operand of ours is its call of
# deflate (4826, 29 operand rows over 3256). deflate's are crc32 (893), deflate_stored (4825) and fill_window (2581), which
# no name reaches either; crc32 is 66 rows over 960 with 3 inserted and 2 deleted: the target returns early for a null
# buffer with an `if ... return`, ours with a block result. So CZip waits for zlib's code (ZLIB_CFLAGS are not confirmed,
# below). CreateZipFile (9543, with ConvertToOpen and minizip's zipOpen inlined) is 380 rows over 2051, 15 inserted and 21
# deleted: the target pushes `this` first for its store of m_zip, and the inlined minizip code has an `if ... br` where ours
# has a `br_if`. DoAdd (9538) is unresolved on std::system_category and not looked into.
# The ecourna compile rule has only -Isrc; these TUs include <boost/signals2/...> and <minizip/zip.h> (zlib contrib).
ECOURNA_CXXFLAGS += -I$(BOOST_HDR) -Ithird_party/zlib -Ithird_party/zlib/contrib
ECOURNA_SRCS += api/compression/icompressor.cpp api/compression/clzmacompress.cpp api/compression/lzmasdkstub.cpp
# the ecourna rule turns '_' in a source name into '/': no underscores in unit file names (lzmasdkstub.cpp, not lzmasdk_stub.cpp).
# czip.cpp needs api::io::CFile (api/io/cfile.cpp, in 03-ecourna-api-io-util.mk); it joins the link only once that unit is in ECOURNA_SRCS
# (fragments are read in name order, 03 before 06), so the skeleton link never sees an undefined CFile.
ifneq ($(filter api/io/cfile.cpp,$(ECOURNA_SRCS)),)
ECOURNA_SRCS += api/compression/czip.cpp
endif
# zlib 1.3.1 + minizip (third_party/zlib, contrib/minizip zip.c ioapi.c): the target inlines zipOpen64/zipClose/... into
# CZip, so the library must be in the link. The flags are conan's zlib defaults, not confirmed against the target; its
# link-order slot is unknown, so it is appended after RHVoice.
ZLIB_DIR := build/out/zlib/O3pic
ZLIB_CFLAGS := -O3 -fPIC -DNDEBUG -D_LARGEFILE64_SOURCE=1 -Ithird_party/zlib
ZLIB_SRCS := adler32 compress crc32 deflate infback inffast inflate inftrees trees uncompr zutil
ZLIB_OBJS := $(addprefix $(ROOT)/$(ZLIB_DIR)/,$(addsuffix .o,$(ZLIB_SRCS)) minizip_zip.o minizip_ioapi.o)
$(ROOT)/$(ZLIB_DIR)/minizip_%.o: $(ROOT)/third_party/zlib/contrib/minizip/%.c $(ROOT)/src/units/06-ecourna-api-compression.mk
	$(H) mkdir -p $(ZLIB_DIR) && build/docker-build.sh emcc $(ZLIB_CFLAGS) -c third_party/zlib/contrib/minizip/$*.c -o $(R)
$(ROOT)/$(ZLIB_DIR)/%.o: $(ROOT)/third_party/zlib/%.c $(ROOT)/src/units/06-ecourna-api-compression.mk
	$(H) mkdir -p $(ZLIB_DIR) && build/docker-build.sh emcc $(ZLIB_CFLAGS) -c third_party/zlib/$*.c -o $(R)
RHVOICE_OBJS += $(ZLIB_OBJS)
# the units' bodies have no caller in the skeleton yet: 06-ecourna-api-compression-roots.cpp address-takes them (same mechanism as 11-ecourna-api-security-roots.cpp;
# `override` keeps it when try-tu.sh passes EXTRA_OBJS on the make command line)
$(ROOT)/$(APP)/06-ecourna-api-compression-roots.o: $(ROOT)/src/units/06-ecourna-api-compression-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/06-ecourna-api-compression-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/06-ecourna-api-compression-roots.o
