# uenux2 api::CGenericTags::TagSize (target fn 5468) in src/uenux2/src/api/util/cgenerictags.cpp, the file its
# std::source_location record names (line 46 col 15, the CUeUtilError 7016 throw), with the class header
# (api/util/cgenerictags.h) and the 7016 enumerator of api/util/eueutilerror.h. CGenericTags has no RTTI: the map of
# tags at +8 is TagSize's and insert's (fn 1071, which stores the byte at node +28 from a size_t), and the two size_t
# members at +0 and +4 are read from the class's one inlined construction (fns 3831 and 5892 store 4 and 3 there;
# insert compares the tag's size with +0 minus 1, and 5892 takes +4 characters as the tag); their names are chosen.
# The map's find is the twin of the matched std::map<std::string, unsigned short>::find (fn 163): the same body for any
# mapped type. The file's other records (insert, EncodeTLV, AppendTLV, WalkTreeTLV, DecodeTLV) are not reconstructed.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CGENERICTAGS_SRCS := src/api/util/cgenerictags.cpp
UENUX2_SRCS += $(CGENERICTAGS_SRCS)
# TagSize's two callers (fns 3647 and 5466) are not reconstructed yet: 33-uenux2-cgenerictags-roots.cpp gives it two
# call sites
$(ROOT)/$(APP)/33-uenux2-cgenerictags-roots.o: $(ROOT)/src/units/33-uenux2-cgenerictags-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/33-uenux2-cgenerictags-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/33-uenux2-cgenerictags-roots.o
