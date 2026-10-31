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
//   GetText are that object's, the same code. CRespostasDSNumero's constructor is declared only (out of line in the
//   target, fn 5729); COpcaoDS is copied, as fn 2753 copies it.
// - a control block: std::make_shared<T> for __shared_ptr_emplace<T>, with T std::string (vptr 1588328, stored by fns
//   652, 1150, 1901, 2734, 2747, 5397, 10440 and 10465) and api::CInputMenuField (1579324, fn 3675); and the
//   std::shared_ptr<T> made from a std::unique_ptr<T>, for __shared_ptr_pointer<T*, std::default_delete<T>,
//   std::allocator<T>>, with T comum::CCalculaCV (1575124, fn 12110, whose push<CCalculaCV> record at
//   cpolysingletonlist.h:129 takes the std::unique_ptr). A dropped builder needs T's constructor declared, not defined.
// And one stand-in caller, of CCalculaCV's destructor, kept by its address: its comment names the target caller it
// stands for.
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
extern const char w121_vt_calcula[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum10CCalculaCVENS_14default_deleteIS2_EENS_9allocatorIS2_EEEE");
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

__attribute__((optnone, noinline)) std::shared_ptr<comum::CCalculaCV> w121_calcula(
    std::unique_ptr<comum::CCalculaCV> calcula)
{
    return std::shared_ptr<comum::CCalculaCV>(std::move(calcula));
}

namespace {

// Stands for fn 12110, the second target caller of CCalculaCV's destructor (fn 5614); the block's __on_zero_shared is
// the first. With one caller, binaryen would inline the destructor into it. Two calls, so the body is no target function's.
__attribute__((noinline)) void w121_destroi_calcula(comum::CCalculaCV* primeiro, comum::CCalculaCV* segundo)
{
    primeiro->~CCalculaCV();
    segundo->~CCalculaCV();
}

const void* volatile w121_sink;

struct SW121Roots {
    SW121Roots()
    {
        w121_sink = reinterpret_cast<const void*>(&w121_destroi_calcula);
        w121_sink = w121_vt_respostas;
        w121_sink = w121_vt_opcao;
        w121_sink = w121_vt_string;
        w121_sink = w121_vt_menu;
        w121_sink = w121_vt_calcula;
    }
} w121_roots;

} // namespace
