# uenux2 comum::gravadores over comum::EUeComumGravadoresError (app/comum/gravadores/euecomumgravadoreserror.h), in the
# files the records name, paths relative to src/uenux2:
# - CBaseError<comum::EUeComumGravadoresError, SErrorLimits{8600, 8800}>'s constructor (target fn 283, a thunk of fn 710
#   that passes the vptr 1552984), which the header's alias instantiates; the symbol file names it by that vptr.
# - comum::CGravadorUtil (src/app/comum/gravadores/cgravadorutil.{h,cpp}): ConverteFase (target fn 2274, record :97).
#   DeterminaNomeArquivo (fn 3798, a chosen name) with DeterminaNomeArquivoSemLetra (records :28, :33, :38), which
#   binaryen inlines into it (its second stack frame), matches at the tree's -O3 (below).
# - comum::asn::ConverteSerialFlash (target fn 3605, records :26 and :31) and DesconverteSerialFlash (fn 3604, record
#   :54, matched at the tree's -O3: below) in src/app/comum/gravadores/asn/util.cpp, with the header util.h beside it.
# - comum::md::CVersoesArquivos's constructor (target fn 5867) with ValidaCriacao (records :28, :33), which binaryen
#   inlines into it, in md/cversoesarquivos.cpp, the class header beside it; libc++'s hinted emplace into its
#   std::map<std::string, std::string> (fn 1221) comes from that object. The hinted __find_equal it calls (fn 1346,
#   matched under the symbol of std::map<std::string, unsigned short>'s, a twin: the two compare only the key) comes
#   from the tree root app/roots_boost.o, whose byte-identical instance is ahead of that object's in the link.
# - comum::IGravador's constructor (fn 1396) with IResultado's (record iresultado.cpp:40) inlined by binaryen, written
#   in iresultado.cpp and matched at the tree's -O3 (below); comum::CGravadorWSQ's constructor (target fn 3796) with
#   ValidaTipoBiometria (record cgravadorwsq.cpp:73) inlined by clang; comum::CGravadorRCSecao::CriaIdentidadeEleitor
#   (target fn 5845, record cgravadorrcsecao.cpp:230). The class heads are unit 60's (igravador.h, iresultado.h,
#   cgravadorwsq.h) and the head-only cgravadorrcsecao.h; this unit declares there the constructors and members it
#   writes.
# - IResultado's destructor (fn 12090, unit 60's match): its copy in the link now comes from iresultado.cpp.o, which
#   emits IResultado's vtable with the constructor, ahead of unit 102's roots object; the same symbol, and it still
#   matches.
# - CGravadorRCSecao's implicit deleting destructor (fn 11615, slot 1): its vtable is emitted in
#   122-uenux2-app-comum-gravadores-pending.cpp, whose trap of GravaResultado (fn 11616, slot 7, record
#   cgravadorrcsecao.cpp:110) is the class's key function; the roots keep that vtable. cgravadorrcsecao.h gives the
#   class its layout (60 bytes, from fn 12098, which builds it); slot 0 holds IResultado's destructor (fn 12090).
# - Two inline accessors under chosen names, CConfiguracaoEleicao::GetPleito() and md::CPleito::GetID(): fn 3798 formats
#   the word at +28 of CConfiguracaoEleicao, its CPleito's identifier. With the unit's edits of headers (these two and
#   unit 60's), every object the link held before is byte-identical (542 objects, sha1 before and after).
#
# Evidence: the records give each member's name, file, line and column, and the signatures; the codes, the messages and
# the bodies give the rest. The enum's values are the codes every thrower passes to fn 283 and the two that fns 3825 and
# 3826 pass to their merged body 6044 (docs/reference/facts/placing.md P6). IGravador's constructor is in iresultado.cpp
# by choice, one the data allows: IGravador's vtable (@1553648) follows that file's record (@1553632), so the object
# that emits it (the key function's, or the vtable's first user's: docs/reference/facts/placing.md P4) can be
# iresultado.cpp's. The constructor has no record, and a record-less object between that record and
# ccabecalhoentidade.cpp's (@1553700) would give the same order; its line there is a choice too.
# Chosen: the enumerators' names, the header paths, DeterminaNomeArquivo's name, the two accessors' names, the
# CVersoesArquivos map alias, the constructors' parameter types beyond what the records spell (CGravadorWSQ's tipo de
# biometria as unsigned int and its last argument as bool, from the unsigned compare and the byte store), the lines of
# the functions with no record (each above the function it calls, DeterminaNomeArquivo after the one it calls), that
# CriaIdentidadeEleitor, ValidaCriacao and ValidaTipoBiometria are private, `.Get()` where DeterminaNomeArquivoSemLetra
# formats the identifiers, and every member and parameter name.
#
# Forms measured in this unit's link (pnpm wasm score against the target, then the scan):
# - ConverteFase lists its cases 't', 's', 'o'. In the order 'o', 's', 't' the switch starts with 49 and sets 51 in a
#   block, where the target starts with 51 and sets 49: 20 rows differ, three of them the two constants and the
#   br_table's targets, and the order written matches.
# - ConverteSerialFlash fills `char byte[3] = {0}` and then its two digits, and keeps HexToInt's result in a local
#   before push_back. An initializer list {c0, c1, '\0'} stores the NUL after the digits, where the target stores it
#   first, and push_back(HexToInt(byte)) in one expression frees the temporary string after the push_back, where the
#   target frees it before: 68 over 367 rows with both, a match with neither. Each was not measured alone.
# No other spelling was measured, so no form here is listed as giving the same bytes.
#
# Matched only at the tree's -O3:
# - 3798 DeterminaNomeArquivo and 3604 DesconverteSerialFlash call std::string::append(const char*, size_t) in the
#   target (fn 160), which clang inlines at -O2 and calls at -O3: compiled by tools/round/try-tu.sh --symbols at -O2,
#   the objects of cgravadorutil.cpp and gravadores/asn/util.cpp call __grow_by_and_replace in both functions, and
#   with --flags -O3 they call append(const char*, size_t). At -O2 they scored 200 over 954 rows and 121 over 346. At the
#   tree's -O3 3604 matches, and 3798 scored 82 over 862 (72 operand-only, 10 inserted) while comum's ID names were
#   iresultado.h's CBaseType aliases, which masked the zone and the section it takes with 65535 where the target
#   compares them with no mask. Since those names are plain integers (143-uenux2-cidentificacao.mk has the
#   measurement), 3798 compares them with no mask, as the target does, and matches at the tree's -O3.
# - 1396 IGravador's constructor equalled the target's but for operands (20 over 239 rows), and the scan read it
#   `unresolved self-voted`: its call of 3798 was the only vote for 3798's name. It matches since 3798 does.
#
# Not matched, and what each waits for:
# - The gravadores/md data classes, CConversorTipoApuracaoSA and the other recorders' destructors are unit 136's.
#   CVersoesContratos::GetValor and CDependenciasContratos::GetValor (3825, 3826, the merge thunks of 6044) wait for the class whose constructor
#   (fn 5480) both build and whose map their find (fn 10877) and end (fn 5481) read; 6044 and 10877 wait for them.
# - fn 5841, which converts a comum::md::CComparecimentoMesario into ecourna's CComparecimentoMesario (fn 3486): its one
#   caller is GravaResultado (fn 11616), which calls it twice. Written as a private const member of CGravadorRCSecao
#   after CriaIdentidadeEleitor, it builds a CNumeroInscricaoEleitoral from a copy of the poll worker's identifier, a
#   CRegistroIdentificacaoEleitor over a std::make_shared copy of it, the time by from_time_t(ConvertToLocalTime()) and
#   the collection state, and in the whole link (pnpm wasm score against the target) it scored 44 over 278 rows: every
#   row but those of the state was the target's up to operands. The target computes the state in a block (result
#   i32) after ConvertToLocalTime's call, the shape of a function binaryen inlines into its one caller (a reading: the
#   mapping written in the same TU, as a switch or as ifs, came before that call under try-tu.sh --single, and kept out
#   of line it came after). Out of line in cgravadorutil.cpp, over the poll worker by const reference, three forms
#   (ifs on the state, the flag at +20 and the finger; ifs on the state first; a switch) scored 44, 51 and 51 over 278
#   to 281. The
#   target loads the finger and the byte at +20 only after its test of state 1, tests that byte as `& 1` and combines it
#   with `state == 2` before testing the finger: the forms by reference gave the loads' place and not the rest, and one
#   over the three values by value (run alone, through try-tu.sh --single's template by hand) gave the combination with
#   the loads before the test and no `& 1`. Its remainder not explained and nothing written needing it, it is not
#   written (docs/how-to-decompile.md step 5).
GRAVADORES_SRCS := src/app/comum/gravadores/cgravadorutil.cpp src/app/comum/gravadores/iresultado.cpp \
	src/app/comum/gravadores/cgravadorwsq.cpp src/app/comum/gravadores/cgravadorrcsecao.cpp src/app/comum/gravadores/asn/util.cpp \
	src/app/comum/gravadores/md/cversoesarquivos.cpp
