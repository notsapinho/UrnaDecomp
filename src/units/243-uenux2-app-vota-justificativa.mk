# uenux2 vota operador: the justification of a voter whom the urna does not list, the pair of singletons
# vota::CProcuraEleitor::StartState (fn 10631, unit 104) goes to: vota::CConfirmaJustificativa
# (app/vota/operador/justificativa/cconfirmajustificativa.{h,cpp}) and vota::CIniciaJustificativa
# (justificativa/ciniciajustificativa.{h,cpp}). Paths relative to src/uenux2. Target fns matched: 3626, the D2 the three
# Confirma classes' slot 0 holds (matched under CConfirmaJustificativa's D1, named by `vtable`), and the statics' exit
# destructors 10621 (CConfirmaJustificativa's mutex), 10617 and 10616 (CIniciaJustificativa's pointer and mutex), and
# 10622 (its pointer's, below). Both
# GetInst and both constructors have no index of their own: 10631 holds them inlined, and matches with them (unit 104).
#
# Evidence, each class's header says the rest (RTTI, vtable, statics):
# - Two TUs. In the target, CConfirmaJustificativa::GetInst is a call in the object that defines CIniciaJustificativa's
#   constructor, inlined by binaryen: 10631 pushes the new CIniciaJustificativa before the inlined body and hands it to
#   IIniciaJustificativa's constructor (3624) after. In one TU clang inlines it, and 10631 scored `69 over 277 rows
#   (same 208, replaced 64 [61 operand-only], inserted 3, deleted 2)` with the object reloaded before 3624's call; in two,
#   `69 over 276 rows (same 207, replaced 65 [65 operand-only], inserted 2, deleted 2)`, the reload gone (pnpm wasm score,
#   the rest of the tree unchanged; the rows left were unit 104's measured local swap). The data order is evidence for
#   the two files too: compiled in one TU the two classes lay out both vtables, then both typeinfos (wasm-objdump -x),
#   and in two each vtable is followed by its typeinfo, the target's order (ledger/classes.json), and
#   CConfirmaJustificativa's, CIniciaJustificativa's, CConfirmaJustificativaTemporario's,
#   CIniciaJustificativaTemporario's, CConfirmaJustificativaTransito's and CIniciaJustificativaTransito's alternate in
#   that order (@1589252 to @1589532), after IEleitorImpedidoVotar's (@1589136, unit 161) and before
#   CJustificativaEfetuada's (@1589804, unit 142); in use band 1 the statics' exit destructors link in the same order,
#   10622 and 10621, then 10617 and 10616. Which file names the six objects have, and that the link line is not in name
#   order there, is not evidence: the names are the classes', how-to step 3's rule 4, chosen. The sources below keep the
#   data's order.
# - CConfirmaJustificativa's destructor is out of line in its .cpp, so the class has a key function: 10631 frees a
#   replaced object with `this` after a call of IConfirmaJustificativa's D2 (1688), the out-of-line shape
#   (docs/reference/facts/reading.md R5); with the destructor implicit, our object freed what the D2 returns. Its slot 0
#   is 3626, `f1688(p0)`, which our D2 gives. CIniciaJustificativa's is implicit: slots 0 and 1 are the shared 174 and
#   144, and 10631 frees a replaced object with no call.
# - CConfirmaJustificativa's constructor passes IConfirmaJustificativa's (3625, unit 174) the text
#   comum::md::CTradutorFrase::Traduz (654) makes of "não pertence <S|a|ao|à> <SCSN>", through FraseNaoPertence, a helper
#   of the file's anonymous namespace that clang inlines: the constructor's 32-byte frame has the literal's temporary at
#   +20 and Traduz's result at +8, as the target's; `Traduz("...")` in the member list and `Traduz(std::string("..."))`
#   give +8 and +20 (wasm-objdump -d of try objects of the three forms).
# - CIniciaJustificativa's constructor hands IIniciaJustificativa's CConfirmaJustificativa::GetInst(); the target
#   allocates the CIniciaJustificativa before it calls that GetInst.
# - GetInst is defined above the constructor in both files, measured on 10631 (unit 104's fragment has the scores).
# - CConfirmaJustificativa's pointer's exit destructor, 10622, is `f3885(p0, 1905700)`, a thunk into the body binaryen
#   merged from the exit destructors of the three Confirma singletons (10611, 10615, 10622), two of which 10635 creates
#   (fragment 283's classes): with them in the link, 10622 and 3885 match. The pointer's .bss name took a
#   `callers+content` hand line while 10622 waited; with 10622 matched, two scans and splat-build without the line moved
#   no row and gave the target's sha256 (docs/reference/splat.md "Reviewing a match"), so it went: the generated line
#   (10631's votes) holds the name, with 10622's match.
#
# Chosen: the four paths, FraseNaoPertence's name and linkage, the statics' names and the lines. Not measured, and
# they may give the same bytes: a lambda or a static member in FraseNaoPertence's place.
#
# No roots: the stand-in for CEleitorEncontrado::StartState (10635) that gave vota::NaoAceitaJustificativa (4578, unit
# 168), CEleitorNaoEncontrado::GetInst (5424, unit 161), IEleitorImpedidoVotar's constructor (1905, unit 161) and
# IConfirmaJustificativa's (3625, unit 174) their second call site went when 10635 was written (unit 104).
APP_VOTA_JUSTIFICATIVA_SRCS := src/app/vota/operador/justificativa/cconfirmajustificativa.cpp \
    src/app/vota/operador/justificativa/ciniciajustificativa.cpp
UENUX2_SRCS += $(APP_VOTA_JUSTIFICATIVA_SRCS)
