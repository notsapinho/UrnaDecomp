# uenux2 comum::CGravadorRDV::GravaResultado (target fn 11587, slot 7) in app/comum/gravadores/cgravadorrdv.cpp, a
# chosen path beside cgravadorrdv.h (no record names the class's file), paths relative to src/uenux2. It is the class's
# key function, so cgravadorrdv.cpp.o emits CGravadorRDV's vtable and implicit destructors now (fns 11586, 11585, unit
# 136's matches, under the same symbols), not unit 136's pending object. The file's notes say what the body reads and
# what is chosen; cgravadorrdv.h why +164 is a CRdv pointer and +52 the urna's ETipoArquivo; api/io/asn/cfileasn.h has
# CFileASN::CodeObject (the "CodeObject de " writer 11587 holds behind a frame of its own), and ecourna's
# api/io/cfile.hpp why CFile::Write takes a std::vector<uebyte>.
#
# Matched with it: api::CFileASN::DecodeObject<ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto> (fn 5825), this
# object's instance (its records lie in this object's data in the target, after CGravadorRDV's vtable; its other target
# caller, 5680, is not written, and the roots stand in for it).
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
CGRAVADORRDV_305_SRCS := src/app/comum/gravadores/cgravadorrdv.cpp
UENUX2_SRCS += $(CGRAVADORRDV_305_SRCS)
# ecourna's media information (CInformacaoMidia holds a Boost ptime) and its converter, whose header includes the
# generated ASN.1 module by its bare name; the generic uenux2 rule does not depend on the generated modules
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorrdv.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR) -Isrc/asn1/modules
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorrdv.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
# 305-uenux2-cgravadorrdv-roots.cpp stands in for the callers not written; it compiles with the tree's flags
$(ROOT)/$(APP)/305-uenux2-cgravadorrdv-roots.o: $(ROOT)/src/units/305-uenux2-cgravadorrdv-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/305-uenux2-cgravadorrdv.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null) $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -Isrc/asn1/modules -c src/units/305-uenux2-cgravadorrdv-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/305-uenux2-cgravadorrdv-roots.o
