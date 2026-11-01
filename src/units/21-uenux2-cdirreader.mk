# uenux2 api::CDirReader in src/uenux2/src/api/util/cdirreader.cpp, the file its std::source_location records name, with
# the class header (api/util/cdirreader.h: the directory path, the DIR* and the current dirent*, at +0, +12 and +16) and
# the 7009 and 7010 enumerators of api/util/eueutilerror.h:
#   1914  the constructor           record at line 30, col 19 (7009)
#   1260  NextEntry                 record at line 43, col 15 (7010)
#   1913  the destructor; 5470 Open, 2232 Close, 1912 IsDir, 2231 IsFile, 5469 IsLink: no record
#   6020  binaryen's merge of IsDir and IsFile
# What the bodies show: the constructor zeroes the members and, for a non-empty path, calls 5470 and throws unless the
# DIR* is set; 5470 opens the directory with opendir and, when that succeeds, closes the one held (2232's body,
# inlined), copies the path and keeps the DIR*; 2232 closes it with closedir and clears the path and the two pointers;
# 1913 does that and frees the path, returning this; 1912 and 2231 are thunks into 6020 with S_IFDIR and S_IFREG, 6020
# and 5469 stat (5469 lstat, against S_IFLNK) the path, a '/' and the entry's d_name. The names Open, Close, IsDir,
# IsFile and IsLink are chosen (the header says from what). The constructor writes only the path's size byte and its
# terminator, the shape of a std::string built from an empty literal: the header initializes the path from "" (compared
# on the object with wasm-objdump: the default constructor stores all 12 bytes). IsDir, IsFile and IsLink read m_entrada
# into a local before building the path: the target reuses the loaded pointer for d_name, where a second read of the
# member gave a reload (`score 13 over 171` for 5469 and `12 over 171` for 6020, one row inserted and one deleted
# each, against `7 over 170` and `6 over 170`, every row an operand, pnpm wasm score on the whole link). The members' order in the file: the target's use bands put the
# constructor before the destructor and IsDir (band 6), Close before IsFile (band 5) and Open before IsLink (band 2), a
# higher index linking first, which this order gives as each takes its place at its first mention; the lines of the
# destructor (original 35-38) and of the members after NextEntry are a choice.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and
# every uenux2 header.
CDIRREADER_SRCS := src/api/util/cdirreader.cpp
UENUX2_SRCS += $(CDIRREADER_SRCS)
# no caller of the members outside the class is reconstructed yet: 21-uenux2-cdirreader-roots.cpp gives each two call
# sites or more
$(ROOT)/$(APP)/21-uenux2-cdirreader-roots.o: $(ROOT)/src/units/21-uenux2-cdirreader-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/21-uenux2-cdirreader-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/21-uenux2-cdirreader-roots.o
