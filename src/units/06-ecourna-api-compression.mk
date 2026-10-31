# ecourna api/compression (ICompressor, CZip over zlib/minizip, CLzmaCompress over the 7-Zip wrapper).
# CZip::Close (2691) matches with zlib's deflate chain, which zlib's object order below gives: Close calls minizip's
# zipCloseFileInZipRaw64 (3379), which calls deflate (4826), which calls crc32_z (893), deflate_stored (4825) and
# fill_window (2581).
# CreateZipFile (9543, with ConvertToOpen and minizip's zipOpen64 inlined) is written and has no target name: against ours
# it is 380 rows over 2051, 343 of the 344 replaced operand-only, 15 inserted and 21 deleted, the same with the order
# below as before it. The target pushes `this` for its store of m_zip ahead of c_str() and the inlined code, ours after
# the inlined code, and the inlined minizip code has an `if ... br` where ours has a `br_if`.
# DoAdd (9538) is written and unresolved on std::system_category: 752 rows over 2794, 557 of the 561 replaced
# operand-only, 158 inserted and 33 deleted. Its callees in the target 891 and 1053 pair with libc++'s system_category
# and generic_category (census addr), and each is unresolved on its static's guard (.bss, no target symbol); 3334,
# 3564 and 4679 have no pair, and localtime (6270) is unresolved self-voted.
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
# CZip, so the library must be in the link. Its place on the link line is unknown, so it is appended after RHVoice.
# The flags are conan's zlib defaults. The 35 scan rows whose candidate is a zlib or minizip object of ours all match at
# them. In a small link of zlib, minizip and a driver, -O2, -Os or -O3 without -fPIC adds non-operand rows to bodies
# that -O3 -fPIC gives with operand rows only, and leaving out -D_LARGEFILE64_SOURCE=1 changes none of the 18 scored
# (docs/reference/facts/libraries.md B8).
# minizip's objects link ahead of zlib's, ioapi.o first. Measured: crc32.c defines crc32 as a 14-byte call of crc32_z.
# With crc32.o ahead of zip.o, our link keeps crc32 with crc32_z inlined, its null-buffer return a block result, and 893,
# 4825 and the rest of the chain do not pair. With zip.o ahead, it keeps crc32_z with the target's `if ... return 0`,
# and the chain matches. Evidence: in the target's uses==1 band ioapi.c's functions (8121-8127) sit above zip.c's
# (8117-8119), deflate.c's (8114, 8115) and zutil.c's zcalloc (8112), which reads as ioapi.o, zip.o, deflate.o,
# zutil.o in link order (docs/reference/facts/link-order.md L1), with no decimal-digit boundary inside the group. zlib's
# own objects keep the order they had; trees.o after deflate.o agrees with the uses==2 band (4821-4823 under
# 4824-4827), and the places of adler32.o and crc32.o among them are not measured.
ZLIB_DIR := build/out/zlib/O3pic
ZLIB_CFLAGS := -O3 -fPIC -DNDEBUG -D_LARGEFILE64_SOURCE=1 -Ithird_party/zlib
ZLIB_SRCS := adler32 compress crc32 deflate infback inffast inflate inftrees trees uncompr zutil
ZLIB_OBJS := $(addprefix $(ROOT)/$(ZLIB_DIR)/,minizip_ioapi.o minizip_zip.o $(addsuffix .o,$(ZLIB_SRCS)))
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
