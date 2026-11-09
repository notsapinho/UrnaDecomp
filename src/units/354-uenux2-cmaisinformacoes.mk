# uenux2 the "Mais informações" screen of the vote's menu: vota::CMaisInformacoes::StartState (target fn 11897,
# matched), vota::CTelasVota::CriaTelaMaisInformacoes (fn 6599, written, differs in binaryen's local numbering only) and
# vota::CItemVisualizarCandidatosVota::Slot2 (fn 12244, matched), with the functions 6599 holds inlined:
# vota::CMenuMaisInformacoesVota's constructor and, through it, comum::CMenuBase's and the vota and comum menu items'.
# Each of them belongs in a landed unit's file, so this fragment compiles no source (src/units/README.md "Landing a
# unit") and holds the one stand-in the chain needs; each unit's fragment has its paragraph:
# - 11897: unit 104's cmaisinformacoes.cpp (104-uenux2-app-vota-estados.mk), its trap gone from that unit's pending file;
# - 6599: unit 110's ctelasvota.cpp, declared in ctelasvota.h; the menu's constructor: the new
#   app/vota/eleitor/comum/cmenumaisinformacoesvota.cpp, compiled in unit 110's list after ctelasvota.cpp
#   (110-uenux2-singletons.mk says where each file sits, why, and what 6599 differs in);
# - the vota items' constructors, the menu's class and 12244: unit 102's citensmenuvota.{h,cpp}
#   (102-uenux2-control-blocks.mk), whose pending file went with 12244, its one member; the .cpp stays in unit 102's
#   list;
# - the comum items' constructors: unit 156's citemmenu.cpp, declared in citemmenu.h (156-uenux2-fimvotacao-bu.mk);
# - CMenuBase's constructor: unit 59's cmenubase.cpp (59-uenux2-cmenubase.mk).
# The stand-ins whose every target caller this brings into the link went: unit 59's roots file (the vtable sink for the
# constructor 6599 holds, and AdicionaItem's caller, 6599) and, in unit 102's roots, the five item blocks and the five
# item vtables (stored by the menu's constructor). The stand-ins that also stand for callers still not written stay
# (units 31, 89, 98, 111 and 165 name 6599 or 12244 among their callers).
# No roots: 354-uenux2-cmaisinformacoes-roots.cpp stood for 6599's other target caller, 7787, so that binaryen kept
# 6599 out of line (docs/reference/facts/tool-traps.md X1); unit 443's constructor makes that call since, and the file
# went: the link without it moved no row (steps 7 to 9: 0 matches added, 0 renamed, no verdict changed).
