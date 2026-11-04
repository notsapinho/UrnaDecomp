# uenux2 vota operador comum: the voter's photo on the operator's LCD (app/vota/operador/comum/fotoeleitor.{h,cpp} and
# infofoto.{h,cpp}): vota::MostraFotoIndisponivel (target fn 3617, matched) and vota::ApresentaFotoEleitor (3616,
# written, `no-candidate`: below), with MostraEleitorSemBiometria, ValidaFotoEleitor and LeInfoFoto, which 3616 holds
# inlined. Paths relative to src/uenux2.
#
# Evidence:
# - 3616 has no record of its own; it holds comum::md::CBiometriaEleitor::GetFoto inlined (record cbiometriaeleitor.cpp:115,
#   unit 91's), loads texts no other target function loads, and its callers are the StartState slots of
#   vota::CNomeEleitor, IConfirmaJustificativa and IEleitorImpedidoVotar (10501, 10589, 10625). It takes no `this`. 3617,
#   its one callee with three call sites, shows ":/resource/images/biometria/fotoIndisponivel.jpg".
# - The place: use band 3 holds 3617 and 3616 between cinformacaothreadoperador.cpp's 3623 to 3619 and
#   cregistradigitaloperador.cpp's 3614 (ledger/ordinals.tsv), 3617 above 3616, so 3617 is defined first. Not in
#   cinformacaothreadoperador.cpp: 3616 calls SetEleitorSemFoto (5413) and SetFotoNaoApresentada (1904), which clang would
#   inline there. A file of vota under app/vota/operador/comum/ (how-to step 3, rule 5); its name and this unit's list,
#   after the units whose objects link there in the target, are chosen.
# - Behind frames of their own in 3616, each inlined by binaryen into its one caller: MostraEleitorSemBiometria (32
#   bytes), ValidaFotoEleitor (32), GetFoto (16, unit 91's file), comum::CInfoMTLCD::MostraImagem over the bytes (16,
#   unit 153's file) and the CLogVota members of its logs (16, and 384 for each std::format: app/vota/log/clogvota.cpp).
#   clang keeps each of this TU's out of line at uenux2's flags: MostraFotoIndisponivel and MostraEleitorSemBiometria
#   cost 315, ValidaFotoEleitor 510, LeInfoFoto 1035, against 250 (-Rpass=inline).
# - 3617 and MostraEleitorSemBiometria are one expression each, CInfoMTLCD::GetInst's call first in the code and the
#   image and its string destroyed after MostraImagem, in that order (a CFixedImage temporary over a string one).
# - ValidaFotoEleitor: no SOF marker (any of the three words still -1) is CApresentacaoFotoEleitor::ErroFormato and the
#   load error log, a width outside 120 to 240 or a height outside 160 to 320 ErroResolucao and its log, other than 8
#   bits per pixel ErroProfundidadeCores and its log; the tests' ranges are the target's compares. LeInfoFoto's walk:
#   infofoto.h. Its cases are written in the target's block order (COM, APP1, the segments skipped, SOFn, the rest):
#   with SOFn first, 3616 read 341 over 1552 rows (64 inserted, 72 deleted), in this order 274 over 1521, and with
#   LeInfoFoto in a TU of its own 243 over 1516 (pnpm wasm score; infofoto.h has the reading).
# - The success path: the photo's bytes copied, a CFoto of format 1 (EFI_JPEG) over the copy, then the LCD through
#   CInfoMTLCD::MostraImagem over the copy, IInformacaoThreadOperador's SetFotoApresentada (slot 28, called on GetInst's
#   result: a free vota:: function over it gives the same code once binaryen inlines it) and the log.
#
# Written, not matched: ApresentaFotoEleitor, 243 over 1516 rows (28 inserted, 33 deleted), all of them in LeInfoFoto's
# walk: our std::vector::at throw block sits inside the walk's loop, the target's after it, with the stores of the five
# words split differently around it. Not explained. Its name holds through a callers+content hand line in
# splat/symbol_addrs.txt (the record and texts only 3616 loads), which 10501, 10589 and 10625 match through.
#
# Chosen: every name in these files (functions, struct, members), the files and header paths, the free functions'
# namespace, the struct's zero starts of its last two words, the case labels' spelling.
FOTOELEITOR_SRCS := src/app/vota/operador/comum/fotoeleitor.cpp src/app/vota/operador/comum/infofoto.cpp
UENUX2_SRCS += $(FOTOELEITOR_SRCS)
