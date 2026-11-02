// libc++'s std::set<std::string> hinted insert, __tree<std::string>::__emplace_hint_unique_key_args<std::string, const
// std::string&> (target fn 2281), whose target callers are RHVoice's 1248 and 5309 (property<std::set<std::string>>'s
// constructor, which calls it twice) and comum's 12098 (vota::CGravaResultado::StartState, not reconstructed). The
// target's copy is a uenux2 object's built without strict aliasing: instantiated at UENUX2_CXXFLAGS the function loads a
// value again after a store, as the target's body does, and with strict aliasing it does not; RHVoice's language.cpp,
// the other object of ours that emits it, gives another body. Which uenux2 object is not identified: with strict
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
