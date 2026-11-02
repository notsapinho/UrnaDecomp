# uenux2: the wasm simulator's start, mock/app/simulador/wasm/simulador.cpp and simulador.h: target fn 8302 under the
# chosen name simulador::Inicializa, the three functions binaryen inlined into it (InicializaAmbiente,
# InicializaDispositivos, InicializaLog: each has a frame of its own inside 8302, which has none), and the constructor of
# the settings main builds for it, simulador::SConfiguracao (fn 8311, matched). The source is compiled from unit 101's
# list (src/units/101-uenux2-api-util-singletons.mk), ahead of api/util/itimerscheduler.cpp: this fragment holds no
# rule. The executable TU's main, which calls 8302, is unit 170's; the CPath member 8302 holds inlined
# (CPath::SetPathRoot) is unit 190's cpath.cpp; CWasmLogd's constructor is unit 62's cwasmlogd.cpp; the set and push
# forms are unit 100's headers. Each of those fragments says what it rests on.
#
# Matches with this file (against 0fe14b05, by target index): 8311; 4879 and 4890, CPolySingleton<ITimerScheduler>::set
# and <ISystemDateTime>::set, whose records (1531292, 1531932) lie among 8302's (4890's line names the raw-pointer
# template over CWasmSystemDateTime because binaryen folds that body with set(unique_ptr<ISystemDateTime>) of
# isystemdatetime.cpp.o, which fn 1155 calls, and keeps this object's name: the two forms give one body, so the bytes
# do not decide which the target's 4890 is, and its name is the link order's pick); the two mocks' members (unit 75: they
# came from that unit's roots object, which is gone) and the control blocks push<T> builds here (8036 for IScreenMT,
# 11554 and 11557 for ITextToSpeech); has<T> thunks 4853, 4872, 4877. Measured on the order: with simulador.cpp in a
# fragment of its own, after itimerscheduler.cpp, 4879's copy was itimerscheduler.cpp.o's and read `differs +0xa5 target
# +0xa3 i32.store align=2 offset=172 | ours offset=120` (`pnpm wasm score`: 141 over 895 rows, 136 operand-only); listed
# before it, 4879 matches from this object. In the target this TU's data lie before api/'s.
#
# Not matched: 8302 (no-candidate). Our body is the target's in shape but for, at least:
# - the ITextToSpeech set: the target calls fn 4162, the executable TU's copy of CPolySingleton<ITextToSpeech>::set
#   (landing pads), which only votaInit's code instantiates (not written); ours inlines this TU's copy;
# - CPath::GetPathLog: the target calls fn 5899; clang inlines it into our InicializaLog (it is inline in cpath.h, unit
#   190's choice), so unit 190's two roots calls stay;
# - CWasmScreen's constructor: the two forms unit 69's fragment names (the log text's build, the two 16-bit stores);
# - InicializaDispositivos' frame: the unique_ptr IInterfaceInit's set leaves there is at +4, the target's at +8;
# - the push bodies 8302 holds inlined differ only in operands.
#   (`diff` of the two disassemblies with local numbers, call targets and addresses masked.)
#
# Evidence and choices.
# - The layout of 8302: a frameless body that ends with the std::function's call (slot 6, __throw_bad_function_call
#   when empty), after three inlined bodies with frames of 16, 16 and 64 bytes. That these are functions of their own
#   is evidence (the frames); that they are three, their names, their being in this TU and external, are choices.
#   main passes the settings by address and the std::function by address, destroying both after the call.
# - InicializaAmbiente: CPath::SetPathRoot("/"), create_directories("/uenux") (fn 2548 with a null error_code), then
#   setenv("PROJECT_DIR", ".") and setenv("BUILD_DIR", "/") (fn 6256: libc's setenv, its third argument folded; the
#   literals are the tails at 378041 and 358800).
# - InicializaDispositivos: ITimerScheduler::CreateInst<CWasmTimerScheduler>, then a set per device in the target's
#   order (its vptr stores: CWasmInit with the settings' +0, CWasmScreen with +16 and +18, CWasmScreenMT, CWasmInputKbd,
#   CWasmInputMT, CWasmResource, CUrnaMock, CPowerMock, CWasmBeep, CWasmNullSound, CWasmNullPaper, CWasmNullPrinter,
#   CWasmNullTextToSpeech, CWasmSystemDateTime). Each is `set(new C)`, the raw-pointer set (unit 100's fragment):
#   the operator new comes before the info pointer's call, and the info pointer's call before the unique_ptr's store.
#   For IInterfaceInit and CEscritorLog the target holds the unique_ptr in the caller's frame and remove<T> in a frame
#   of its own; for the others in set's frame, remove<T> inside it. Our link gives each the shape the target has with
#   one form for all; a reading: the two are the classes whose type name is read through a typeinfo (key functions).
# - InicializaLog: `CPath::GetPathLog() / "logd.dat"` in a named path, then set(new CWasmLogd(path)): the path's copy is
#   the constructor's by-value argument, made after operator new (C++17's order) and destroyed after the set.
# - SConfiguracao: an int at +0 (main passes 10), a std::string at +4 ("VOTA Web", moved from a by-value parameter:
#   main destroys its temporary after the call), two TPosition at +16 and +18 (js_ler_dimensao_tela's results, 16-bit
#   in main). 8302 reads +0, +16 and +18; nothing reads the string. Every name and the int's type are chosen.
# - CWasmLogd's constructor (cwasmlogd.cpp): m_arquivo is a std::filesystem::path, since the target calls
#   path::__parent_path (fn 1840) on the member itself; the constructor creates that directory and opens and closes
#   the file with "wb". The parameter by value and the move are the target's (it nulls the caller's temporary).
# - CPath::SetPathRoot (cpath.cpp): it copies its argument into a local before it assigns s_pathRoot (a copy
#   construction, then __assign_no_alias, in its own 96-byte frame), builds both "/dsk/fi/" and "/dsk/fe/" before
#   either path, and sets s_pathFlash[0] and [1] as GetPathRootSemSA builds them. The name, the parameter's type and the
#   named local are chosen; the copy's form is not measured against others.
