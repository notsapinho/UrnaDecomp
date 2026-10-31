# uenux2 comum's log and CInformacaoEleicao, at the paths their std::source_location records name:
# - api::CLoga::loga (target fn 433) in src/api/uelog/cloga.cpp, record 26:36;
# - comum::IEventosLog in src/app/comum/log/ieventoslog.cpp: loga (233, a chosen name) and ConverteERelatoriosUE (5879,
#   record 426:19), with 2861, CBaseError<comum::EUeComumLogError>'s constructor thunk, the header euecomumlogerror.h;
# - comum::CLogComum in src/app/comum/log/clogcomum.cpp: LogaCopiandoArqResParaFI and LogaResultadoCopiadoResFE (5878, 3828,
#   thunks of binaryen's 6045, records 76:18, 84:18), LogaNivelBateria (5875, record 106:18, holding the ieventoslog.cpp
#   records 440:19 and 456:19), GetInst (948);
# - comum::CArquivosResultado::GetInst (348, in unit 95's files) and 2900, binaryen's body of the two GetInst, with the
#   mutex destructors 11659 and 11639, which the content pass pairs once the statics have names;
# - comum::CInformacaoEleicao in src/app/comum/informacao/cinformacaoeleicao.cpp: the constructor (603), EhModoDemonstracao
#   (2286, record 40:36) and seven members clang inlined it into (1950, 2865, 3847, 5914, 5915, 5916, 5917).
# Files: the order here is the data's, ieventoslog.cpp's records (@1552880) before clogcomum.cpp's (@1552996). Chosen
# paths: cloga.h, clogcomum.h, euecomumlogerror.h, cinformacaoeleicao.h, each beside the .cpp its records name.
#
# Written, not matching, and what each waits for:
# - 6045 (`differs`) and 5876 (`no-candidate`, no anchor without equal instructions): uenux2's level. Their literals are 43
#   and 40 bytes, and the target has no search of the literal for a brace, which -O2 keeps past 36 bytes and -O3 past 74
#   (docs/reference/facts/reading.md R13): `wasm-objdump -d` of clogcomum.cpp's object counts 4, 4 and 5 br_table rows in the
#   three members at -O2 and none at -O3. std::format stays as the source: the other 19-byte literal (5875) matches, and
#   the tree's evidence is the level (docs/reference/facts/levels.md V3), which is reserved. In a try link at
#   -O3 -std=c++23 the rows are `41 over 254` and `47 over 316`, 24 of each inserted being GetInst's body, which clang
#   inlines there at cost 225 under threshold 250. So GetInst's form below is to re-read if the level moves.
#   3828 and 5878 match as thunks: their one call is named by `call` evidence, and 6045's two voters are those thunks.
# - 11660, 11640 (the pointers' destructors, no-candidate): the target's are thunks of 349, binaryen's merge of 57 such
#   destructors. Our two stay whole bodies: two are not enough for binaryen to form it (`__cxx_global_array_dtor` of both
#   objects, 13 rows each, in this link).
# - vota::CExibeAlertaDesligamento::StartState (12018) stays pending in unit 61: its pending file says why.
# - not reconstructed: 184 (CLogVota::GetInst, a CPolySingletonList::push), 5372 (needs 816, 1686, 1903, 2224), 10226,
#   12098 and the other CLogComum members, 2742 and 3603 (the other thunks of 2900: their classes are not named).
#
# Inlining, by who did it. clang: EhModoDemonstracao into the seven members (one frame, restored after the member's load)
# and ConverteStatusBateria into LogaCargaBateria (no prologue, the throw's string in that frame, the length folded into
# the format argument: `i64.const 30064771072`). binaryen: LogaCargaBateria into LogaNivelBateria (a second prologue,
# i32.sub(g0, 432), so a function of its own, out of line in ieventoslog.cpp: it reads +4 of the instance and holds
# ConverteStatusBateria) and ConverteFonteAlim into LogaCargaBateria (a third prologue). -Rpass=inline at this tree's
# level: ConverteFonteAlim cost=305, ConverteStatusBateria cost=225, threshold=225. So the plain form leaves
# ConverteStatusBateria out of line by one tick (`168 over 502`, a third prologue where the target has none), and `inline`,
# which raises the threshold to 325, gives the target (`52 over 464`, all operand-only, now a match). That keyword is a
# choice of this level: at -O3 the threshold is 250 and the plain form would do. Left without `inline`, ConverteFonteAlim
# stays binaryen's as the target has it. binaryen also removes GetInst's empty constructor and destructor calls.
#
# GetInst, what the bytes decide (probe of the shape at uenux2's flags, object rows):
# - 2900 reads the pointer again after `new` and tests the old value. reset(new T) with a constructor the TU can see
#   folds that away, and the store goes straight after new: `load, new, store, unlock`. Only a constructor the TU cannot
#   see keeps it: `load, new, ctor, load, store, delete, load, unlock`. So GetInst does not see the constructor.
# - With the constructor alone out of line, a GetInst in the class is inlined by clang into 6045's and 5876's members.
#   With the destructor out of line too its cost is 225 and it stays a call, which the target's 348 is. Declared `inline`
#   after the class, the hint inlines it (threshold 325, no symbol in the object). So: in the class, no `inline`, and
#   both special members declared in the class and defined in the .cpp. That is one form that gives these bytes, and the
#   target does not say the class holds GetInst: a function of another TU that does not see them would give the same.
# - Both empty bodies are `= default` in the .cpp, a choice: no byte holds them.
# - The statics' .cpp: their destructors' table slots lie in that object's run (slots 2140 and 2141 before 347's handle
#   slots 2142 and 2143). 948 is emitted by this unit's roots object, the only TU that calls it, an inline member of a
#   landed header: compiled with -fno-strict-aliasing its rows are the same (35 rows, `wasm-objdump -d` masked).
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
# `if` and `return` for ?: (the seven members); the counts `unsigned` for `int`; m_dados a pointer for a reference (the
# members and 603); std::unique_lock or std::scoped_lock for the std::lock_guard, `== nullptr` for `!`, and
# `s_instancia = std::unique_ptr<T>(new T)` for reset (GetInst); std::make_unique for reset in the shape probe, not in this
# class, whose constructor is private.
#
# Chosen, no byte decides: every name but the records' (loga 233, LogaCargaBateria, GetInst, s_instancia, s_mutex,
# m_aplicativo, the seven members, SDadosInformacaoEleicao and its members, the enumerators of ERelatoriosUE,
# EStatusOperacaoRelatorio and EUeComumLogError); the namespace of ERelatoriosUE and EStatusOperacaoRelatorio; the
# severities as bare casts, as ESeveridade has no enumerator; the lines of every function but the throws' and the lines the
# column records hold; 603's parameter type; the statics' order in the .cpp. The definition above the Converte members
# gave the match, and no other order was linked.
#
# Hand edits in splat/symbol_addrs.txt: GetInst's two names and four statics, `callers+content`, from the calls aligned
# with fn 347 and the CLogComum members and from the table slots of the destructors that load the same addresses. None
# reads a match. Removing them leaves 348 and 948 `unresolved` and 11659 and 11639 `no-candidate`.
#
# src/app/roots_uenux2.cpp holds std::operator+(string&&, string&&): the first real uenux2 TU that instantiates
# CPolySingleton<T>::instance links ahead of libc++.a, and its -O2 copy took 252 (docs/reference/facts/splat.md S10 item
# 10). Its comment says how the copy stays the target's. 837, 11157 and 611 now come from this unit's objects, at uenux2's
# flags, and stay matched; the 13 other instances stay in unit 100's roots object.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_COMUM_LOG_SRCS := src/api/uelog/cloga.cpp src/app/comum/log/ieventoslog.cpp src/app/comum/log/clogcomum.cpp src/app/comum/informacao/cinformacaoeleicao.cpp
UENUX2_SRCS += $(APP_COMUM_LOG_SRCS)
# nothing reconstructed calls these yet: 111-uenux2-app-comum-log-roots.cpp stands in for the target's callers
$(ROOT)/$(APP)/111-uenux2-app-comum-log-roots.o: $(ROOT)/src/units/111-uenux2-app-comum-log-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/111-uenux2-app-comum-log.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/*.h) $(wildcard $(ROOT)/src/uenux2/src/app/comum/log/*.h) $(wildcard $(ROOT)/src/uenux2/src/app/comum/informacao/*.h) $(ROOT)/src/uenux2/src/api/uelog/cescritorlog.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/111-uenux2-app-comum-log-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/111-uenux2-app-comum-log-roots.o
