# uenux2 comum::CGeradorRelVersaoPacoteDados, the packages' versions report, in
# src/app/comum/relatorios/cgeradorrelversaopacotedados.{h,cpp}, with the two out-of-line helpers its user and its slot 4
# hold inlined: comum::AdicionaParametro (src/app/comum/relatorios/adicionaparametro.{h,cpp}) and
# vota::LeDadosDisponiveisCarga (src/app/vota/eleitor/iniciovotacao/auxiliares/ledadosdisponiveiscarga.{h,cpp}). Paths
# relative to src/uenux2. Their one user is vota::CImpressaoVersaoPacotes::StartState (target fn 11905), unit 176's,
# written with them (src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk has its notes).
#
# Matched: the D2 (target fn 3691) and the D0 (11224), named by the census's pairs (pair-addr), and Imprime (5592, slot
# 2), named by 11905's call. The constructor has no target index: 11905 holds it inlined. Scores (pnpm wasm score
# against build/out/wasm-map/vota_web/names.tsv, before step 8): 3691 3 over 82 rows, 11224 2 over 7, 5592 1 over 23,
# all operand-only.
#
# Written, not matched: ImprimeVersoesPacotes (11222, slot 4), named by its vtable slot, 26 over 537 rows, all
# operand-only (calls, data and one table slot). It is `unresolved` on two things it waits for, which pnpm wasm
# splat-remap against this link lists: `+01c4 i32.const 1061: an address of ours: string tail occurs 4098 times`, the
# end of its "{}{}{}", which the target holds as the tail of "{:05}{:04}{:04}{}{}{}{}" (string 1071, loaded by
# vota::CGeraBU::StartState, fn 12110, not written), and `+0320 call 3607: ...GetResumoHashVersoesPacotes... has no
# target function`, the call of fn 3703 (below). In a scratch whole link (tools/round/try-tu.sh with a TU that returns
# that literal) and with a scratch copy of the symbol file that names 3703 our GetResumoHashVersoesPacotes, splat-remap
# prints `target 11222: IDENTICAL`; with the literal and no such name, only the call is left. So 11222 waits for 12110
# (the literal) and for a name for 3703.
# - comum::md::estadoaplicacao::CEstadoGeral::GetResumoHashVersoesPacotes (3703) is written in unit 215's
#   cestadogeral.cpp (its fragment and cestadogeral.h have the notes): it differs, 133 over 556 rows, in the code it
#   holds inlined from ecourna's base64.cpp (unit 00's note), so no srcloc-anchor names it (the opcodes differ), and its
#   one caller in our link, 11222, is named by its vtable slot, which casts no vote. A callers+content hand line for it
#   would carry 11222's call and nothing else, and 11222 waits for the literal as well, so there is none.
#
# Pending (287-uenux2-cgeradorrelversaopacotedados-pending.cpp says what each waits for): ImprimeTituloJE (11223, slot
# 3) and ImprimeRodape (5596, slot 5); the slots of ImprimeTituloJE's lambda's std::function (vtable @1576316: 11221,
# 11219, 2881, 11218, 11217) come with it.
#
# Evidence beyond the class header's:
# - AdicionaParametro is out of line in another TU than ImprimeVersoesPacotes. 11222 holds it behind a 32-byte frame of
#   its own, and keeps the destroy check of its "Dados:" temporary after it. Defined in cgeradorrelversaopacotedados.cpp
#   (external: clang does not inline it, `too costly to inline (cost=360, threshold=250)` from try-tu.sh --symbols
#   --flags '-Rpass=inline -Rpass-missed=inline'), 11222 scored 96 over 540 rows, 3 inserted and 15 deleted: the check
#   is gone (a reading: clang drops it when it can read the callee); in a TU of its own, 26 over 537, operand-only. It takes the
#   builder, not `this`: written as a member of the class, its body would be comum::CGeradorRelPU::AdicionaParametro's
#   (fn 677, unit 183) byte for byte, which binaryen's merge of identical functions would give 11222 to call, a reading
#   (not linked). Its body is 677's, over the builder passed in.
# - LeDadosDisponiveisCarga is out of line in another TU than 11905. 11905 holds it behind a 64-byte frame of its own
#   (the converter's vptr stored at +60, the entity at +8). In cimpressaoversaopacotes.cpp clang inlines it into
#   StartState (cost=95, threshold=375, the same remarks); in a TU of its own 11905 scores 183 over 2146 rows, all
#   operand-only (calls, data, the packed format strings and two table slots). That object compiled with
#   -fno-strict-aliasing gives a byte-identical link (shasum -a 256 of build/out/wasm/vota_web/vota_web_wasm.wasm,
#   156fc597... both ways), so the bytes say nothing of its directory's flags.
#
# Chosen, no evidence names them: the slots' names but ImprimeTituloJE (cgeradorrelversaopacotedados.h), the two
# helpers' names, their being free functions in the namespace of their caller's class (docs/reference/facts/reading.md
# R10), their files' paths and names, and the order of the three sources below (not measured: the first order linked
# gives the scores above). The class's directory is the data's: its vtable and typeinfo (@1576276, 1576308) lie in
# app/comum/relatorios/'s classes in name order (CCalculaCV, CGeradorBU, CGeradorBUQRCode and -Vota, then two
# MontaCabecalho lambdas' typeinfos, 1576100 and 1576180, before it; CImprimirExtratoCarga's 1576380, then
# cpartecandidatos.cpp's CParte* classes from 1576500, CRelatorioTesteImpressora and CSigVerifier after it), where
# cgeradorrelversaopacotedados.cpp sorts; in use band 1 its functions 11224 to 11217 lie between the static
# destructors 11225/11226 and CImprimirExtratoCarga's 11216, ahead of cpartecandidatos.cpp's 11215 to 11210. The
# src/uenux2/unplaced.cpp label `uenux2/src/app/comum/dados/cgeradorrelversaopacotedados.cpp` over 3691, 5592 and 11222
# is a class-convention guess (docs/reference/facts/placing.md P3), which the data overrule (P4). The file name is the
# class-name convention. LeDadosDisponiveisCarga's file sits beside its caller, a choice: the data put the copies of the
# templates it instantiates (the records of CFileASN::ReadFromFile<DadosDisponiveisCarga> and IConversorASN's
# Desconverte, 1562856 to 1562972) right after cconversorcabecalhopacote.cpp's data, a TU not identified (a reading).
CGERADORRELVERSAOPACOTEDADOS_SRCS := src/app/vota/eleitor/iniciovotacao/auxiliares/ledadosdisponiveiscarga.cpp \
    src/app/comum/relatorios/cgeradorrelversaopacotedados.cpp src/app/comum/relatorios/adicionaparametro.cpp
UENUX2_SRCS += $(CGERADORRELVERSAOPACOTEDADOS_SRCS)
# The members not reconstructed: 287-uenux2-cgeradorrelversaopacotedados-pending.cpp gives the vtable trapping bodies,
# compiled with the class's directory's flags (app/comum/relatorios/ builds without strict aliasing)
$(ROOT)/$(APP)/287-uenux2-cgeradorrelversaopacotedados-pending.o: $(ROOT)/src/units/287-uenux2-cgeradorrelversaopacotedados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/287-uenux2-cgeradorrelversaopacotedados.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(call uenux2_cxxflags,src/app/comum/relatorios/cgeradorrelversaopacotedados.cpp) -c src/units/287-uenux2-cgeradorrelversaopacotedados-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/287-uenux2-cgeradorrelversaopacotedados-pending.o
