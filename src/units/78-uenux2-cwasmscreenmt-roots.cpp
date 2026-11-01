// Roots: keep unit 78's classes in the skeleton link, reached the way the target reaches them.
// - simulador::CWasmScreenMT, api::CBeepFieldMT, CBuzzFieldMT and CClockFieldMT: every member is reached through its
//   vtable only (`awk -F'\t' '$2==8746' ledger/callgraph.tsv` and the same for the other slots print nothing). The one
//   reference is a vptr store: fns 1072, 941 and 728 (unit 31) hold the fields', so this file takes the fields'
//   vtables' addresses, which keeps every slot; the screen's is stored by fn 8302 (unit 188), which needs no line here. api::CPreShowClearMT's vptr is
//   stored by fns 1694 and 301 (unit 31's cmtformbuilder.cpp), the only target functions that load it, so it needs no
//   line here. The constructors have no caller here, as they have no function of their own in the target.
// - std::string::assign(size_type, char), target fn 1355: the table holds it (elem[6489]: fn 2672, a TU with exceptions,
//   reaches it through invoke_*), so binaryen keeps its result, and CWasmScreenMT::Clear's calls hold a `drop`. Its
//   address is taken here for the same reason; without it our link has only direct callers that drop the result, and
//   binaryen removes it.
// - the control blocks of the classes the target builds with std::shared_ptr<U>(new T), the __shared_ptr_pointer<T*, ...>
//   whose __get_deleter are target fns 11034-11039 and 10537 (vtables @1580040-1580240 and @1590608; the other slots
//   are the shared 174, 144 and 172). fn 8036 (@1531492), std::shared_ptr<IScreenMT>(std::unique_ptr)'s, comes from
//   push<IScreenMT>, which fn 8302 (unit 188) holds, so it needs no line here. 11034 to
//   11039 come from cmtformbuilder.cpp.o now, ahead of this object, as do 11040 and 11046, the blocks of
//   IForm<IScreenMT> and CPreShowClearMT (@1580000, @1579896), which fn 1694 builds, and fn 301 the second, so nothing
//   here instantiates them; the other builders are not reconstructed. Each
//   CompartilhaX below instantiates one and nothing else: it takes a T* it never gets, so it uses no constructor, and no
//   vtable, of T. As with std::make_shared, the control blocks' members come from
//   this object until the builders land; T's own inline members stay the units' objects', first on the link line. Their
//   addresses are taken so they stay in the link; nothing calls them. The lines' order is free: it changes no function's
//   re-pointed bytes, and splat-symbols' resolveBytes finds a typeinfo name string by its content at any alignment
//   (docs/reference/facts/splat.md section S9), so where this object puts the deleter names in our link matters to no
//   match. Compiled with APP_CXXFLAGS.
#include <memory>

#include "api/gui/cbeepfieldmt.h"
#include "api/gui/cbuzzfieldmt.h"
#include "api/gui/cclockfieldmt.h"
#include "api/gui/cfixedtext.h"
#include "api/gui/cledfieldmt.h"
#include "api/gui/ctextfieldmt.h"
#include "api/gui/iscreenmt.h"
#include "app/vota/operador/comum/ctextfieldupdatemt.h"

extern "C" {
extern const char cbeepfieldmt_vt[] __asm__("_ZTVN3api12CBeepFieldMTE");
extern const char cbuzzfieldmt_vt[] __asm__("_ZTVN3api12CBuzzFieldMTE");
extern const char cclockfieldmt_vt[] __asm__("_ZTVN3api13CClockFieldMTE");
int string_assign_fill(int, int, int) __asm__("_ZNSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6assignEmc");
}

namespace {

template <typename TBase, typename T>
std::shared_ptr<TBase> Compartilha(T* objeto)
{
    return std::shared_ptr<TBase>(objeto);
}

using SharedCampoMT = api::IFormField<api::IScreenMT>;

const void* volatile cwasmscreenmt_sink;

struct SCWasmScreenMTRoots {
    SCWasmScreenMTRoots()
    {
        cwasmscreenmt_sink = cbeepfieldmt_vt;
        cwasmscreenmt_sink = cbuzzfieldmt_vt;
        cwasmscreenmt_sink = cclockfieldmt_vt;
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&string_assign_fill);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<api::IText, api::CFixedText>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<SharedCampoMT, api::CBuzzFieldMT>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<SharedCampoMT, api::CClockFieldMT>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<SharedCampoMT, api::CLedFieldMT>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<SharedCampoMT, api::CTextFieldMT>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<SharedCampoMT, api::CTextFieldUpdateMT>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<SharedCampoMT, api::CBeepFieldMT>);
    }
} cwasmscreenmt_roots;

} // namespace
