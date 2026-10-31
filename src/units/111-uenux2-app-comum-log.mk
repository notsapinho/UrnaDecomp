# uenux2 comum's log and CInformacaoEleicao, at the paths their std::source_location records name:
# - api::CLoga::loga (target fn 433) in src/api/uelog/cloga.cpp, record 26:36;
# - comum::IEventosLog in src/app/comum/log/ieventoslog.cpp: loga (233, a chosen name), logaAlerta (1398, a chosen name)
#   and ConverteERelatoriosUE (5879, record 426:19), with 2861, CBaseError<comum::EUeComumLogError>'s constructor thunk,
#   the header euecomumlogerror.h;
# - comum::CLogComum in src/app/comum/log/clogcomum.cpp: LogaCopiandoArqResParaFI and LogaResultadoCopiadoResFE (5878, 3828,
#   thunks of binaryen's 6045, records 76:18, 84:18), LogaNivelBateria (5875, record 106:18, holding the ieventoslog.cpp
#   records 440:19 and 456:19), GetInst (948);
# - comum::CArquivosResultado::GetInst (348, in unit 95's files) and 2900, binaryen's body of the two GetInst, with the
#   mutex destructors 11659 and 11639 and the pointers' 11660 and 11640, thunks of 349, which the content pass pairs once
#   the statics have names;
# - comum::CInformacaoEleicao in src/app/comum/informacao/cinformacaoeleicao.cpp: the constructor (603), EhModoDemonstracao
#   (2286, record 40:36) and seven members clang inlined it into (1950, 2865, 3847, 5914, 5915, 5916, 5917). The
#   constructor takes the ecourna::app::dados::CParametrosUrna that CConfiguracaoEleicao holds at +88 (the offsets the
#   members read are that class's fields; cinformacaoeleicao.h). AceitaJustificativa (5918, a chosen name) reads the
#   byte at +394 with no test of the demonstration mode; the class header says where its callers and band put it.
# - comum::IEventosLog, added after the unit landed: logaErro (2282, severity 3) and the five members that log one fixed
#   text, LogaMidiaResultadoAusente, LogaMidiaResultadoInvalida, LogaMesarioIndagadoImprimirZeresima,
#   LogaErroEstadoAplicativo and LogaImprimindoRelatorioEstadoUrna (5885, 5883, 5882, 5881, 5880; every name chosen,
#   ieventoslog.h says from what). 5885, 5881 and 5880 are thunks of binaryen's 3902, which this link forms from those
#   three and no other function, as the target's does (its callers are those three). Their lines, 344 to 372, above
#   logaAlerta's 375, are a choice; their order is the band's (uses 2), 5885 first. Each is written as a call of loga
#   or logaErro on its text, which clang inlines there; a direct call of api::CLoga::loga was not tried.
# Files: the order here is the data's, ieventoslog.cpp's records (@1552880) before clogcomum.cpp's (@1552996). Chosen
# paths: cloga.h, clogcomum.h, euecomumlogerror.h, cinformacaoeleicao.h, each beside the .cpp its records name.
#
# logaAlerta (1398) is loga with severity 2: `f433(i32.load[p0+4], 2, p1)`. Seven of its eight target callers (10415,
# 10416, 10420, 10512, 10642, 10676, 10774) call it on vota::CLogVota::GetInst()'s result (fn 184), so the class is
# IEventosLog or CLogVota; the eighth, 6115, a merged body reached from 2495 and 4556, calls it on its first parameter.
# Its band (uses 9) puts it between 1399 (app/comum/cpath.cpp's GetPathResult, record 189) and 1396
# (app/comum/gravadores/iresultado.cpp's constructor, record 40). In the data, the run between those two files' records
# (@1552104, @1553632) holds records of 19 files, ieventoslog.cpp's (@1552880) among them, and clogvota.cpp's
# (@1532800) lie outside it: that rules out clogvota.cpp only, and with the class above it is IEventosLog's, in this
# file. No other function of the file is in its band, so its place in the file, above the constructor, is a choice.
# One caller is in the link, unit 119's slot 28 (10774, which matches at the tree's -O3); the roots file stands in for
# the other seven. The census pairs it (`shape`), and step 9 matches it by that pair.
#
# Written, not matching, and what each waits for:
# - 6045 and 5876 match at the tree's -O3; at -O2 they were `differs` and `no-candidate`. Their literals are 43 and 40
#   bytes, and the target has no search of the literal for a brace, which -O2 keeps past 36 bytes and -O3 past 74
#   (docs/reference/facts/reading.md R13): `wasm-objdump -d` of clogcomum.cpp's object counts 4, 4 and 5 br_table rows in the
#   three members at -O2 and none at -O3. std::format stays as the source: the other 19-byte literal (5875) matches at
#   both levels. Before the tree took -O3, with this unit's four TUs at
#   -O3 alone and the tree's -std=c++20, a try link read `13 over 230` and `19 over 292`, all operand-only, and
#   `splat-remap --against` printed IDENTICAL for both, operand kinds verified (`tools/round/try-tu.sh --flags -O3
#   --skip-units 111-uenux2-app-comum-log.mk --roots src/units/111-uenux2-app-comum-log-roots.cpp`, with 233's name in a
#   copy of the symbol file, since splat-remap reads no match list). GetInst stays a call there: it is in
#   another object. 3828 and 5878 match as thunks: their one call is named by `call` evidence, and 6045's two voters are
#   those thunks.
# - vota::CExibeAlertaDesligamento::StartState (12018) stays pending in unit 61: its pending file says why.
# - not reconstructed: 5372 (needs 816, 1686, 1903, 2224), 10226,
#   12098 and the other CLogComum members, 2742 and 3603 (the other thunks of 2900: their classes are not named).
#
# Inlining, by who did it. clang: EhModoDemonstracao into the seven members (one frame, restored after the member's load)
# and ConverteStatusBateria into LogaCargaBateria (no prologue, the throw's string in that frame, the length folded into
# the format argument: `i64.const 30064771072`). binaryen: LogaCargaBateria into LogaNivelBateria (a second prologue,
# i32.sub(g0, 432), so a function of its own, out of line in ieventoslog.cpp: it reads +4 of the instance and holds
# ConverteStatusBateria) and ConverteFonteAlim into LogaCargaBateria (a third prologue). -Rpass=inline at -O2, the tree's
# level when this was measured: ConverteFonteAlim cost=305, ConverteStatusBateria cost=225, threshold=225. So the plain
# form left ConverteStatusBateria out of line by one tick (`168 over 502`, a third prologue where the target has none), and
# `inline`, which raises the threshold to 325, gives the target (`52 over 464`, all operand-only, now a match). At the
# tree's -O3 the threshold is 250, over that cost, so the keyword is a choice there (not measured without it). Left without `inline`, ConverteFonteAlim
# stays binaryen's as the target has it. binaryen also removes GetInst's empty constructor and destructor calls.
#
# GetInst, what the bytes decide (objects at uenux2's flags, rows masked, unless a link is named):
# - Where it is defined. In all four thunks of 2900 (348, 948, 2742, 3603) the mutex lies 24 bytes below the pointer, and
#   the pointer's destructor has the lower table slot of the two (11660 2140, 11659 2141; 11640 2171, 11639 2172; 10522 4087,
#   10521 4088; 10281 4466, 10280 4467). Seven shapes were probed, GetInst in the class or in the .cpp, above or below the
#   statics, the statics in either order, and only GetInst in the .cpp above statics written pointer then mutex gives both
#   orders. This link holds both: mutex 1497676, pointer 1497700, the pointer's destructor in slot 1355 and the mutex's in
#   1356. Why is a reading: a body above the definitions names the mutex first, and the definitions set the destructors'
#   order. The statics' .cpp: their destructors' slots lie in that object's run (2140 and 2141 just before 2142 and 2143,
#   which 275 and 680 of the next object, carquivossavd.cpp, load; this link has the same run, 1355 and 1356 before 1357
#   and 1358), and 348 sits beside 347 in that object (ld_index 2149 and 2154) as their indices do in the target.
# - The constructor is out of line. 2900 reads the pointer again after `new` and tests the old value. At -fPIC a
#   constructor defined out of line stays a call, in its own TU too, with no remark from clang, which keeps that reload,
#   and binaryen removes the empty call at link. Why -fPIC does this is not measured. Declared `= default` in the class,
#   or implicit, it folds: 18 rows where the form written has 37, `load, new, store, unlock`.
# - The destructor out of line is a choice. Implicit, GetInst's object loses one call that binaryen removes anyway (34 rows
#   against 37: `local.get 2; call ~T; drop` go, the rest stays in order); that form was not linked.
# - Both empty bodies are `= default` below the statics, a choice: `{}` gives the same rows, and their lines are free.
#
# Columns. A default-argument std::source_location takes the begin of the call expression (probe: `S::inst().f();` at 4
# spaces records column 5, `auto& v = S::inst();` column 15), so instance() begins at column 36, 18, 25 and 36 on those
# lines. A local holding the instance places it: that it is a local, and each local's name and spelled type, are chosen.
#
# Evidence, measured with the object's rows, numbers masked: the local `mensagem`, since the temporary file name is
# destroyed before the call of loga (a temporary in the call's argument: 20 rows differ in LogaCopiandoArqResParaFI, 352 in
# LogaCargaBateria); `default` last (moved first in ConverteStatusBateria: 346 rows of LogaCargaBateria differ, and the
# throw's line needs it last); m_imprimeBJust a bool, read with `i32.const 1; i32.and` (a byte tested
# `!= 0`: 9 rows differ, docs/reference/facts/reading.md R14); the literals, `case` values and codes 8852 to 8854; every
# throw's line: the three switches fill lines 396 to 456 exactly, with `case` at 8 spaces and each `return` on its own line.
#
# The same bytes, measured per function: the severity in a local, or an `if` over two calls (LogaCargaBateria); `const` or
# not on `mensagem` and `etapa`; `status == STATUS_OPERACAO_INICIO ? "Inicio" : "Termino"` for the test of `status`;
# integer `case` labels; instance() chained into the call instead of a local (433, 5875, 2286), at another column;
# `if` and `return` for the six counts' ?: (measured on GetNumViasPU); `EhModoDemonstracao() ? false : m_dados.m_imprimeBJust`
# or `if` and `return` for ImprimeBJust's `&&`; the counts `unsigned` for `int`; m_dados a pointer for a reference (the
# members and 603); in GetInst, measured on CArquivosResultado's, std::unique_lock or std::scoped_lock for the
# std::lock_guard, `== nullptr` for `!`, `s_instancia = std::unique_ptr<T>(new T)` for reset, a `T*` result with
# s_instancia.get() for the reference, which every caller drops, and `{}` for either `= default`; std::make_unique for
# reset in the shape probe, not in this class, whose constructor is private. GetInst in the class with no `inline` gives
# the same linked bytes at -O2 only, with both special members out of line (cost=225, threshold=225), and not the target's
# orders; its object reads 35 rows against 37, since the constructor's call differs by what the TU sees.
#
# Chosen, no byte decides: every name but the records' (loga 233, logaAlerta 1398, LogaCargaBateria, GetInst,
# s_instancia, s_mutex, m_aplicativo, the eight members and m_parametros, logaErro and the five fixed-text members, the enumerators of ERelatoriosUE,
# EStatusOperacaoRelatorio and EUeComumLogError); 603's parameter taken by `const &` and held as a reference member,
# where a pointer is the same address; the namespace of ERelatoriosUE and EStatusOperacaoRelatorio; the
# severities as bare casts, as ESeveridade has no enumerator; the lines of every function but the throws' and the lines the
# column records hold. The definition above the Converte members gave the match, and no other order
# was linked.
#
# Hand edits in splat/symbol_addrs.txt: GetInst's two names and four statics, `callers+content`, from the calls aligned
# with fn 347 and the CLogComum members and from the table slots of the destructors that load the same addresses. None
# reads a match. Taking out the four statics' lines leaves 348 and 948 `unresolved` and 11659 and 11639 `no-candidate`.
# Taking out the two GetInst lines, with 348, 948 and 2900's match lines, moves no row: the census pairs the two tied bodies
# by position, the wrong way round in this link (348 `CLogComum::GetInst`, 948 `CArquivosResultado::GetInst`), so each
# partner differs and the content pass takes the right body through the four statics' lines; those two names rest on
# the calls and not on the census.
#
# src/app/roots_uenux2.cpp holds std::operator+(string&&, string&&): the first real uenux2 TU that instantiates
# CPolySingleton<T>::instance links ahead of libc++.a, and its copy at -O2 took 252 (docs/reference/facts/splat.md S10 item
# 10). Its comment says how the copy stays the target's. 837, 11157 and 611 now come from this unit's objects, at uenux2's
# flags, and stay matched; the 13 other instances stay in unit 100's roots object.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_COMUM_LOG_SRCS := src/api/uelog/cloga.cpp src/app/comum/log/ieventoslog.cpp src/app/comum/log/clogcomum.cpp src/app/comum/informacao/cinformacaoeleicao.cpp
UENUX2_SRCS += $(APP_COMUM_LOG_SRCS)
# nothing reconstructed calls these yet: 111-uenux2-app-comum-log-roots.cpp stands in for the target's callers
$(ROOT)/$(APP)/111-uenux2-app-comum-log-roots.o: $(ROOT)/src/units/111-uenux2-app-comum-log-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/111-uenux2-app-comum-log.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/*.h) $(wildcard $(ROOT)/src/uenux2/src/app/comum/log/*.h) $(wildcard $(ROOT)/src/uenux2/src/app/comum/informacao/*.h) $(ROOT)/src/uenux2/src/api/uelog/cescritorlog.h $(wildcard $(ROOT)/src/ecourna/app/dados/parametrizacaourna/*.hpp) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/111-uenux2-app-comum-log-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/111-uenux2-app-comum-log-roots.o
