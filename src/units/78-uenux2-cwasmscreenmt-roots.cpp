// Roots: keep unit 78's classes in the skeleton link, reached the way the target reaches them.
// - simulador::CWasmScreenMT, api::CBeepFieldMT, CBuzzFieldMT, CClockFieldMT and api::CPreShowClearMT: every member is
//   reached through its vtable only (`awk -F'\t' '$2==8746' ledger/callgraph.tsv` and the same for the other slots print
//   nothing). The one reference is a vptr store in code not reconstructed (fn 8302 for the screen, fns 1072, 941, 728
//   and the callers of the factory that holds CPreShowClearMT's), so this file takes each vtable's address, which keeps
//   every slot. The constructors have no caller here, as they have no function of their own in the target.
// - std::string::assign(size_type, char), target fn 1355: the table holds it (elem[6489]: fn 2672, a TU with exceptions,
//   reaches it through invoke_*), so binaryen keeps its result, and CWasmScreenMT::Clear's calls hold a `drop`. Its
//   address is taken here for the same reason; without it our link has only direct callers that drop the result, and
//   binaryen removes it.
// - the control blocks of the classes the target builds with std::shared_ptr<U>(new T), the __shared_ptr_pointer<T*, ...>
//   whose __get_deleter are target fns 11034-11040, 11046 and 10537 (their vtables @1579896-1580240 and @1590608; the
//   other slots are the shared 174, 144 and 172), and the one std::shared_ptr<IScreenMT>(std::unique_ptr<IScreenMT>)
//   makes, fn 8036 (@1531492). The code that builds them is not reconstructed. Each CompartilhaX below instantiates one
//   and nothing else: it takes a T* it never gets, so no constructor, and so no vtable, of T is used. As with
//   std::make_shared, the roots object is where the control block's members come from until the real builders land, and
//   T's own inline members stay the units' objects', which come first on the link line. The function addresses are
//   taken so the stand-ins stay in the link; nothing calls them. The order of the lines below is a choice for the scan's
//   sake: a type's name string that our link happens to put at a multiple of 4 is placed by its bytes only at a multiple
//   of 4 of the target, so this order leaves none of the deleter names there. Compiled with APP_CXXFLAGS.
#include <memory>

#include "api/gui/cbeepfieldmt.h"
#include "api/gui/cbuzzfieldmt.h"
#include "api/gui/cclockfieldmt.h"
#include "api/gui/cfixedtext.h"
#include "api/gui/cledfieldmt.h"
#include "api/gui/cpreshowclearmt.h"
#include "api/gui/ctextfieldmt.h"
#include "api/gui/iform.h"
#include "api/gui/iscreenmt.h"
#include "app/vota/operador/comum/ctextfieldupdatemt.h"

extern "C" {
extern const char cwasmscreenmt_vt[] __asm__("_ZTVN9simulador13CWasmScreenMTE");
extern const char cbeepfieldmt_vt[] __asm__("_ZTVN3api12CBeepFieldMTE");
extern const char cbuzzfieldmt_vt[] __asm__("_ZTVN3api12CBuzzFieldMTE");
extern const char cclockfieldmt_vt[] __asm__("_ZTVN3api13CClockFieldMTE");
extern const char cpreshowclearmt_vt[] __asm__("_ZTVN3api15CPreShowClearMTE");
int string_assign_fill(int, int, int) __asm__("_ZNSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6assignEmc");
}

namespace {

template <typename TBase, typename T>
std::shared_ptr<TBase> Compartilha(T* objeto)
{
    return std::shared_ptr<TBase>(objeto);
}

std::shared_ptr<api::IScreenMT> CompartilhaTela(std::unique_ptr<api::IScreenMT> tela)
{
    return std::shared_ptr<api::IScreenMT>(std::move(tela));
}

using SharedCampoMT = api::IFormField<api::IScreenMT>;

const void* volatile cwasmscreenmt_sink;

struct SCWasmScreenMTRoots {
    SCWasmScreenMTRoots()
    {
        cwasmscreenmt_sink = cwasmscreenmt_vt;
        cwasmscreenmt_sink = cbeepfieldmt_vt;
        cwasmscreenmt_sink = cbuzzfieldmt_vt;
        cwasmscreenmt_sink = cclockfieldmt_vt;
        cwasmscreenmt_sink = cpreshowclearmt_vt;
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&string_assign_fill);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<api::IText, api::CFixedText>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<SharedCampoMT, api::CBuzzFieldMT>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<SharedCampoMT, api::CClockFieldMT>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<SharedCampoMT, api::CLedFieldMT>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<SharedCampoMT, api::CTextFieldMT>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<SharedCampoMT, api::CTextFieldUpdateMT>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<api::IForm<api::IScreenMT>, api::IForm<api::IScreenMT>>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<api::IPreShow<api::IScreenMT>, api::CPreShowClearMT>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&Compartilha<SharedCampoMT, api::CBeepFieldMT>);
        cwasmscreenmt_sink = reinterpret_cast<const void*>(&CompartilhaTela);
    }
} cwasmscreenmt_roots;

} // namespace
