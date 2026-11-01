# uenux2 api::CGenericTags::TagSize (target fn 5468) in src/uenux2/src/api/util/cgenerictags.cpp, the file its
# std::source_location record names (line 46 col 15, the CUeUtilError 7016 throw), with the class header
# (api/util/cgenerictags.h) and the 7016 enumerator of api/util/eueutilerror.h. CGenericTags has no RTTI: the map of
# tags at +8 is TagSize's and insert's (fn 1071, which stores the byte at node +28 from a size_t), and the two size_t
# members at +0 and +4 are read from the class's one inlined construction (fns 3831 and 5892 store 4 and 3 there; insert
# compares the tag's size with +0 minus 1, and 5892 takes +4 characters as the tag); their names are chosen. The map's
# find is the twin of the matched std::map<std::string, unsigned short>::find (fn 163): the same body for any mapped
# type. CGenericTags::insert (fn 1071, records at lines 31, 34 and 37, col 15: the 7013, 7014 and 7015 throws) matches
# since src/api/ builds with strict aliasing (src/Makefile UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6), named by its records
# (evidence:srcloc-anchor); before, nothing named it (`no-candidate`), since a record anchors a pair only when the two
# bodies are the same opcodes (docs/reference/splat.md section 2). It inserts std::make_pair(tag, tamanho): the target copies
# the tag into a pair whose second word is a 4-byte size_t, moves it into the node and stores the byte there, after the
# find. Its difference is the map's __insert_node_at: our object reads the new node back after the store to the begin
# node, where the target keeps it in a local. In a whole-link try with csystem.cpp and cgenerictags.cpp at `--flags
# -fstrict-aliasing` it scores `54 over 878 rows`, all operand-only, against `62 over 883 (57 operand-only, 5 inserted)`
# with -fno-strict-aliasing. EncodeTLV
# (5467, records at lines 79 and 85) is not written: it holds a body that reads as libm's exp2, inlined, and calls 6278
# and 6279, which nothing names; AppendTLV (5466, line 102) and fn 3647, `EncodeTLV(tag, valor, TagSize(tag))`, call it.
# WalkTreeTLV and DecodeTLV (5892) are not reconstructed. Paths relative to src/uenux2; the generic uenux2 rule depends
# on the source and every uenux2 header.
CGENERICTAGS_SRCS := src/api/util/cgenerictags.cpp
UENUX2_SRCS += $(CGENERICTAGS_SRCS)
# TagSize's two callers (fns 3647 and 5466) and insert's (3831 and 5892) are not reconstructed yet:
# 33-uenux2-cgenerictags-roots.cpp gives each two call sites
$(ROOT)/$(APP)/33-uenux2-cgenerictags-roots.o: $(ROOT)/src/units/33-uenux2-cgenerictags-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/33-uenux2-cgenerictags-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/33-uenux2-cgenerictags-roots.o
