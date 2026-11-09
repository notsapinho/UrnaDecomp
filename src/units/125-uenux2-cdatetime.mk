# uenux2 api::CDate and api::CDateTime, in src/uenux2/src/api/util/cdate.cpp and cdatetime.cpp, the files their
# std::source_location records name (cdate.cpp:94 and :104 for CDate(const std::string &), :130 for Format; cdatetime.cpp:31,
# :61 and :206 for CDateTime(const std::string &), ConvertFromLocalTime and ConvertFromTimestamp), with the class headers
# (cdate.h and cdatetime.h, which held the layouts only, say what each member rests on) and the 7001, 7002, 7003, 7005,
# 7006 and 7008 enumerators of api/util/eueutilerror.h, named from their messages and what their throws test.
# api::CTime's new members are unit 24's (ctime.cpp), and CAjusteDataHora's Ajusta(const CDateTime &) unit 101's.
# Target functions:
#   matched    706 Format, 3649 CDate(const std::string &), 2764 ConvertFromTimestamp (and unit 24's 779 CTime::Format),
#              at the tree's -O3 (below);
#              5479 IsValidDate, 1382 CDate(), 2765 CDate(dia, mes, ano), 1261 CDate::operator<=>;
#              479 CDateTime::Now, 1000 CDateTime(time_t), 5475 CDateTime(const std::string &), 1381 ConvertToLocalTime,
#              2233 operator+=(int), 759 CDateTime::operator<=>; libc's timegm (2961), which 1381 and 2233 call; and,
#              with units 24 and 101, 2230 CTime() and 10875 Ajusta(const CDateTime &)
#              Those four append to a std::string outside a throw, a call to std::string::append (fn 160) in the
#              target, which clang inlines at -O2. Before the tree took -O3, with -O3 for the three files
#              (tools/round/try-tu.sh cdate.cpp cdatetime.cpp ctime.cpp --flags -O3 --skip-units 24-uenux2-ctime.mk, the
#              two roots files as one --roots) each scored operand-only: 706 38 over 923 rows, 3649 33 over 363, 2764 28
#              over 576, 779 16 over 596 (pnpm wasm score against the try's link-map names); at -O2 985 over 1772, 191 over
#              469, 328 over 698 and 938 over 1355. 3649 is named by the call votes of 2765 and 5475.
#              5472 FormatCurrentDate and 5473 FormatCurrentTime, the callbacks cdatetime.h describes, match at the
#              tree's -O3 with 706 and 779, which they call; at -O2 they were operand-only (3 over 32 and 3 over 30 rows,
#              the callee rows) and `unresolved`, named by pair-depth0 hand lines. Until 5343 (unit 165's) matched
#              no vote reached them (their one direct caller, 11216, has its name by vtable evidence; 7787 is not
#              written): the scan's content pass found each, and 11216 matches over them. 5343, which passes their
#              slots, names them now (`evidence:table by:5343`). They sit in band 2 of
#              ledger/ordinals.tsv between 5475 and 5471 (cluster 765, labelled cdatetime.cpp), and are defined after
#              ConvertFromLocalTime, 5473 first (names.tsv's ld_index); their lines are chosen. The forms, each object
#              against the target's frame offsets: a named CDateTime and a copy of its date
#              (`const CDateTime agora = Now(); const CDate data = agora.GetData(); return data.Format(formato);`) puts
#              the CDateTime at +16 and the copy at +8 in 5472, +4 and +0 in 5473, as the target does;
#              `return Now().GetData().Format(formato)` with a GetData that returns by value, and
#              `const CDate data = Now().GetData();`, put the CDateTime at +8 and the copy at +24 (5472), +0 and +12
#              (5473). GetData's and GetHora's return by reference is 11198's (cdatetime.h).
#              10870 FormatCurrentDateTime, a third callback (cdatetime.h), matches: the scan's content pass finds
#              it, and no vote names it. Its one reference in the target is the table slot 3117 that
#              api::CFormBuilder::AddStatusHeader (fn 502, unit 31) passes, which holds it in our link too.
#              Written as `agora.GetData().Format(agora.GetHora().Format(formato))` on a named CDateTime, it is
#              operand-only against the target (5 over 48 rows, the call and data rows). Its band-1 neighbours
#              (10868 to 10872 in ledger/ordinals.tsv) are CDefaultGenericFactory slots, which place nothing; its
#              line after FormatCurrentDate is a choice.
#   written    the rest below.
#              5476 ConvertFromLocalTime is operand-only (14 over 90 rows) and read `unresolved self-voted` until unit
#              170: it calls std::to_string(long long) (fn 4658), whose other target caller, 3612, was not written
#              then, so 5476 was the name's one voter; unit 170's object names 4658's callee __itoa (2869), and both
#              match since. 3612 (unit 152's AtualizaMensagem) is in the link now, and the roots' TempoEmTexto, which
#              stood for it, went.
#              5478 operator+= and 5477 operator-= match (named by pair-addr at step 8), on two things measured in the
#              whole link (pnpm wasm score in build/out/wasm/vota_web, splat-remap --no-kinds, then steps 7 to 10):
#              - The loops over the months write `m_mes++` before `resto -= diasNoMes`. With the subtraction first, as
#                this file had it, they scored 86 over 550 and 30 over 530 rows at the tree's -O3 (291 over 558 and 271
#                over 543 at -O2, measured before): ours stored the month once, after the loop (and in += nested the
#                month loop in the year loop's exit), where the target stores 1 before the loop and each increment
#                inside it. Written increment first, both scored 11 over 522 and 11 over 525, every row a call or a
#                data address. What the IR of operator-= shows (the file's compile line with -mllvm
#                -print-after=instcombine,licm and -filter-print-funcs, docs/reference/facts/codegen.md C12): with the
#                increment's store last in the loop's body, the first InstCombine merges it with `m_mes = 1` into one
#                store in the loop header, which LICM then sinks after the loop; with the subtraction last the two
#                stores stay apart, in a loop whose header is the month's switch, and the target's code keeps them in
#                the loop.
#                That the target's source had this order is a reading of that measurement. += also writes `m_ano++`
#                before `resto -= diasNoAno`, a choice: the other order gives the same plain wasm (shasum -a 256).
#              - The day count of a month comes from clang's switch tables in the non-leap copies of the loops: 12 bytes
#                read as the table's address less 1 plus the month (531859 in the target), and 48 bytes read at the
#                month less 1 (531872). The scan places the first address through the object it falls in, the last byte
#                of whatever precedes the table (docs/reference/splat.md 3). In the target that is cajustedatahora.cpp's
#                typeinfo name of std::default_delete<api::IAjusteDataHora> (0x81d62, size 0x32; the tables follow it at
#                0x81d94 and 0x81da0), whose line step 8 writes by content (evidence:content at bed17f80, now voted by
#                5477 and 5478 as well). With cdate.cpp.o after app/comum/dados/asn/candidatura/cindexadorfotos.cpp.o
#                (the order at bed17f80) the address fell in that object's typeinfo name, and splat-remap stopped there
#                (+0x82, i32.const 531859). So api/util/cajustedatahora.cpp, unit 101's file, is compiled from this
#                unit's list, right before cdate.cpp: the target's data have that order in .rodata (those tables) and in
#                .data (cajustedatahora's control block vtable and typeinfo at 0x182c58 and 0x182c74, then g_seculo at
#                0x182c80). Either move that puts cajustedatahora.cpp.o right before cdate.cpp.o gives IDENTICAL for
#                both (splat-remap --no-kinds), measured: cdate.cpp into unit 101's list after cajustedatahora.cpp, and
#                cajustedatahora.cpp into this list before cdate.cpp. src/units/README.md "Names" takes the move whose
#                count falls (docs/reference/facts/codegen.md C4's record-aware count over bed17f80's link line, and the
#                same on 81333bd6's): cajustedatahora.cpp.o 452 objects out of the data order in unit 101's list, 399
#                before cdate.cpp.o (400 after it and 401 after cdatetime.cpp.o, counted only, neither linked nor
#                measured: neither puts it before cdate.cpp.o); the other move, cdate.cpp.o, 399 here and 450 to 453 at
#                the four places of unit 101's list (452 after cajustedatahora.cpp.o). The move restores 72 pairs (23 of
#                app/vota/eleitor, 21 of app/comum/dados, 8 of app/comum/gravadores, 20 elsewhere) and inverts 19:
#                eleven of app/vota/operador (eight of leidentidade, cfinalizaoperador, csincronismooperador and
#                outrasopcoes/cfimaquisicaovotos), two of app/vota/eleitor/fimvotacao, vota/monitor/cthreadmonitor, two
#                of app/comum/comparecimentomesario/estados, comum/gravadores/asn/util, comum/util/cmonitoraalimentacao
#                and api/uelog/cloga. It moved no row but 5477 and 5478 into `match`; three twins' match lines took the
#                name of a copy that now links first (631 and 4739 simulador.cpp.o's, 2924's merge body
#                ITimerScheduler's) and has<IAjusteDataHora> (2469) is ciniciodeciclo.cpp.o's copy now.
#              They were hand-named in splat/symbol_addrs.txt by their bodies (callers+content) while they differed;
#              without those two lines a scan and splat-build keep every row (12961 at 2bd38333, the target's sha256),
#              so they went.
#              3648 CDate::operator- matches (operand-only, 1 over 9 rows, and `no-candidate` until 5477 had a name);
#              654 (CTradutorFrase::Traduz, unit 98) calls it on the "-" sign.
#              CDate::operator+(int) const, operator-'s counterpart (a copy, then operator+=), has no target function: 654
#              holds it inlined by binaryen on the "+" sign (it copies the 8-byte date, then calls 5478). Its name, after
#              operator-'s, and its being out of line in cdate.cpp, as operator- is, are chosen.
# The 16-bit static 2000 that IsValidDate and CDate(const std::string &) add to a two-digit year is an object of
# namespace api, named g_seculo here (a chosen name), at the head of cdate.cpp's data (1584256, before its first record at
# 1584260). Its external linkage is the bytes': a const or file-static object nothing writes would fold into the code;
# that it is a namespace global and not a static member is chosen. Its name was a hand edit of splat/symbol_addrs.txt
# (callers+content): 3649, CDate's constructor by its records, and 5479 are the only target functions that read the word
# (`grep -rlE 'i32\.const 1584256($|[^0-9])' build/out/splat/pieces/asm`), each as an i32.load16_u added to the year when
# the string has 6 characters. Step 8 names it now by those two readers' votes (`vote:2 by:3649,5479`), and the hand
# edit went: removed alone, it moved no row of a scan run twice and the build verified.
# The weekday names are a table of seven pointers at 1584308, in cdate.cpp's data after its records.
# Forms measured against another: Bissexto is `ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)`, where the target tests
# %4 with a branch first (5479 at 11 over 378 rows; grouped `(%4 && %100) || %400` it has no branch, 30 over 386);
# operator-= and operator+= take a month's day count once per iteration, from a variable assigned in the loop's condition
# (computed again in the body, -O3 keeps two copies: 5477 at 120 over 578), and += its year length the same way (5478 at
# 124 over 568 without), both measured with the subtraction before the increment, the order the file had then.
# Written in the target's order and not compared with another: CDate(const std::string &) stores
# the year, the month, the day and the weekday, CDate() the day, the month, the year and the weekday; ConvertFromLocalTime
# builds the time before the date and stores the date first (two locals, then two assignments); the weekday takes
# `+= dias % 7` (`+= 7 - dias % 7` in -=) and then `%= 7`, as the target wraps the sum to 16 bits before the remainder.
# Chosen, no byte decides: every name but the records' (Format, CDate(const std::string &), the three CDateTime functions
# with records) and the messages': IsValidDate, IsValidDateTime, Now, ConvertToLocalTime, operator+= and operator<=> of
# CDateTime, FormatCurrentDate, FormatCurrentTime (and that they are static members), GetData and GetHora, CDate's
# operators and getters, g_seculo, DIAS_SEMANA and the file-static helpers Bissexto, DiasNoMes,
# DiasNoAno and DiaDoAno, which clang inlines, and that they are file-static functions and not members; IsValidDate
# and IsValidDateTime free functions in api, declared in the headers, as unit 24's IsValidTime is (5475 holds
# IsValidDateTime with a stack prologue of its own, binaryen's inlining, so it is a function of the object, left unrooted;
# that it is external rather than file-static is not measured); g_seculo's type, a short; every line but
# the records'; and the order of the functions without a record, inside the order the bands give (ledger/ordinals.tsv,
# reverse link order inside a band, read against build/out/wasm-map/vota_web/names.tsv's ld_index): in cdate.cpp
# IsValidDate, operator+=, operator-= (band 2) and CDate(const std::string &) before operator- (band 3); in cdatetime.cpp
# ConvertFromLocalTime before CDateTime(const std::string &) (band 2), as CDateTime(time_t), defined above both, calls
# it first (docs/reference/facts/reading.md R9). CDate's constructor from three numbers delegates to the one from a
# string through std::format("{:02}{:02}{:04}", ...), the string at 8593.
# Added since: fn 5474, CDateTime::operator+=(const std::chrono::seconds&), which passes the count's low word to
# operator+=(int) (fn 2233). Its one caller, vota::CEstadoComDesligamentoAutomatico::ProcessTick (fn 12061, unit 97),
# calls it twice, so it keeps its body; band 2 puts it between CDateTime(const std::string &) and FormatCurrentTime
# (5475, 5474, 5473), so it is defined after operator+=(int), a place among those the band allows. Its name, its
# parameter's type and its void result are chosen. And CDateTime's operator== and CTime's (defaulted, inline in their
# headers), which 12061 holds: four 16-bit compares, then one 32-bit.
# Added since: fn 5471, CDateTime::operator-(const CDateTime &), ConvertToLocalTime of this one minus the other's,
# which clang inlines twice over one struct tm (the target fills its frame's tm from each in turn and calls timegm after each,
# fn 2961). Its callers are two text callbacks, vota::testeteclado::CEsperaRetestar's (fn 11826, unit 138) and fn
# 13012 (unit 443's TextoAlertaDesligamento), both in the link (unit 220's roots stood for 13012 until then). 10 over
# 113 rows, operand-only, before step 8, which named
# it by pair-addr; matched at step 9. Its place, after FormatCurrentDate and operator+ (line 133, in the blank run
# before :203), follows the band (cdatetime.h); the name, const and time_t are chosen.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
# api/util/cajustedatahora.cpp is unit 101's file, listed here before cdate.cpp for 5477 and 5478 (above).
CDATETIME_SRCS := src/api/util/cajustedatahora.cpp src/api/util/cdate.cpp src/api/util/cdatetime.cpp
UENUX2_SRCS += $(CDATETIME_SRCS)
# the callers of these members outside the two files are not reconstructed yet: 125-uenux2-cdatetime-roots.cpp reaches
# each function the way the target does (its header lists them); it includes no tree header
$(ROOT)/$(APP)/125-uenux2-cdatetime-roots.o: $(ROOT)/src/units/125-uenux2-cdatetime-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/125-uenux2-cdatetime.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/125-uenux2-cdatetime-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/125-uenux2-cdatetime-roots.o
