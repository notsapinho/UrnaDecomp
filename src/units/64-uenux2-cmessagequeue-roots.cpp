// Roots: api::CPriorityMessageQueue<api::SMessage> (api/ipc/cmessagequeue.h), a class template whose users are not
// reconstructed yet, reached the way the target reaches it.
// - Remove (target fn 2073): the target calls it directly from 4337, 4343, 4349 (twice) and 10204. Two noinline callers
//   give it more than one call site, so binaryen keeps its body out of line, and it is then the one caller of
//   std::priority_queue::pop, which clang leaves out of line and binaryen inlines into it, as in the target.
// - The destructors (target fns 3162, 3157): the target reaches them only through the vtable @1534764 and the vtables
//   of vota::CMessageEleitor and vota::CMessageOperador, so the sink takes the vtable's address.
// The header is included because nothing else instantiates the template: the bodies are its template instance
// (src/units/README.md, "A body a companion object supplies"). A class template has no key function, so only a TU that
// uses the vtable emits it, D2 and D0. The constructor that does in the target (lines 113-114 of the header) needs
// api::CPolySingleton, which is not in the tree. The optnone function below makes the non-virtual destructor call
// instead, so clang emits the COMDAT D2 and with it the vtable and the D0 (unit 19's device); it is not rooted, so
// wasm-ld drops it. When the TU of vota::CMessageEleitor lands, its object comes first on the link line and takes
// these instances over.
#include "api/ipc/cmessagequeue.h"

using TFilaMensagens = api::CPriorityMessageQueue<api::SMessage>;

extern "C" const char w64_vtable[] __asm__("_ZTVN3api21CPriorityMessageQueueINS_8SMessageEEE");

__attribute__((optnone, noinline)) void w64_emite_destrutor(TFilaMensagens& fila)
{
    fila.TFilaMensagens::~TFilaMensagens();
}

namespace {

__attribute__((noinline)) int TipoDaProxima(TFilaMensagens& fila)
{
    return fila.Remove().m_tipo;
}

__attribute__((noinline)) int SomaDasProximas(TFilaMensagens& fila)
{
    const int primeira = fila.Remove().m_tipo;
    return primeira + fila.Remove().m_valor;
}

const void* volatile w64_sink;

struct SW64Roots {
    SW64Roots()
    {
        w64_sink = w64_vtable;
        w64_sink = reinterpret_cast<const void*>(&TipoDaProxima);
        w64_sink = reinterpret_cast<const void*>(&SomaDasProximas);
    }
} w64_roots;

} // namespace
