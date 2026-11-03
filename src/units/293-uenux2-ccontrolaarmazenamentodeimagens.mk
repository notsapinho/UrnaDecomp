# uenux2 callees of comum::CControlaArmazenamentoDeImagens' fn 2725 (5103 B, ccontrolaarmazenamentodeimagens.cpp's
# records at lines 73 to 152; not written: below) that other target functions call too, paths relative to src/uenux2.
# Matched (steps 7 to 9 on this link):
# - api::CPolySingleton<api::IKernelHSM>::instance (target fn 2279, records cpolysingleton.h:78 and
#   cpolysingletonlist.h:99 and :105), over the head of api::IKernelHSM this unit adds (src/api/hwil/ikernelhsm.h, its
#   notes there);
# - ecourna::api::io::DeserializeFromFile<ModuloEnvelopeChave::EntidadeChave> (fn 2280, the records of
#   DeserializeFromBuffer, serialization.hpp:44 and :47, which binaryen inlines into it);
# - comum::asn::GravaArquivo for md::CEntidadeHashes (fn 5367), in the new
#   src/app/comum/gravadores/asn/cconversorentidadehashes.cpp, and its merge with unit 160's GravaArquivo for the
#   envelope (fn 2724): fn 6006, which forms once both are in the link (both writers' notes are in their headers);
# - libc's __futimesat (fn 6236, the body of utimes, which binaryen inlines into its callers) and SQLite's dotlockLock
#   (fn 12674), its other caller, from the libraries: with the roots' calls of utimes binaryen keeps __futimesat out of
#   line, as the target does, where it inlined it into dotlockLock before.
# The two templates' instances come from this unit's roots object, the first to instantiate them in our link; the
# target's copies are cgravadorbu.cpp's by a reading of the data (their records lie in that object's run of the data,
# before IGravadorEnvelope's vtable @1554456), a uenux2 object without strict aliasing, the flags the roots rule below
# compiles with.
#
# Measured on this link (pnpm wasm score against the target, then the scan):
# - 2280 with the file read in DeserializeFromFile's own scope, the CFile alive across the decode: 117 over 319 rows
#   (67 replaced, all operand-only, 25 inserted, 25 deleted: the CFile destroyed after the decode, and the locals
#   numbered otherwise), where the target destroys the CFile before the decode and builds the buffer in the stack slot
#   of the mode string, which died before it. With the read in a static helper that returns the buffer
#   (serialization.hpp's ReadWholeFile, inlined by clang: internal linkage, one call), 33 over 294, every row an operand
#   (calls, data addresses, the error's table slot), and the scan matches it. The helper inline (not static) and an
#   immediately called lambda each stayed out of line, and clang then inlined DeserializeFromFile into the roots'
#   stand-in (names.tsv lists the helper and DeserializeFromBuffer, and no DeserializeFromFile). The helper's name and
#   linkage are chosen; no record names it. `static inline` and an anonymous namespace give this unit's roots object
#   byte for byte, and `inline` alone keeps the helper out of line and DeserializeFromFile inlined into the stand-in
#   (each compiled at the roots' rule from a copy of the header found first and prefix-mapped to the tree's path, the
#   unchanged copy's object cmp-equal to the link's). `static` stays, though a function of internal linkage that a
#   template of external linkage calls is an ODR hazard once a second TU instantiates DeserializeFromFile (only this
#   unit's roots include the header now).
# - 2279 82 over 900 rows, 5367 and 2724 6 over 10 each, 6006 58 over 712, every row an operand.
# - 6236 against our __futimesat: with the stand-in reading the result, 11 over 69 rows (its i32 result, which the
#   target's type lacks); dropping it, as both target callers do, 3 over 67, operands only, and dotlockLock 4 over 54
#   (5 over 55 with the stand-in that read it: a drop after the call).
#
# fn 2725 is not written. It calls fn 2742 (`f2900(1908612, 1908636)`, the GetInst of a 1-byte singleton no evidence
# names, merged into CLogComum::GetInst's body 2900) and drops the result, and 2742's other callers (10316, 10451,
# 10465) are not written either, so a name for 2742 would rest on 2725's vote alone, which the build refuses as
# self-voted (a reading of docs/reference/splat.md "No circular evidence"). Its other callee with no body of ours is
# 1555 (49 B: an out-of-line copy of the std::string at +0 of its argument, which both of 2725's throw paths call on
# the key file's path; 11419, 11616 and 11629 call it too). Its callees 5739, 5168 and 2724 are written in units 89,
# 05 and 160.
CCONTROLAARMAZENAMENTO_SRCS := src/app/comum/gravadores/asn/cconversorentidadehashes.cpp
UENUX2_SRCS += $(CCONTROLAARMAZENAMENTO_SRCS)
# the converter includes generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(CCONTROLAARMAZENAMENTO_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# 293-uenux2-ccontrolaarmazenamentodeimagens-roots.cpp stands in for the callers not written; it compiles with the
# tree's flags, the flags of the object whose template copies the target keeps
$(ROOT)/$(APP)/293-uenux2-ccontrolaarmazenamentodeimagens-roots.o: $(ROOT)/src/units/293-uenux2-ccontrolaarmazenamentodeimagens-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/293-uenux2-ccontrolaarmazenamentodeimagens.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null) $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/293-uenux2-ccontrolaarmazenamentodeimagens-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/293-uenux2-ccontrolaarmazenamentodeimagens-roots.o
