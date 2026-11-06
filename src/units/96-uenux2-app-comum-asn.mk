# uenux2 comum::asn::Utils in src/app/comum/asn/util.cpp, the records' file: ConverteFase, DesconverteFase,
# ConverteTipoLocalVotacao and DesconverteTipoLocalVotacao (target fns 1712, 2843, 3801, 3800), and DesconverteAbrangencia
# (5827), and DesconverteSexo, which binaryen inlines into CConversorDadosCandidato::DoDesconverte (11450, below);
# CConversorDadoCarga (below); the IDEleitoral, TipoPacote, IDPacote and Sistema conversions, which binaryen inlines into
# comum::asn::CConversorCabecalhoPacote's two slots (11437, 11438, below), with that converter's file and unit 245's two
# others, moved into this list. The class header app/comum/asn/util.h, the error header
# euecomumasnerror.h and the enum EUrnaFase (app/comum/eurnafase.h, which unit 60's cgravadorwsq.h includes in place of
# its opaque `: int`
# declaration: the target formats EUrnaFase through fn 536, formatter<unsigned int>).
#
# Evidence: the records give each member's name and signature, the throws' lines and columns (19 is a throw inside the
# switch, in a default:, for the two Fase members; 11 is a throw after the switch for the other three), and the
# codes, messages and bodies give the rest. A by-value TipoLocalVotacao is the address of the caller's copy (3800's p0).
# The switch tables 497848 and 497860 and the identity ranges give the enums' values.
# Chosen: the names of the enumerators, where ETipoLocalVotacao and md::ETipoAbrangencia are declared, EUrnaFase's
# comum:: scope, the header paths, and that one template over the underlying type formats the enums (util.h). `: int`
# with an explicit formatter<unsigned int> gives the same bodies.
#
# Forms that give the same function, measured in the object with the object-local numbers masked:
# - the switch's `return X::a;` against `return X(X::a);` and `{ X r; r.set_a(); return r; }` (1712, 3801);
# - `default: break;` against no default before the throw after the switch (5827, 3801, 3800);
# - `fase.asInt()` against `static_cast<int>(fase)` in the message (2843, 3800), and `switch (x)` against
#   `switch (x.asInt())` over the entity (2843, 3800);
# - an if chain against the switch in 5827;
# - the formatter's template against an explicit specialization per enum, E by value against `const E&`, and a template
#   context against std::format_context&.
# A local result assigned in the switch and returned after it does not give 1712 or 3801: the constructor moves ahead of
# the check. So the switch returns.
#
# Not matched, and what each waits for:
# 5827 DesconverteAbrangencia formats a generated `int` enum, so its handle is fn 1711, formatter<int>; it matched when
# 11450 below, which stores another slot of 1711 (DesconverteSexo's handle), gave the name a second voter.
#
# DesconverteDataJE (fn 2276) is matched: a DataJE's "YYYYMMDD" into api::CDate through CStringUtils::ToByte and ToWord.
# No record names it (it throws nothing): its name, its place in util.cpp, its line and its being a Utils member are
# chosen, from DesconverteDataHoraJE's record (util.cpp:41) and its callers (1713 and the converters 11365, 11384, 11395).
# The target takes the three substrings before the first call and destroys them after the last: three named locals
# (year, month, day) and CDate(ToByte(dia), ToByte(mes), ToWord(ano)).
# - 1713 DesconverteDataHoraJE is written and `unresolved self-voted`: ModuloTiposEleitorais::DataJE::theInfo (1913204)
#   and HoraJE::theInfo (1913248), the info words of the two temporaries it builds, were named by its own votes alone.
#   DataJE's has a second voter now, ConverteDataJE (3802, below); HoraJE's other reader is the static initializer
#   14478 alone, so 1713 still waits for it. Its body is 21 over 272 rows from the target, all operand-only (pnpm
#   wasm score). The two substrings are named locals (the target destroys them at the end and each DataJE or HoraJE
#   temporary right after its call): with the substrings as temporaries in the calls, 73 over 284 rows, 12 inserted,
#   18 deleted. DesconverteHoraJE (no record; name and line chosen) is api::CTime(hora), which clang inlines into 1713,
#   where the target builds the CTime in a local of its own; the result is api::CDateTime's (CDate, CTime) constructor,
#   inline in api/util/cdatetime.h (a choice). 7671 is its throw's code (EUE_COMUM_ASN_FORMATO_DATA_INVALIDO, a chosen name).
#   ModuloTiposEleitorais::DataJE and HoraJE are new in src/asn1/modules/ModuloTiposEleitorais.{h,cxx}: RTTI gives the
#   names and NumericString bases, 14478 fills their theInfo (8 to 8 and 6 to 6 characters, before DataHoraJE's), and
#   ModuloProcessoEleitoral::Pleito's data field is a DataJE (CConversorPleito, fragment 140, reads it).
# - ConverteDataJE and ConverteDataHoraJE (fns 3802 and 1080) are matched: an api::CDate formatted "YYYYMMDD", and an
#   api::CDateTime's date so, "T" and its time formatted "hhmmss" (fns 706 and 779), into the entity's string type
#   through a temporary of it, the result built from the temporary's characters (fns 1521 and 2190). No record names
#   them (they throw nothing): their names, their being Utils members, their place in util.cpp (after
#   DesconverteHoraJE) and their lines are chosen, from DesconverteDataHoraJE's record and their callers (1080: the
#   converters 10273, 10276, 10291, 11390, 11399 and 11589; 3802: 11385 twice and 11394). The formatted strings are
#   named locals: the target frees each format's literal string before the next call. Fragment 172 has the converters
#   and what was measured; ConverteDataHoraJE's callers are all written (10273 is fragment 321's), so the roots stand
#   in for none of them.
# - 731, the base's default DoConverte and DoDesconverte merged, and 11418, IConversorBiometriaASN's default DoConverte,
#   need -O3, the tree's level since the measurement below (docs/reference/facts/levels.md §V3). Their format strings are 44 and 47
#   bytes. In a body that is only such a throw, the object at -O2 keeps libc++'s search of the format string for a brace
#   (__try_constant_folding, inlined by clang) as a loop: a probe folds up to 36 bytes, and at -O3 up to 74. The target has
#   no such loop for these and keeps one for its strings of 79 bytes and more (10226, 11514, 10772). In a
#   private link with UENUX2_EXTRA=-O3 (facts/app-flags.md §F9 item 6), holding the defaults in iconversorasn.h and
#   comum::asn::CConversorHistoricoVotoImpresso for one inherited DoDesconverte, the shared body gives `target 731:
#   IDENTICAL` from splat-remap; thunks 11360 and 10275 differ in operands only, their call of 731; 11418's rows differ
#   in operands only and its first difference is the record, which a scratch file cannot hold; and every match of the
#   tree still verifies, sha256 the target's. Both are written in their headers since, at the tree's -O3, and match:
#   fragment 159 says what they rest on. CConversorDadosCandidato's slot 2 is that default (11449), emitted here with
#   the vtable.
# - DesconverteIdEleitoral, ConverteTipoPacote, DesconverteTipoPacote, ConverteIdPacote, ConverteIdSistema and
#   DesconverteIdSistema (records util.cpp:89, 231, 329, 344, 419, 451) and DesconverteIdPacote (no record: its name, its
#   being a Utils member and its place after ConverteIdPacote are chosen) are matched inside the two slots of
#   comum::asn::CConversorCabecalhoPacote that hold them, DoDesconverte (11437) and DoConverte (11438), each behind a
#   stack-pointer prologue of its own; the md members they call are fragment 273's. The tables the four Tipo and Sistema
#   switches compile to give md::ETipoPacote's and ESistemaJE's values (app/comum/md/ccabecalhopacote.h). ConverteIdPacote's
#   throw is at column 15, one block deep, so the CIDEleitoral kinds are an if chain whose else throws (a switch's
#   default would put it at 19); the three selections are one setSelection(kind - 1) in the target's body and in ours.
#   DesconverteIdEleitoral keeps a frame of its own inside DesconverteIdPacote's in the target, and clang leaves it out
#   of line in this TU too (-Rpass-missed=inline: cost 330 over a threshold of 250), so binaryen inlines both. The Tipo
#   and Sistema throws format the md enums through fn 536 (table slots 2286, 2287) and the entities' values as int (code 3), the
#   `asInt()` of the other Desconverte members. The switches' spelling (a default only in DesconverteTipoPacote and
#   DesconverteIdEleitoral, and the case order) is chosen, not compared with other forms. ModuloTiposEleitorais::Sistema
#   is the target's RTTI's class (typeinfo name @497739), now a type of its own in src/asn1/modules/ModuloTiposEleitorais.h,
#   and CabecalhoPacote's tipoPacote and idPacote setters take const_reference (11438 builds a temporary of each field's
#   type, docs/reference/facts/asn1.md A3); origem keeps the generated setter of a NamedNumber (11438 stores its value).
#
# ConverteAbrangencia (inlined by binaryen into 11462), ConverteTurno and DesconverteTurno (into 11401 and 11402) are
# here too, at their records' lines; their callers are in fragment 107 and in cconversordadocarga.cpp. No default in the
# first two switches: a `default: break;` gives the same bytes (measured on ConverteTurno's object).
#
# cconversordadocarga.cpp (CConversorDadoCarga, target fns 11401, 11402, 5693, 5694; it moved here from unit 93's list)
# comes after util.cpp in this list, and that order is measured (docs/reference/facts/codegen.md C4), with pnpm wasm
# score. As written, after util.cpp: 11402 matches, and 11401 is 50 over 510 rows, all operand-only. With
# static_cast<int>(turno) for the turn in its throw, 69 over 512, 54 of them operand-only, 2 inserted and 10 deleted. With
# that cast and the converter's object ahead of util.cpp's, in unit 93's list: 11402 is 73 over 652 with 3 inserted and 5
# deleted, and 11401 83 over 513 with 3 and 12. So the order is what makes 11402 match. The cases of DesconverteModelo run
# from ue2022 down: in ascending order the block of 2013 comes first and 11402 is `differs` at +0x24a.
# - 11401 matches since mock/app/comum/cappinfobuilder.cpp links ahead of this object at the executable TU's rule (unit
#   253). It differed first at +0x52 on one operand, as CAppInfo::IndiceTurno (1553) did, unit 109's fragment:
#   ConverteTurno's throw in the target passes the turn as a handle, table slot 474, fn 9868, whose body calls
#   formatter<unsigned int>::format out of line (fn 5906, called by 4027 too), an -Oz copy. Our link merged that handle
#   into fn 536's body, one of its 31 slots, so the two slots voted for two target functions, and a hand line for 536
#   kept its name and the eleven rows that would leave `match` (1712, 2253, 3702, 275, 680, 3801, 5633, 5689, 5900, 11392
#   and 11405). That object's copy of the handle is the link's now, the votes no longer split, and the line went.
#   An explicit `std::formatter<EUrnaTurno> : std::formatter<unsigned int> {}` does not compile: libc++'s format takes an
#   integral.
#
# comum::asn::CConversorDadosCandidato::DoDesconverte (target fn 11450, slot 3 of the class's vtable @1562224) in
# app/comum/dados/asn/candidatura/cconversordadoscandidato.cpp comes after util.cpp in this list, and that order is
# measured: it inlines Utils::DesconverteSexo (record util.cpp:483) and CDadosCandidato's constructors, out of line in
# 124-uenux2-app-comum-dados-asn.mk's cdadoscandidato.cpp. Linked ahead of util.cpp (in fragment 124, which sorts
# before 96), 11450 scores 108 over 1389 rows with 2 inserted and 4 deleted, the inlined switch's result copied into
# another local; after it, 80 over 1387, all operand-only, and it matches. The rest of 11450's evidence and choices are
# fragment 124's, with its data class. DesconverteSexo's cases run sexoMasculino, sexoFeminino, sexoNaoInformado: the
# target's switch table, [0 1 3 1 2] with 1 set before it, is that order's alone of the six (measured on a probe), and
# its throw comes after a `default: break;`, as in DesconverteAbrangencia (column 11). Its parameter's type is the
# record's spelling, ModuloTiposEleitorais::CodigoSexo (src/asn1/modules/ModuloCandidatos.h).
#
# app/comum/dados/asn/correspondencia/cconversorcabecalhopacote.cpp, cconversordadosdisponiveiscarga.cpp beside it and
# app/comum/dados/md/correspondencia/cdadosdisponiveiscarga.cpp came here from unit 245's list, in that list's order,
# after util.cpp, and that order is measured (pnpm wasm score on the whole link; docs/reference/facts/codegen.md C4).
# Ahead of util.cpp in unit 245's list, 11437 is 444 over 1330 rows (54 inserted, 51 deleted) and 11438 161 over 934 (11
# and 15; a reading of the rows: the arguments of the inlined Utils calls sit in other locals). With the converter's file
# after util.cpp and cconversordadosdisponiveiscarga.cpp left ahead of it, 11437 is 112 over 1276 and 11438 80 over 923,
# all operand-only, and 11423 is 835 over 2739 and 11424 242 over 1520 (fragment 245 measured that order of its two
# converters). With the three after util.cpp, 11437 and 11438 as
# above, and 11423 (145 over 2696) and 11424 (109 over 1513) as in unit 245's list, all operand-only. The list follows
# the target's data: util.cpp's records (@1555908 to @1556148) lie before the vtables of CConversorDadosCandidato
# (@1562224), CConversorCabecalhoPacote (@1562736) and CConversorDadosDisponiveisCarga (@1565788), then come
# cconversordadocarga.cpp's records (@1567732 to @1567812) and CConversorDadoCarga's vtable (@1567828), then
# cdadosdisponiveiscarga.cpp's records (@1572092 to @1572220). So cconversordadocarga.cpp follows the two converters.
# Its place moves no row: right after util.cpp, as the list had it before, every scan row reads the same, and so do
# the symbol file and the census's pairs (measured on the whole link).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header.
COMUM_ASN_SRCS := src/app/comum/asn/util.cpp \
  src/app/comum/dados/asn/candidatura/cconversordadoscandidato.cpp \
  src/app/comum/dados/asn/correspondencia/cconversorcabecalhopacote.cpp \
  src/app/comum/dados/asn/correspondencia/cconversordadosdisponiveiscarga.cpp \
  src/app/comum/dados/asn/estadoaplicacao/cconversordadocarga.cpp \
  src/app/comum/dados/md/correspondencia/cdadosdisponiveiscarga.cpp
UENUX2_SRCS += $(COMUM_ASN_SRCS)
# No roots: the members' callers are all in the link, and so is CConversorDadosCandidato's vtable's one storer, 11448
# (unit 159's CConversorCandidatura::DoDesconverte): the roots file, whose sink kept that vtable, went with it.
# cconversordadoscandidato.cpp also holds CConversorDadosCandidato's constructor, out of line for 11448, which holds it
# inlined by binaryen (cconversordadoscandidato.h and fragment 159 say what shows it); it has no target index of its own.
# the converter includes generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(COMUM_ASN_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
