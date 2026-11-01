# uenux2 comum::CRelatorioTesteImpressora, the printer test report, in src/app/comum/relatorios/: its overrides in
# crelatoriotesteimpressora.cpp (the file of its records), the class in crelatoriotesteimpressora.h, its base
# comum::CImprimirExtratoCarga in cimprimirextratocarga.h with its one out-of-line member in cimprimirextratocarga.cpp, and
# the callee comum::CRelUtil::GetSeparadorFase in crelutil.cpp (its record's file) with crelutil.h and
# euecomumrelatorioserror.h, the error it throws; and CRelUtil's GetIDCargaFormatado and IncluiAvisoModoDemonstracao in
# crelutil.cpp (below).
#
# Matched: the overrides TemHorarioVerao, EhTreinamento, GetHorarioVerao, EstaEmHorarioVerao, GetCorrespondencia,
# GetCabecalho, EhEleicaoComunitaria, EhModoDemonstracao, GetNomeEleicao, GetPleito, GetTipoUrna, GetUF, GetTitulo,
# GetMensagemEncerramento, GetMensagemCondicoes and GetSeparadorFase (target fns 11202, 11201, 11199, 11198, 11197, 11195,
# 11194, 11193, 11192, 11191, 11190, 11189, 11187, 11186, 11184, 11183: slots 3, 2, 7, 8, 9, 11, 12, 22, 13, 14, 17, 16,
# 21, 18, 19, 20 of the vtable @1576652); the base's ImprimeDataHoraEmissao (11216, slot 25); CRelUtil::GetSeparadorFase
# (1919, record crelutil.cpp:554:23) and CBaseError<EUeComumRelatoriosError>'s constructor (580, the thunk of binaryen's
# 710 for that enum); and three libc++ instances InicializaTradutorFrase brings, from this unit's object:
# pair<const char, CLabelParametrizado>'s constructor from a char and a label (1552) and its copy constructor (5793), and
# the label map's __assign_multi (5794, found by content; its target callers are 11196 and 7787, and it holds the address
# of CTradutorFrase's map). The map's __tree::destroy (1706), matched before from ctradutorfrase.cpp.o, comes from this
# object now, which links first. The base's GetConteudosQRCodeAdicionais (slot 6) is the body of 902, whose match line
# it takes over from RHVoice's language_info::get_country, a twin.
# - EstaEmHorarioVerao (11198) tests the date of api::CDateTime::Now() (fn 479) against the CHorarioVerao of CHV through
#   comum::md::CHorarioVerao::Contem, out of line in chorarioverao.cpp (unit 147, which has the two forms measured).
# - GetCorrespondencia (11197) calls CDadoCorrespondencia's copy constructor, fn 1249 in the target, which has landing
#   pads (invoke_iii), so the target's copy is an -fexceptions object's, and ours, from this unit's object, differs from
#   it (188 over 232 rows). A callers+content hand line of splat/symbol_addrs.txt names 1249 from its body and from
#   11197's call; 11197 (3 over 9 rows, all operand-only, with the roots' stand-in for 1249's other callers) matches over
#   it, and with the line out it is `unresolved` again.
# - ImprimeDataHoraEmissao (11216) prints "EMISSAO DO RELATORIO" and one std::format line of the date and the time, from
#   api::CDateTime::FormatCurrentDate and FormatCurrentTime (fns 5472, 5473, unit 125's callbacks, which match at the
#   tree's -O3 with their callees 706 and 779). The four
#   strings of the second line (the two formats and the two results) are destroyed after its call, the last built first,
#   which reads as one statement holding the format and both calls, as written; other forms were not linked. The style 1
#   and the alignments 2 and 0 are the constants the target passes (IPaper::EStyle has no enumerators, ipaper.h).
#
# Written and not matched: InicializaTradutorFrase (11196, slot 10) builds a std::map<char, CLabelParametrizado> of the
# four labels of CConfiguracaoEleicao's CParametrosUrna ('M' municipio, 'Z' zona, 'S' secao, 'P' partido) and hands it
# to CTradutorFrase::SetLabels (ctradutorfrase.h). It differs at -O2 and at the tree's -O3: the target calls the map's initializer-list constructor (fn 5795, which holds the insertion
# inlined), and at -O2 clang inlines that constructor into 11196, 281 over 345 rows (`unresolved` on the insertion's
# __emplace_hint_unique_extract_key, which the target has inside 5795). In a private link with this TU at -O3 and a
# scratch second caller of the constructor in it (standing for 7787, the target's other caller), 11196 scores 20 over
# 289 and 5795 1 over 172, all operand-only; without that second caller binaryen inlines the constructor into 11196 (212
# over 453, as in the whole link at the tree's -O3). So 5795 needs a stand-in for 7787 here. The list handed straight to the setter keeps the constructor
# out of line at -O3 too, in a probe object; it was not linked.
#
# Pending, in the -pending.cpp, whose header says what each waits for: GetConteudoQRCode (11200), GetDadosLocal (11188).
# Not reconstructed: the constructor (5586, declared; its stub stays in crelatoriotesteimpressora.cpp): it calls
# 1382 and 1261, which unit 125 matches as api::CDate's default constructor and operator<=> (the latter's name chosen
# there), and 2787, 2788, which have no name. Slots 4, 23 and 24 are the base's defaults,
# bodies binaryen shares (434, 425), matched under other classes' names; slots 0 and 1 are the implicit destructors,
# 174 and 144, shared too.
#
# Where things are. crelatoriotesteimpressora.cpp's one record is line 173 (ConverteTipoAlimentacao, inlined into
# GetDadosLocal, not written), and it stays blank. The members are defined in the order of their target indices, a higher
# index first: inside the use-1 band that is the link order (docs/how-to-decompile.md step 3), 11202 to 11189 before 11188
# and 11187 to 11183 after; their lines are chosen. cimprimirextratocarga.h's path and the base's slot names are chosen;
# that header says what places the base in a file of its own (its typeinfo, and 11216 in the band), whose one function's
# lines are chosen. crelutil.h, euecomumrelatorioserror.h and crelatoriotesteimpressora.h are chosen paths beside the
# sources.
#
# What the bytes decide, measured with `pnpm wasm score` in the whole link:
# - GetTipoUrna reads the urna's type through CDadoCarga::GetTipoUrna, an inline member of cdadocarga.h (unit 93's header,
#   one line added): the target keeps GetGeral() + 32 apart from the select of 4 or 8, the shape a member clang simplifies
#   before it inlines it gives. The same ternary written in the slot folds to a select of 36 or 40 (11 over 62, 2 rows
#   deleted), and the member out of line in cdadocarga.cpp, which binaryen inlines, gives 17 over 67. The inline member
#   gives 7 over 62, all operand-only. The constructor (5586) holds the same shape.
# - GetSeparadorFase (1919) builds its CInformacaoEleicao as a named local: as a temporary in the if, its frame differs
#   (111 over 346). Its cases run SIMULADO, TREINAMENTO, OFICIAL: in phase order the br_table is [3 0 1] where the target's
#   is [1 3 0] (45 over 343). The if/else around the switch puts the throw at column 23, a choice among forms that do.
# Chosen, the other way not linked: the slots' const; GetTipoUrna's switch; the getters this unit adds and their return
# by reference (cconfiguracaoeleicao.h, cestadogeral.h, chv.h, cpe.h, cprocessoeleitoral.h, cdadocarga.h: inline, chosen
# names, no layout changed; every other object compiles to the same bytes with them, cmp before and after).
#
# The type at CConfiguracaoEleicao + 88. EhModoDemonstracao and 1919 build comum::CInformacaoEleicao on it. That header
# (unit 111) took a struct of its own there, SDadosInformacaoEleicao; cconfiguracaoeleicao.h holds an
# ecourna::app::dados::CParametrosUrna, whose fields are at the offsets CInformacaoEleicao's members read. Its constructor
# takes that class now: 603's match line follows the new symbol (a rename, splat-match), and the masked disassembly of
# cinformacaoeleicao.cpp's object is the same before and after.
#
# Roots (123-uenux2-crelatoriotesteimpressora-roots.cpp): the vtable's address, as the constructor stores it, and three
# stand-ins for callers not reconstructed, each of a function with several callers in the target that binaryen would
# inline into its one caller here: w123_separador for 1919's (without it 11183 scores 388 over 390, measured on an earlier form of 1919), w123_erro for 580's 13 other throwers (without it
# binaryen inlines the constructor into 1919, 90 over 387, and neither 580 nor 1919 matches). w123_erro stands for the
# nine throwers not in the link (the roots file lists them; 942 and 2786 are in it) and goes with the last, and
# w123_separador when one of 2785, 11943, 11946, 12105 or 12110 does. w123_copia, which stood for 1249's other callers
# (without a second caller binaryen inlines the copy and 11197 scored 204 over 208), went before all of them landed, on
# a link without it that moves no row: 11395 (unit 93) calls 1249 three times and reads its result as the stand-in did,
# and with it out 11197 and 5856 (unit 160) keep `match` (without 11395 in the link they left it: `+0xf target drop |
# ours +0xf end` in 11197's scan row); 5637, 5740 and 12098 still wait. The third, w123_labels, stands for 7787's call of 5794 through SetLabels, so that 5794 keeps two call sites; it goes when 7787
# lands.
#
# CRelUtil's other written members, in crelutil.cpp (that file's note gives their lines):
# - GetIDCargaFormatado (target fn 2786, record crelutil.cpp:69:15) joins seven three-character pieces of the load code
#   with "." and the rest from position 21, and throws CUeComumRelatoriosError 9085 with the code between brackets when
#   the code has 20 characters or fewer. The test comes first with the throw inside it: written as an else after the
#   return, the compare came out as `i32.ge_u 21` where the target has `i32.gt_u 20`, and the success path's temporaries
#   8 bytes higher in the frame (198 over 1144 rows, 3 not operand-only); as written, 40 over 1144, all operand-only, the one operand that is
#   no call and no data address being the thrown object's destructor's table slot (69, fn 4636). Measured with
#   `pnpm wasm score` against our plain link.
# - IncluiAvisoModoDemonstracao (fn 5583, no record) reads as a CRelUtil member: its callers are IncluiCabecalhoEleicoesMZS
#   (fn 1543, record crelutil.cpp:307) and fn 5591, and it tests CInformacaoEleicao::EhModoDemonstracao as
#   GetSeparadorFase does. It adds the demonstration-mode line, centred in style 1, and two blank lines: 10 over 69,
#   all operand-only. Its name, its lines and its being a static member are chosen.
# Their callers are not reconstructed. w123_idcarga stands for 2786's four (5579, 11256, 12105, 12110) and
# w123_demonstracao for 5583's two (1543, 5591): each calls its function twice, as the target's several callers do; each
# goes when every caller it stands for is in the link.
CRELATORIOTESTEIMPRESSORA_SRCS := src/app/comum/relatorios/crelatoriotesteimpressora.cpp src/app/comum/relatorios/crelutil.cpp \
                                  src/app/comum/relatorios/cimprimirextratocarga.cpp
UENUX2_SRCS += $(CRELATORIOTESTEIMPRESSORA_SRCS)
# cconfiguracaoeleicao.h reaches ecourna's chorariosurna.hpp, which includes Boost (unit 88 adds the path the same way)
$(addprefix $(ROOT)/$(APP)/uenux2/,$(addsuffix .o,$(CRELATORIOTESTEIMPRESSORA_SRCS))): UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# the pending and roots objects include the class header, which reaches ecourna and uenux2 headers alike
W123_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/123-uenux2-crelatoriotesteimpressora-pending.o: $(ROOT)/src/units/123-uenux2-crelatoriotesteimpressora-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/123-uenux2-crelatoriotesteimpressora.mk $(W123_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/123-uenux2-crelatoriotesteimpressora-pending.cpp -o $(R)
$(ROOT)/$(APP)/123-uenux2-crelatoriotesteimpressora-roots.o: $(ROOT)/src/units/123-uenux2-crelatoriotesteimpressora-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/123-uenux2-crelatoriotesteimpressora.mk $(W123_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/123-uenux2-crelatoriotesteimpressora-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/123-uenux2-crelatoriotesteimpressora-pending.o $(APP)/123-uenux2-crelatoriotesteimpressora-roots.o
