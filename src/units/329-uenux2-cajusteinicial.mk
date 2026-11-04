# uenux2 vota::CAjusteInicial and vota::IAjusteInicial (app/vota/eleitor/cajusteinicial.{h,cpp}, the header new, and
# iajusteinicial.h): IAjusteInicial::GetInst (record cajusteinicial.cpp:57; no target index: binaryen inlines it into
# its one caller, vota::CThreadEleitor::Run, fn 7061, unit 116's), CAjusteInicial's constructor and its slot 2,
# StartState (target fn 7160, 5220 B), with what 7160 holds inlined: the four members the records name, behind
# frames of their own (ValidaTemposDesligamento, :74, :79, :84; InicioVota, :170, :178; LimpaMidiaResultado, :191;
# AjustaDataHora, :220, :245), and two free functions with no record, CriaControladorRegistraMesarios here, behind a
# frame of its own, and AbreDiretorio in cthreadeleitor.cpp, with none (it lies in LimpaMidiaResultado's 80-byte
# frame; the null test after it gives another TU); the GetInst, constructor and statics of the four states 7160 holds
# inlined, written in their own units' files (vota::CFinalizaAquisicao, unit 223; CVerificaQtdBUsAdicionais, unit 185;
# CVerificaEleicaoPassou, unit 199; testeteclado::CRetomada, unit 138); five EUeVotaError codes
# (app/vota/euevotaerror.h, chosen names).
#
# The source compiles in unit 116's list (CTHREADS_SRCS), ahead of cthreadeleitor.cpp, the target data's order:
# cajusteinicial.cpp's records (@1534280 to @1534408) lie between csincronismovotoeleitor.cpp's and cthreadeleitor.cpp's
# (@1534648), and the fimvotacao/ and iniciovotacao/ files whose GetInsts 7160 holds come after both. That order was
# measured against this fragment's own list (after every other unit's): the same rows for 7160 and 7061. This fragment
# keeps the notes and the include path.
#
# Status. 7061 is unit 116's and matches (its paragraph there). 7160 is written; step 9 reads it `unresolved`, `ours
# +0xee9 i32.const 1780048: an address of ours: _ZN4vota12testeteclado9CRetomada6s_instE (.bss) has no target symbol`:
# the statics its inlined GetInsts read have no name, since no target function but 7160 and their exit destructors
# loads them (below) and 7160, named by its vtable slot, casts no vote. Its body differs in binaryen's local numbering
# besides: `pnpm
# wasm score` against the plain link (names.tsv after make -C src link-map) reads 402 over 2225 rows (same 1823,
# replaced 390 of which 389 operand-only, 6 inserted, 6 deleted); both sides declare 10 i32 and 2 i64 locals and hold
# 2218 instructions; every operand row that is no call and no data address is a local index, a .bss address of the
# inlined GetInsts' statics, a table slot of the throws' destructors or a std::format string's packed address, and the
# 13 rows that are not operand-only are a compare and four adds whose operands binaryen orders by local index
# (ValidaTemposDesligamento's `i32.lt_u` reads `i32.gt_u` with the operands swapped; the terminator stores of four
# string copies). The locals differ from AjustaDataHora's first rows on (the target keeps CAppInfo::GetInst()'s result
# in local 2 and GetGeral()'s in local 4, ours the other way), and in the registrar the target puts the info in local 1
# and operator new's result in local 3, ours in 4 and 1. Not explained. These moved no row: cajusteinicial.cpp in this
# fragment's list or in unit 116's; StartState and CriaControladorRegistraMesarios after AjustaDataHora or in the blank
# run between ValidaTemposDesligamento and InicioVota; the file built without strict aliasing (its directory has it; the
# link was byte-identical, so the flag decides nothing here); the registrar's pointer named or a temporary; and the
# compare's rows are the same in the first draft's link, written `tempoAviso > tempoDesligamento`, and in this one,
# written the other way round. 7160 stays written: a vtable slot whose body is one remainder off (how-to step 5),
# CAjusteInicial's slot 2, whose vtable 7061's vptr store keeps. The exit destructors of the statics its inlined
# GetInsts read (11832 and 11833, CRetomada's mutex and pointer @1834972 and @1834996; 11915 and 11916,
# CVerificaEleicaoPassou's @1834356 and @1834380; 12024 and 12025, CVerificaQtdBUsAdicionais's @1833964 and @1833988;
# 12114 and 12115, CFinalizaAquisicao's @1833444 and @1833468) wait for its match: no target function but 7160 and the
# destructor loads each address (`/usr/bin/grep -rlE 'i32\.const <address>($|[^0-9])' build/out/splat/pieces/asm`).
# A reading, not measured: once the locals are the target's, the statics' names can come only from hand lines (.bss
# objects led by their exit destructors, docs/how-to-decompile.md step 9 "Hand edits"), since 7160 alone votes for them.
#
# What the target shows (pnpm wasm fn ../target/vota_web_wasm.wasm 7160 from asmlift-wasm/, and the records):
# - The class: RTTI, si_class of vota::IAjusteInicial, itself a si_class of comum::CAppState (typeinfos @1534424 and
#   @1534436); the vtable @1534236 [174, 144, 7160, 7480, 1661, 218, 425, 218, 425], CAppState's with slot 2 its own.
#   GetInst allocates 12 bytes, the base's size, and passes 0 to the base's constructor (fn 224): no data member, the
#   constructor a default one (CAppState's argument defaults to 0). The target has no vtable of IAjusteInicial (no word
#   equal to its typeinfo follows a zero word) and CAjusteInicial is its one derived class (ledger/classes.json).
# - GetInst: has<IAjusteInicial> (fn 2450), then CPolySingleton<IAjusteInicial>::set over `new CAjusteInicial` behind a
#   16-B frame of its own (set, which clang keeps out of line), then instance(), the record at :57 column 12 the start
#   of `api::CPolySingleton<IAjusteInicial>::instance()` after `return `. The landed CLogVota::GetInst (fn 184) has the
#   shape, `if (!has<I>()) set(std::unique_ptr<I>(new C)); return instance();`. The constructor is out of line here:
#   7061 keeps operator new's pointer and stores the vptr through fn 224's returned this, as an out-of-line constructor
#   that binaryen inlines gives (unit 116's paragraph has the two scores).
# - StartState holds, in this order and each behind a stack frame of its own, so each a function clang kept out of line
#   and binaryen inlined (docs/reference/facts/reading.md R10): AjustaDataHora (48 B), ValidaTemposDesligamento (48 B),
#   LimpaMidiaResultado (80 B), then, when comum::CInformacaoEleicao over CConfiguracaoEleicao's parameters (+88, fns
#   603 and 1950) prints the BJust and no comum::IControladorRegistraMesarios is registered (fn 2446), the registrar (16
#   B, with push<T>'s 512 B inside it), then InicioVota (544 B). Their order in the file follows the records' lines;
#   StartState and the registrar, which have none, are last, a choice (measured above: their place moves no row).
# - AjustaDataHora: when the demo mode is on (IInterfaceInit's GetDemoMode, fn 729, through CPolySingleton::instance,
#   the record at :220 column 36) or the load's phase (+48 of CAppInfo::GetGeral() const, fn 457) is 51, and the vote
#   state (CAppInfo::GetVota, fn 261) is at most 55, it shifts the clock: the target date and time is the voting's start
#   (CConfiguracaoEleicao +556) for a voter training, else the zeresima's (+544) with its time less 30
#   (CTime::operator-, fn 3641); AdicionaDeltaT (3702) gets the difference of the two local times from CDateTime's
#   ConvertToLocalTime, SetAjusteDataHora (3705) stores it, IAjusteDataHora's slot 0 (record :245 column 13) adjusts,
#   and CSincronizaVota::SincronizaEstadoGeral (3333) saves. GetGeral() const is called before the demo mode is tested,
#   so the phase is read into a named bool first.
# - ValidaTemposDesligamento: CConfiguracaoEleicao's +180 and +184 (GetTempoDesligamentoAutomatico,
#   GetTempoAvisoDesligamentoAutomatico); throws 9405 when the first is not positive, 9406 when the second is not, 9407
#   when the second is greater (records :74, :79, :84, column 15, their messages the target's literals).
# - InicioVota: the vote state and the closing state from the const GetVota (fn 903, whose turn argument binaryen
#   folded: the target calls it with `this` alone where GetInst()'s non-const result calls fn 261), so a const
#   CAppInfo&; a switch over the state (br_table from 49) to the next state's GetInst, those of CVerificaEleicaoPassou,
#   CRetomada, CFinalizaAquisicao and CVerificaQtdBUsAdicionais inlined, the others calls (3865, 5973, 3864, 6129, 6084,
#   5983, 6037, 6174, 5984, 2291); for a closed vote a second switch over the closing state; each default logs
#   LogaErroEstadoAplicativoDesconhecido (3279) and throws 9303 or 9304 with std::format of "Estado encerramento nao
#   conhecido = {}" or "Estado nao conhecido = {}" (records :170 column 27, :178 column 19).
# - LimpaMidiaResultado: on a training load (phase 51) not of a voter training, IInterfaceInit's HabilitarMR,
#   IsMRPresenteSemHabilitar (else comum::IEventosLog's LogaMidiaResultadoAusente, 5885, on CLogVota::GetInst()),
#   HabilitarMR, IsMRMontadoSemHabilitar and
#   then DesmontarMRSemDesabilitar and DesabilitarMR (unit 35's, inlined by binaryen: unit 35's roots no longer give it
#   a second call site), HabilitarMR, MontarMRSemHabilitar; then a directory reader over CPath::GetPathMR(), and for
#   each entry whose name starts with neither "infomidia" nor "turno2", CSystem::RemoveFile of the path joined with it.
#   The reader is built after GetPathMR's path and its string copy, by operator new and CDirReader's constructor (fn
#   1914), and tested for null before the loop; it is freed with free of the D2's result (fn 1913), the shape of a
#   delete in a TU that only declares the destructor. Measured on the object: `if (leitor)` over a `new` written in this
#   TU folds away (the variant's object differs only in data offsets), as `new` cannot return null, and a new-expression
#   calls operator new before it evaluates its argument (the first draft's link has new(20) before GetPathMR's call), so
#   the pointer comes from a function clang does not see: AbreDiretorio, of another TU (R10's rule: a free function of
#   the caller's namespace in a .cpp chosen, here cthreadeleitor.cpp, which this lane writes).
# - The registrar: inside its 16-B frame the poly singletons' info (the g_polySingletonsInfo call) is read first and
#   operator new(4) comes after it, then the vptr of vota::CControladorRegistraMesariosVota (1586608) and
#   CPolySingletonList::set's has, remove and push. `CPolySingleton<I>::set(std::unique_ptr<I>(new C))` in StartState,
#   `set(new C)` and `set(std::make_unique<C>())` all give new first and then the info, in the caller (measured on the
#   object), so the info is read in a function of its own before the object is built: the form of
#   IQRCodeBUDS::CreateInst (cmostraqrcodebu.cpp, unit 37), whose GetQRDSInst (fn 1956) is the one other target function
#   with this order (a search of the pieces for a 16-B frame, the info call and then call 137). Written beside
#   StartState it stays a function of its own in this object, as CPolySingleton<IAjusteInicial>::set and both push<T>
#   do (`wasm-objdump -x -j Function` on cajusteinicial.cpp.o lists them), so clang does not inline it there.
#
# Chosen, no evidence names them: the free functions' names, their being free functions of vota, their files and lines
# (CriaControladorRegistraMesarios beside StartState, AbreDiretorio in cthreadeleitor.cpp after Run); the private
# members' access; the constructor's being declared public; the locals' names (the record at :220 fixes the length of
# `const bool demonstracaoAtiva = `, :191 that of `comum::IInterfaceInit& interface = `); the enumerators' names
# (euevotaerror.h says from what); the header's path beside the .cpp; the lines between the records; std::unique_ptr
# for the reader and the registrar's pointer (a raw pointer and delete is the other form, not compiled);
# IAjusteInicial's path beside the .cpp and its having no key function. The same rows, measured: the registrar's pointer
# named or a temporary.
#
# cajusteinicial.cpp includes app/comum/dados/cconfiguracaoeleicao.h, which reaches Boost through
# CConfiguracaoMunicipio's CHorariosUrna (an include path, not a flag of the code: unit 88 adds the same)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/cajusteinicial.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
