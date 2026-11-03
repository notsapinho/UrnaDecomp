# ecourna api/compression (ICompressor, CZip over zlib/minizip, CLzmaCompress over the 7-Zip wrapper).
# CZip::Close (2691) matches with zlib's deflate chain, which zlib's object order below gives: Close calls minizip's
# zipCloseFileInZipRaw64 (3379), which calls deflate (4826), which calls crc32_z (893), deflate_stored (4825) and
# fill_window (2581).
# CZip's constructor (5193) is defined in czip.cpp, after ConvertToErrorMessage, a line chosen: the target calls it from
# comum::CGravadorWSQ::CompactaWsq (5821, unit 122) twice, and defined in czip.hpp clang inlined it there (both links
# measured before step 8). Its band, 5194 (clzmacompress.cpp's), 5193, 5192 (icompressor.cpp's), puts it in czip.cpp.o.
# It stores CZip's vptr after ICompressor's constructor (5192), copies the path's string to +16, stores 0, the level
# and 0 at +36, +32 and +28 and invokes CreateZipFile through table slot 6119; every row is operand-only and it
# matches by content (the scan's content pass finds it: its depth-0 shape is the only one on both sides; a
# vptr+shape hand line that named it carried no row, measured, and went).
# CZip's destructor is declared in czip.hpp and defined in czip.cpp after Close: CompactaWsq calls its D2 (2690) out of
# line, twice. Defined in the class, clang inlined it there (-Rpass=inline: cost 110 against 250; 170 with
# ICompressor's destructor inline in its header, still inlined), and 5821 then held the D2's code where the target
# calls 2690. Out of line, 2690 and the D0 (9540) still match from this object (the D0 holds the D2's code; measured:
# 9540 matches from this object with the destructor out of line). Its line after Close is a choice the
# use bands allow: in czip.cpp.o Close (2691) comes before the D2 (2690) in band 4 and the D0 (9540) between
# CreateZipFile (9543) and ConvertToCompressLevel (9539) in band 1, as the index order asks (docs/how-to-decompile.md
# step 3, "The order of two members"); defined right after the constructor, the D2 came before Close.
# CreateZipFile (9543, with ConvertToOpen and minizip's zipOpen64 inlined) matches since the constructor that invokes it
# is in this object; before, its only reference was the roots' address and it was 380 rows over 2051 against the
# target (343 of the 344 replaced operand-only, 15 inserted and 21 deleted: `this` pushed for the store of m_zip
# ahead of c_str() in the target, after the inlined code in ours, and an `if ... br` where ours had a `br_if`). What
# in the object took that difference away was not compared.
# ICompressor's constructor (5192) matches, with boost's shared_count::~shared_count (2203) out of line. clang keeps
# that call in this object (-Rpass-missed=inline: cost 90, threshold 45); at 5e41daca our link held no body of it
# (names.tsv), binaryen having inlined it into 5192 (a reading). Its other target callers, 9536 (signal_impl's
# constructor, table slot 6135, which 5192
# invokes), 9558 and 9521, each with landing pads, are the app signal's -fexceptions copies, which this unit's objects
# give since the tree root src/app/roots_boost.cpp (the Boost probe at APP_CXXFLAGS, no landing pads, ahead of both
# trees) declares three of the signal's templates extern: signal_impl's constructor, make_shared of an invocation_state
# from a copy and the connection list, and operator(). The link then takes icompressor.cpp.o's constructor (9536) with
# make_shared over a new list (9527) and invocation_state's constructor (9521), and clzmacompress.cpp.o's operator()
# (9583) and make_shared from a copy (9558). Measured on whole links (steps 6 to 9, gains and losses by index against
# 5e41daca, with every other line of the root in place), each line left out alone: without the constructor's, 6156 9520
# 9521 9526 9527 9536 9549 9551 9553 9554 9555 9557 9558 do not match; without make_shared's, 9521 9549 9551 9553 9554
# 9555 9557 9558; without operator()'s, 2204 5203 5204 9564 9576; 5192 and 2203 match in each, no line loses a row of
# the base, and with none of them (5e41daca) 5192 is unresolved (90 over 155 rows, 68 inserted: ~shared_count inlined
# in its landing pad). operator() (9583, ours from clzmacompress.cpp.o)
# scores 59 over 683 rows, all operand-only, and reads unresolved on the table slot of slot_call_iterator_t's
# lock_next_callable (9578, no candidate: ours scores 198 over 810 rows, 130 inserted), so CZip's and CLzmaCompress's
# AtualizaProgresso (9537, 9585), which invoke operator(), read unresolved on its slot. The rtti-vptr hand line that
# named 5192 for 5193's call (the only target function that holds ICompressor's vtable address point) went: with 5192
# matched, a generated `call` line names it, and without the hand line steps 8 to 10 move no scan row and build the
# target's sha256 with every match.
# ICompressor::Add(const std::filesystem::path&) and globToFileList (record icompressor.cpp:61) are in the link inside
# 5821, where binaryen inlines Add; with them come libc++'s std::regex members this object instantiates (9534, the
# constructor from a std::string, and 3526, 5187, 9518), vector<path>'s __init_with_size and slow push_back (9531,
# 9516), and libc++.a's directory_iterator.o and operations.o rows the iterators reach (unit 122's fragment lists the
# matches). globToFileList's lambda, `$_0::operator()` (9532, out of line: both loops invoke it through table slot
# 6145, its two captures passed as parameters: a reading, clang's argument promotion), matches: it copies the entry's
# path before it asks is_regular_file, as the target's 9532 does (its first rows copy the string at +0; with the test
# first, as written before, it scored 104 over 388 rows). `&&` or a nested `if` for the two tests, and the copy `const`
# or `auto`, give the same object; a reference for the copy gives another (the object compared at its compile line).
# The rest is read from the rows of 5821, which hold Add and
# globToFileList inlined:
# Add calls Add(const std::vector<path>&) once on globToFileList's result (one invoke of slot 6151 with the vector at
# +12, after the regex and the two paths are destroyed); the message of the throw builds on caminho (a copy of +128),
# not on the argument; the "/*" suffix is a std::filesystem::path whose string() endsWith takes, after caminho's
# string() (the copies at +96, then +24 and +80, destroyed in the reverse order); and endsWith is a size test and one
# memcmp of the tail, which std::string::ends_with gives (5821 scored 648 over 4036 rows with compare(), 508 over 3946
# with ends_with). That ends_with is called in a helper, its parameters' types, the lambda's and the helper's names are
# chosen; endsWith over (const std::string&, const std::filesystem::path&), calling string() inside, is another form
# the order of the copies allows, not measured. 5821's remaining rows are unit 122's fragment's. This
# object gives the link's std::regex members over std::string (9534, 5187, 5191 match from it): a tree
# root at these flags, src/app/roots_regex.cpp, gave them first while 5821 was not in the link, and went with it.
# The census pairs 9534 with this object's copy by `addr` (with that root's by `shape`, which named it not), and
# 9518 has a name by `table`; it is `unresolved` on its callee 3526 (__parse_basic_reg_exp), which has none: 9518 is
# 3526's one target caller (ledger/callgraph.tsv), so only 9518's own call would name it, and 5189, 2689 and 2688
# below them wait the same way. No vptr anchors 9518 either: the target's const char* and __wrap_iter parsers
# (2062, 9518) both hold __end_state<char>'s vptr (1535228) and four other regex vptrs, and with
# src/app/roots_cbasetype.cpp's copy matching 2062 each forms a same-shape pair with ours (pnpm wasm fingerprint
# --depth 0), so the vptr anchors nothing (docs/reference/splat.md, `vptr-anchor`).
# DoAdd (9538) is written and unresolved on std::system_category: 582 rows over 2643, the 561 replaced all
# operand-only, 7 inserted and 14 deleted, measured after unit 206 gave CFile's destructor the catch DoAdd holds
# inlined. Its callees in the target 891 and 1053 pair with libc++'s system_category
# and generic_category (census addr), and each is unresolved on its static's guard (.bss, no target symbol); 3564
# (CFile's destructor, out of line) matches since unit 206 (3334, libc++'s posix_stat, matches too), 4679 (ErrorHandler<unsigned long long>::report) matches since unit
# 261's stand-in gives it its second caller, and localtime (6270) and generic_category (1053) are unresolved
# self-voted on a .bss word that only each reads in the target (localtime's buffer 1932496, generic_category's guard
# 1926460: grep of the split's pieces), which no hand line may name (docs/reference/splat.md section 3, "No circular
# evidence"). DoAdd now reads `unresolved` on the table slot of CZip::AtualizaProgresso, which no symbol line names
# (9537 pairs with it by the census and is unresolved, on operator()'s slot: above).
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
# Two whole-link orders were measured. With zlib's objects first and then zip.o and ioapi.o, the order this fragment
# had, our link keeps crc32 with crc32_z inlined, its null-buffer return a block result, and 893, 4825 and the rest of
# the chain do not pair. With ioapi.o and zip.o first, it keeps crc32_z with the target's `if ... return 0`, and the
# chain matches. Between the two, zip.o moves past every zlib object, deflate.o and trees.o as well as crc32.o, so
# which object's place decides is not measured. Evidence: in the target's uses==1 band ioapi.c's functions (8121-8127)
# sit above zip.c's (8117-8119), deflate.c's (8114, 8115) and zutil.c's zcalloc (8112), which reads as ioapi.o, zip.o,
# deflate.o, zutil.o in link order (docs/reference/facts/link-order.md L1), with no decimal-digit boundary inside the
# group: it sits in a tight run of the band, which a split across a boundary would put far apart. zlib's
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
