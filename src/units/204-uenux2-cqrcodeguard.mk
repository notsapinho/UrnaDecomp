# uenux2 api::CQRCodeGuard (src/api/gui/cqrcodeguard.h, cqrcodeguard.cpp): its constructor, target fn 5502 (13,815 B),
# into which binaryen inlined libqrencode's QRcode_encodeString and every library function only it calls (unit 187
# compiles the library). Evidence: the record cqrcodeguard.cpp 23:15 gives the .cpp's path, the constructor's signature
# and its throw's line, the CUeGuiError 4947 (EUE_GUI_QRCODEGUARD_FALHA_AO_CRIAR in api/gui/eueguierror.h, its name
# chosen from the message) with the target's literal "Não foi possível criar o QR code" (ledger/strings.tsv 191812,
# 32 bytes, Latin-1). The class's layout, its inline destructor and accessor, and what is chosen are in the header's
# comment; the file's other lines are chosen.
#
# Measured: in the whole link, before steps 7 to 9, pnpm wasm score of 5502 against our constructor read 140 over 7128
# rows, all operand-only (the errno and libqrencode table addresses, and the CBaseError destructor's table slot), and the
# scan matched it by its srcloc-anchor name. The constructor stores 0 at +0 before the call: evidence; that a
# mem-initializer gives it is chosen (a default member initializer or an assignment gives the same store). The target
# then stores the encoder's result there and tests it. The call's arguments, read from
# 5502's body as unit 187's former roots stand-in read them: version 0 and QR_ECLEVEL_L (the 28-byte QRinput 5502
# allocates is stored with 0 at +0 and +4), QR_MODE_8 (no Kanji test is left in 5502 or in Split_eat8, fn 5348, which has
# no hint parameter) and case-sensitive (no copy of the text is upper-cased).
#
# Its callers: the target calls 5502 directly from 10967 (api::CQRCodeImage::GetData, written in unit 79's
# cqrcodeimage.cpp, which differs: unit 79's fragment says why) and 2772 (api::CQRCodeImagePaper::MontaImagem, not
# written), so the roots' w204_dado stands for 2772, the second call site that keeps 5502 out of line. Unit 187's roots
# stand-in for 5502's call of QRcode_encodeString went with this unit. With the guard's destructor in the link, 1254
# (the body binaryen merges BitStream_free and QRcode_free into) is named QRcode_free: unit 187's fragment says why.
CQRCODEGUARD_SRCS := src/api/gui/cqrcodeguard.cpp
UENUX2_SRCS += $(CQRCODEGUARD_SRCS)
# cqrcodeguard.h includes libqrencode's qrencode.h, and UENUX2_CXXFLAGS has no path to it. An include path is not a flag
# of the code (asmlift-wasm/benchmark/README.md "The compile setups").
$(ROOT)/$(APP)/uenux2/$(CQRCODEGUARD_SRCS).o: UENUX2_CXXFLAGS += -Ithird_party/libqrencode
W204_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/204-uenux2-cqrcodeguard-roots.o: $(ROOT)/src/units/204-uenux2-cqrcodeguard-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/204-uenux2-cqrcodeguard.mk $(W204_HDRS) $(ROOT)/third_party/libqrencode/qrencode.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -Ithird_party/libqrencode -c src/units/204-uenux2-cqrcodeguard-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/204-uenux2-cqrcodeguard-roots.o
