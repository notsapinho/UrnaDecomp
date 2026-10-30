# uenux2 api::CDataText<T>, api::CDataTextFmt<T> and api::CDataImage<T>, the data-source texts and images, with
# api::CTextSource, one of their T, and api::CQRCodeImage, whose destructors binaryen merges with those of
# CDataText<std::function<std::string()>>. Evidence and choices are in each header's comment:
#   src/api/gui/cdatatext.h, cdatatextfmt.h, cdataimage.h   paths chosen: no record names them
#   src/api/gui/ctextsource.h                               path evidence: record 37:19, the constructor's throw
#   src/api/gui/cqrcodeimage.h, cqrcodeimage.cpp            the .cpp's path evidence: record 36:15; the header's chosen
# The class templates have no source of their own: every function matched from them is a template instance, emitted here
# by the roots object, which builds each instantiation the way the target's callers do and takes the place of those callers
# until they land. The target functions:
#   CDataText<CTextSource>                       D2 10536, D0 10535, GetText 10534
#   CDataTextFmt<CTextSource>                    D2 10748, D0 10747, GetText 10746
#   CDataTextFmt<function<string(const string&)>>  D2 12291, D0 12290, GetText 12287
#   CDataText<string (*)()>                      GetText 12784 (D2 and D0 are the shared 174 and 144)
#   CDataText<const string& (*)()>               GetText 12580 (the same)
#   CDataText<function<string()>>                D2 12305, D0 12303, GetText 12301
#   CDataTextFmt<string (*)(const string&)>      D2 12323, D0 12317; GetText 6404, shared with the next
#   CDataTextFmt<const string (*)(const string&)>  D2 12567, D0 12564, GetText 6404
#   CDataImage<vector<unsigned char> (*)()>      GetData 6330 (a twin of __func<string (*)(), string()>'s slot 6)
#   CQRCodeImage                                 constructor 3662, D2 10966, D0 10964
#   byn$mgfn-shared bodies                       6060 and 6059, of CQRCodeImage's and CDataText<function<string()>>'s D2 and D0;
#                                                the other thunks above join 1566 and 1565
#   __shared_ptr_emplace<X> D2, D0               12796 12788, 12586 12581, 12309 12306, 12335 12328, 12575 12570, 12294 12292,
#                                                12518 12517, 12313 12311; slot 2 of two with std::function, 2967
#   __shared_ptr_pointer<X*, ...>::__get_deleter 10533 10745 11998 10623 11245 12345 12546
# GetData (10967) is pending: the fragment's -pending.cpp names what it waits for. The other instantiations (over
# comum's and vota's classes, and the three of CDataTextFmt<comum::(anonymous namespace)::CComparecimentoMesariosDS>) wait
# for those classes.
#
# Measured by compiling each form as an overlay of the header and comparing the object's functions, 87 of them, with
# call targets and object-local indices masked. Forms that change no function of this unit:
#   CTextSource::operator()() returning std::string; operator()(const std::string&) defined `inline` after the class;
#   std::snprintf, or 512 for sizeof; `return std::string(texto);`; the destructors declared `= default` in the class;
#   GetText declared `inline`; CDataText's T as `const T&`; CDataTextFmt's string by value, copied into the member, and
#   CQRCodeImage's std::function the same way (these three change only the stand-ins' own helpers, allocate_shared and
#   construct_at); CQRCodeImage's first parameter without `const`; the roots compiled with -fno-strict-aliasing, which is
#   UENUX2_CXXFLAGS's difference from APP_CXXFLAGS.
# Forms measured not to:
#   operator()(const std::string&) without `inline`: it stays out of line in the object and binaryen inlines it into 10746,
#   whose row is then `differs` at +0x3, with an outer block and the string's address in a local;
#   `final` on either template: 24 functions differ, the D2s and D0s among them. The target's D2s begin with the vptr store.
#
# Six of the seven __get_deleter matches rest on one more thing. Each holds the address of a __shared_ptr_default_delete
# type's _ZTS string, which no typeinfo names, so only its content places it, and resolveBytes in
# asmlift-wasm/src/splat-symbols.ts places a string whose address in our link is 4-aligned only at a 4-aligned target
# copy. 12345's target copy is 4-aligned, so it resolves wherever ours lies; the other six are not. Their strings lie in
# one run of type names, from unit 15's pending object to this roots object, so a change in the length of the names
# before them in that run moves them: by 3 bytes mod 4 it turns 12546, 10745 and 11998 `unresolved` (which stops
# splat-match), by 1 byte 10623 and 11245, by 2 bytes 10533. The order of the roots' sink lines is chosen so that none
# of the six lies 4-aligned. It changes no function's bytes and serves only that test, which a resolveBytes reading the
# object's alignment makes order-independent.
#
# CTextSource's constructor, with the record at 37:19, is written and in no object: no stand-in builds a CTextSource. Built
# once to measure it, the record is the target's (check_srcloc --strict, 1 of 1). Writing it took the stubs of fns 1150
# (1768 B) and 652 (4609 B): both inline it, it is their only record, and tools/round/stubs.py counts a function whose
# record lines all hold code as written. Neither is written; no evidence names their file.
UENUX2_SRCS += src/api/gui/cqrcodeimage.cpp
$(ROOT)/$(APP)/79-uenux2-cdatatext-pending.o: $(ROOT)/src/units/79-uenux2-cdatatext-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/79-uenux2-cdatatext.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/79-uenux2-cdatatext-pending.cpp -o $(R)
$(ROOT)/$(APP)/79-uenux2-cdatatext-roots.o: $(ROOT)/src/units/79-uenux2-cdatatext-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/79-uenux2-cdatatext.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h $(ROOT)/src/ecourna/api/exception/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/79-uenux2-cdatatext-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/79-uenux2-cdatatext-pending.o $(APP)/79-uenux2-cdatatext-roots.o
