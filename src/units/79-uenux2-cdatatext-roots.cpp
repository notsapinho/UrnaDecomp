// Roots: each of this unit's classes is built where the target's callers build it. 3068, 604, 651, 3058, 5409 and 5419
// are written (unit 31), and what they instantiate comes from their objects, ahead of this one. The others are not
// reconstructed, so these stand-ins build each instantiation the way those callers do, with the exact template arguments
// the RTTI spells:
//   std::make_shared<X>, where the target has __shared_ptr_emplace<X>: CDataText over std::string (*)() (fn 3068 builds it
//     so) and const std::string& (*)() (3060), CDataTextFmt over std::string
//     (*)(const std::string&) (3058 builds it so);
//   SharedIText(new X), where the target has __shared_ptr_pointer<X*, shared_ptr<IText>::__shared_ptr_default_delete<IText, X>, ...>:
//     CDataText over CTextSource (5409), std::string (*)() (604) and std::function<std::string()> (5419), CDataTextFmt
//     over CTextSource (652) and std::string (*)(const std::string&) (651).
// The one std::shared_ptr<X>(new X) of a CDataTextFmt, over const std::string (*)(const std::string&), is 7787's
// (vota::AdicionaNumeroPartido, unit 443's, in the link through unit 441's roots): its stand-in went.
// So this object instantiates the classes, as the sanctioned exception for std::make_shared does (src/units/README.md
// "Companion files"), and it is where their vtables, slots and control blocks come from until those callers land: they
// are template instances of landed headers, compiled with APP_CXXFLAGS like the other stand-ins. The destructors have no
// direct caller: they are reached through the vtables the constructors store and through the control blocks.
// CQRCodeImage's constructor, fn 3662, has three direct callers in the target, 3059, 12040 and 12055, all in the link:
// 12055 (unit 37: its std::make_shared is in vota::CTelasVota::CriaTelaQRCodeBU, ctelasvota.cpp, which binaryen
// inlines into it), 3059 (unit 110's, SharedIImage(new X), whose __shared_ptr_pointer block comes from its object) and
// 12040 (unit 387's, through ctelasvota.cpp's CTelasVota::CriaTelaQRCodeCertificado, inlined into it the same way);
// the stand-ins for 3059 and 12040 went. So did the one for CDataImage over std::vector<unsigned char> (*)(), whose
// builder 6689 (unit 387's, ctelasvota.cpp) is in the link: that instance and its block come from ctelasvota.cpp.o.
// CDataText over std::function<std::string()> and its control block, which only 12055 builds with std::make_shared,
// come from ctelasvota.cpp.o since then, and the stand-in for it went. So did the ones for CDataTextFmt over
// const std::string (*)(const std::string&) by std::make_shared (2028, vota::AdicionaSiglaPartido) and CDataText over
// comum::CCargoDSNomeSexoCandidato (6528), comum::CCandidaturasDSNome and comum::CCandidaturasDSNumero (4185), whose
// builders are written in ctelasvota.cpp (unit 378): those instances come from its object. The stand-ins differ in
// their bodies and are
// address-taken from a static constructor. They take
// CTextSource by reference, as fn 5409 does, and build none: the target holds the record at ctextsource.h 37:19 twice, once
// in each of two TUs, and our link holds no record of that kind yet.
//
// The order of the sink lines is chosen and free: it changes no function's bytes, and the _ZTS strings whose place it
// decides are found by their content at any alignment (splat-symbols' resolveBytes, docs/reference/facts/splat.md
// section S9), so no match depends on where they fall in our link. The fragment says what the seven __get_deleter
// matches rest on.
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "api/gui/cdatatext.h"
#include "api/gui/cdatatextfmt.h"
#include "api/gui/ctextsource.h"

namespace {

using api::CDataText;
using api::CDataTextFmt;
using api::CTextSource;
using api::SharedIText;

using FonteTexto = std::string (*)();
using FonteReferencia = const std::string& (*)();
using FonteFormato = std::string (*)(const std::string&);
using FuncaoTexto = std::function<std::string()>;

__attribute__((noinline)) SharedIText TextoDaFonte(const CTextSource& fonte, api::ETextAlignment alinhamento)
{
    return SharedIText(new CDataText<CTextSource>(fonte, alinhamento));
}

__attribute__((noinline)) SharedIText TextoDaFonteFormatado(const CTextSource& fonte, const std::string& formato,
                                                            api::ETextAlignment alinhamento)
{
    return SharedIText(new CDataTextFmt<CTextSource>(fonte, formato, alinhamento));
}

__attribute__((noinline)) SharedIText TextoCompartilhado(FonteTexto fonte)
{
    return std::make_shared<CDataText<FonteTexto>>(fonte);
}

__attribute__((noinline)) SharedIText TextoProprio(FonteTexto fonte, api::ETextAlignment alinhamento)
{
    return SharedIText(new CDataText<FonteTexto>(fonte, alinhamento));
}

__attribute__((noinline)) SharedIText TextoReferencia(FonteReferencia fonte)
{
    return std::make_shared<CDataText<FonteReferencia>>(fonte);
}

__attribute__((noinline)) SharedIText TextoFuncaoProprio(const FuncaoTexto& fonte, api::ETextAlignment alinhamento)
{
    return SharedIText(new CDataText<FuncaoTexto>(fonte, alinhamento));
}

__attribute__((noinline)) SharedIText TextoFormatoProprio(FonteFormato fonte, const std::string& formato,
                                                          api::ETextAlignment alinhamento)
{
    return SharedIText(new CDataTextFmt<FonteFormato>(fonte, formato, alinhamento));
}

void* volatile w79_sink;

struct SW79Roots {
    SW79Roots()
    {
        w79_sink = reinterpret_cast<void*>(&TextoCompartilhado);
        w79_sink = reinterpret_cast<void*>(&TextoDaFonteFormatado);
        w79_sink = reinterpret_cast<void*>(&TextoFuncaoProprio);
        w79_sink = reinterpret_cast<void*>(&TextoFormatoProprio);
        w79_sink = reinterpret_cast<void*>(&TextoDaFonte);
        w79_sink = reinterpret_cast<void*>(&TextoReferencia);
        w79_sink = reinterpret_cast<void*>(&TextoProprio);
    }
} w79_roots;

} // namespace
