// libc++'s std::map<unsigned char, std::string> hinted insert, __tree::__emplace_hint_unique_key_args<unsigned char,
// const pair&> (target fn 3266), which map's initializer-list constructor calls once per pair: its target callers are
// vota::CDigitalReconhecida::ProcessInput (10481, the map of vota::CLogVota::LogaTipoHabilitacaoEleitor inlined there)
// and 3076 (vota::AdicionaGifCargo, the cargos' map of images, :/resource/gifs/, written with unit 378, differs). The
// target's copy loads a pointer again after a store, as this instance at UENUX2_CXXFLAGS does (2 over 101 rows, the
// calls), where app/vota/log/clogvota.cpp's, with strict aliasing, does not (15 over 101, 5 rows deleted). Which
// uenux2 object gives it is not identified. ctelasvota.cpp's object, which holds 3076, emits the instance too, but it
// links after clogvota.cpp.o: a link with this object compiled without the instance keeps clogvota.cpp.o's copy, and
// 3266 reads no-candidate and 10481 unresolved there, so the instance stays. It brings
// __tree::__find_equal<unsigned char> (3251), whose match line step 9 renamed to this instance, a twin of
// md::CVotosCargos' map's, which links later. urna_insere_mapa_texto only instantiates: nothing calls it, and it leaves
// the link. It compiles at UENUX2_CXXFLAGS, the tree's own flags, and links last in APP_OBJS, after roots_rhvoice.o and
// roots_boost.o: the instance brings __tree_balance_after_insert (fn 152) too, whose copy ahead of roots_rhvoice.o
// would be this object's, without strict aliasing, and 152 then differs from the target and 447 (RHVoice::str::less)
// reads unresolved; after them 152 stays roots_rhvoice.o's (both places measured on whole links through steps 6 to 10
// with a set's hinted insert at UENUX2_CXXFLAGS: src/units/268-uenux2-cgeracaoversoescontratos.mk).
#include <map>
#include <string>

void urna_insere_mapa_texto(std::map<unsigned char, std::string>& mapa,
                            const std::pair<const unsigned char, std::string>& valor)
{
    mapa.insert(mapa.end(), valor);
}
