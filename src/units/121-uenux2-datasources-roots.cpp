// Roots of unit 121, in the shapes src/units/README.md "Companion files" sanctions. The dropped builder and the sink
// that kept the text api::CDataText<comum::CRespostasDSNumero> (vptr 1537840) went once its storer, fn 6652, was in
// the link (unit 441): ctelasvota.cpp.o, 6652's object, emits that class's vtable and members now, and
// CRespostasDSNumero's constructor, which 6652 calls, is defined in crespostas.cpp (fn 5729, one body with
// api::CSynchronizer's).
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

#include "api/gui/cmtformbuilder.h"
#include "api/gui/iinputfield.h"
#include "app/comum/relatorios/ccalculacv.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

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
    }
} w121_roots;

} // namespace
