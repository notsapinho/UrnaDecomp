# uenux2 comum::gravadores over comum::EUeComumGravadoresError (app/comum/gravadores/euecomumgravadoreserror.h), in the
# files the records name, paths relative to src/uenux2:
# - CBaseError<comum::EUeComumGravadoresError, SErrorLimits{8600, 8800}>'s constructor (target fn 283, a thunk of fn 710
#   that passes the vptr 1552984), which the header's alias instantiates; the symbol file names it by that vptr.
# - comum::CGravadorUtil (src/app/comum/gravadores/cgravadorutil.{h,cpp}): ConverteFase (target fn 2274, record :97).
#   DeterminaNomeArquivo (fn 3798, a chosen name) with DeterminaNomeArquivoSemLetra (records :28, :33, :38), which
#   binaryen inlines into it (its second stack frame), is written and does not match (below).
# - comum::asn::ConverteSerialFlash (target fn 3605, records :26 and :31) and DesconverteSerialFlash (fn 3604, record
#   :54, written, not matched) in src/app/comum/gravadores/asn/util.cpp, with the header util.h beside it.
# - comum::md::CVersoesArquivos's constructor (target fn 5867) with ValidaCriacao (records :28, :33), which binaryen
#   inlines into it, in md/cversoesarquivos.cpp, the class header beside it; libc++'s hinted emplace into its
#   std::map<std::string, std::string> (fn 1221) comes from that object. The hinted __find_equal it calls (fn 1346,
#   matched under the symbol of std::map<std::string, unsigned short>'s, a twin: the two compare only the key) comes
#   from the tree root app/roots_boost.o, whose byte-identical instance is ahead of that object's in the link.
# - comum::IGravador's constructor (fn 1396) with IResultado's (record iresultado.cpp:40) inlined by binaryen, written in
#   iresultado.cpp and not matched (below); comum::CGravadorWSQ's constructor (target fn 3796) with ValidaTipoBiometria
#   (record cgravadorwsq.cpp:73) inlined by clang; comum::CGravadorRCSecao::CriaIdentidadeEleitor (target fn 5845,
#   record cgravadorrcsecao.cpp:230). The class heads are unit 60's (igravador.h, iresultado.h, cgravadorwsq.h) and the
#   head-only cgravadorrcsecao.h; this unit declares there the constructors and members it writes.
# - IResultado's destructor (fn 12090, unit 60's match): its copy in the link now comes from iresultado.cpp.o, which
#   emits IResultado's vtable with the constructor, ahead of unit 102's roots object; the same symbol, and it still
#   matches.
# - CGravadorRCSecao's deleting destructor (fn 11615, slot 1, 42 B) has no body of ours, and its row stays
#   `no-candidate`: its stub left cgravadorrcsecao.cpp once CriaIdentidadeEleitor was defined there (stubs.py counts a
#   virtual member of a class our sources define). It waits for the class's vtable, which a written key function
#   (GravaResultado, fn 11616, slot 7, or an out-of-line destructor) emits in cgravadorrcsecao.cpp's object.
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
# Not matched, and what each waits for:
# - 3798 DeterminaNomeArquivo and 3604 DesconverteSerialFlash call std::string::append(const char*, size_t) in the
#   target (fn 160), which clang inlines at this tree's -O2 and calls at -O3: compiled by tools/round/try-tu.sh
#   --symbols, the objects of cgravadorutil.cpp and gravadores/asn/util.cpp call __grow_by_and_replace in both
#   functions, and with --flags -O3 they call append(const char*, size_t). They scored 200 over 954 rows and 121 over 346
#   in the link of this unit's landing. -O3 for uenux2 is the user's decision. Since comum's names are plain integers
#   (143-uenux2-cidentificacao.mk has the measurement), 3798 compares the zone and the section it takes with no mask, as
#   the target does, and scores 191 over 944 rows.
# - 1396 IGravador's constructor equals the target's but for operands (20 over 239 rows), and the scan reads it
#   `unresolved self-voted`: its call of 3798 is the only vote for 3798's name. It matches when 3798 does, or when
#   another caller of 3798 (fns 1276, 12134) lands.
# - Not written: CEnvelopeGenerico::ValidaCriacao (3822), CEntidadeHashes::ValidaCriacao (5855), CUrna::ValidaCriacao
#   and constructors (5862, 2854, 2855), the converters of CConversorEnvelopeGenerico, CConversorTipoApuracaoSA,
#   CConversorCorrespResultado and CConversorUrna (10270, 10271, 10282, 10283, 10288, 10289, 10284, 10287) and
#   CCorrespondenciaResultado (2801): each needs its data class's layout, which no header of ours has (CUrna's
#   constructors copy an 88-byte identification at +16 whose 76-byte part fn 1557 copies). CVersoesContratos::GetValor
#   and CDependenciasContratos::GetValor (3825, 3826, the merge thunks of 6044) wait for the class whose constructor
#   (fn 5480) both build and whose map their find (fn 10877) and end (fn 5481) read; 6044 and 10877 wait for them.
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
