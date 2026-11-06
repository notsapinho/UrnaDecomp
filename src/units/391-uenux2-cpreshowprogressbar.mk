# Unit 391: vota::CPreShowProgressBar::PreShow (target fn 13550, slot 2 of the class's vtable @1536544, its key
# function), matched, in src/uenux2/src/app/vota/eleitor/comum/cpreshowprogressbar.cpp, with api::CStepsProgressBar's
# constructor (record cstepsprogressbar.cpp:428:15), which 13550 holds behind a second prologue (binaryen inlined it,
# so it has no target function of its own), written in unit 41's cstepsprogressbar.cpp (that fragment has what the
# constructor rests on). This fragment lists no source: unit 150's list compiles cpreshowprogressbar.cpp, before
# ctelascargo.cpp, for its place (that fragment has the count). Scores are `pnpm wasm score
# ../target/vota_web_wasm.wasm 13550 <link> <ours>` at the default depth, whole link at the tree's flags: the forms
# measured before vota::DesenhaDescricaoModo became a member (below) on 8f35addb with this unit, the rest on 59a65ba6
# with this unit.
#
# The file: no record names it. PreShow is the class's one out-of-line virtual member, so its object emits the vtable
# and typeinfo, which the target's data hold between cpoliticaexecucaoeleitor.cpp's records (@1536400 to @1536543) and
# ctelascargo.cpp's (@1536576), app/vota/eleitor/comum's files in name order there; the file is that directory's and
# named after the class (docs/how-to-decompile.md step 3, rules 2 and 4), the name a choice. The class head stays in
# app/vota/comum/cpreshowformvota.h (its comment says why).
#
# What 13550 does, read from its folded readout (the body written gives each of these rows, its locals aside): the
# screen cleared (IScreen's slot 4 with 1), vota::DesenhaDescricaoModo (4620) at {320, 30}, one step per choice of each
# post comum::CCargos keeps (CConfiguracaoEleicao::GetCargo, 861; the post's GetNomeNeutro, 1547, with " - " and
# GetOrdinalEscolha, 2258, when it has more than one choice), the steps counted until the current post's current choice
# (CCargos's GetCurrentEleicaoID 2835 and GetCurrentCargoID 1938 unless IsFim, 602; vota::g_escolhaAtual), and with two
# steps or more an api::CStepsProgressBar over (2, 2, the screen's width - 3, 30) in the colours 3, 2, 36, 2, 1, 3 and
# 0, drawn (5504) and destroyed (3665).
#
# What matches it: 13550 is `match` with every row of `pnpm wasm score` an operand (47 over 1007 rows, same 960,
# replaced 47 [47 operand-only], inserted 0, deleted 0; the one row that is no call or data address is the CUeGuiError
# throw's destructor, table slot 69 against our 43, which re-points to 4636). The last two forms of the list below made
# it so, and api::CStepsProgressBar::Draw (5504), its callee, needs a hand line (below). The object's place decides
# nothing measured: a link with cpreshowprogressbar.cpp in a list of this fragment's own (before cprogressbar.cpp.o)
# gives the same 47 over 1007.
#
# Forms the bytes decide, each measured against the one before it (rows of the score or the object's disassembly):
# - the more-than-one-choice test as a `const bool` read before the choice loop: the target tests `>= 2` in the loop on
#   the post's count loaded before it, and the loop's condition reads the count again. A TQtdEscolha local tested in
#   the loop gives `qtd == 1` computed before the loop (the object), and reading the member in the loop reloads it.
# - the choice counter `unsigned` (`int` gives the same object): a TQtdEscolha counter masks the latch (`i32.and 255`,
#   `i32.le_u`), where the target compares the old count with `i32.lt_u`.
# - `nome`, `ordinal` and `passo` named const strings: `nome + ordinal` allocates (operator+ of two lvalues), push_back
#   copies (the target's `__init_copy_ctor_external`, 138, on the long path), `" - " + ordinal` inserts at the front,
#   and the ternary's "" stores two bytes, as the target does.
# - the update as two ifs, `if (atual && escolha == escolhaAtual) atingido = true;` and `if (!atingido) ++passoAtual;`:
#   the target's branchless or and add; `atingido = atingido || (...)` keeps a branch.
# - `if (passos.size() < 2) return;`: the target's `i32.ge_u` with 2 (binaryen's inversion of the branch, a reading);
#   `if (passos.size() >= 2)` around the bar gives `i32.gt_u` with 1.
# - the bar's rect `api::SRect(2, 2, areaTela.right - 2, 30)` over `areaTela(0, 0, GetWidth() - 1, GetHeight() - 1)`:
#   the normalizing constructor gives the target's max(w - 1, 0) and min/max of 2 (GetHeight's result dropped); the
#   rect written in place gives the same object.
# - in the constructor (unit 41's): the value-initialized base and `std::min<uedword>(m_passos.size(), passo)`, whose
#   other operand order gives 303 over 1033 rows.
# - vota::DesenhaDescricaoModo (4620, in unit 165's cpreshowformvota.cpp) a member of CPreShowFormVota, so PreShow
#   passes it `this`: 297 over 1028 rows with it a free function, 49 over 1008 as the member (the rest of this body
#   unchanged). Binaryen's dead-argument elimination drops the argument, so 4620 keeps its type and its match (6 over
#   109 rows, as before), and so does 7707, its other caller (3 over 28); step 9 renamed 4620's match line to the
#   member's symbol. cpreshowformvota.h says why it is a member; the forms that pass `this` otherwise are not measured.
# - the current post held as a comum::CCargos::TCargoEleicao (`cargoEleicaoAtual`), its fields assigned in the
#   `if (!fim)` and compared one by one: 49 over 1008 rows with the two ids as scalars, 47 over 1007 so (the cargo
#   compare's operands: the target loads the post's cargo first, then compares the current one). clang orders that
#   compare in its IR, and binaryen keeps clang's order: optimize-instructions moves a local.get right of a load and
#   then sorts it left by node kind, so each of the six runs on 13550 flips it (13550 printed after each pass, build
#   below). With a scalar `TCargoID cargoAtual` clang widens its phi to i32 (`icmp eq i32 %phi, %zext`: the phi first);
#   the pair's field stays i8 and the compare keeps the source's order (`icmp eq i8 %load, %field`, the IR of this
#   object). `item == cargoEleicaoAtual`, the pair's operator==, gives another object (the pair form measured below);
#   the pair default-constructed or built from (0, 0) gives this one.
#
# Why `this` decides the locals (a reading, with what was measured): in the target, 13550's parameter 0's local, `this`,
# holds GetInst's range result, the steps vector's end pointer (with its two zero sets on the loop's guard) and the
# destroy loop's iterator, the three values clang gives one local in the link's r02 text. Binaryen's -Oz optimizes
# 13550 three times (its function passes before inlining, then once per inlining-optimizing iteration that inlines into
# it). With `this` unused, the first round's coalesce-locals takes the reverse order, where fim (a copy carrier, with
# few uses) takes the parameter's index before the end, so the end gets an index of its own and rse drops its zero
# sets; from then on the end is live at the function's entry, which interferes with the parameters, and the later
# rounds give `this`'s index to the choice counter. Measured with a build of the image's binaryen
# (version_130-4-gb9c72894) that prints coalesce-locals' inputs and choices, whose `wasm-opt -Oz` on r02-stripped.wasm
# gives r05.wasm byte for byte: on the r02 text with clang's local of those three values renamed to local 0 and the
# cargo compare's operands swapped, the replay gives 47 over 1007 rows, every one an operand, before this source did;
# the r02 text as clang wrote it from the scalar ids gives 297 over 1028.
#
# Forms tried for the locals with 4620 free (8f35addb), none the target's: the current post compared as a pair,
# `item == comum::CCargos::TCargoEleicao(eleicaoAtual, cargoAtual)` (or a pair variable), 99 over 1019 rows (same 920,
# replaced 79 [75 operand-only], inserted 12, deleted 8), its locals near the target's, but its test branchless (an
# `i32.and` of the two compares) and its post id masked (`& 255`) before the loop, where the target branches and
# compares it unmasked: rows the source decides, so not the original's form. The current-post test written in the update
# (250 over 1036, the test then evaluated per choice), `atingido` from false with `!fim && !atingido` (313 over 1022),
# the test's flag after `variasEscolhas` (314 over 1028), `!atingido &&` leading the update (311 over 1030),
# `int atingido` (323 over 1036), the strings in a block of their own (309 over 1037 and 1036, with the update inside it
# and after it), the update and the increment ahead of the strings (301 over 1031), a `contando` flag (333 over 1034);
# the ids uninitialized and `atingido` declared right after `fim` give other objects and the same 297 over 1028; these
# give this body's own object: an `int` choice counter, a `size_t` passoAtual, an `unsigned` or `int` post id, an
# `unsigned` escolhaAtual, structured bindings, g_escolhaAtual read after the counters, `passoAtual` declared first, the
# screen's rect written in place. Without strict aliasing (UENUX2_NOTBAA_FILES on the make line, nothing committed) the
# score is the same, 297 over 1028. The object's place decides nothing measured: 297 over 1028 at fragment 391's own
# place and in unit 150's list; before the min order, 303 over 1033 at fragment 391's place and in unit 41's list after
# cstepsprogressbar.cpp.o. A reading of binaryen, measured on copies (the link's `wasm-opt -Oz` written out as its pass
# list gives r05.wasm byte for byte): its first round on PreShow alone (the function extracted, callees as imports)
# gives this body's end pointer a local of its own and `rse` drops its zero sets; forms whose first round keeps them
# (the test in the update, `atingido` from false, `variasEscolhas` first) still differ from the target in the whole
# link.
#
# Chosen: the file's name, the locals' names and types where the bytes leave them open (`uedword passoAtual`, `unsigned
# escolha`, `cargoEleicaoAtual`, the pair value-initialized), the steps' colours as plain TColor casts.
#
# 5504's name: `api::CStepsProgressBar::Draw` fills slot 2 of that class's vtable in both links (ledger/vtables.json:
# [3665, 10973, 5504, ...]), and step 8 named it so (`evidence:vtable`) until 13550 anchored (`srcloc-anchor`, on the
# constructor's record it holds): 13550's call vote now names it (`evidence:call by:13550`), a name voted by the match
# alone, so the scan reads 13550 `unresolved self-voted` on its call of 5504 (docs/reference/splat.md, "No circular
# evidence"). The `vtable-slot` hand line for 5504 in splat/symbol_addrs.txt keeps the slot's evidence, which no match
# gives; without it 13550 leaves `match`. 5504's own body is written and differs (unit 41's fragment), and the line goes
# once 5504 matches.
# No roots: 13550 is reached through its vtable, which the CriaTela* screens' vptr stores keep (unit 378); this object
# emits the vtable now, and unit 378's pending file (the trap) went. Stand-ins this unit made idle went, call by call:
# unit 41's roots file (DestroiBarrasPassos, 3665's second caller), unit 165's ModoProgressBar (4620), unit 88's
# MesmoCargo (1938) and NomesNeutros (1547) and one call each of SomaEleicoes (2835, for 11209 now) and Ordinais (2258,
# for 12811 now), and unit 110's ConsultaTodos call of GetCargo (861), which stood for 13550 alone. The constructor's
# throw takes EUE_GUI_STEPSPROGRESSBAR_SEM_SEGMENTOS (5014) in api/gui/eueguierror.h; of the 632 objects the edited
# headers (that enum, cstepsprogressbar.h, cpreshowformvota.h) recompile, only the two roots files this unit edits
# changed (md5 against 8f35addb's objects). Making 4620 a member (cpreshowformvota.h again) changes
# cpreshowformvota.cpp.o and this object only: ctelasvota.cpp.o and unit 102's roots object, the header's other
# includers, compiled against the header before and after are byte-identical, and so is every other object of the link
# line (md5 of all 1102 before and after rebuilding the tree with the new header).
# cpreshowprogressbar.cpp reaches Boost through cconfiguracaoeleicao.h.
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/comum/cpreshowprogressbar.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
