# uenux2 vota eleitor classes no landed file holds, in app/vota/eleitor/ (paths relative to src/uenux2):
# vota::impl::ISincronismoVotoEleitor's destructor and GetInst with its default instance,
# vota::impl::CSincronismoVotoEleitor (csincronismovotoeleitor.{h,cpp}), and vota::CFimVotoEleitor's constructor,
# GetInst and statics (cfimvotoeleitor.{h,cpp}). Both GetInsts are held inlined by vota::CSincronismoEleitor::ProcessKey
# (fn 7181, unit 192's csincronismoeleitor.cpp), which matches with them.
#
# Target functions matched:
# - 7175, the exit destructor of ISincronismoVotoEleitor::GetInst's mutex (f150(1833164)), and 7212 and 7202, those of
#   CFimVotoEleitor's s_inst (f349(p0, 1833132)) and s_mutex (f150(1833108)). The scan's content pass found the three
#   (their match lines' symbols have no line in splat/symbol_addrs.txt; a rescan writes `symbol` in their source
#   column). Each is right by what it destroys: ours, the __cxx_global_array_dtor (and .2) of
#   csincronismovotoeleitor.cpp.o and cfimvotoeleitor.cpp.o (pnpm wasm fn on our link), destroy the mutex, s_inst and
#   s_mutex, and splat/symbol_addrs.txt places those three names at 1833164, 1833132 and 1833108. The names have
#   7181's votes and hold through these second matches (docs/reference/splat.md section 3).
# - Rows this unit's sources release in other units: 7181 (unit 192), with the executable TU's has<T> and push<T> thunks
#   2741 and 5398 that it calls and the TU's set<ISincronismoVotoEleitor>, 9437, over them (unit 170's paragraph).
#
# Written since: CSincronismoVotoEleitor::Sincroniza (7174, slot 2, 3288 B), the class's key function, in
# csincronismovotoeleitor.cpp after GetInst, so that object emits the vtable (the pending file that trapped it went).
# - The body: frameless, it calls CTelasVota::GetInst().IncrementaBarraSincronismo() (407, 2369) four times, around
#   vota::CSincronizaVota::SincronizaVotoMI, CLogVota::GetInst().LogaVotoComputado() (184, then
#   "O voto do eleitor foi computado" to comum::IEventosLog::loga, 233, behind a 16-byte frame of its own, the shape of
#   the CLogVota members clogvota.h lists) and SincronizaVotoMV, and returns true. The two halves are
#   csincronizavota.cpp's: they hold its anonymous SincronizaRDVInternoSeguro and SincronizaRDVExternoSeguro (records
#   290 and 303), which only that file can call, and binaryen inlined each into 7174, its one caller, behind a 48- and a
#   16-byte frame (unit 205's fragment says what they do). Their steps in other files take frames of their own in 7174
#   as binaryen inlined each into its one caller: CRdv's SalvaTemporarioInterno, ConfereTemporarioInterno and their
#   Externo pair and comum::SubstituiRdvInterno and SubstituiRdvExterno (crdv.cpp, unit 381: 48 bytes each),
#   CEleitores::GravaEleitorCorrenteMI (celeitores.cpp, unit 110's list: 32 bytes) and LogaVotoComputado (clogvota.cpp:
#   16 bytes).
# - The frames' layouts are the forms': the ".tmp" path as comum::GetArquivoRdvTemporarioInterno() (or Externo), a
#   function clang inlines (with a named std::string in each user instead, ReplaceFile's three strings sat in another
#   order); the read back as CRdv::ConfereArquivo over CRdv::Le, two private members clang inlines (with Le alone, a
#   64-byte frame against the target's 48: the bytes below the path); the database written through a temporary
#   dao::CEleitorDinamicoDAO (as a named local after a named path, the path's and the DAO's offsets swapped). pnpm
#   wasm score on the link: 258 over 1491 rows (4 inserted) before those three, 181 over 1487 after, all operand-only
#   (calls, the flag's address and the throw's destructor slot).
# - Names: 2543 (comum::VerificaIntegridadeVotos, unit 98's, written and no match: the user's rule) is named by step
#   8's `call` line from its two callers in the link, 7174 and fragment 386's 6734, each the other's holding match.
#   With 7174 alone that line was 7174's own vote, which the build's fixed point refuses as self-voted, and a
#   `callers+content` hand line named 2543 from its own rows; it went once 6734 was in (removed on copies: no row moves;
#   with the name out on both sides 6734 and 7174 fall). 7174 is `srcloc-anchor` (its records 290 and 303) and matches.
# - Chosen: the names of the steps and of the halves, their files where no record names one, and the lines.
#
# Written since: CFimVotoEleitor::StartState (7198, slot 2, record cfimvotoeleitor.cpp:42), the class's key function,
# so cfimvotoeleitor.cpp.o emits the vtable. It shows the form at +156 of vota::CTelasVota (slot 2, through a getter
# ctelasvota.h has now), beeps through IBeep's slot 2 with 4 (its instance() call at :42), says "fim" (the 3 bytes
# at 150256) through CVotacaoStateAudio::PlayMessage (1204, unit 97's) when CEstadoAudio is active, posts a message
# of type 1 to CThreadOperador's queue (api::SMessage{1, &fila} at priority 1, as cverificaeleicaopassou.cpp posts
# its own) and goes to CAguardaMensagem. It waited for 1204 alone, and matched as written (pnpm wasm score before
# step 8: operand rows only). Its lines and the includes' are a choice, StartState's above :42.
#
# What the target shows:
# - ISincronismoVotoEleitor's destructor is out of line in csincronismovotoeleitor.cpp, its key function
#   (isincronismovotoeleitor.h has the evidence: where its typeinfo lies, and the executable TU's has<T> loading the
#   type name from it). Which member is the key function, and `= default`, are chosen.
# - GetInst's record, csincronismovotoeleitor.cpp:67 column 98, is the closing parenthesis of
#   POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(ISincronismoVotoEleitor, CSincronismoVotoEleitor) (unit 50's
#   macro, whose column reading this record fits: 52 plus the two names' lengths). CSincronismoVotoEleitor is 4 bytes:
#   7181 allocates 4 and stores only the vptr (@1534164).
# - CFimVotoEleitor: cfimvotoeleitor.h has the layout, the constructor out of line (measured on 7181: an in-class
#   constructor leaves one row inserted and one deleted) and the statics' order. The constructor, GetInst and the
#   statics are above StartState in cfimvotoeleitor.cpp, as the exit destructors' order puts them (ld_index 4911,
#   4912, 4913 for 7212, 7202 and 7198).
# - Link order: in the target's use band 1 cfimvotoeleitor.cpp's functions (7212, 7202, 7198) link before
#   csincronismoeleitor.cpp's (7195, 7187, 7181, 7178), which link before csincronismovotoeleitor.cpp's (7175, 7174):
#   the directory's name order. This fragment lists cfimvotoeleitor.cpp after unit 192's csincronismoeleitor.cpp.
#   Every row of the three objects this branch matches is `match` with that order, and inside each object the matched
#   rows keep the target's order (ld_index 4592 < 4593 for 7212, 7202; 4361 < 4362 for 7181, 7178).
# - Data: csincronismovotoeleitor.cpp's data in the target holds GetInst's record (@1534132), the interface's typeinfo
#   (@1534148), CSincronismoVotoEleitor's vtable (@1534156) and typeinfo (@1534176), then instance<T>'s records; ours
#   emits the class's vtable and typeinfo in csincronismovotoeleitor.cpp.o now, after GetInst's record and the
#   interface's own vtable and typeinfo (wasm-objdump -x -j Data of the object).
#
# Chosen, no evidence names them: the paths of both headers, the files' lines other than the two records', GetInst's
# place in cfimvotoeleitor.cpp, the statics' names, EVENTO_NENHUM for the base constructor's 0, and this fragment's
# order against unit 192 (above).
APP_VOTA_ELEITOR_SRCS := src/app/vota/eleitor/cfimvotoeleitor.cpp src/app/vota/eleitor/csincronismovotoeleitor.cpp
UENUX2_SRCS += $(APP_VOTA_ELEITOR_SRCS)
