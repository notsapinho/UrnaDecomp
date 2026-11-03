#pragma once

// comum::CGeradorRelVersaoPacoteDados. Reconstruction notes, not TSE's text. RTTI names the class (typeinfo 1576308, no
// base) and its vtable (@1576276) holds six slots: the D2 (target fn 3691), the D0 (11224: the D2's call, then a free
// of this, so the destructor is out of line, how-to step 5), and fns 5592, 11223, 11222 and 5596. Slot 3 is
// ImprimeTituloJE: RTTI names a lambda of the class's ImprimeTituloJE() (typeinfo 1576372), a non-const member with no
// parameter, whose std::function's vtable (@1576316) fn 11223 alone stores. Its one user,
// vota::CImpressaoVersaoPacotes::StartState (fn 11905), builds it in its frame: 24 zeroed bytes at +4, the vptr, then a
// copy of the vector<md::CCabecalhoPacote> of the md::CDadosDisponiveisCarga it read; then it calls slot 2 directly
// with two strings and the D2. Slot 2 (fn 5592) calls slots 3, 4 and 5 through the vtable, then
// api::CPaperFormBuilder::Show (fn 3671) on this + 4 with its two strings; the D2 destroys the vector at +16 (fn 3863)
// and then the builder's vector at +4. Those stores give the layout: the builder at +4, the packages at +16.
//
// The constructor is out of line in the .cpp, a reading: 11905 holds it with its returned `this` in a second local
// (docs/reference/facts/reading.md R10's sign of binaryen's inlining); defined in the class it was not linked. The
// class is not final, a reading too: slot 2 calls slots 3 to 5 through the vtable, which clang would not leave on
// `this` of a final class.
//
// Chosen: the names Imprime, ImprimeVersoesPacotes and ImprimeRodape (slots 2, 4 and 5) and their parameters, the
// members' names and access, the constructor's being explicit, the destructor's empty body (`= default` out of line was
// not linked), the slots' constness but ImprimeTituloJE's (its lambda's mangled name has no const), and this header's
// path, beside the .cpp (src/units/287-uenux2-cgeradorrelversaopacotedados.mk says what places that).

#include <string>
#include <vector>

#include "api/gui/cpaperformbuilder.h"
#include "app/comum/md/ccabecalhopacote.h"

namespace comum {

class CGeradorRelVersaoPacoteDados {
public:
    explicit CGeradorRelVersaoPacoteDados(const std::vector<md::CCabecalhoPacote>& pacotes);
    virtual ~CGeradorRelVersaoPacoteDados();

    virtual void Imprime(const std::string& titulo, const std::string& subtitulo);

protected:
    virtual void ImprimeTituloJE();
    virtual void ImprimeVersoesPacotes();
    virtual void ImprimeRodape();

private:
    api::CPaperFormBuilder m_builder;
    std::vector<md::CCabecalhoPacote> m_pacotes;
};

} // namespace comum
