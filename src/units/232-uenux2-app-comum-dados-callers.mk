# uenux2 comum dados callers: the stand-ins of comum members whose files landed units compile, in
# 232-uenux2-app-comum-dados-callers-roots.cpp. No source of its own: each member is written in its file, and that file's
# fragment has a paragraph on it (src/units/README.md "Landing a unit" item 2): md/processoeleitoral/ccargo.cpp and
# cconfiguracaoeleicao.cpp (unit 88: 1923, 3775 and the copy constructor of std::vector<md::CCargo>, 2289) and
# md/candidatura/ccandidatura.cpp (unit 89: std::vector<md::CDadosCandidato>::__init_with_size, 2870). The roots declare
# their callees through asm labels and include no header, so they emit no TSE code: no match comes from this object.
#
# The stand-ins, each for the target callers its comment names, none of them written; each goes when they are in the
# link:
# - DetalhesConsulta: two calls of md::CCargo::GetDetalheConsulta (1923) for 3074, 3819, 5604, 6999, 7787 and 11253.
#   ccargo.cpp's own calls are inlined by clang, so without these the link drops 1923's body. With it in the link,
#   binaryen merges it with md::CLocal::GetContingencia (3724, unit 89) into one body as the target's 6029 does, and
#   1923, 3724 and 6029 match (fragments 88 and 89).
# - CargosEleicao: two calls of CConfiguracaoEleicao::GetCargos (3775), for 5735 and 7787, which pass false, and 11629,
#   which passes true; the stand-in passes both.
# - CopiaCargos: one call of std::vector<md::CCargo>'s copy constructor (2289), for 1953, 5777 and 11371; GetCargos is
#   the other caller. Without it binaryen inlines 2289 into GetCargos, which then differs (fragment 88).
# - Suplentes: one call of std::vector<md::CDadosCandidato>::__init_with_size (2870), for 5808, 5952 and 7787;
#   md::CCandidatura's constructor (5660) is the other caller. Without it binaryen inlines 2870 into 5660, which then
#   differs (fragment 89).
#
# Not written: two tree destroys whose one target caller, 7787, holds the code that builds and destroys each tree,
# inlined. Each body calls itself, so its row waits for a name with a voter other than its own body (how-to step 1, "The
# row's own symbol"): 7787's match, or a caller that is written. Measured in a link with a stand-in that destroys each
# tree (not committed): both differ from the target in their calls only (pnpm wasm score: 3785 3 over 40 rows, 3781 4
# over 50, all operand-only), and step 9 leaves 3785 `unresolved` on its own call and 3781 `no-candidate`.
# - 3785: std::map<std::string, std::vector<uebyte>>'s destroy. The map is a local of comum::CCandidaturas::LoadFromFile
#   (records ccandidaturas.cpp:201 and :208 around it in 7787): 7787 looks a string up in it through fn 163 (a string
#   map's find, matched as another instance with the same bytes), reads the found vector's bytes unsigned and inserts
#   each, widened to a 32-bit key, with a string into another map (32-byte nodes, the key at +16, a std::string at +20,
#   compared unsigned), the shape of the std::map<uedword, std::string> the records give. The census ties our body with
#   RHVoice's std::map<std::string, std::vector<pitch::target_t>> destroy (target 3568), whose bytes are the same but
#   for the call of itself, so no pair names it.
# - 3781: the destroy of a std::set of ecourna::app::dados::CFederacao (56-byte nodes, the federation at +16, ordered by
#   its 16-bit id compared unsigned), a local of comum::CFederacoes::Load (records cfederacoes.cpp:141 and :149 around
#   it in 7787). No evidence names the set's comparator, which is part of the symbol.
$(ROOT)/$(APP)/232-uenux2-app-comum-dados-callers-roots.o: $(ROOT)/src/units/232-uenux2-app-comum-dados-callers-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/232-uenux2-app-comum-dados-callers.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/232-uenux2-app-comum-dados-callers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/232-uenux2-app-comum-dados-callers-roots.o
