# uenux2 vota::IQRCodeBUDS::~IQRCodeBUDS, the D2 and D0 in slots 0 and 1 of the class's vtable (target fns 12050 and
# 12049, vtable @1542084, RTTI N4vota11IQRCodeBUDSE), in src/uenux2/src/app/vota/eleitor/fimvotacao/cmostraqrcodebu.cpp,
# the file the record of the class's constructor names (line 38 col 15, the CUeVotaError 9372 throw). The destructor has
# no record: it is the inline one declared in the class (cmostraqrcodebu.h, a chosen path: the class's only record is in
# the .cpp that defines its members, and no record names a header), because the target's D0 holds the D2's body, which
# clang gives only for an inline destructor. An inline destructor of a class with no other virtual member is emitted,
# with the vtable, only by a TU that defines a constructor, so the unit writes the constructor too (its record's throw
# on line 38). The constructor has no target function of its own: GetQRDSInst (fn 1956, record line 31) holds it,
# inlined by binaryen through IQRCodeBUDS::CreateInst (below). With them: the class header and the 9372 enumerator of a
# new app/vota/euevotaerror.h (RTTI CBaseError<vota::EUeVotaError, SErrorLimits{9300, 9500}> gives the enum's name and
# limits; the enumerator's name, chosen from the message, the header's path and the CUeVotaError alias name, both after
# api/util/eueutilerror.h, are choices no evidence makes).
# vota::CMostraQRCodeBU, the file's other class: GetInst (fn 2888), the constructor, the out-of-line destructor (fns
# 785, 1560, shared with other states) and the statics, whose mutex's exit-time destructor (fn 12056) matches;
# cmostraqrcodebu.h says what its layout rests on. GetInst matches since unit 138's caplicacaoencerrada.cpp defines
# vota::CAplicacaoEncerrada's two statics (their exit-time destructors are fns 12060 and 12059): its s_inst (@1833848)
# had no voter but GetInst (`unresolved self-voted`) until the pointer's exit-time destructor (fn 12057) matched, and
# the target's 12057 is a thunk into fn 1564, binaryen's merge of such destructors over the D2 fn 785, which forms only
# from three members; CMostraQRCodeBU's and unit 156's CMostraQRCodeCertificado's were two.
#
# Matches: ProcessInput (fn 12051, record line 85), with CMostraQRCodeCertificado::GetInst inlined; through its vote the
# certificate state's statics are named, and their exit-time destructors (fns 12041, 12042, unit 156's object) match.
# The switch on Read()'s result writes its cases in the target's block order, CONFIRMA before BRANCO (with BRANCO first
# the two case blocks swap, 60 over 210 rows); the CONFIRMA test, the step back and forth and the AjustaTela call are
# IQRCodeBUDS's inline members, chosen.
# StartState's three texts, the std::string (*)() functions it passes by table slot (1505 to 1507, the order of its
# frame's three std::function temporaries): fn 12054, the help text, the shorter one when the boletim has one part
# (TextoAjuda); fn 12053, the part shown, partes.at(atual) (ConteudoQRCode); fn 12052, "atual + 1/size" with
# std::to_string (TextoPagina). They call GetQRDSInst, internal to this file, so they are this file's; they match
# through the content pass (no symbol line names them), and our StartState passes them in the target's slot order.
#
# Written, not matching:
# - StartState (fn 12055, record 70, `differs`, named by its vtable slot): the demo-mode test (CAplicacaoEncerrada
#   next), IQRCodeBUDS's index reset, the screen from CTelasVota::CriaTelaQRCodeBU (ctelasvota.h has its evidence and
#   choices), the form moved into +28, AjustaTela, `this` next. In the whole link (pnpm wasm score, default depth) it is
#   281 over 2368 rows (same 2087, replaced 255 [252 operand-only], inserted 11, deleted 15). What differs: the target
#   computes the screen's height, the area's bottom + 1, into a local of its own and subtracts 48, 27 and 115 from it
#   (CONFIRMA's and Continuar's rows, the help text's bottom); clang folds that into bottom - 47, - 26 and - 114 for
#   every form of the height compiled (a TPosition, int, unsigned or uint16_t local, the area's copy with its bottom
#   moved, a size point; objects and scratch TUs at ctelasvota.cpp's flags). The other inserted and deleted rows are
#   where two of the area's fields are kept (a stack value against a local) and the locals' numbers; not explained
#   apart from the height. Measured on the way, in the whole link: the area read as one local copy (three i16 loads)
#   732 over 2421; through AreaTela's by-value copy (the target's one i64.load) 756 over 2418; with the layout values
#   as locals declared ahead of their statements 284 over 2370, and 281 over 2368 with the version's row one too.
#   The locals declared before or after the status header give the same link (sha256 compared), and so does the height
#   as a uint16_t or a TPosition. CQRCodeImage's constructor takes its std::function by value since (cqrcodeimage.h
#   says why): fn 3662's match line follows the symbol (a rename) and its body is unchanged.
# - GetQRDSInst (fn 1956, record 31, `unresolved`): it calls CCabecalhoQRCodeBuilder::DefineHistoricoCarga (fn 5622),
#   written in unit 93 and `no-candidate` (its body is the target's but for its locals' numbers: 89 over 431 rows, every
#   replaced row operand-only), and Gera (fn 5604, unit 155's, `no-candidate`). It holds, inlined by binaryen, two
#   functions with frames of their own (IQRCodeBUDS::GeraPartes, 880 bytes, and IQRCodeBUDS::CreateInst, 16), and from
#   other files CAppInfo::GetGap's non-const overload (record cappinfo.cpp:42) and CPolySingleton's set, push and
#   instance. It scores 650 over 2482 rows (51 inserted, 57 deleted): the gap's correspondences are read through a local
#   holding +184 where the target folds 184 into the loads, and GeraPartes's empty-loop and throw blocks sit apart from
#   the target's. Both are measured, not explained. Its name reaches it by its callers' votes (`call by:5982,12051`).
# - AjustaTela (fn 5982, record 195, `unresolved self-voted`): 44 over 696 rows, all operand-only, but its callee
#   FindFieldAs<CTextField> (fn 1721, api/gui/iform.h, record 142) has no voter but 5982, and 1721 `differs`: 51 over
#   163 rows, its type-mismatch throw placed after the loop where the target keeps it before the loop's step (with the
#   field copied before the cast, as the target increments the count before dynamic_cast; without the copy, 46 over 142
#   and the increment after the cast; with std::find_if, 137 over 222). cmostraqrcodebu.cpp compiled at -O2, -Os and at
#   -O3 with and without strict aliasing places the throw last in 1721's copy; only -Oz places it inside the loop, and
#   shortens the copy from 162 to 111 lines of wasm-objdump -d (the target's has the -O3 copy's length). A call clang
#   does not know never returns, inlined by binaryen afterwards, would leave the block in the loop (a reading, not
#   written: that is a noreturn question). The seven
#   fields are CTextFields: fn 940, which it calls on them, is api::CTextField::SetCorTexto (unit 27), the body binaryen
#   shares with CTextBox::SetStatus, and whose match line moves to that name (a twin rename).
# Each score above is pnpm wasm score in the whole link of the commit that adds StartState.
#
# The trap file and the roots file went with StartState: its call of AjustaTela is in the link (5982 has its two call
# sites), and nothing is pending.
#
# Chosen as unit 104's states are (the shape it measured): GetInst's name and reference result, s_inst and s_mutex and
# their order after GetInst, the local trava, the constructor out of line and above the destructor, declared first;
# the definitions' lines, after IQRCodeBUDS's constructor and above the records of the members not written; the
# member's name, and its type spelled out (unit 156's fragment says why not CFormInterativoTelaVota). Chosen too:
# GeraPartes and CreateInst as IQRCodeBUDS's static members (two functions, from the two frames; free functions in
# cmostraqrcodebu.cpp would serve), their bodies' order of statements as the target's, the accessors, and every
# function's line but the records'. In StartState: the demo flag in a local, `bool ehDemo = `, whose width the record's
# column (70:19) fixes (the form of CRetirarMR::ProcessInput, whose record 78:19 has the same column), and the early
# return. The three texts: their names, their internal linkage (an external definition at the same place gives the
# same order of functions in the object, a reading), and their place: declared in an anonymous namespace above
# StartState (the room the records leave above line 70 holds no three definitions) and defined after ProcessInput;
# the object holds them right after StartState, where they are first mentioned, and the target's index order
# (12055, 12054, 12053, 12052, 12051 in one use band) has them so.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
IQRCODEBUDS_SRCS := src/app/vota/eleitor/fimvotacao/cmostraqrcodebu.cpp
UENUX2_SRCS += $(IQRCODEBUDS_SRCS)
