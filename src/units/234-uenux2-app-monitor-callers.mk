# Unit 234: no source of its own. Its roots file stood for the unwritten target callers of the functions this unit
# adds to landed units' sources (src/units/README.md "Landing a unit" item 2), each of which that unit's fragment
# describes in a paragraph of its own, with its evidence, its choices and its score; every stand-in went once its
# callers were in the link, and the roots file with the last:
# - unit 35, app/comum/iinterfaceinit.cpp: comum::FormataTamanho (target fn 1947, a chosen name), a size formatter,
#   whose stand-in went once its three target callers were in the link (3268, 10226 and 5896, unit 35's);
# - unit 04, ecourna's app/dados/asn/datahoraasn.cpp: ecourna::app::dados::asn::FormataHora (fn 2686, a chosen name
#   and file), the time of day of a boost::posix_time::ptime, whose stand-in went once its one target caller,
#   vota::CImpressaoPU::StartState (11902, unit 176's), was in the link;
# - unit 165, app/vota/cexecucaovotacooperativa.cpp: vota::CExecucaoVotaCooperativa::ProcessaEntradaEleitor (fn 7823,
#   slot 7), which needs no stand-in: the class's vtable is in the link.
# Two more are described here:
# - vota::CLogVota::LogaQuantidade (fn 3268, a chosen name), in app/vota/log/clogvota.cpp (unit 119's file; the CLogVota
#   members' notes sit in the fragments that add them, as clogvota.h says);
# - the hand line of splat/symbol_addrs.txt that named fn 4349, CThreadEleitor::ProcessaEventos (unit 116's), for 7823,
#   until a generated line caught up with it (below).
# All four match.
#
# LogaQuantidade (3268). Evidence: its one target caller, vota::CThreadMonitor::Run (10226, unit 116's; the roots'
# Quantidades stood for it until it was in the link, and went), calls
# it three times (ledger/callgraph.tsv), each time on vota::CLogVota::GetInst()'s result (fn 184) and a temporary of its
# own frame that holds a std::string at +0 ("memoria total", "memoria livre" and "memoria usada", with accents, 13 bytes
# each) and a 64-bit word at +16 (fn 5463's "MemTotal" and "MemFree" values widened and shifted left by 10, and their
# difference). 3268 calls comum::FormataTamanho (1947) on the low word at +16 first, then std::format of "Quantidade de
# {} [{}]" (234429) over the name and that result (argument types 429: 13 and 13) and comum::IEventosLog::loga (233)
# on its first argument. Its place: in band 3 it lies right after clogvota.cpp's 3279 and 3272, the second the file's
# last member (LogaVotoCargoSemCandidatoPorSuspensao), so it is written after it, at the end of the file
# (build/out/wasm-map/vota_web/names.tsv after the link: 3279 ld 2726, 3272 ld 2735, 3268 ld 2736); the band and the
# GetInst-result call are the shape of this class's out-of-line Loga members (clogvota.h). pnpm wasm score before step
# 8: 12 over 246 rows, all operand-only; the scan matched it by content. Chosen: the name, from its message; its being
# a member of CLogVota, after the class's other Loga members (a free function taking a comum::IEventosLog& gives the
# same object, the member's and that function's bodies compared with their names masked after try-tu.sh --symbols);
# the parameter's type, std::pair<std::string, uint64_t> (the bytes give a string at +0 and a 64-bit word at +16).
#
# The hand line for 4349 (callers+content, below the marker), which went once CThreadEleitor's Run (7061, unit 116)
# matched: step 8 names 4349 by Run's call since (`evidence:call by:7061`; Run is named by its records), and with that
# hand line alone out of a copy of the symbol file, two scans beside a control moved no row and splat-build on the
# copies gave the target's sha256, so it went. Before that 4349 had no generated name: its two target callers, Run (slot
# 2, then a trap) and 7823 (slot 7), are named by vtable, which casts no vote (docs/reference/splat.md section 2).
# Without the line, step 9 read 7823 `unresolved`,
# `ours +0x1d call 3692: _ZN4vota14CThreadEleitor15ProcessaEventosEv has no target function`, with every other row as
# before; with it, 7823 matches and 4349's row goes from no-candidate to unresolved, on the debug wrapper 2072 its body
# calls (unit 116's fragment). The line leads with 4349's own body, read without the match: it opens with the two
# tests 7823 makes, holds ProcessarMensagens and ProcessarEntrada under two stack frames, the second with the record at
# 1534648 (cthreadeleitor.cpp:134) that no other target function loads, and ours scores 35 over 632 rows against it
# (33 operand-only and 2 deleted, the target's `i32.const 1; i32.eq` of one test of +8).
