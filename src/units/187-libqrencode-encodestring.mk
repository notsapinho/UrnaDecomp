# libqrencode 4.1.1 (third_party/libqrencode; docs/reference/facts/libraries.md B10), the QR encoder whose one caller in
# the target is fn 5502 (stub in api/gui/cqrcodeguard.cpp). No TSE source: the library's nine objects, compiled here as
# fragment 06 compiles zlib's, and a roots file that stands for 5502's call of QRcode_encodeString.
#
# Matched, 17 library functions binaryen keeps out of line, each a census pair of our function of that name: 493
# BitStream_appendNum, 1147 QRspec_lengthIndicator, 1253 MMask_writeFormatInformation, 1254 BitStream_free, 1534
# QRinput_estimateBitsMode8, 1899 QRinput_estimateBitsModeAn, 2719 QRinput_estimateBitsModeNum, 3596
# QRinput_List_newEntry, 3597 QRinput_append, 5346 MQRspec_getWidth, 5347 MQRspec_getDataLengthBit, 5348 Split_eat8, 5349
# QRspec_getMinimumVersion, 5350 BitStream_appendBytes, 5351 QRinput_getByteStream, 5352 QRinput_isSplittableMode and
# 10241 MQRspec_getECCLength. The eleven tables they and 5502 read (QRinput_anTable, qrspec.o's and mqrspec.o's) hold the
# target's bytes at the addresses step 8 names them at (B10). 1254 is the body binaryen merges BitStream_free and
# QRcode_free into: the target's 2772 and 10967 call it as QRcode_free, which nothing in our link calls yet, so the
# line names BitStream_free. Once a caller of QRcode_free lands, binaryen may keep qrencode.o's copy instead, as the
# probe does (its driver calls QRcode_free, it links qrencode.o first, and it names the body QRcode_free), and step 9
# would then rename the line.
#
# What waits, and for what:
# - 2218 MQRspec_lengthIndicator, 2718 QRinput_encodeBitStream and 3595 RSECC_encode are `unresolved` on an operand that
#   is an array's base with a constant index folded in: lengthTableBits[mode][version - 1] reads mqrspec.o's
#   lengthTableBits from 4 bytes before the array (2218, and 2718, which inlines MQRspec_maximumWords), and
#   generatorInitialized[length - 2] reads from 2 bytes before that array (3595). Both places are padding, in our link and
#   in the target, and the scan places an address only through the data object that holds it ("is in no data object of
#   ours"). Against the target their bodies differ in operands alone: 1 over 12, 10 over 765 and 30 over 548 rows, every
#   one operand-only (pnpm wasm score at depth 0).
# - 3595's generator[length - 2] is generator - 62, before the array: in our link 2 bytes into RSECC_mutex, in the target
#   6 bytes into the 24 bytes before `initialized` that no target function reads, so step 8 names RSECC_mutex by 3595's
#   vote at 0x1d2510, 4 bytes past where rsecc.o's order puts it. No other operand reads that place.
# - 5502 itself, api::CQRCodeGuard's (13,815 B), into which binaryen inlined every library function with one call site.
#
# Evidence and measurements, with their commands in B10:
# - The version. 4.1.1 is the repository's last tag, and its default branch's head. Of the probes of 4.0.0, 4.0.2,
#   4.1.0 and 4.1.1 (tools/libs/libqrencode/build.sh, score.sh), 4.1.1's leaves the fewest rows differing: 2718 10 over 765
#   against 46, 60 and 60, and 5351 5 over 857 against 40, 188 and 200. 4.1.1 changed only qrinput.c: the Micro QR path of
#   QRinput_estimateBitStreamSizeOfEntry calls MQRspec_lengthIndicator, and the target's 5351 calls 2218.
# - The flags. CMakeLists.txt's own defines (the version, HAVE_SDL=0, STATIC_IN_RELEASE=static) with -O3 -fPIC -DNDEBUG
#   and HAVE_LIBPTHREAD=1, each measured on the probe against the target: -O2 gives 2718 203 over 893 and inlines 3596,
#   -Os and -Oz more; without -fPIC 1147, 1253, 2718, 3595, 3596, 5349, 5351 and 10241 gain rows inserted or deleted;
#   without HAVE_LIBPTHREAD 3595 is 186 over 560 (with it, 30 over 548, and no call is left of the mutex's lock and
#   unlock, as in the target).
# - The order, where the target reads it. A band lists its functions in reverse link order
#   (docs/reference/facts/link-order.md L1), so in link order the uses==2 band reads 5352 and 5351 (qrinput.o), 5350
#   (bitstream.o), 5349 (qrspec.o), 5348 (split.o), then 5347 and 5346 (mqrspec.o); the uses==3 band 3597 and 3596
#   (qrinput.o), then 3595 (rsecc.o); the uses==10 band 1254, then 1253 (mmask.o), so mmask.o links after the object
#   1254's merged body comes from (bitstream.o, or qrencode.o). The target's .rodata holds qrinput.o's, qrspec.o's and
#   mqrspec.o's tables in that order (QRinput_anTable 0x85c30, qrspecCapacity 0x85cb0, mqrspecCapacity 0x868e0; data
#   order is link order, link-order.md L7 item 15). The rest of the order is chosen (below).
# - The place. The target's bands and .bss put the library among uenux2's api objects (after api/ipc/cthread.cpp and
#   api/ipc/posix/, before api/audio/alsa/cwavfile.cpp), where LINK_OBJS has no slot; it goes after RHVoice and zlib, as
#   fragment 06 puts zlib. The companions' slot was measured too: with `override EXTRA_OBJS += $(QRENCODE_OBJS)` in
#   place of the RHVOICE_OBJS line below (the objects between unit 17's roots and this unit's on the link line),
#   make -C src link, census, splat-symbols and splat-match printed 10539 matches, 17 added and 0 renamed: the same 17
#   as here, line for line, so none left; there our .bss puts generator - 62 in unit 17's roots sink, which step 8 names at the target's 0x1d2510.
# - The roots. In the whole link binaryen's dead-argument pass folds 5502's constants down to Split_eat8, as in the
#   target, whose 5348 has no hint parameter; the probe keeps it (117 over 315 rows there, 3 over 224 operand-only rows
#   in the link).
#
# Chosen: -DHAVE_STRDUP=1, CMake's configure result under emscripten, and strict aliasing, CMake's default: neither moves
# any of the 20 rows. The version macros and HAVE_SDL=0, which only functions the link drops read. The stand-in's name.
# The order where the target does not read it, CMakeLists.txt's list of sources: qrencode.o first and mask.o between
# split.o and mqrspec.o, which nothing in the target places (neither keeps a function out of line in our link,
# build/out/wasm-map/vota_web/names.tsv after make -C src link-map; mask.o has no data and qrencode.o only its version
# string; in the target qrencode.o may hold 1254's merged body), rsecc.o between qrspec.o and split.o (the band puts it
# after qrinput.o only) and mmask.o last (after 1254's object only).
QRENCODE_DIR := build/out/libqrencode/4.1.1-O3pic
QRENCODE_CFLAGS := -O3 -fPIC -DNDEBUG -DHAVE_LIBPTHREAD=1 -DHAVE_STRDUP=1 -DMAJOR_VERSION=4 -DMINOR_VERSION=1 -DMICRO_VERSION=1 \
                   '-DVERSION="4.1.1"' -DHAVE_SDL=0 -DSTATIC_IN_RELEASE=static -Ithird_party/libqrencode
