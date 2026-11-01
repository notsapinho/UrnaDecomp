// Reconstruction's note, not TSE's text. The file's records are the string constructor's, line 24 (target fn 2246),
// and those of api::isResource and api::getResourceFile (api/gui/iresource.h), which it inlines. Every other line, and
// LeArquivo, are a choice (src/units/158-uenux2-api.mk).
#include "api/gui/cfixedimage.h"

#include "api/gui/eueguierror.h"
#include "api/gui/iresource.h"
#include "ecourna/api/io/cfile.hpp"

namespace api {
namespace {

std::vector<uebyte> LeArquivo(const std::string& arquivo)
{
    return ecourna::api::io::CFile::ReadFileBinary(arquivo);
}

} // namespace


CFixedImage::CFixedImage(const std::string& arquivo)
{
    if (arquivo.empty()) {
        throw CUeGuiError(EUE_GUI_FIXEDIMAGE_NOME_VAZIO, "Nome do arquivo vazio");
    }

    if (!isResource(arquivo)) {
        m_dados = LeArquivo(arquivo);
    } else {
        m_dados.swap(*getResourceFile(arquivo));
    }
}

} // namespace api

// <stubs>
// f13441 · 386 B · unmatched · placement: link order · name unknown
// void f13441(i32) { ... }

// f3617 · 222 B · unmatched · placement: link order · name unknown
// void f3617() { ... }
// </stubs>
