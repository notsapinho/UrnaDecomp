// Roots of unit 121, in the shapes src/units/README.md "Companion files" sanctions: a builder the link drops, and the
// vtable it stores kept by the static constructor below. None of the target's builders is reconstructed. Each builder
// here is an optnone function that nothing calls, which wasm-ld drops; clang emits what it instantiates in this object,
// and the sink keeps the one vtable the target's own builder stores (the grep for its address point lists the function):
// - a class with no key function, built in the builder so that this object emits its vtable and the slots: the text
//   api::CDataText<comum::CRespostasDSNumero> (vptr 1537840, stored by fn 6652). Its GetText calls the source's call
//   operator, defined out of line in crespostas.cpp, which binaryen inlines into its one caller (fn 12621). Unit 102's
//   roots object, ahead of this one, instantiates CDataText<CRespostasDSNumero> too, in a builder it drops, so the
//   copies the link keeps of that class's vtable and GetText are that object's, the same code. CRespostasDSNumero's
//   constructor is declared only: fn 6652 builds the source with a call of fn 5729, which stores its byte and returns
//   this, and fn 600 calls the same body on another class's one-byte object (unit 154 writes that one, CSynchronizer's),
//   so the target holds one body for both and does not tell which source defines it.
// No control block is left: std::string's __shared_ptr_emplace<T> (vptr 1588328, stored by fn 10465, and by 652, 1150,
// 1901, 2734, 2747, 5397 and 10440) went, its builder and sink with it, once those functions were in the link, one
// storer giving the reference the sink gave; the one of api::CInputMenuField (1579324) went once its builder, fn 3675
// (unit 120's file), was.
// And two stand-in callers, of CCalculaCV's destructor and Reinicia, kept by their addresses: each comment names the
// target callers it stands for. The one of vota::AdicionaCampoNumerico (fn 1151) went: its last target caller not in the
// link, fn 10500 (unit 239's), is. So did those of IncluiString (fn 942) and CalculaCodigo (fn 3700): their target
// callers 5967, 11260 and 11974 (unit 220's roots) are in the link.
// vota::CEscolheOpcao::GetInst (fn 2753), whose four target callers (10677, 10698, 10740 and 10754) are in the link,
// stores the vptrs of CEscolheOpcao and of CDataText<CEscolheOpcao::COpcaoDS>
// in cescolheopcao.cpp's object, so no sink keeps those vtables here. CCalculaCV's own block, __shared_ptr_pointer<CCalculaCV*, std::default_delete<CCalculaCV>, ...> (vptr
// 1575124, stored by fn 12110), has no builder here: one in this object only declares the destructor, so the block's
// __on_zero_shared frees what the destructor returns, where the target's (fn 11263) frees the pointer it passed, and
// the destructor (fn 5614) then keeps its result and stops matching. The fragment has the measurement.
//
// Compiled with APP_CXXFLAGS, like the other roots; the fragment says what UENUX2_CXXFLAGS gives. The order of the sink
// lines is free (docs/reference/facts/splat.md section S9).
#include <memory>
#include <string>

#include "api/gui/cdatatext.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/iinputfield.h"
#include "app/comum/dados/crespostasds.h"
#include "app/comum/relatorios/ccalculacv.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

extern "C" {
extern const char w121_vt_respostas[] __asm__("_ZTVN3api9CDataTextIN5comum18CRespostasDSNumeroEEE");
}

__attribute__((optnone, noinline)) void w121_respostas(uebyte digitos)
{
    const api::CDataText<comum::CRespostasDSNumero> texto(comum::CRespostasDSNumero{digitos});
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

// Stands for fn 12110, the target caller of CCalculaCV::Reinicia (fn 5615) that is not in the link (fn 3700, the other,
// is), so that 5615 keeps two call sites (src/units/README.md "Companion files").
__attribute__((noinline)) unsigned w121_reinicia(comum::CCalculaCV& calcula, const std::string& valor)
{
    calcula.Reinicia(valor);
    return valor.size() + 121;
}

const void* volatile w121_sink;

struct SW121Roots {
    SW121Roots()
    {
        w121_sink = reinterpret_cast<const void*>(&w121_destroi_calcula);
        w121_sink = reinterpret_cast<const void*>(&w121_reinicia);
        w121_sink = w121_vt_respostas;
    }
} w121_roots;

} // namespace
