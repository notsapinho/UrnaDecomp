// Roots: nothing written calls this unit's classes. Each is built where the target's callers build it, none of which is
// reconstructed, so these stand-ins build each instantiation the way those callers do, with the exact template arguments
// the RTTI spells:
//   std::make_shared<X>, where the target has __shared_ptr_emplace<X>: CDataText over std::string (*)() (fn 3068 builds it
//     so), const std::string& (*)() (3060) and std::function<std::string()> (12055), CDataTextFmt over std::string
//     (*)(const std::string&) (3058), const std::string (*)(const std::string&) (2028) and
//     std::function<std::string(const std::string&)> (5936), CDataImage over std::vector<unsigned char> (*)() (6689),
//     and CQRCodeImage (12040, 12055);
//   SharedIText(new X), where the target has __shared_ptr_pointer<X*, shared_ptr<IText>::__shared_ptr_default_delete<IText, X>, ...>:
//     CDataText over CTextSource (5409), std::string (*)() (604) and std::function<std::string()> (5419), CDataTextFmt
//     over CTextSource (652) and std::string (*)(const std::string&) (651);
//   SharedIImage(new X): CQRCodeImage (3059);
//   std::shared_ptr<X>(new X): CDataTextFmt over const std::string (*)(const std::string&) (7787).
// So this object instantiates the classes, as the sanctioned exception for std::make_shared does (src/units/README.md
// "Companion files"), and it is where their vtables, slots and control blocks come from until those callers land: they
// are template instances of landed headers, compiled with APP_CXXFLAGS like the other stand-ins. The destructors have no
// direct caller: they are reached through the vtables the constructors store and through the control blocks.
// CQRCodeImage's constructor, fn 3662, has three direct callers in the target, so two stand-ins call it here, and it stays
// a function of its own. The stand-ins differ in their bodies and are address-taken from a static constructor. They take
// CTextSource by reference, as fn 5409 does, and build none: the target holds the record at ctextsource.h 37:19 twice, once
// in each of two TUs, and our link holds no record of that kind yet.
//
// The order of the sink lines is chosen, for a reason outside the source: they decide the order of this object's _ZTS
// strings, and the name of a __shared_ptr_default_delete type has no typeinfo beside it, so only its content places it, and
// splat-symbols' resolveBytes does not place one whose address in our link happens to be 4-aligned while the target's is
// not. This order leaves none of the seven names 4-aligned; the fragment says what that holds and what it does not.
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "api/gui/cdataimage.h"
#include "api/gui/cdatatext.h"
#include "api/gui/cdatatextfmt.h"
#include "api/gui/cqrcodeimage.h"
#include "api/gui/ctextsource.h"

namespace {

using api::CDataImage;
using api::CDataText;
using api::CDataTextFmt;
using api::CTextSource;
using api::SharedIImage;
using api::SharedIText;

using FonteTexto = std::string (*)();
using FonteReferencia = const std::string& (*)();
using FonteFormato = std::string (*)(const std::string&);
using FonteFormatoConst = const std::string (*)(const std::string&);
using FonteImagem = std::vector<unsigned char> (*)();
using FuncaoTexto = std::function<std::string()>;
using FuncaoFormato = std::function<std::string(const std::string&)>;

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

__attribute__((noinline)) SharedIText TextoFuncao(const FuncaoTexto& fonte)
{
    return std::make_shared<CDataText<FuncaoTexto>>(fonte);
}

__attribute__((noinline)) SharedIText TextoFuncaoProprio(const FuncaoTexto& fonte, api::ETextAlignment alinhamento)
{
    return SharedIText(new CDataText<FuncaoTexto>(fonte, alinhamento));
}

__attribute__((noinline)) SharedIText TextoFormatoFuncao(const FuncaoFormato& fonte, const std::string& formato,
                                                         api::ETextAlignment alinhamento)
{
    return std::make_shared<CDataTextFmt<FuncaoFormato>>(fonte, formato, alinhamento);
}

__attribute__((noinline)) SharedIText TextoFormato(FonteFormato fonte, const std::string& formato)
{
    return std::make_shared<CDataTextFmt<FonteFormato>>(fonte, formato);
}

__attribute__((noinline)) SharedIText TextoFormatoProprio(FonteFormato fonte, const std::string& formato,
                                                          api::ETextAlignment alinhamento)
{
    return SharedIText(new CDataTextFmt<FonteFormato>(fonte, formato, alinhamento));
}

__attribute__((noinline)) SharedIText TextoFormatoConst(FonteFormatoConst fonte, const std::string& formato)
{
    return std::make_shared<CDataTextFmt<FonteFormatoConst>>(fonte, formato);
}

__attribute__((noinline)) SharedIText TextoFormatoConstProprio(FonteFormatoConst fonte, const std::string& formato,
                                                               api::ETextAlignment alinhamento)
{
    return std::shared_ptr<CDataTextFmt<FonteFormatoConst>>(new CDataTextFmt<FonteFormatoConst>(fonte, formato, alinhamento));
}

__attribute__((noinline)) SharedIImage ImagemDaFonte(FonteImagem fonte)
{
    return std::make_shared<CDataImage<FonteImagem>>(fonte);
}

__attribute__((noinline)) SharedIImage ImagemQRCodeCompartilhada(api::TPosition tamanho, const FuncaoTexto& fonte)
{
    return std::make_shared<api::CQRCodeImage>(tamanho, fonte);
}

__attribute__((noinline)) SharedIImage ImagemQRCodePropria(api::TPosition tamanho, const FuncaoTexto& fonte)
{
    return SharedIImage(new api::CQRCodeImage(tamanho, fonte));
}

void* volatile w79_sink;

struct SW79Roots {
    SW79Roots()
    {
        w79_sink = reinterpret_cast<void*>(&ImagemQRCodePropria);
        w79_sink = reinterpret_cast<void*>(&TextoFormato);
        w79_sink = reinterpret_cast<void*>(&TextoCompartilhado);
        w79_sink = reinterpret_cast<void*>(&TextoDaFonteFormatado);
        w79_sink = reinterpret_cast<void*>(&TextoFormatoConst);
        w79_sink = reinterpret_cast<void*>(&ImagemQRCodeCompartilhada);
        w79_sink = reinterpret_cast<void*>(&TextoFormatoConstProprio);
        w79_sink = reinterpret_cast<void*>(&TextoFuncaoProprio);
        w79_sink = reinterpret_cast<void*>(&ImagemDaFonte);
        w79_sink = reinterpret_cast<void*>(&TextoFuncao);
        w79_sink = reinterpret_cast<void*>(&TextoFormatoProprio);
        w79_sink = reinterpret_cast<void*>(&TextoDaFonte);
        w79_sink = reinterpret_cast<void*>(&TextoReferencia);
        w79_sink = reinterpret_cast<void*>(&TextoFormatoFuncao);
        w79_sink = reinterpret_cast<void*>(&TextoProprio);
    }
} w79_roots;

} // namespace
