# uenux2 api::CSystem::GetFileSize (target fn 2759) and api::truncate (5457) in src/uenux2/src/api/util/csystem.cpp,
# the file their std::source_location records name (lines 334 and 1024, col 15: the CUeUtilError 7038 and 7070
# throws), with the class header api/util/csystem.h and the two enumerators of api/util/eueutilerror.h.
# truncate is external and not in the header: in the target's run of this file's records, its record (address
# 1584900, line 1024) sits in line order among the external functions' ones, before ZeroFill's (1584916, line 1039);
# clang defers a file-static function's body, and so its records, past every external one. Its one caller, ZeroFill
# (2761), is in this file. api::ExistResource (1690, record at line 64, address 1584932) comes after ZeroFill's, with
# the anonymous-namespace helpers: it is file-static, declared in no header, and stays a stub until two of its callers
# here (2762 IsEmptyDir, 5455, 2761 ZeroFill) are written, without which clang does not emit it out of line.
# CSystem's other members (TemporaryPath 5455, IsEmptyDir 2762, CopyFile 378, Rename 11584, AreFilesEqual, ZeroFill
# 2761) are not reconstructed yet. Paths relative to src/uenux2; the generic uenux2 rule depends on the source and
# every uenux2 header.
CSYSTEM_SRCS := src/api/util/csystem.cpp
UENUX2_SRCS += $(CSYSTEM_SRCS)
# neither function's callers are reconstructed yet: 32-uenux2-csystem-roots.cpp gives each two call sites or more
$(ROOT)/$(APP)/32-uenux2-csystem-roots.o: $(ROOT)/src/units/32-uenux2-csystem-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/32-uenux2-csystem-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/32-uenux2-csystem-roots.o
