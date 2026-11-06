# ecourna: the core app/dados/asn converters (CConversorTurno, Fase, CargoID, Foto, CabecalhoEntidade,
# IdentificadorEleitor, parametrizacaourna/LabelParametrizado, TituloRelatorio, ParametrosUrna), the data classes they
# build that have out-of-line bodies (CFoto, CCabecalhoEntidade) and the ASN.1 date-time helpers (asn/datahoraasn.cpp).
# cconversorturno.cpp is saved as UTF-8, not Latin-1 (.editorconfig's UTF-8 section): the target holds the
# "Turno inválido." both converters throw (9192/9191) as UTF-8 bytes at 367628, the one UTF-8 text string
# ledger/strings.tsv lists (its other `utf8` rows are binary data), and has no Latin-1 copy of it.
# CConversorLabelParametrizado::DesconverterGeneroLabel's cases run neutro, feminino, masculino. Evidence: 9167's br_table
# is [1 2 4 0 3] 2, and of the six orders of the three cases only this one gives it (measured on the object: the enum's
# order, for one, gives [1 2 4 3 0] 2).
# ecourna::app::dados::asn::FormataHora (fn 2686), added since in asn/datahoraasn.cpp: the time of day of a
# boost::posix_time::ptime as "{:02}:{:02}:{:02}" (8945), its hours, minutes and seconds as three long long (argument
# types 4228). Evidence: it reads the ptime's 64-bit count through its second parameter; for INT64_MAX - 1, INT64_MAX and
# INT64_MIN (boost's not_a_date_time, pos_infin and neg_infin) it takes the hours, minutes and seconds of that count
# itself, +-2562047788, 0 and +-54, else of the count modulo 86400000000, the microseconds of a day: time_of_day()'s
# hours(), minutes() and seconds(), spelled as ConverteDataHora spells them; its calls that can throw go through
# invoke_*, with a landing pad that ends in __resumeException, an -fexceptions object's code. Its one target caller,
# vota::CImpressaoPU::StartState (11902, unit 176's), calls it four times, each next to a call of fn 2687, which
# formats a date as "{:02}/{:02}/{:04}" over boost's from_day_number (1376) and was not written then (fragment 265's
# FormataData now); its stand-in, in fragment 234's roots, went once 11902 was in the link. pnpm wasm score before step 8:
# 21 over 317 rows, all operand-only; the census paired it (shape) and the scan matched it. Chosen: the name and the
# file, a choice against the band: in band 4, 2687, 2686 and 2685 (a thunk into 6155, the body binaryen merges with
# ConverteDataHora's 9220) lie between api/compression/czip.cpp's 2690 and api/security/csha.cpp's 2684, where the data
# hold icompressor.cpp's, cfile.cpp's, base64.cpp's, chkdfseed.cpp's and ckey.cpp's records and no date class, and
# ConverteDataHora (band 1) lies among app/dados/asn's converters. The file is the one whose function 2685 shares a body
# with, a weak reason: binaryen's merge is module-wide and ties no TU, and an ecourna api/ file between czip.cpp and
# csha.cpp, where the band puts it, is the better reading. The parameter is not by value, which the bytes rule out:
# ptime is trivially copyable, and a probe function taking one by value compiles to `(i64) -> i64`, by const
# reference to `(i32) -> i64` (em++ -O2 -std=c++23 over Boost's headers), and 2686 takes an address. A const
# reference, as ConverteDataHora takes, over a const pointer, which fits the bytes too, is chosen.
# ConverteDataHora (9220) matches since fragment 265: the target's is `f6155(p0, p1, 8913, 8944)`, a thunk into
# binaryen's merge (6155) of its body with that of 2685, which fragment 265 writes, with 2687, as
# ecourna::api::security::ConverteDataHoraSemSeparador in an api/security/ file, by the band above; our link forms the
# same merge once 2685 is in it, and 6155 matches under the merge's name, after ConverteDataHora. Boost's from_day_number
# (1376) and greg_month's and greg_day's on_error (5183, 5182) match from this unit's datahoraasn.cpp.o since then, the
# first ecourna object that emits them, once src/app/roots_boost.cpp leaves them to ecourna's objects (fragment 265).
# ecourna::app::dados::asn::DesconverteDataHora (fn 1877, asn/datahoraasn.cpp) matches since Boost's parse_iso_time
# copy (5851, unit 122's object), whose table slot it passes to invoke_iiii, does. It returns early for a text shorter
# than 9 characters, before it tests the last one for 'Z': the target branches past the 'Z' case on `i32.lt_u` against
# 9, once in each branch of the string's long/short test, which that form gives, where the one condition
# `texto.size() >= 9 && texto.back() == 'Z'` (and `> 8`) gives `i32.le_u` against 8 (llvm-objdump -d of each form's
# object, compiled by tools/round/try-tu.sh --symbols at the directory's flags; in the whole link the one condition
# scored 31 over 420 rows, two of them not operands, pnpm wasm score). `!(texto.size() < 9 || texto.back() != 'Z')`
# gives the same code for the function; an early return on `texto.size() < 9 || texto.back() != 'Z'`, before the
# rewrite, does not (383 of its 462 instructions differ from the early return's, compared position by position). The
# early return is chosen between the two that give the bytes.
# In the whole link 1877 scores 27 over 420 rows, all operand-only, before the scan.
DADOS_ASN_SRCS := app/dados/asn/cconversorturno.cpp app/dados/asn/cconversorfase.cpp app/dados/asn/cconversorcargoid.cpp \
                 app/dados/asn/cconversorfoto.cpp app/dados/asn/cconversorcabecalhoentidade.cpp \
                 app/dados/asn/cconversoridentificadoreleitor.cpp app/dados/asn/datahoraasn.cpp \
                 app/dados/asn/parametrizacaourna/cconversorlabelparametrizado.cpp \
                 app/dados/asn/parametrizacaourna/cconversortitulorelatorio.cpp \
                 app/dados/asn/parametrizacaourna/cconversorparametrosurna.cpp \
                 app/dados/cfoto.cpp app/dados/ccabecalhoentidade.cpp app/dados/parametrizacaourna/cparametrosurna.cpp

# The converters reference the records of the generated ASN.1 modules (built by src/mk/asn1.mk), so the modules
# join the link here.
override EXTRA_OBJS += $(ASN1MOD_OBJS)

# DADOS_ASN_TRY=1 in the environment leaves the converter TUs out, so tools/round/try-tu.sh can compile the same TUs as
# candidates while the module objects above stay linked.
ifndef DADOS_ASN_TRY
ECOURNA_SRCS += $(DADOS_ASN_SRCS)
# prerequisites only (no recipe: the generic rule compiles them): the ASN.1 headers, which the generic rule does not name
$(foreach u,$(DADOS_ASN_SRCS),$(eval $(ROOT)/$(APP)/ecourna/$(subst /,_,$(u)).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# No roots: the target reaches the converters' DoConverte/DoDeconverte only through their vtables, and every vtable
# has a function in the link that stores its vptr, which keeps it as the roots file's sink did: CConversorTurno's 9179
# and 9190, CConversorFase's 9052, 9056, 9179 and 9190, CConversorCargoID's 11349, 11351 and 11352, CConversorFoto's
# 11422 and 11440, CConversorIdentificadorEleitor's 9112 and 9114, CConversorLabelParametrizado's 9156 and 9164,
# CConversorTituloRelatorio's 5102 and 9161. The roots file went with its last sink.
endif
