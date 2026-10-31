# uenux2 comum::CRelatorioTesteImpressora, the printer test report, in src/app/comum/relatorios/: its overrides in
# crelatoriotesteimpressora.cpp (the file of its records), the class in crelatoriotesteimpressora.h, its base
# comum::CImprimirExtratoCarga in cimprimirextratocarga.h, and the callee comum::CRelUtil::GetSeparadorFase in crelutil.cpp
# (its record's file) with crelutil.h and euecomumrelatorioserror.h, the error it throws.
#
# Matched: the overrides TemHorarioVerao, EhTreinamento, GetHorarioVerao, GetCabecalho, EhEleicaoComunitaria,
# EhModoDemonstracao, GetNomeEleicao, GetPleito, GetTipoUrna, GetUF, GetTitulo, GetMensagemEncerramento,
# GetMensagemCondicoes and GetSeparadorFase (target fns 11202, 11201, 11199, 11195, 11194, 11193, 11192, 11191, 11190,
# 11189, 11187, 11186, 11184, 11183: slots 3, 2, 7, 11, 12, 22, 13, 14, 17, 16, 21, 18, 19, 20 of the vtable @1576652);
# CRelUtil::GetSeparadorFase (1919, record crelutil.cpp:554:23) and CBaseError<EUeComumRelatoriosError>'s constructor
# (580, the thunk of binaryen's 710 for that enum). The base's GetConteudosQRCodeAdicionais (slot 6) is the body of 902,
# whose match line it takes over from RHVoice's language_info::get_country, a twin.
#
# Written and not matched: GetCorrespondencia (11197, slot 9) is `unresolved`: it calls CDadoCorrespondencia's copy
# constructor, fn 1249 in the target, which no evidence names. The target's 1249 has landing pads (invoke_iii), so it
# is not a uenux2 object's copy, and ours (from this unit's object) differs from it: 188 over 232 rows. 11197 itself is
# 3 over 9 rows, all operand-only (`pnpm wasm score`), with the roots' stand-in for 1249's other callers.
#
# Pending, in the -pending.cpp, whose header says what each waits for: ImprimeDataHoraEmissao (11216, slot 25, the base's),
# GetConteudoQRCode (11200), EstaEmHorarioVerao (11198), InicializaTradutorFrase (11196), GetDadosLocal (11188).
# Not reconstructed: the constructor (5586, declared; its stub stays in crelatoriotesteimpressora.cpp): it calls
# api::CDateTime's 1382 and 1261, which no evidence names yet, and 2787, 2788. Slots 4, 23 and 24 are the base's defaults,
# bodies binaryen shares (434, 425), matched under other classes' names; slots 0 and 1 are the implicit destructors,
# 174 and 144, shared too.
#
# Where things are. crelatoriotesteimpressora.cpp's one record is line 173 (ConverteTipoAlimentacao, inlined into
# GetDadosLocal, not written), and it stays blank. The members are defined in the order of their target indices, a higher
# index first: inside the use-1 band that is the link order (docs/how-to-decompile.md step 3), 11202 to 11189 before 11188
# and 11187 to 11183 after; their lines are chosen. cimprimirextratocarga.h's path and the base's slot names are chosen;
# that header says what places the base in a file of its own (its typeinfo, and 11216 in the band). crelutil.h,
# euecomumrelatorioserror.h and crelatoriotesteimpressora.h are chosen paths beside the sources.
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
# inline into its one caller here: w123_copia for 1249's (without it binaryen inlines the copy and 11197 scores 204 over
# 208), w123_separador for 1919's (without it 11183 scores 388 over 390, measured on an earlier form of 1919), w123_erro for 580's 13 other throwers (without it
# binaryen inlines the constructor into 1919, 90 over 387, and neither 580 nor 1919 matches). w123_erro can go when a
# second thrower of EUeComumRelatoriosError lands (CCalculaCV::IncluiString, fn 942, is one), w123_separador when one of
# 2785, 11943, 11946, 12105 or 12110 does.
#
# Not kept: an inline static setter of comum::md::CTradutorFrase's map (ctradutorfrase.h) for InicializaTradutorFrase,
# which stays pending (the -pending.cpp header has the measurement).
CRELATORIOTESTEIMPRESSORA_SRCS := src/app/comum/relatorios/crelatoriotesteimpressora.cpp src/app/comum/relatorios/crelutil.cpp
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
