# uenux2 the "Mais informações" screen of the vote's menu: vota::CMaisInformacoes::StartState (target fn 11897,
# matched), vota::CTelasVota::CriaTelaMaisInformacoes (fn 6599, written, differs in binaryen's local numbering only) and
# vota::CItemVisualizarCandidatosVota::Slot2 (fn 12244, matched), with the functions 6599 holds inlined:
# vota::CMenuMaisInformacoesVota's constructor and, through it, comum::CMenuBase's and the vota and comum menu items'.
# Each of them belongs in a landed unit's file, so this fragment compiles no source (src/units/README.md "Landing a
# unit") and holds the one stand-in the chain needs; each unit's fragment has its paragraph:
# - 11897: unit 104's cmaisinformacoes.cpp (104-uenux2-app-vota-estados.mk), its trap gone from that unit's pending file;
# - 6599: unit 110's ctelasvota.cpp, declared in ctelasvota.h; the menu's constructor: the new
#   app/vota/eleitor/comum/cmenumaisinformacoesvota.cpp, compiled in unit 110's list after ctelasvota.cpp and
#   citensmenuvota.cpp (110-uenux2-singletons.mk says where each sits, why, and what 6599 differs in);
# - the vota items' constructors, the menu's class and 12244: unit 102's citensmenuvota.{h,cpp}
#   (102-uenux2-control-blocks.mk), whose pending file went with 12244, its one member; the .cpp is compiled in unit
#   110's list now;
# - the comum items' constructors: unit 156's citemmenu.cpp, declared in citemmenu.h (156-uenux2-fimvotacao-bu.mk);
# - CMenuBase's constructor: unit 59's cmenubase.cpp (59-uenux2-cmenubase.mk).
# The stand-ins whose every target caller this brings into the link went: unit 59's roots file (the vtable sink for the
# constructor 6599 holds, and AdicionaItem's caller, 6599) and, in unit 102's roots, the five item blocks and the five
# item vtables (stored by the menu's constructor). The stand-ins that also stand for callers still not written stay
# (units 31, 89, 98, 111, 120 and 165 name 6599 or 12244 among their callers).
# 354-uenux2-cmaisinformacoes-roots.cpp: 6599's other target caller, 7787, is not written, and a function with one call
# in the link is inlined by binaryen into it (docs/reference/facts/tool-traps.md X1), so its stand-in gives 6599 a
# second call site. Compiled as app code; it declares what it calls through an __asm__ label and includes no header.
$(ROOT)/$(APP)/354-uenux2-cmaisinformacoes-roots.o: $(ROOT)/src/units/354-uenux2-cmaisinformacoes-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/354-uenux2-cmaisinformacoes.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/354-uenux2-cmaisinformacoes-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/354-uenux2-cmaisinformacoes-roots.o