UENUX2_SRCS += $(GRAVADORES_SRCS)
# cgravadorutil.cpp includes app/comum/dados/cconfiguracaoeleicao.h, whose ecourna headers include Boost (as unit 88's
# sources do): an include path, not a flag of the code
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorutil.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# nothing reconstructed calls most of these yet: 122-uenux2-app-comum-gravadores-roots.cpp stands in for the target's
# callers, two call sites each
$(ROOT)/$(APP)/122-uenux2-app-comum-gravadores-roots.o: $(ROOT)/src/units/122-uenux2-app-comum-gravadores-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/122-uenux2-app-comum-gravadores.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -I$(BOOST_HDR) -c src/units/122-uenux2-app-comum-gravadores-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/122-uenux2-app-comum-gravadores-roots.o
# CGravadorRCSecao::GravaResultado is not reconstructed: 122-uenux2-app-comum-gravadores-pending.cpp gives it a trapping
# body, compiled with the tree's flags, and emits the class's vtable and implicit deleting destructor
$(ROOT)/$(APP)/122-uenux2-app-comum-gravadores-pending.o: $(ROOT)/src/units/122-uenux2-app-comum-gravadores-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/122-uenux2-app-comum-gravadores.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/122-uenux2-app-comum-gravadores-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/122-uenux2-app-comum-gravadores-pending.o
