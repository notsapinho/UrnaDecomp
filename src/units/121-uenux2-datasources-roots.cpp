// Roots of unit 121, in the shapes src/units/README.md "Companion files" sanctions: a builder the link drops, and the
// vtable it stores kept by the static constructor below. None of the target's builders is reconstructed. Each builder
// here is an optnone function that nothing calls, which wasm-ld drops; clang emits what it instantiates in this object,
// and the sink keeps the one vtable the target's own builder stores (the grep for its address point lists the function):
// - a class with no key function, built in the builder so that this object emits its vtable and the slots: the texts
//   api::CDataText<comum::CRespostasDSNumero> (vptr 1537840, stored by fn 6652) and
//   api::CDataText<vota::CEscolheOpcao::COpcaoDS> (1588108, fn 2753). Their GetText call the source's call operator,
//   defined out of line in crespostas.cpp and cescolheopcao.cpp, which binaryen inlines into its one caller (fns 12621
//   and 10685; the fragment says which form the target shows). Unit 102's roots object, ahead of this one, instantiates
//   CDataText<CRespostasDSNumero> too, in a builder it drops, so the copies the link keeps of that class's vtable and
//   GetText are that object's, the same code. CRespostasDSNumero's constructor is declared only: fn 6652 builds the
//   source with a call of fn 5729, which stores its byte and returns this, and fn 600 calls the same body on another
//   class's one-byte object, so the target holds one body for both and does not tell which source defines it. COpcaoDS
//   is copied, as fn 2753 copies it.
// - a control block: std::make_shared<T> for __shared_ptr_emplace<T>, with T std::string (vptr 1588328, stored by fns
//   652, 1150, 1901, 2734, 2747, 5397, 10440 and 10465) and api::CInputMenuField (1579324, fn 3675). A dropped builder
//   needs T's constructor declared, not defined.
// And two stand-in callers, of CCalculaCV's destructor and of IncluiString, kept by their addresses: each comment names
// the target callers it stands for. CCalculaCV's own block, __shared_ptr_pointer<CCalculaCV*, std::default_delete<CCalculaCV>, ...> (vptr
// 1575124, stored by fn 12110), has no builder here: one in this object only declares the destructor, so the block's
// __on_zero_shared frees what the destructor returns, where the target's (fn 11263) frees the pointer it passed, and
// the destructor (fn 5614) then keeps its result and stops matching. The fragment has the measurement.
//
// Compiled with APP_CXXFLAGS, like the other roots; the fragment says what UENUX2_CXXFLAGS gives. The order of the sink
// lines is free (docs/reference/facts/splat.md section S9).
#include <memory>
#include <string>

#include "api/gui/cdatatext.h"
#include "api/gui/cinputmenufield.h"
#include "app/comum/dados/crespostasds.h"
#include "app/comum/relatorios/ccalculacv.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

extern "C" {
extern const char w121_vt_respostas[] __asm__("_ZTVN3api9CDataTextIN5comum18CRespostasDSNumeroEEE");
extern const char w121_vt_opcao[] __asm__("_ZTVN3api9CDataTextIN4vota13CEscolheOpcao8COpcaoDSEEE");
extern const char w121_vt_string[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEENS4_IS6_EEEE");
extern const char w121_vt_menu[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api15CInputMenuFieldENS_9allocatorIS2_EEEE");
}

__attribute__((optnone, noinline)) void w121_respostas(uebyte digitos)
{
    const api::CDataText<comum::CRespostasDSNumero> texto(comum::CRespostasDSNumero{digitos});
}

__attribute__((optnone, noinline)) void w121_opcao(const vota::CEscolheOpcao::COpcaoDS& opcao)
{
    const api::CDataText<vota::CEscolheOpcao::COpcaoDS> texto(opcao);
}

__attribute__((optnone, noinline)) std::shared_ptr<std::string> w121_string(const std::string& valor)
{
    return std::make_shared<std::string>(valor);
}

__attribute__((optnone, noinline)) std::shared_ptr<api::CInputMenuField> w121_menu(
    const api::SPoint& posicao, const api::SFont& font, api::TPosition largura)
{
    return std::make_shared<api::CInputMenuField>(posicao, font, largura);
}

namespace {

// Stands for the two target callers of CCalculaCV's destructor (fn 5614): fn 11263, the __on_zero_shared of CCalculaCV's
// block (the header says why this object builds none), and fn 12110, which holds push<CCalculaCV> and the release of its
// std::unique_ptr. With one call site, binaryen would inline the destructor into it. Two calls, so the body is no target
// function's.
__attribute__((noinline)) void w121_destroi_calcula(comum::CCalculaCV* primeiro, comum::CCalculaCV* segundo)
{
    primeiro->~CCalculaCV();
    segundo->~CCalculaCV();
}

// Stands for the eight target callers of CCalculaCV::IncluiString (fn 942): fns 5967, 11253, 11254, 11255, 11256, 11260,
// 11980 and 11981, none of them in our link. With one call site, binaryen would inline it into it.
__attribute__((noinline)) void w121_inclui(comum::CCalculaCV& calcula, const std::string& primeira, const std::string& segunda)
{
    calcula.IncluiString(primeira);
    calcula.IncluiString(segunda);
}

const void* volatile w121_sink;

struct SW121Roots {
    SW121Roots()
    {
        w121_sink = reinterpret_cast<const void*>(&w121_destroi_calcula);
        w121_sink = reinterpret_cast<const void*>(&w121_inclui);
        w121_sink = w121_vt_respostas;
        w121_sink = w121_vt_opcao;
        w121_sink = w121_vt_string;
        w121_sink = w121_vt_menu;
    }
} w121_roots;

} // namespace
