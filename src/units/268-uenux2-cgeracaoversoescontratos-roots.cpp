// Roots of unit 268 (src/units/268-uenux2-cgeracaoversoescontratos.mk): callers that stand for the target callers not
// reconstructed, fn 12098 (vota::CGravaResultado::StartState, which holds CGeracaoVersoesContratos::GetInst inlined)
// above all, so that each function keeps the call sites the target gives it; each stand-in names the callers it stands
// for, and goes when they are all in the link. Compiled with APP_CXXFLAGS; the object compiled at uenux2's flags, with
// strict aliasing and without it, is cmp-equal to it.
//
// comum::CGeracaoVersoesContratos::ObtemDependencias (target fn 5869): its target callers are itself and fn 12098,
// which calls it once; this noinline caller stands for 12098, and with the recursive call the function has two call
// sites. The result is built in place, so this object instantiates no member of std::set.
#include <format>
#include <new>
#include <set>
#include <string>

#include "api/pattern/cpolysingletonlist.h"
#include "app/comum/gravadores/cgeracaoversoescontratos.h"

__attribute__((noinline)) void w268_dependencias(comum::CGeracaoVersoesContratos& geracao, void* destino,
    const std::string& contrato, std::set<std::string>& dependencias)
{
    ::new (destino) std::set<std::string>(geracao.ObtemDependencias(contrato, dependencias));
}

namespace {

void* volatile w268_sink;

struct SW268Roots {
    SW268Roots()
    {
        w268_sink = reinterpret_cast<void*>(&w268_dependencias);
    }
} w268_roots;

} // namespace

// Stands in for the other target callers of fn 1163, libc++'s
// __tree<std::string>::__emplace_hint_unique_extract_key<const std::string&> (a std::set<std::string>'s hinted insert,
// the emplace inlined into it): 5360 and 11620, which build a std::set<std::string> from an initializer list (two and
// eight inserts at the end hint). Both are in the link now (units 227 and 136), and 5360 calls 1163 twice; 11620 does
// not: the set it holds is comum::CPath's (cpath.cpp, built without strict aliasing), which inlines 1163 and calls the
// emplace (unit 190's fragment), so the stand-in stays for 11620. ObtemDependencias's set copy calls 1163 at one site,
// and binaryen inlines a function called once. Called through its label with the object's signature (the iterator
// result is one i32), so this object instantiates nothing of std::set; the label resolves while
// cgeracaoversoescontratos.cpp builds with strict aliasing, which keeps 1163 out of line there (src/Makefile
// UENUX2_TBAA_DIRS), as unit 227's cmontadorhash.cpp.o, built so too and linked ahead of it, does.
extern "C" int w268_insere(int, int, int) __asm__(
    "_ZNSt3__26__treeINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEENS_4lessIS6_EENS4_IS6_EEE33__"
    "emplace_hint_unique_extract_keyB8ne210108IRKS6_EENS_15__tree_iteratorIS6_PNS_11__tree_nodeIS6_PvEElEENS_21__"
    "tree_const_iteratorIS6_SI_lEEOT_NS_22__extract_key_self_tagE");

__attribute__((noinline)) void w268_conjunto(int conjunto, int fim, int primeiro, int segundo)
{
    w268_insere(conjunto, fim, primeiro);
    w268_insere(conjunto, fim, segundo);
}

namespace {

void* volatile w268_sink_conjunto;

struct SW268RootsConjunto {
    SW268RootsConjunto()
    {
        w268_sink_conjunto = reinterpret_cast<void*>(&w268_conjunto);
    }
} w268_roots_conjunto;

} // namespace

// Stands in for the target callers of fn 2860, api::CPolySingletonList::has<comum::CGeracaoVersoesContratos> (the
// template of api/pattern/cpolysingletonlist.h): fn 12098, which calls it three times, and fn 14478
// (__wasm_call_ctors, the static initializer of a TU not written, which calls has<T>(g_polySingletonsInfo()) and drops
// the result). One call for each. The link's copy is cgeracaoversoescontratos.cpp's, whose GetInst instantiates it.
__attribute__((noinline)) int w268_tem()
{
    return api::CPolySingletonList::has<comum::CGeracaoVersoesContratos>()
        ? 3
        : (api::CPolySingletonList::has<comum::CGeracaoVersoesContratos>() ? 5 : 7);
}

