#pragma once

// comum::CGeradorRelPU. Reconstruction notes, not TSE's text. RTTI names the class (typeinfo 1545296, no base), and its
// vtable (@1545280) holds the D2 and the D0 (fns 11901 and 11900, thunks into binaryen's merged bodies 6055 and 6054,
// which pass the vptr). Its one user, vota::CImpressaoPU's slot 2 (fn 11902, not reconstructed), builds it in its frame:
// the vptr at +0 and 12 zeroed bytes at +4, the api::CPaperFormBuilder that AdicionaParametro (fn 677) reaches at
// this + 4. The layout is a reading of those stores. The vtable and the typeinfo lie in CImpressaoPU's data, right after
// CImpressaoPU's own (@1545224, typeinfo 1545268), so the class has no key function (docs/reference/facts/reading.md
// R6): its destructor is inline, declared because the class has no base.
//
// Chosen: this header's and cgeradorrelpu.cpp's paths (the family's directory and the class's name in lower case), the
// name AdicionaParametro and its parameters, the member's name and the access.

#include <string>

#include "api/gui/cpaperformbuilder.h"

namespace comum {

class CGeradorRelPU {
public:
    virtual ~CGeradorRelPU() = default;

    void AdicionaParametro(const std::string& nome, const std::string& valor);

private:
    api::CPaperFormBuilder m_builder;
};

} // namespace comum
