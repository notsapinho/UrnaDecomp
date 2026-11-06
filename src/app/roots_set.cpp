// libc++'s std::set<std::string> hinted insert, __tree<std::string>::__emplace_hint_unique_key_args<std::string, const
// std::string&> (target fn 2281), whose target callers are RHVoice's 1248 and 5309 (property<std::set<std::string>>'s
// constructor, which calls it twice) and vota's 12098 (vota::CGravaResultado::StartState, not reconstructed; its
// records are in src/app/vota/eleitor/fimvotacao/cgravaresultado.cpp). The target's copy is a uenux2 object's built
// without strict aliasing: instantiated at UENUX2_CXXFLAGS the function loads a value again after a store, as the
// target's body does, and with strict aliasing it does not; RHVoice's language.cpp, the next object of ours that emits
// it (voice.cpp emits it too), gives another body. Which uenux2 object is not identified: with strict
// aliasing a set's hinted insert keeps __emplace_hint_unique_extract_key out of line, the emplace inlined into it (fn
// 1163's shape), and emits no 2281, so app/comum/gravadores/cgeracaoversoescontratos.cpp, which builds so, gives none,
// and 12098's object, under src/app/vota/, would not either while that directory builds with strict aliasing (a
// reading). So this root stands for an object not written yet, and goes once that object is written and gives the copy.
// It compiles at UENUX2_CXXFLAGS, the tree's own flags, and links last in APP_OBJS, after roots_rhvoice.o and
// roots_boost.o: the instance brings __tree_balance_after_insert (fn 152) too, whose copy ahead of roots_rhvoice.o would
// be this object's, without strict aliasing, and 152 then differs from the target and 447 (RHVoice::str::less) reads
// unresolved; after them 152 stays roots_rhvoice.o's. Both places were measured on whole links through steps 6 to 10
// (src/units/268-uenux2-cgeracaoversoescontratos.mk). urna_insere_conjunto only instantiates: nothing calls it, and it
// leaves the link.
#include <set>
#include <string>

void urna_insere_conjunto(std::set<std::string>& conjunto, const std::string& valor)
{
    conjunto.insert(conjunto.end(), valor);
}

// libc++'s std::map<unsigned char, std::string> hinted insert, __tree::__emplace_hint_unique_key_args<unsigned char,
// const pair&> (target fn 3266), which map's initializer-list constructor calls once per pair: its target callers are
// vota::CDigitalReconhecida::ProcessInput (10481, the map of vota::CLogVota::LogaTipoHabilitacaoEleitor inlined there)
// and 3076 (vota::AdicionaGifCargo, the cargos' map of images, :/resource/gifs/, written with unit 378, differs). The
// target's copy loads a
// pointer again after a store, as this instance at UENUX2_CXXFLAGS does (2 over 101 rows, the calls), where
// app/vota/log/clogvota.cpp's, with strict aliasing, does not (15 over 101, 5 rows deleted). Which uenux2 object gives
// it is not identified (3076's, a reading: ctelasvota.cpp's object, which holds 3076 now, was not measured without this
// instance); the instance goes once that object is. It brings
// __tree::__find_equal<unsigned char> (3251), whose match line step 9 renamed to this instance, a twin of
// md::CVotosCargos' map's, which links later. urna_insere_mapa_texto only instantiates: nothing calls it, and it leaves
// the link.
#include <map>

void urna_insere_mapa_texto(std::map<unsigned char, std::string>& mapa,
                            const std::pair<const unsigned char, std::string>& valor)
{
    mapa.insert(mapa.end(), valor);
}
