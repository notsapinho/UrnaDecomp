# uenux2 api::CBmpConversor::VerticalFlip and InvertColors (target fns 3664 and 3663), the class's two static members,
# in src/uenux2/src/api/gui/cbmpconversor.cpp, the file their std::source_location records name (lines 23 and 27 col
# 15, the CUeGuiError 4900 and 4901 throws; line 60 col 15, the 4903 throw), with the class header
# (api/gui/cbmpconversor.h) and the three enumerators of api/gui/eueguierror.h. Paths relative to src/uenux2; the
# generic uenux2 rule depends on the source and every uenux2 header.
#
# CreateBitmapHeader, the third static member: its record, cbmpconversor.cpp 122:15 (`static std::vector<uebyte>
# api::CBmpConversor::CreateBitmapHeader(const unsigned long, const unsigned long, const unsigned long, const int)`), no
# function loads, and its code is in api::CQRCodeImage::GetData (fn 10967, unit 79, matched), its one caller, behind a
# second prologue: a 1078-byte vector holding a BMP file header, an info header for 8 bits per pixel and a palette of
# 256 grays. binaryen folded the fourth argument, a constant, and with it every test of it, the throw at line 122 among
# them, so the throw's code and message are not in the target's code. Its message is chosen among the target's literals
# no function loads, "Numero de cores nao suportado" (ledger/strings.tsv 137582; docs/reference/facts/reading.md R1), a
# plain message as the frame wants: GetData keeps CreateBitmapHeader's 16-byte frame, a plain message's std::string, and
# ours with this literal keeps the same 16 bytes (a std::format throw's frame is hundreds of bytes, unit 143's
# fragment). Its code, EUE_GUI_CREATEBITMAPHEADER_CORES_NAO_SUPORTADAS 4902, is chosen too (eueguierror.h says why), and
# so is the fourth parameter's role, the number of colours (from the message).
#
# The two tests of numColors. Evidence: the target stores the file header's type (+0) and size (+2) right after the
# vector is built, then the rest of the header from +46 down to +6, and its zero fill of the vector is 1024 bytes from
# +54. Measured (the object of each form, compiled at this tree's flags, and GetData's code in a link of that object with
# a second TU that passes 256, at the build's link flags, -Oz -fexceptions): the stores of one basic block run from the
# highest offset down whatever order the source writes them in (the type and size written last still come last); a
# throw, std::abort() or a return between the size and the rest leaves the fill at 1072 bytes from +6, and a test there
# whose other path only writes or computes leaves it at 1024 from +54 with the target's order. Reading: the target's
# object has a block boundary between the size and the rest, on whose other path nothing reads memory, and binaryen
# folded the test that made it. Written here: the throw tests `numColors <= 0 || numColors > 256`, so that numColors
# stays unknown to clang below it, and after the size `if (numColors < 256)` clears the palette entries from numColors
# on with std::memset; GetData passes 256, so binaryen folds both. Chosen: both conditions and what the second test
# guards. The target holds no code of that path. The clear changes nothing for any input: the vector's
# value-initialization had already zeroed those entries, and the palette loop after it writes all 256. A palette loop
# bounded by numColors, where it would, gives another loop (below). Forms that give the same GetData in that link: the
# first test as `numColors > 256` alone; the second as `numColors != 256`; in place of the std::memset, a loop over the
# entries from numColors to 255 storing 0, the same loop storing white (255, 255, 255, 0), or header.resize to the
# entries in use. Forms that give other code:
#   the throw's test between the size and the rest: the fill is 1072 bytes from +6 in the object, as with std::abort()
#   or a return of the header there; __builtin_trap() there (a probe, not a TSE form) gives the target's stores and fill
#   in the object;
#   the type and size inside `if (numColors == 256)`, or the whole header inside it: the fill is 1078 bytes from +0;
#   the rest of the header in an if/else on numColors, a 24-bit header in the else: the fill is 1072 bytes;
#   a loop computing the bit count from numColors between the size and the rest: the target's order and fill in the
#   object, but binaryen keeps the loop, and the bit count it stores parts +26..+33 into three stores where the target
#   has one 8-byte store;
#   a switch on numColors for the bit count there: binaryen folds it, and the same three stores;
#   a switch on numColors for a shift of the grays, or a division of 256 by numColors for their step, there: clang turns
#   either into straight code, one block, the type and size last;
#   the palette loop bounded by numColors (`i < numColors` with the clear or without it, `i != numColors`, an unsigned
#   counter, a pointer per entry): the unrolled loop keeps a second counter the target's has not.
# Before the two tests, every form measured stored the type and size last, after the info header, from +46 down to +0,
# in one block: the two structs copied from locals with std::memcpy, std::copy or a struct assignment, one packed struct
# of both copied once, the fields written through pointers into the vector, aggregate initialization, the info header
# copied first, the file header written byte by byte, through 32-bit casts or with std::memcpy per field, the type and
# size copied after the rest, header.resize after a default vector, and either parameter order, at -O1, -O2 and -Os and
# with -fno-strict-aliasing or -fexceptions added; GetData scored 52 over 839 rows then (8 rows inserted, 8 deleted:
# those stores; pnpm wasm score at 0c3a9009).
# The rest is read from the bytes. The header's 54 bytes are written field by field, with the constant neighbours merged
# into 8-byte stores: a packed file header whose reserved words are one 32-bit field (two 16-bit fields merge +6..+9 and
# +10..+17 instead of the target's +6..+13 and +14 alone), then the info header. Chosen: writing them through pointers
# into the vector (the type and size are written apart from the rest, so no copy of a whole struct fits, and no other
# spelling, std::memcpy per field or byte writes, was measured with the two tests). The width, height and size are its
# parameters, in the order (size, width, height): GetData then reads the image's size before CQRCodeImage's width at
# the call, as the target does, where (width, height, size) reads the width first. The target's 1078 = 54 + 4 * 256
# and 20000 pixels per meter are its constants. Names chosen: the structs, their fields, the parameters and locals.
CBMPCONVERSOR_SRCS := src/api/gui/cbmpconversor.cpp
UENUX2_SRCS += $(CBMPCONVERSOR_SRCS)
# no roots: the three target functions that call both, 10316, 10451 and 10465 (units 135, 221 and 282), are in the link,
# so the roots file that gave each two call sites went
