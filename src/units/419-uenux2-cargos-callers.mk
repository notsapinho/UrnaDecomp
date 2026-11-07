# Unit 419: no source of its own. Its roots file stands for the unwritten target caller, fn 7787, of the two comum
# functions this unit adds to landed units' sources (src/units/README.md "Landing a unit" item 2); each of those units'
# fragments describes its member in a paragraph of its own, with the evidence, the choices and the scores:
# - unit 13, app/comum/dados/crdvvota.cpp: comum::CargosPorEleicao (target fn 5735);
# - unit 88, app/comum/dados/cconfiguracaoeleicao.cpp: comum::CConfiguracaoEleicao::GetTodosCargos (target fn 5790).
# Both match. 7787 is the one target caller of each and calls each twice (`call 5735` and `call 5790` each count 2 in
# build/out/splat/pieces/asm/comum/7787.wat), neither is in the target's table or exports, and nothing else in our link
# calls them, so each stand-in calls its callee twice. The second calls are needed: in a link of the roots compiled with
# one call of each (docs/reference/facts/workflow.md W13, "One variant object in the whole link"), neither
# _ZN5comum16CargosPorEleicaoEv nor _ZNK5comum20CConfiguracaoEleicao14GetTodosCargosEv is in the map's names.tsv (15400
# functions named against the plain link's 15402, at 220a19a0): binaryen inlines each into its stand-in. The calls of
# GetTodosCargos pass GetInst()'s result, as 7787's do. With the two in the link, other stand-ins lost calls: unit 88's
# IDsEleicoes (5791 for 5735) went, its XorCargos calls 2257 once (for 7787; the other call stood for 5790), and unit
# 232's CargosEleicao calls 3775 once (for 7787; the other call stood for 5735); steps 6 to 10 on the link with all of
# it moved no row but 5735 and 5790 into match. The roots compile at APP_CXXFLAGS and declare what they call through asm
# labels: they emit no TSE code, so no match rests on their flags. The census pairs no target function with a stand-in
# (how-to step 7's command lists the same 34 pairs as at bed17f80). Each stand-in goes when 7787 is in the link.
$(ROOT)/$(APP)/419-uenux2-cargos-callers-roots.o: $(ROOT)/src/units/419-uenux2-cargos-callers-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/419-uenux2-cargos-callers.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/419-uenux2-cargos-callers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/419-uenux2-cargos-callers-roots.o
