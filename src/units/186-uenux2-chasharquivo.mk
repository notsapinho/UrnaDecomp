# uenux2 api::hash::CHashArquivo's out-of-line members in src/api/hash/chasharquivo.cpp, the file their records name:
# the constructor (target fn 3600) and ValidaObjeto (5364, records chasharquivo.cpp:26 and :30), with the
# CBaseError<api::EUeHashError, SErrorLimits{5100, 5150}> constructor its two throws instantiate (2723, a thunk into
# binaryen's 710, named by the vptr it passes) and the new header api/hash/euehasherror.h. The class header,
# api/hash/chasharquivo.h, is unit 46's, whose DoDesconverte (10269) is the constructor's one caller written.
# The roots file also holds two template instances the target keeps from uenux2 objects not written, each matched from
# the roots object as code a landed header defines (src/units/README.md "Companion files"):
# - std::vector<comum::md::CComparecimentoMesario>::__emplace_back_slow_path (5375), which the scan's content pass
#   matches (source `content`: no step-8 name). The target body moves a 52-byte element, a std::string at +0 (zeroed
#   after the move), words at +12 and +16 and 29 bytes from +20 copied as four i64 (+20, +28, +36, +41), the layout
#   app/comum/comparecimentomesario/md/ccomparecimentomesario.h gives CComparecimentoMesario (that header's note says fn
#   5377 holds the same 29-byte copy); its one caller, 11616, copies such an element into a temporary before each of its
#   two calls. That the element is that class is a reading of the layout: the content pass compares bytes, not the type.
# - CBaseError<comum::EUeComumReconhecimentoBiometricoError, SErrorLimits{9000, 9050}>'s constructor (5369, a thunk
#   into 710 named by the vptr it passes), with the new header
#   app/comum/reconhecimentobiometrico/euecomumreconhecimentobiometricoerror.h. Its one caller, 2725 (5103 B, with the
#   records of CControlaArmazenamentoDeImagens' static GerarCaminhosUnicos, LeChavePublica and CifrarWsq), is not
#   written: of the 46 direct callees `pnpm wasm fn` lists for it, 16 had no `func:` line in splat/symbol_addrs.txt
#   before this unit, 5369 among them, and 15 have none after it.
#
# Evidence:
# - 3600 copies its two `const std::string&` into +0 and +12, calls 5364 on `this` and returns `this`; the object
#   (wasm-objdump -d of chasharquivo.cpp.o) already holds that call twice, after each path of the second copy, as the
#   target's body does, so binaryen keeps 5364 out of line with two call sites in one caller.
# - 5364 tests the string at +0, then the one at +12, and throws code 5100 with "CHashArquivo: nome inválido." on line
#   26 and 5101 with "CHashArquivo: hash inválido." on line 30, column 15 each (ledger/source-locations.tsv).
# - 2723's callers are 5364 (twice) and 5360 (not written); the typeinfo of the class whose vptr it passes gives the
#   enum's name, namespace (api) and limits.
# - Measured with `pnpm wasm score` against the links before step 8 named anything: 3600 4 over 56 rows, 5364 14 over
#   64, 2723 2 over 8, 5375 5 over 216, 5369 2 over 8, every row operand-only; step 9 matched all five.
#
# Chosen, no evidence names them: the enumerators' names in both headers, both headers' paths (beside the classes that
# throw them), the constructor's lines and parameter names, and the constructor above ValidaObjeto (they are in
# different use bands, 3600 in uses 3, 5364 in uses 2, so no band gives their order); the gap between them stands for
# lines whose content is unknown.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CHASHARQUIVO_SRCS := src/api/hash/chasharquivo.cpp
UENUX2_SRCS += $(CHASHARQUIVO_SRCS)
# callers not reconstructed: 186-uenux2-chasharquivo-roots.cpp stands for them (its header says which), compiled at the
# tree's flags since it instantiates template code the target keeps from uenux2 objects
$(ROOT)/$(APP)/186-uenux2-chasharquivo-roots.o: $(ROOT)/src/units/186-uenux2-chasharquivo-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/186-uenux2-chasharquivo.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/186-uenux2-chasharquivo-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/186-uenux2-chasharquivo-roots.o
