# uenux2 api: four classes of api/gui/ and api/audio/, each with its evidence in its header:
# - api::Logger::log (target fn 10815, slot 2 of the vtable @1586188) in src/uenux2/src/api/audio/crhvoicetexttospeech.cpp:
#   `if (level == RHVoice_log_level_error) std::clog << "RHVoice [" << tag << "]: " << message << std::endl;`, the
#   literals and std::clog (0x1d5af8) read from the body. It is the class's key function, so that object emits the vtable.
#   Chosen: that log is out of line there and not inline in api/audio/logger.h (the vtable lies in the data of the object
#   that holds CRHVoiceTextToSpeech's; both readings put it there; the inline one is not measured), and the file's path.
# - api::CRHVoiceTextToSpeech's implicit destructors, D2 and D0 (target fns 5441 and 10838), which 158-uenux2-api-pending.o
#   emits with the vtable, where DoSynthesize (fn 10841), the key function, is a trap. Measured: without `final` the D2
#   begins with the class's own vptr store, which the target's does not. The members' types beyond their destruction, and
#   that the destructor is implicit rather than defined in the class without `inline` (the same D0 shape), are chosen
#   (api/audio/crhvoicetexttospeech.h).
# - api::CPreShowClearScreen::PreShow (target fn 11139), inline in api/gui/cpreshowclearscreen.h; no key function, so
#   158-uenux2-api-roots.o emits it with the vtable, at the tree's flags.
# - api::CFixedImage::CFixedImage(const std::string &) (target fn 2246), in src/uenux2/src/api/gui/cfixedimage.cpp, the
#   file its record names (24:15), with api::isResource and api::getResourceFile, inline in api/gui/iresource.h, which it
#   inlines (records 97:12 and 82:12), and the 4913 enumerator of EUeGuiError. Measured, by the frame offsets of the
#   object: the file read written in the constructor, `m_dados = ReadFileBinary(arquivo)` or through a local moved in,
#   puts the path at +8, the vector at +24 and the throw's string at +36, where 2246 has them at +32, +8 and +20; the
#   same read in a function clang inlines into the constructor gives 2246's offsets, a file-static LeArquivo and a lambda
#   called in place alike (the same object code). LeArquivo, its name and its being file-static are chosen. The two
#   branches the other way round (`if (isResource(arquivo)) swap; else read`) give another object.
# Hand lines in splat/symbol_addrs.txt: 3746 and 3764 (`callers+content`), the destructors of ITextToSpeech's two
# containers. Their names came from 9427's `call` votes while 9427 held ITextToSpeech's vptr as an anchor; the D2 5441
# stores that vptr too, so the anchor and those votes went, and 5441, 9427 and 11489 read `unresolved` on the two calls
# (the scan of this unit before the lines). With the lines 5441 and 9427 (unit 82's D0) match; 11489 is the executable
# TU's copy and stays `differs`.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
API158_SRCS := src/api/audio/crhvoicetexttospeech.cpp src/api/gui/cfixedimage.cpp
UENUX2_SRCS += $(API158_SRCS)
# logger.h includes RHVoice's core/event_logger.hpp: an include path, not a flag of the code
$(ROOT)/$(APP)/uenux2/src/api/audio/crhvoicetexttospeech.cpp.o: UENUX2_CXXFLAGS += -Ithird_party/RHVoice/src/include
# $(UENUX2_HDRS) is still empty when the fragments are read, so the companion rules name the directories they read.
API158_HDRS := $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h $(ROOT)/src/uenux2/src/api/audio/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/ecourna/api/*.hpp $(ROOT)/src/ecourna/api/exception/*.hpp $(ROOT)/src/ecourna/api/pattern/*.hpp)
# DoSynthesize (target fn 10841) is not reconstructed: 158-uenux2-api-pending.cpp gives the vtable a trapping body,
# compiled with the unit's flags
$(ROOT)/$(APP)/158-uenux2-api-pending.o: $(ROOT)/src/units/158-uenux2-api-pending.cpp $(ROOT)/src/units/158-uenux2-api.mk $(ROOT)/src/Makefile $(API158_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/158-uenux2-api-pending.cpp -o $(R)
# the constructors that store the three vtables and the callers of CFixedImage's are not reconstructed:
# 158-uenux2-api-roots.cpp takes the vtables' addresses and stands in for the callers, at the tree's flags
$(ROOT)/$(APP)/158-uenux2-api-roots.o: $(ROOT)/src/units/158-uenux2-api-roots.cpp $(ROOT)/src/units/158-uenux2-api.mk $(ROOT)/src/Makefile $(API158_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/158-uenux2-api-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/158-uenux2-api-pending.o $(APP)/158-uenux2-api-roots.o
