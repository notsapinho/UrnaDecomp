# uenux2 comum::CGravadorRDV::GravaResultado (target fn 11587, slot 7) in app/comum/gravadores/cgravadorrdv.cpp, a
# chosen path beside cgravadorrdv.h (no record names the class's file), paths relative to src/uenux2. It is the class's
# key function, so cgravadorrdv.cpp.o emits CGravadorRDV's vtable and implicit destructors now (fns 11586, 11585, unit
# 136's matches, under the same symbols), not unit 136's pending object. The file's notes say what the body reads and
# what is chosen; cgravadorrdv.h why +164 is a CRdv pointer and +52 the urna's ETipoArquivo; api/io/asn/cfileasn.h has
# CFileASN::CodeObject (the "CodeObject de " writer 11587 holds behind a frame of its own), and ecourna's
# api/io/cfile.hpp why CFile::Write takes a std::vector<uebyte>.
#
# Matched with it: api::CFileASN::DecodeObject<ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto> (fn 5825). The
# target's copy is this object's instance (its records lie in this object's data in the target, after CGravadorRDV's
# vtable). Its other target caller, 5680 (comum::asn::Decodifica), is unit 13's, in
# app/comum/dados/asn/rdv/cconversorregistrodigitalvoto.cpp, whose object links ahead of this one, so our link keeps
# that object's copy, compiled at the tree's flags without strict aliasing as this object is (only the include paths
# differ), and 5825 matches from it; the roots stand-in for 5680 went with it, and with it this unit's -roots.cpp.
#
# Measured in the whole link before step 8 (pnpm wasm score against the target):
# - 11587: 111 over 1155 rows, operand-only, every operand a call, a data address, the packed format string of
#   CodeObjectFunction's throw or a table slot (the format buffer's, the exception's destructor's), which step 9's names
#   resolve; 5825: 51 over 532, the same kinds.
# - With the coded bytes copied into a std::vector<char> for the write (CFile::Write over that type), 11587 scored 115
#   over 1155 rows, 4 deleted: the target keeps two `__throw_length_error` paths, one per byte-vector copy, and ours
#   one (wasm-objdump -d of cgravadorrdv.cpp.o shows one call of it in GravaResultado, and two, of the char and the
#   uebyte vector's, with the second copy a std::vector<uebyte>; that the two copies' paths joined because they called
#   one function is a reading).
# No other form was measured.
#
# CGravadorRDV's constructor, which vota::CGravaResultado::StartState (fn 12098) holds inlined with no frame of its own
# (its vptr store at line 454 of the folded readout `pnpm --silent wasm fn ../target/vota_web_wasm.wasm 12098` prints,
# counted from the line after `;; --- folded readout`), is written in cgravadorrdv.cpp ahead of GravaResultado,
# unrooted (wasm-ld drops it), so with no target index and no match until 12098 is written: IGravador's constructor with
# the extension 6 and the SAVD file 37, the date-time at +40, 49 at +52, the correspondence's copy (fn 1249) at +56, the
# empty optional at +152 and the CRdv at +164 (cgravadorrdv.h). Measured on the object (wasm-objdump -d): it opens no
# frame and calls IGravador's constructor and the copy, as 12098's code does. Chosen: its line, its parameters' order
# and form, and the constants as its own rather than 12098's arguments (one call cannot tell them apart).
CGRAVADORRDV_305_SRCS := src/app/comum/gravadores/cgravadorrdv.cpp
UENUX2_SRCS += $(CGRAVADORRDV_305_SRCS)
# ecourna's media information (CInformacaoMidia holds a Boost ptime) and its converter, whose header includes the
# generated ASN.1 module by its bare name; the generic uenux2 rule does not depend on the generated modules
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorrdv.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR) -Isrc/asn1/modules
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorrdv.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
