#pragma once

// comum::CGeradorRelPU. Reconstruction notes, not TSE's text. RTTI names the class (typeinfo 1545296, no base), and its
// vtable (@1545280) holds the D2 and the D0 (fns 11901 and 11900, thunks into binaryen's merged bodies 6055 and 6054,
// which pass the vptr). Its one user, vota::CImpressaoPU's slot 2 (fn 11902), builds it in its frame: the vptr at +0
// and 12 zeroed bytes at +4, the api::CPaperFormBuilder that AdicionaParametro (fn 677) reaches at this + 4. The layout
// is a reading of those stores. The vtable and the typeinfo lie in CImpressaoPU's data, right after CImpressaoPU's own
// (@1545224, typeinfo 1545268), so the class has no key function (docs/reference/facts/reading.md R6): its destructor
// is inline, declared because the class has no base.
//
// 11902 then prints the report through the members below, none of them virtual (the vtable has two slots), all out of
// line in cgeradorrelpu.cpp: Imprime has no frame of its own (binaryen's inlining of a function with one caller leaves
// no sign then, a reading); ImprimeTituloJE, ImprimeParametros and ImprimeHorarios each sit in 11902 behind a stack
// frame of their own (48, 272 and 448 bytes: binaryen's inlining of a function with one caller); and 11902 calls fn
// 5596, comum::CGeradorRelVersaoPacoteDados::ImprimeRodape, on this object: ImprimeRodape below is that function's text
// over this class's builder, which binaryen merges into one body with it, as the target holds one body for both.
//
// Chosen: this header's and cgeradorrelpu.cpp's paths (the family's directory and the class's name in lower case), the
// names AdicionaParametro, Imprime, ImprimeTituloJE (after comum::CGeradorRelVersaoPacoteDados's slot 3, whose title
// block is of the same shape), ImprimeParametros, ImprimeHorarios and ImprimeRodape and their parameters, the members'
// being members, the member's name, the access and the destructor's `= default`.

#include <string>

#include "api/gui/cpaperformbuilder.h"

namespace ecourna::app::dados {
class CConfiguracaoMunicipio;
} // namespace ecourna::app::dados

namespace comum {

class CGeradorRelPU {
public:
    virtual ~CGeradorRelPU() = default;

    void Imprime(const std::string& titulo, const std::string& via);
    void AdicionaParametro(const std::string& nome, const std::string& valor);

private:
    void ImprimeTituloJE();
    void ImprimeParametros();
    void ImprimeHorarios(const ecourna::app::dados::CConfiguracaoMunicipio& municipio);
    void ImprimeRodape();

    api::CPaperFormBuilder m_builder;
};

} // namespace comum
