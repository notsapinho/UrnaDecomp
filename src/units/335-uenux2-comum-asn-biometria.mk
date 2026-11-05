# uenux2 comum's biometry converters, their own slots (paths relative to src/uenux2, beside the .cpp each class's
# records name, headers landed with unit 159): comum::asn::CConversorDedo::DoDesconverte (target fn 11416,
# app/comum/dados/asn/eleitor/cconversordedo.cpp, records :159 and :169), CConversorBiometriaEleitor::DoDesconverte
# (11422, cconversorbiometriaeleitor.cpp, record :26) and CConversorBiometriaEleitorCifrada::DoDesconverte (11419,
# cconversorbiometriaeleitorcifrada.cpp, records :91, :101 and :109 of its LeChave); with what they hold or call:
# CConversorDedo's static DesconverteTipo (record :159), comum::md::CDedo's constructor (md/eleitor/cdedo.cpp, records
# :28 and :33), the minutiae decoder fn 5702 (comum::asn::DesconverteMinucias, cconversordedo.cpp) and the class it
# builds, comum::asn::CMinuciasCompactadas (asn/eleitor/cminuciascompactadas.{h,cpp}), and the cifrada converter's
# Decifra and LeChave. Its other new code is in landed units' files: CBiometriaEleitor's three constructors in unit
# 91's md/eleitor/cbiometriaeleitor.cpp and ecourna's CBitArray(const std::vector<uebyte>&) in unit 03's
# api/util/cbitarray.cpp (those fragments' paragraphs).
#
# Matched (steps 7 to 9 on this link): 11416, 11422, 11419, 5702; libm's log2 (2972, libc_optz.a(log2_small.o), no
# source of ours), which 5702 calls twice; libc++'s std::filesystem::path::string() const (1555), this TU's instance,
# which LeChave's two throws call; and SQLite's logFunc (12450), log2's other caller in our link. The census paired
# 2972 and 12450 with nothing at the base (ledger/functions.tsv at 64134702): that binaryen inlined log2 into logFunc,
# its one caller there, and keeps it out of line now that 5702 gives it two more call sites, is a reading. Before step
# 8 each member scored operand rows only (pnpm wasm score in this link): 11416 60 over 748, 5702 54 over 1256, 11422
# 67 over 1245, 11419 246 over 2574 (calls, data addresses, packed std::format strings, table slots, __THREW__). 11416
# and 5702 match together: 11416 alone named 5702 (evidence:call by:11416), and the scan read 11416 `unresolved
# self-voted` while 5702 differed.
#
# What the target shows: each member holds out-of-line functions binaryen inlined into it, each behind a prologue of
# its own where it has a frame (docs/how-to-decompile.md step 3):
# - 11416: DesconverteTipo (480 bytes; the throw's code 7896) and CDedo's constructor (528 bytes, codes 8061 and
#   8062), between two calls of 5702 (one for the count test, record :169, code 7897; one for the CDedo it builds).
# - 5702 (112 bytes, no record): the bytes of the Dedo's minucias, CBitArray's constructor from them (ecourna code:
#   its landing pad destroys the bit array's members, invoke_v and invoke_ii around vector::at and the bitset's
#   growth), five GetValor fields and the groups of 9 and 8 bits with their points, then CMinuciasCompactadas's
#   constructor (36 bytes at +8, a block whose result is the constructed object) with Descompacta in it, and the copy
#   of its minutiae.
# - 11422: three CBiometriaEleitor constructors (with the photo and the fingers and with the fingers only behind
#   32-byte frames, the temporary map they move into the optional destroyed by fn 781 there; with the photo only,
#   frameless) and IConversorASN<Dedo, CDedo>::Desconverte (640 bytes), the CConversorDedo whose vptr it stores
#   (1566488) built on its stack; and a ModuloEleitores::BiometriaEleitor::dedos::value_type built and destroyed at +8
#   that nothing reads (SEQUENCE_OF_Base's constructor, fn 516, its Dedo default argument, the vptrs 1566184 and
#   1566056): written as an unused local, `listaDedos`, a reading.
# - 11419 (144 bytes): Decifra (128), LeChave in it (176: the key file "bio.sk1" under CPath::GetPathChave, its
#   existence, the EntidadeChave read through DeserializeFromFile, the HSM's password through
#   CPolySingleton<IKernelHSM>::instance, record :101 column 40, the factory's cipher and its Decrypt), ecourna's
#   CCipheredIn constructor (80 bytes, landing pads, records ccipheredin.cpp:79, :82 and :85), then CFileASN's
#   DecodeObject (32) and DecodeObjectFunction (736, records cfileasn.h:135 and :143) and IConversorASN's Desconverte
#   (640, record :71) over a CConversorBiometriaEleitor it builds (vptr 1566000).
# Placement: CBitArray's vtable (@1566524), which 5702's inlined destructor stores, lies right after CConversorDedo's
# (@1566480) in cconversordedo.cpp's run of the data, before its default DoConverte's record (@1566548), so 5702 is
# that file's code (a reading); the data put the asn/eleitor files in name order (cconversorbiometriaeleitor.cpp,
# ...cifrada.cpp, cconversordedo.cpp, cconversorentidadeeleitores.cpp, cconversorimpedido.cpp, ledger/vtables.json and
# ledger/source-locations.tsv), and our link puts these objects after unit 310's (fragment order); no other order of
# the objects was tried.
#
# Measured forms (pnpm wasm score of the member against the target in this link, or in a link of the plain link's own
# command with one object swapped, docs/reference/facts/workflow.md W13):
# - 5702: CMinuciasCompactadas's constructor and Descompacta in cconversordedo.cpp, 637 over 1382 rows: the object's
#   call of the constructor (the C1, an alias of the C2 this TU defines) drops its result. In a TU of their own, with
#   each point copied by value and a 32-bit inner counter: 211 over 1296; the pair a struct (std::pair's copy is a
#   loop, the target copies the list with memcpy) and no test of an empty list: 68 over 1259; the group count reset
#   before the minima and the X width computed before the Y width: 54 over 1256, every row an operand. Uninitialized
#   widths set in a test of the empty list instead: 111 over 1277. The bytes assigned from the OCTET_STRING's own
#   iterators call the __wrap_iter instance (roots_vector.o's, fn 1158), and the scan read `differs` (`target call
#   5496 | ours call 1158`); from `const uebyte*` they call 5496, the executable TU's copy; the pointer taken before
#   the vector's declaration scored 61 over 1260, after it 54.
# - 11419: unit 05's roots address-took CCipheredIn's constructor, which kept it out of line: 1067 over 2595 rows;
#   that root goes (its one target caller is 11419), 470 over 2603. The session key copied by the range constructor
#   (its loads come before the vector's stores in the target) and the password vector declared in the singleton's
#   statement: 448 over 2594. The order of the three members in the file, the records' lines fixed: LeChave, Decifra,
#   DoDesconverte 448; Decifra, DoDesconverte, LeChave 448; LeChave, DoDesconverte, Decifra 409 over 2592;
#   DoDesconverte, Decifra, LeChave 246 over 2574, every row an operand (the written order).
# - 11416 and 11422 scored operand rows only as first written.
#
# Chosen, no evidence names them: 5702's name, its being a free function of comum::asn (it reads no class state:
# docs/how-to-decompile.md step 3, the member rule), its external linkage and its place at the head of
# cconversordedo.cpp; CMinuciasCompactadas, SPar, their members, Descompacta (and its being a member), GetMinucias and
# their file; Decifra (name, being a member, the order of its parameters); DesconverteTipo's and LeChave's being
# private and DesconverteTipo's ten cases (CDedo::TipoDedo has no enumerators: the casts); the limit 200 as a literal
# in CDedo's constructor; every local's name, `listaDedos` among them; and every line but the records'. The layout of
# line 101 is chosen too: the record fixes the call's column.
#
# The stand-ins this unit's members ended went with it: unit 03's CBitArray roots, unit 91's CriaComum pair, unit 137's
# vtable sinks for CSymmetricCipherFactory and CCepescCipher, whose vptrs 11419 stores (unit 137's roots file with
# them), and src/app/roots_iconversorasn.cpp's Foto pair for 11422; a link without them moves no row. Unit 05's root of
# CCipheredIn's constructor went: 11419's match needs it gone.
# DeserializeFromFile<ModuloEnvelopeChave::EntidadeChave> (2280), CPolySingleton<api::IKernelHSM>::instance (2279) and
# std::filesystem::path::string() (1555) match from unit 293's ccontrolaarmazenamentodeimagens.cpp.o, which instantiates
# them too and links ahead of this unit's objects. serialization.hpp's ReadWholeFile has internal linkage, so with that
# header in three TUs the program breaks the one-definition rule its comment names; the link keeps that object's
# instance of 2280, whose ReadWholeFile is that TU's, and 11419 calls it.
BIOMETRIA335_SRCS := src/app/comum/dados/asn/eleitor/cconversorbiometriaeleitor.cpp \
                     src/app/comum/dados/asn/eleitor/cconversorbiometriaeleitorcifrada.cpp \
                     src/app/comum/dados/asn/eleitor/cconversordedo.cpp \
                     src/app/comum/dados/asn/eleitor/cminuciascompactadas.cpp \
                     src/app/comum/dados/md/eleitor/cdedo.cpp
UENUX2_SRCS += $(BIOMETRIA335_SRCS)
# include paths, no code flags: cconversordedo.cpp includes ecourna's cbitarray.hpp, which includes
# <boost/dynamic_bitset.hpp>, and cconversorbiometriaeleitor.cpp ecourna's cconversorfoto.hpp, which includes the ASN.1
# module by its bare name
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/asn/eleitor/cconversordedo.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/asn/eleitor/cconversorbiometriaeleitor.cpp.o: UENUX2_CXXFLAGS += -Isrc/asn1/modules
