# uenux2 api::CDataText<T>, api::CDataTextFmt<T> and api::CDataImage<T>, the data-source texts and images, with
# api::CTextSource, one of their T, and api::CQRCodeImage, whose destructors binaryen merges with those of
# CDataText<std::function<std::string()>>. Evidence and choices are in each header's comment:
#   src/api/gui/cdatatext.h, cdatatextfmt.h, cdataimage.h   paths chosen: no record names them
#   src/api/gui/ctextsource.h                               path evidence: record 37:19, the constructor's throw
#   src/api/gui/cqrcodeimage.h, cqrcodeimage.cpp            the .cpp's path evidence: record 36:15; the header's chosen
# The class templates have no source of their own: every function matched from them is a template instance, emitted here
# by the roots object, which builds each instantiation the way the target's callers do and takes the place of those callers
# until they land; 12632's GetText links from unit 102's roots object instead, ahead of this one, the same code. The
# target functions:
#   CDataText<CTextSource>                       D2 10536, D0 10535, GetText 10534
#   CDataTextFmt<CTextSource>                    D2 10748, D0 10747, GetText 10746
#   CDataTextFmt<function<string(const string&)>>  D2 12291, D0 12290, GetText 12287
#   CDataText<string (*)()>                      GetText 12784 (D2 and D0 are the shared 174 and 144)
#   CDataText<const string& (*)()>               GetText 12580 (the same)
#   CDataText<comum::CCargoDSNomeSexoCandidato>  GetText 12632 (the same), a call of the source's operator, fn 2268 (unit 129)
#                                                (linked from unit 102's roots object)
#   CDataText<comum::CCandidaturasDSNome>        GetText 12649 (the same), a call of the source's operator, fn 5807 (unit 89),
#                                                linked from unit 102's roots object
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
#   std::vector<unsigned char>::insert(const_iterator, size_type, const value_type&)  3661, which GetData calls three times
# GetData (10967) is pending: the fragment's -pending.cpp names what it waits for. 3661 reads as libc++'s fill insert of
# a std::vector<unsigned char> (it grows the buffer, fills with the byte the last parameter points to, and throws the
# vector's length error, fn 158), with the value GetData passes, 255; the roots object calls it twice for GetData.
# CDataText<CCargoDSNomeSexoCandidato>'s control block (12637, 12636) is unit 102's; the roots' std::make_shared of it
# instantiates the same block, which links from unit 102's object, ahead of this one, as 12632's GetText does.
# The roots' stand-ins for fn 4185, which builds CDataText<comum::CCandidaturasDSNome> and
# CDataText<comum::CCandidaturasDSNumero> with std::make_shared and is not written, keep both classes' vtables, which unit
# 102's dropped builders emit and nothing stored until now: 12649 matches (pnpm wasm score 1 over 7 rows, operand-only,
# in the whole link before steps 7 to 9), and so does 12742, CDataText<CCandidaturasDSNumero>::GetText, since fn
# 11973 is in the link: the end of its format string, "{:0{}}", is in the target the tail of "  {}{}{:0{}}" (address
# 1042), 11973's literal. Its source's call operator is unit 180's, and that fragment has the measurement. The control blocks of both (12654, 12650, 12760, 12752) are unit 102's.
# The other instantiations (over comum's and vota's classes, and the three of
# CDataTextFmt<comum::(anonymous namespace)::CComparecimentoMesariosDS>) wait for those classes, but for two that unit
# 121 brings: CDataText<vota::CEscolheOpcao::COpcaoDS>, whose GetText (10685) matches, and CDataText<comum::CRespostasDSNumero>;
# its fragment says what their other rows wait for.
#
# Measured by compiling each form as an overlay of the header and comparing the object's functions, 87 of them, with
# call targets and object-local indices masked. Forms that change no function of this unit:
#   CTextSource::operator()() returning std::string; operator()(const std::string&) defined `inline` after the class;
#   std::snprintf, or 512 for sizeof; `return std::string(texto);`; the destructors declared `= default` in the class;
#   GetText declared `inline`; CDataText's T as `const T&`; CDataTextFmt's string by value, copied into the member, and
#   CQRCodeImage's std::function the same way (these three change only the stand-ins' own helpers, allocate_shared and
#   construct_at); CQRCodeImage's first parameter without `const`; the roots compiled with -fno-strict-aliasing, which was
#   UENUX2_CXXFLAGS's difference from APP_CXXFLAGS while the tree built at -O2.
# The roots compiled with UENUX2_CXXFLAGS (-O3 -fno-strict-aliasing -std=c++23) and with APP_CXXFLAGS: 131 of the 132
# functions the two objects share compare equal (133 at APP_CXXFLAGS); what differs is the stand-in TextoFuncao and the
# allocate_shared it inlines at -O3, so every instance the object emits, 3661 among them, is the same at the tree's
# flags; 12632's and 12649's GetText, which link from unit 102's roots object, are the same code in both.
# Forms measured not to:
#   operator()(const std::string&) without `inline`: it stays out of line in the object and binaryen inlines it into 10746,
#   whose row is then `differs` at +0x3, with an outer block and the string's address in a local;
#   `final` on either template: 24 functions differ, the D2s and D0s among them. The target's D2s begin with the vptr store.
#
# Each of the seven __get_deleter matches holds the address of a __shared_ptr_default_delete type's _ZTS string, which
# no typeinfo names, so only its content places it. resolveBytes in asmlift-wasm/src/splat-symbols.ts looks for a
# typeinfo name's bytes at any alignment, as clang emits one at alignment 1 (docs/reference/facts/splat.md section S9),
# so where the roots object puts these strings in our link changes no match, and the order of its sink lines is free:
# it changes no function's bytes either.
#
# CTextSource's constructor, with the record at 37:19, is written and in no object: no stand-in builds a CTextSource. Built
# once to measure it, the record is the target's (check_srcloc --strict, 1 of 1). Writing it took the stubs of fns 1150
# (1768 B) and 652 (4609 B): both inline it, it is their only record, and tools/round/stubs.py counts a function whose
# record lines all hold code as written. Neither is written; no evidence names their file.
UENUX2_SRCS += src/api/gui/cqrcodeimage.cpp
$(ROOT)/$(APP)/79-uenux2-cdatatext-pending.o: $(ROOT)/src/units/79-uenux2-cdatatext-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/79-uenux2-cdatatext.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/79-uenux2-cdatatext-pending.cpp -o $(R)
W79_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/79-uenux2-cdatatext-roots.o: $(ROOT)/src/units/79-uenux2-cdatatext-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/79-uenux2-cdatatext.mk $(W79_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/79-uenux2-cdatatext-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/79-uenux2-cdatatext-pending.o $(APP)/79-uenux2-cdatatext-roots.o
