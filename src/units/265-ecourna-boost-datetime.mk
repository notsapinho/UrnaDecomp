# ecourna's Boost date_time copies, and two ptime formatters: ecourna::api::security::FormataData (target fn 2687) and
# ConverteDataHoraSemSeparador (2685), in api/security/conversaodatahora.{hpp,cpp}. The copies come from other units'
# objects once the tree root src/app/roots_boost.cpp stops giving its own; this fragment holds the evidence for that
# root's edit and for its probe's (tools/libs/boost/probe.cpp), and the root's comment cites it.
#
# What matches (11 target fns):
#   - from unit 04's app/dados/asn/datahoraasn.cpp.o: boost::date_time::gregorian_calendar_base<...>::from_day_number
#     (1376) and the on_error of greg_month's and greg_day's range policies (5183, 5182); ConverteDataHora (9220);
#   - from unit 12's api/sql/sqlite/csqlstatement.cpp.o: CSqlStatement::SetDateTime (9422), month_formatter's
#     format_month in iso_extended_format (9414) and to_simple_string_type over a time_duration (9415);
#   - libc++'s basic_ostream<char>::operator<<(long long) (8040, libc++.a's ios.instantiations.o), which only 9415's copy
#     reaches in our link (four invoke_ calls through its table slot); the census paired nothing with it at 441ae041;
#   - from this fragment's source: FormataData (2687) and ConverteDataHoraSemSeparador (2685); and binaryen's merge of
#     2685 with ConverteDataHora (6155), matched under the merge's name, after ConverteDataHora.
#
# Whose copies (evidence). 1376, 5182, 5183, 9414 and 9415 call invoke_* imports and __cxa_find_matching_catch_*
# (`pnpm wasm fn` on each): an -fexceptions object's code. roots_boost.o, at APP_CXXFLAGS (-O2, no -fexceptions), links
# ahead of both trees and gave our link its copies of from_day_number, of to_simple_string_type over a time_duration
# and of ymd_formatter<..., iso_extended_format<char>, char>::ymd_to_string with format_month under it. The root now
# declares the first two `extern template` (src/units/README.md "Companion files": a roots TU supplies no copy that
# should come from another object), and its object emits neither: our link takes from_day_number from datahoraasn.cpp.o,
# the first ecourna object that emits it (csqlstatement.cpp.o's copy is the same function, compared in the two objects
# with call targets by name: which object the target's came from the bytes do not tell), and to_simple_string_type from
# csqlstatement.cpp.o. The on_error copies come with from_day_number: datahoraasn.cpp.o's calls greg_year's once, which
# binaryen inlines, as the target's 1376 holds it, and greg_month's and greg_day's twice each, which stay functions, as
# 5183 and 5182 do (datahoraasn.cpp.o's and csqlstatement.cpp.o's on_error differ only in the object-local addresses of
# their messages). Measured with from_day_number's line alone: 1376 read `36 over 252 rows`, all operand-only (`pnpm
# wasm score`, as below), against `no-candidate` at 441ae041; SetDateTime still called roots_boost.o's
# to_simple_string_type through invoke_vij.
#
# The probe (evidence and measurement). The probe's `to_iso_extended_string(d2)`, a gregorian date, gave ymd_to_string in
# iso_extended_format a second call site in our link, in urna_roots (src/app/roots.o, which calls the probe's
# functions); the target has no function of its own for it, and its one caller is SetDateTime, which holds it inlined
# (binaryen inlines a function with one call site). With the call, and both
# lines above plus the same for ymd_to_string and format_month, 9422 read `917 over 1320 rows (same 403, replaced 181
# [173 operand-only], inserted 11, deleted 725)`; with it taken out, `155 over 1309 rows`, all operand-only, and it
# matches. ymd_to_string and format_month in that format then have no copy in roots_boost.o, which needs no line for
# them. Every other function of roots_boost.o is the same code (764, compared by name before and after with call
# targets by name), but for probe_datetime, which lost the call.
#
# The formatters (evidence). The target's 2685 is `f6155(p0, p1, 8882, 8912)` and ConverteDataHora (9220) `f6155(p0, p1,
# 8913, 8944)`, each passing the begin and the end of its format string ("{:04}{:02}{:02}{:02}{:02}{:02}" and
# "{:04}{:02}{:02}T{:02}{:02}{:02}") to 6155, binaryen's merge of the two bodies: so 2685's code is ConverteDataHora's but
# for that string. With ConverteDataHora alone in the link, 9220 is a whole body where the target has the thunk (`718
# over 721 rows (... inserted 714 ...)`). 2687 formats a ptime's date as "{:02}/{:02}/{:04}" (8609), its arguments typed
# unsigned, unsigned, int (3270): the day, the month, and the year through std::to_string and std::stoi, as
# ConverteDataHora reads it. It calls from_day_number four times, once for the date and once for each of the three, and
# holds two stack prologues, a 16-byte frame that holds the date and a second frame at +0xbb: an out-of-line callee
# binaryen inlined into its one caller (docs/how-to-decompile.md step 3, "Code binaryen inlined from another
# function"). So FormataData(const ptime &) calls a date overload, which clang keeps out of line in that object. Forms
# that differ, in the whole link: three `dataHora.date()` calls in one function, `278 over 610 rows (... inserted 168,
# deleted 11)`; a named date local, `112 over 447 rows (... inserted 5, deleted 21)`; the overload, `36 over 442 rows`,
# all operand-only. Both read the ptime's count through an address, which rules out a ptime by value, as for unit 04's
# FormataHora (its paragraph has the probe); a const reference, as unit 04's functions take it, over a const pointer,
# which fits the bytes too, is chosen.
#
# Chosen: the three functions' names (FormataData from FormataHora's, its sibling in the band; ConverteDataHoraSemSeparador
# from what it does beside ConverteDataHora), the date overload's being an overload that takes the date by const
# reference (a pointer fits the bytes too), their namespace, and the file's path and name: no record names them. The
# directory follows the band (docs/how-to-decompile.md step 3, rule 2): in band
# 4 (`uses` 4 in ledger/ordinals.tsv), 2687, 2686 and 2685 lie between api/compression/czip.cpp's 2690 and
# api/security/csha.cpp's 2684, and the data between czip.cpp's and csha.cpp's records hold icompressor.cpp's, cfile.cpp's,
# base64.cpp's, chkdfseed.cpp's and ckey.cpp's records and no date class (unit 04's paragraph), so the object is an
# unrecorded one between them; csha.cpp is the adjacent side, and api/security/ is taken from it
# (docs/reference/facts/placing.md P5). The file name sorts between ckey.cpp and csha.cpp, where the data's run base64,
# chkdfseed, ckey, csha, csiphashmac is in name order. FormataHora (2686), which lies between them in the band, stays in
# unit 04's datahoraasn.cpp, as that unit chose. In this object FormataData comes first: 2687's higher index needs the
# lower ld_index in one band and one object (build/out/wasm-map/vota_web/names.tsv). The date overload's place is free.
#
# The roots: stand-ins for the unwritten callers of 2687 (vota::CImpressaoPU::StartState, 11902, a trap in unit 176) and
# 2685 (fn 7787), two calls each (265-ecourna-boost-datetime-roots.cpp says which stands for which).
BOOST_DATETIME_SRCS := api/security/conversaodatahora.cpp
ECOURNA_SRCS += $(BOOST_DATETIME_SRCS)
# nothing in the skeleton calls the two formatters: 265-ecourna-boost-datetime-roots.cpp stands for their callers
$(ROOT)/$(APP)/265-ecourna-boost-datetime-roots.o: $(ROOT)/src/units/265-ecourna-boost-datetime-roots.cpp $(ROOT)/src/Makefile \
    $(ROOT)/src/units/265-ecourna-boost-datetime.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/265-ecourna-boost-datetime-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/265-ecourna-boost-datetime-roots.o
