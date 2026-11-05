# uenux2 api::CBmpConversor::VerticalFlip and InvertColors (target fns 3664 and 3663), the class's two static members,
# in src/uenux2/src/api/gui/cbmpconversor.cpp, the file their std::source_location records name (lines 23 and 27 col
# 15, the CUeGuiError 4900 and 4901 throws; line 60 col 15, the 4903 throw), with the class header
# (api/gui/cbmpconversor.h) and the three enumerators of api/gui/eueguierror.h. Paths relative to src/uenux2; the
# generic uenux2 rule depends on the source and every uenux2 header.
#
# CreateBitmapHeader, the third static member: its record, cbmpconversor.cpp 122:15 (`static std::vector<uebyte>
# api::CBmpConversor::CreateBitmapHeader(const unsigned long, const unsigned long, const unsigned long, const int)`), no
# function loads, and its code is in api::CQRCodeImage::GetData (fn 10967, unit 79), its one caller, behind a second
# prologue: a 1078-byte vector holding a BMP file header, an info header for 8 bits per pixel and a palette of 256 grays.
# binaryen folded the fourth argument, a constant, and with it the test and the throw at line 122, so the throw's code
# and message are not in the target's code. Its message is chosen among the target's literals no function loads,
# "Numero de cores nao suportado" (ledger/strings.tsv 137582; docs/reference/facts/reading.md R1), a plain message as the
# frame wants: GetData keeps CreateBitmapHeader's 16-byte frame, a plain message's std::string, and ours with this
# literal keeps the same 16 bytes (a std::format throw's frame is hundreds of bytes, unit 143's fragment). Its code,
# EUE_GUI_CREATEBITMAPHEADER_CORES_NAO_SUPORTADAS 4902, is chosen too (eueguierror.h says why). That the fourth parameter is the number
# of colours (from the message) and the test `!= 256` are chosen: with it as the bits per pixel, tested against 8 and the
# header built from it, the object's stores are the same (the stores' kinds and offsets in a compile of each). The rest is
# read from the bytes. The header's 54 bytes are written field by field, with the constant neighbours merged into 8-byte
# stores: a packed file header whose reserved words are one 32-bit field (two 16-bit fields merge +6..+9 and +10..+17
# instead of the target's +6..+13 and +14 alone), then the info header, each copied into the vector from a local struct.
# The width, height and size are its parameters, in the order (size, width, height): GetData then reads the image's size
# before CQRCodeImage's width at the call, as the target does, where (width, height, size) reads the width first. The
# target's 1078 = 54 + 4 * 256 and 20000 pixels per meter are its constants.
# Not explained: the target stores the file header's type (+0) and size (+2) right after the vector is built, ahead of
# the rest; every form measured stores them last, after the info header, from +46 down (the order of the stores in the
# object, each compiled with this tree's flags): the two structs copied with std::memcpy, std::copy or a struct
# assignment, the fields written through pointers into the vector, aggregate initialization, the info header copied
# first, the file header written byte by byte, through 32-bit casts or with std::memcpy per field, header.resize after a
# default vector, and either parameter order. The test written between the first two fields and the rest stores those two
# first, but leaves the vector's zero fill at 1072 bytes, where the target's is 1024 from +54 (a reading: a fill trimmed
# so needs all 54 header bytes written on every path after it). So GetData differs by those 8 rows (unit 79's
# fragment). Names chosen: the structs, their fields, the parameters and locals.
CBMPCONVERSOR_SRCS := src/api/gui/cbmpconversor.cpp
UENUX2_SRCS += $(CBMPCONVERSOR_SRCS)
# no roots: the three target functions that call both, 10316, 10451 and 10465 (units 135, 221 and 282), are in the link,
# so the roots file that gave each two call sites went
