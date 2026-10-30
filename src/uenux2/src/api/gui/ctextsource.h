#pragma once

// api::CTextSource. The path is evidence: the record of the constructor names it, line 37, column 19, with the signature
// `CTextSource(const std::shared_ptr<std::string> &)` (`awk -F'\t' '$2 ~ /ctextsource/' ledger/source-locations.tsv`).
// That record is the throw below, held inlined by fns 652, 1150, 5397 and 10740; fn 10740 gives its code, 4977, and its
// message, and it copies the two words and takes the reference before it tests, so the test follows the member's copy.
//
// The class's other two members are read from the two instantiations that hold them inlined, and their names are
// chosen: they are operator() because CDataText<T>::GetText and CDataTextFmt<T>::GetText call T that way for every
// other T. fn 10534 copies the string behind the pointer. fn 10746 formats into 512 bytes with the string as the one
// argument and returns the result as a std::string; that member carries `inline` because clang inlines it there. Without
// the keyword it stays out of line in the object and binaryen inlines it, which keeps the format string's address in a
// local and differs (docs/reference/facts/codegen.md C3; the fragment has the measurement).

#include <cstdio>
#include <memory>
#include <string>

#include "api/gui/eueguierror.h"

namespace api {

// (original lines 23-29: content not recovered)
#line 30
class CTextSource {
public:

    explicit CTextSource(const std::shared_ptr<std::string>& text)
        : m_text(text)
    {
        if (!m_text) {
            throw CUeGuiError(EUE_GUI_TEXTSOURCE_TEXTO_NULO, "Texto nulo");
        }
    }

    const std::string& operator()() const { return *m_text; }

    inline std::string operator()(const std::string& formato) const
    {
        char texto[512];
        snprintf(texto, sizeof(texto), formato.c_str(), m_text->c_str());
        return texto;
    }

private:
    std::shared_ptr<std::string> m_text;
};

} // namespace api
