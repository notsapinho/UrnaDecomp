# uenux2 comum dados loaders: the stand-ins of comum members whose files landed units compile, in
# 216-uenux2-app-comum-dados-loaders-roots.cpp. No source of its own: each member is written in its file, and that file's
# fragment has a paragraph on it (src/units/README.md "Landing a unit" item 2): celeitores.cpp and chv.cpp (unit 110:
# 2822, 2821, 1935, 3754), cjustificador.cpp (unit 113: 1391, 2809, 2810, 11475, 11476, 11477) and cintegridadereferencial.cpp
# (unit 98: 5746, 5747). The roots declare their callees through asm labels and include no header, so they emit no TSE
# code: no match comes from this object.
#
# The stand-ins, each for the target callers its comment names, none of them written; each goes when they are in the
# link:
# - Justificadores: two calls of CJustificador::GetInst (1391) for 5971, 6734, 11616, 12105 (11835, unit 138's,
#   10587, unit 152's, 10797, unit 119's, and 10590, unit 283's, are in the link);
# - HabilitadosSemBiometria: two calls of CEleitores::QuantidadeHabilitacaoSemBiometria (2822) for 11242, 12098 and
#   12110 (10699, unit 277's, is in the link);
# - HabilitadosPorTipo: one call each of CEleitores::QuantidadeHabilitacaoBiometrica (2821) and
#   QuantidadeHabilitacaoBiografica (1935) for 11242, 12098, 12110 and, of 1935, 12105 (their other callers, 10701
#   and 10700, unit 277's, are in the link);
# - FotosCandidatura and CargosCandidatura: two calls each of VerificaFotoCandidatura (5746) and VerificaCargoCandidatura
#   (5747) for their two calls each in fn 7787's integrity tests;
# - ConstroiHV: two calls of CHV's constructor (3754) for its three in fn 7787 (CHV::CreateInst, inlined there);
# - CJustificadorDadoTitulo::Text (11475) has its address taken: the target reaches it only by table slot 2949.
#
# Not written: two libc++ instances whose only target callers are TSE functions not written, which bring them: 5787 and
# 5788, std::insert_iterator<std::set<uebyte>>'s assignment and a lower-bound search over a std::set<uebyte>, the
# parts of a std::set_intersection in fn 7787's code (beside its calls of 3713, 5654 and 3778). Two more match since
# their callers landed: 5784, std::vector<md::CRespostaConsulta>'s move assignment, which unit 88's
# CConfiguracaoEleicao::GetCargos brings with its callers 783 and 5789, and 2807, a std::vector copy of 36-byte
# elements, with its caller 11423 (unit 245).
$(ROOT)/$(APP)/216-uenux2-app-comum-dados-loaders-roots.o: $(ROOT)/src/units/216-uenux2-app-comum-dados-loaders-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/216-uenux2-app-comum-dados-loaders.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/216-uenux2-app-comum-dados-loaders-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/216-uenux2-app-comum-dados-loaders-roots.o
