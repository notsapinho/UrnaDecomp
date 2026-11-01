# uenux2 api::CGenericTags in src/uenux2/src/api/util/cgenerictags.cpp, the file its std::source_location records name
# (all at column 15), with the class header (api/util/cgenerictags.h) and the 7013 to 7019 enumerators of
# api/util/eueutilerror.h:
#   5468  TagSize                         record at line 46 (7016)
#   5467  EncodeTLV(tag, valor, tamanho)  records at lines 79 (7017) and 85 (7018)
#   3647  EncodeTLV(tag, valor)           no record
#   5466  AppendTLV(tlv, tag, valor)      no record; it holds AppendTLV(tlv, tag, valor, tamanho), record at line 102
#                                         (7019), which binaryen inlined into it
#   1071  insert                          records at lines 31, 34 and 37 (7013 to 7015)
# CGenericTags has no RTTI: the map of tags at +8 is TagSize's and insert's (fn 1071, which stores the byte at node +28
# from a size_t), and the two size_t members at +0 and +4 are read from the class's one inlined construction (fns 3831
# and 5892 store 4 and 3 there; insert and the encoders compare the tag's size with +0 minus 1, and 5892 takes +4
# characters as the tag); their names are chosen, and so is the in-class constructor from the tag's size that unit 95's
# CriaTags (iinterfacesavd.cpp) calls. The map's find is the twin of the matched std::map<std::string,
# unsigned short>::find (fn 163): the same body for any mapped type.
#
# The overloads. 5466 calls TagSize before its frame's prologue, then holds the record of line 102: binaryen inlined
# the four-argument AppendTLV, which has one caller in the link, into a function that passes it TagSize(tag). 3647 is
# EncodeTLV(tag, valor, TagSize(tag)), and the three-argument EncodeTLV stays out of line, called by it and by
# AppendTLV. That 3647 and 5466 are overloads of the recorded members, their names and their lines are chosen. The
# target's use band 2 runs 5468, 5467, 5466, a higher index linking first: the order the file defines them in.
#
# EncodeTLV throws 7017 when the tag is not m_tamanhoTagComNulo - 1 characters long, takes 2^(8 * tamanho) - 1 as the
# largest value length, pads a copy of the tag with the character ';' + tamanho (the target adds 59 to tamanho; ';' is a
# chosen spelling of that 59) up to
# m_tamanhoTagComNulo characters, throws 7018 when the value is longer, and returns std::format("{}{:0{}x}{}", the
# padded tag, the value's length, 2 * tamanho, the value). The target holds libc's exp2 inlined there, on
# (double)(tamanho << 3): std::pow(2, tamanho * 8), written here, compiles to a call of exp2 (the object imports it),
# which binaryen inlines into EncodeTLV, its one caller; spelling it std::pow is a choice. The padding is
# ecourna::api::util::Repete (fragment 182) on a temporary std::string of that one character. The target reloads the
# temporary's size from memory right after storing it, so the loop was compiled where the store was not visible, and
# binaryen inlined it (a reading). Measured in the whole link (pnpm wasm score against the target's 5467): the loop as
# a file-static function of this file, which clang inlines, scores 220 over 1118 rows (40 inserted, 53 deleted); in a
# uenux2 TU of its own, 129 over 1095 (17 inserted, 16 deleted), with the string's old buffer loaded once where the
# target loads it twice; with -fno-delete-null-pointer-checks added to that TU, or at ecourna's whole flag set, 48 over
# 1078, all operand-only, and the two links are byte-identical, as is the link with the helper at its ecourna path.
# So the helper is placed in ecourna, the one tree here compiled with that flag (docs/reference/facts/app-flags.md F3):
# a reading from the flag, in the forms measured (a file-static function, a uenux2 TU of its own); no record names the
# tree.
#
# libc's exp family. With EncodeTLV in the link, fp_force_eval and fp_barrier (6278, 6279) are bodies of their own and
# match, and so do exp (956), __expo2 (6280), sinh (12297), cosh (12315) and RHVoice's limiter::do_initialize (9639,
# unresolved before on its call of exp). At 694de52 our link has neither barrier as a body of its own
# (build/out/wasm-map/vota_web/names.tsv) and the other five are no-candidate or unresolved: they rest on this unit
# (docs/reference/facts/splat.md S10 item 21). Why binaryen keeps the barriers out of line once exp2 links is not
# measured.
#
# insert (1071) matches since src/api/ builds with strict aliasing (src/Makefile UENUX2_TBAA_DIRS,
# docs/reference/facts/app-flags.md F6), named by its records (evidence:srcloc-anchor); before, nothing named it
# (`no-candidate`), since a record anchors a pair only when the two bodies are the same opcodes
# (docs/reference/splat.md section 2). It inserts std::make_pair(tag, tamanho): the target copies the tag into a pair
# whose second word is a 4-byte size_t, moves it into the node and stores the byte there, after the find. Its
# difference is the map's __insert_node_at: our object reads the new node back after the store to the begin node, where
# the target keeps it in a local. In a whole-link try with csystem.cpp and cgenerictags.cpp at `--flags
# -fstrict-aliasing` it scores `54 over 878 rows`, all operand-only, against `62 over 883 (57 operand-only, 5 inserted)`
# with -fno-strict-aliasing. At 694de52's flags, with cgenerictags.cpp and csystem.cpp compiled by hand with uenux2's
# set and relinked, it scores 56 over 883 rows (51 operand-only, 5 inserted), and without -fno-strict-aliasing 48 over
# 878, all operand-only. WalkTreeTLV and DecodeTLV (records at lines 110 and 136, both held by fn 5892) are not
# reconstructed: unit 95's fragment has 5892's measurement. Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CGENERICTAGS_SRCS := src/api/util/cgenerictags.cpp
UENUX2_SRCS += $(CGENERICTAGS_SRCS)
# the callers of insert, of EncodeTLV(tag, valor) and of AppendTLV(tlv, tag, valor) are 3831 and 5892 for each: 3831 is
# in the link (unit 95's iinterfacesavd.cpp), 5892 is not reconstructed yet, and 33-uenux2-cgenerictags-roots.cpp stands
# for it
$(ROOT)/$(APP)/33-uenux2-cgenerictags-roots.o: $(ROOT)/src/units/33-uenux2-cgenerictags-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/33-uenux2-cgenerictags-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/33-uenux2-cgenerictags-roots.o
