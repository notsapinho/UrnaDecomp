# uenux2 comum::asn::CConversorOrigemConfiguracao::DoConverte and DoDesconverte (target fns 11367 and 11366, vtable
# @1570240 slots 2 and 3) in src/app/comum/dados/asn/processoeleitoral/cconversororigemconfiguracao.cpp, the record of
# DoDesconverte (line 38) names the file. DoDesconverte matches through binaryen's body 6030, which it forms with
# CConversorTipoIdentificadorEleitor::DoDesconverte (fn 11356, unit 98): neither has that shape alone. DoConverte has no
# record, and it is defined above DoDesconverte: that way our indices run as the target's do (docs/reference/splat.md
# "Reviewing a match"), and it is the order the records of CConversorTipoIdentificadorEleitor show (lines 32 and 51).
# The other order gives the same bytes; DoConverte's line is a choice.
# With it: the comum::asn::IConversorASN template (src/app/comum/asn/iconversorasn.h, the base
# its RTTI names; only the class and its virtual pair, the throwing defaults at lines 89/98 not recovered) and the
# comum::md::EOrigemConfiguracao enum it converts (src/app/comum/dados/md/processoeleitoral/eorigemconfiguracao.h; no
# record names that header, the directory follows the md family the converter's directory mirrors).
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
ORIGEMCONFIGURACAO_SRCS := src/app/comum/dados/asn/processoeleitoral/cconversororigemconfiguracao.cpp
UENUX2_SRCS += $(ORIGEMCONFIGURACAO_SRCS)
# No roots: the target reaches DoConverte and DoDesconverte only through the converter's vtable (@1570240), and fn
# 11363 (cconversorprocessoeleitoral.cpp, unit 140), which stores its vptr, is in the link, so the roots file and its
# sink went.