// Stands in for fn 5870's one target caller, fn 12098, which calls it twice: std::make_format_args over a std::string
// and the char array "20260601173148" (libc++'s template), the arguments of the messages of two throws whose records
// are those of comum::md::CDependenciasContratos's and CVersoesContratos's constructors (cdependenciascontratos.cpp:27
// and cversoescontratos.cpp:29; format strings at 235617 and 235546), code 12098 holds behind stack prologues of its
// own. 5870's body holds the array's address (341442) and its wasm type, (i32 i32)->(), has no parameter for it:
// dead-argument elimination folded it, the same at both call sites. Both calls here pass one literal of the same bytes,
// which is no target object, so the fold happens here too. [[clang::noinline]] keeps the two calls: without it clang
// inlines both into this function and the object defines no make_format_args. This object's copy is the link's, as no
// object of ours instantiates it.
__attribute__((noinline)) void w268_formata(void* destino, const std::string& dependencias, const std::string& versoes)
{
    using TArgumentos = decltype(std::make_format_args(dependencias, "20260601173148"));
    [[clang::noinline]] ::new (destino) TArgumentos(std::make_format_args(dependencias, "20260601173148"));
    [[clang::noinline]] ::new (static_cast<char*>(destino) + sizeof(TArgumentos))
        TArgumentos(std::make_format_args(versoes, "20260601173148"));
}

// Stands in for fn 12098, a target caller of fn 5866, comum::CGeracaoVersoesContratos's destructor (out of line in
// cgeracaoversoescontratos.cpp): its code after the push of the singleton deletes the object a std::unique_ptr holds,
// `if (p) { f5866(p); f136(p); }`, which drops the result and frees the object. The other target caller, fn 11636
// (__on_zero_shared of the control block below), is in the link. One call.
__attribute__((noinline)) void w268_destroi(comum::CGeracaoVersoesContratos& geracao)
{
    geracao.~CGeracaoVersoesContratos();
}

// The control block std::__shared_ptr_pointer<comum::CGeracaoVersoesContratos*,
// std::default_delete<comum::CGeracaoVersoesContratos>, std::allocator<comum::CGeracaoVersoesContratos>> (vtable
// @1553544, slots 174, 144, 11636, 11635, 144): push<T>, which CGeracaoVersoesContratos::GetInst reaches through
// CPolySingleton<T>::set, builds it from the std::unique_ptr, and its address point 1553552 is stored by fn 12098 alone
// (/usr/bin/grep -rlE 'i32\.const 1553552($|[^0-9])' build/out/splat/pieces/asm prints only vota/12098.wat), which
// holds GetInst inlined. GetInst is written in cgeracaoversoescontratos.cpp, the destructor's TU, and nothing calls it,
// so wasm-ld drops it: this sink stands for 12098's store, keeps the vtable that object emits, and goes when 12098 is
// in the link.
extern const char w268_bloco_vt[] __asm__(
    "_ZTVNSt3__220__shared_ptr_pointerIPN5comum24CGeracaoVersoesContratosENS_14default_deleteIS2_EENS_9allocatorIS2_EEEE");

namespace {

void* volatile w268_sink_contratos[4];

struct SW268RootsContratos {
    SW268RootsContratos()
    {
        w268_sink_contratos[0] = reinterpret_cast<void*>(&w268_tem);
        w268_sink_contratos[1] = reinterpret_cast<void*>(&w268_formata);
        w268_sink_contratos[2] = reinterpret_cast<void*>(&w268_destroi);
        w268_sink_contratos[3] = const_cast<char*>(w268_bloco_vt);
    }
} w268_roots_contratos;

} // namespace
