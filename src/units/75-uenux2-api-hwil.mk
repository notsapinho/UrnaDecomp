# uenux2 api::IPower and api::IUrna, the hardware interfaces of src/uenux2/src/api/hwil/ (ipower.h, iurna.h, with the
# error type in euehwilerror.h), and the two classes the wasm build implements them with, api::teste::CPowerMock and
# api::teste::CUrnaMock (src/uenux2/mock/api/hwil/cpowermock.h and curnamock.h). The unit has no source of its own: every
# function it matches is defined in a class in those headers, and 75-uenux2-api-hwil-roots.o emits them with the vtables.
# Target functions, by vtable slot:
# - CPowerMock's vtable @1530944, 17 slots: Slot0 (fn 8128, slot 0), BatIntVoltage (8120), BatCurrent (8116), BatExtVoltage
#   (8113), AcVoltage (8111), Slot5 (8109), Slot6 (8108), BatLevel (8107, slot 7), the five defaults IPower's records name,
#   BatIntMaxSocValue, SetBatIntMaxSocValue, BatIntStorageMode, EnableBatIntStorageMode and DisableBatIntStorageMode
#   (8105, 8098, 8091, 8083, 8074, slots 8 to 12, the throws at ipower.h lines 354, 361, 409, 417 and 424, codes 5172 to
#   5176 of EUeHwilError), the implicit destructors (slots 13 and 14: the shared empty bodies 174 and 144, matched
#   already), ReadStatus (8071, slot 15) and Slot16 (slot 16: 434, the shared `return 1`, matched already).
# - CUrnaMock's vtable @1530880, 9 slots: Modelo, NumeroSerie and Slot3 (slots 0, 2, 3: the shared 7-byte getters 1661,
#   2587 and 3383, matched already: 3383's line takes this unit's Slot3, this object coming before sqlite3.o, and 2587's
#   takes unit 50's GetEstadoBiometria, whose object comes first in link order), ModeloAbreviado (8168, slot 1), Slot4
#   (8144), Slot5 (8134), Semente (8131) and the implicit destructors (8130, 8129).
# - round (fn 2953): the libc body Slot5 calls; it is not this unit's code. RHVoice's do_synthesize calls it too, and
#   binaryen inlined it into that one caller until Slot5 gave it a second, so the function keeps its own body.
# Pending, unmatched with its real body in curnamock.h: ModeloAbreviado (8168). It waits for the literal "-{:02}-{:02}"
# in the link, the format string of vota::CMostraEleitorVotando's slot 6 (fn 10425), which is not reconstructed. The
# target's linker merged this member's "{:02}" as the tail of that string (begin 8970, end 8975); ours merges it into the
# one longer string our link holds, "{:04}{:02}{:02}T{:02}{:02}{:02}", and the scan re-points the end pointer, a pointer
# to a NUL, to that string's end, 8944, so the row is `differs` at +0x69. A real body that `differs` is the member's
# state: with that literal added to a scratch link the remap of 8168 prints IDENTICAL, so nothing here needs an edit.
# Why the headers, and evidence against choice:
# - No key function (evidence): both vtables lie in the data of the TU of fn 8302, simulador's init, each with its typeinfo
#   and then its base's (1530924, 1530936; 1531020, 1531032), and fn 8302 is the one function that loads CPowerMock's vptr
#   and, with CUrnaMock's destructors, the one that loads CUrnaMock's (`/usr/bin/grep -rlE 'i32\.const 1530952($|[^0-9])'
#   build/out/splat/pieces/asm`, and 1530888). So every virtual member is inline or pure
#   (docs/reference/facts/reading.md R6), defined in the classes here. That TU is not reconstructed, so the roots file
#   stands for it.
# - ipower.h's path and the five members' names and signatures are records. Everything else named here is chosen, and
#   each header says from what: the other members' names, the block's and the fields' names, iurna.h's and
#   euehwilerror.h's paths, the mock/ tree's two paths. The classes, their bases and the error type with its limits are
#   RTTI's. The constructors are implicit: no target function holds them. Fn 8302 holds them inlined as whole-word
#   stores (`i64.store[p0+4] = 0`, `i64.store[p0+20] = 8589936704`), from which the two headers read the layout; the
#   copies the roots object's builders give, which wasm-ld drops, mask the named bit-fields instead.
# Other forms measured to give the same bytes, each against the chosen one, function by function in the object (a form
# that differs in the object was then linked, the list below says how):
# - that CPowerMock and not IPower defines slots 0 to 6 (ipower.h gives the evidence for IPower); `final` on CPowerMock;
# - the status block as four uint32_t words read with masks and shifts; ReadStatus taking a pointer, const, or with
#   std::memcpy for the assignment; `inline` on a member defined in the class;
# - uint16_t or unsigned instead of int from slots 1, 3 and 4 (the callers read int); Slot5 returning long; Slot6
#   returning int or unsigned; Slot16 as `int` and `return 1`; CUrnaMock's NumeroSerie and Slot3 returning unsigned;
# - the block's 16-bit fields declared std::uint16_t, or its byte field uebyte, as bit-fields of the same widths;
# - BatCurrent as `if (m_status.m_tensaoRede == 0) return -carga; return carga;`, as a `==` ternary, with the cast in
#   each arm and no local, or as one local set in nested ifs;
# - Slot5 with `<=` one lower on every step, with int or unsigned for tensao, with an `if` for the ternary that picks it,
#   with the product's operands swapped, with a C cast and `round`, and with std::lround for the cast and std::round: that
#   one differs in the object, a call to lround, and is identical in a link, where binaryen inlines libc's lround into
#   its one caller;
# - Slot4 with std::memset or std::fill for the fill of the early return, with std::memcpy, std::memmove, std::copy_n or
#   std::ranges::copy for std::copy, with `if (tamanho != 1024) std::memset(...)` for the last std::fill_n, with if/else
#   for the early return, or over a std::array<uebyte, 1024>&; CUrnaMock's Slot5 and Semente with std::memset, std::fill
#   or std::array::fill;
# - std::vector<char> for m_dados; IUrna's members without const; ModeloAbreviado with a local for `m_modelo - 2000`, or
#   as std::vformat over std::make_format_args;
# - CUrnaMock's destructor in the class, with or without `inline`; IPower's and IUrna's destructors as `{}`;
# - compiling the roots with UENUX2_CXXFLAGS (-fno-strict-aliasing) instead of APP_CXXFLAGS, measured when both were at
#   -O2, the tree's level then.
# Forms measured not to, each linked with the variant's roots object in the plain link's place and remapped against its
# target (`splat-remap --no-kinds`; the chosen form, linked the same way, prints IDENTICAL): uint16_t members in the
# block (slots 2, 5, 7), `final` on CUrnaMock (its destructors), Slot0 returning int, BatLevel returning int or written
# with std::min (an unconditional store), Slot5 with one `return` per step, Slot4 with no test (clang joins the paths),
# with the size taken before the test, with the test as `m_dados.size() == 0`, with std::fill (a signed test), with a
# `for` loop for the last std::fill_n or with an unguarded std::memset. ModeloAbreviado over an unsigned or
# with `m_modelo % 100` differs in the object: its argument type constant, its arithmetic. It has no match to compare with.
# Compiled from its /work path with -iquote: the quoted includes then resolve to the absolute paths, which
# -ffile-prefix-map rewrites to /home/rubio/tse/uenux2/src/api/hwil/ipower.h, the file name of the target's records
# (-iquote directories are searched before the -I ones, so the relative -Isrc/uenux2/src of APP_CXXFLAGS does not win;
# unit 19 has the same rule). The prerequisites name the directories the compile reads ($(UENUX2_HDRS) is set after
# src/Makefile reads the fragments: here it would be empty).
$(ROOT)/$(APP)/75-uenux2-api-hwil-roots.o: $(ROOT)/src/units/75-uenux2-api-hwil-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/75-uenux2-api-hwil.mk $(wildcard $(ROOT)/src/uenux2/src/api/hwil/*.h $(ROOT)/src/uenux2/mock/api/hwil/*.h $(ROOT)/src/ecourna/api/exception/*.hpp $(ROOT)/src/ecourna/api/uetypes.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -iquote /work/src/uenux2/src -iquote /work/src/uenux2 -c /work/src/units/75-uenux2-api-hwil-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/75-uenux2-api-hwil-roots.o