QRENCODE_SRCS := qrencode qrinput bitstream qrspec rsecc split mask mqrspec mmask
QRENCODE_OBJS := $(addprefix $(ROOT)/$(QRENCODE_DIR)/,$(addsuffix .o,$(QRENCODE_SRCS)))
$(ROOT)/$(QRENCODE_DIR)/%.o: $(ROOT)/third_party/libqrencode/%.c $(wildcard $(ROOT)/third_party/libqrencode/*.h) $(ROOT)/src/units/187-libqrencode-encodestring.mk
	$(H) mkdir -p $(QRENCODE_DIR) && build/docker-build.sh emcc $(QRENCODE_CFLAGS) -c third_party/libqrencode/$*.c -o $(R)
RHVOICE_OBJS += $(QRENCODE_OBJS)
# the roots include the library's header, qrencode.h, for QRcode_encodeString and the enums
$(ROOT)/$(APP)/187-libqrencode-encodestring-roots.o: $(ROOT)/src/units/187-libqrencode-encodestring-roots.cpp $(ROOT)/third_party/libqrencode/qrencode.h $(ROOT)/src/Makefile $(ROOT)/src/units/187-libqrencode-encodestring.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -Ithird_party/libqrencode -c src/units/187-libqrencode-encodestring-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/187-libqrencode-encodestring-roots.o
