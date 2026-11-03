#pragma once

// The reconstruction's note, not TSE's text. The reader of comum's entities through legravaentidade.h's templates. No
// record names it: the messages of legravaentidade.h's LeEntidadeBiometria and LeEntidadeEm read "CLeitorASN::{} - ..."
// with their caller's name for {}, which target fn 1937 (comum::CEleitorDetalhe::GetBiometria) builds as
// "LeBiometriaEleitor(" + the voter's identifier + ")" and fn 3755 (comum::CFotos::GetImagem, not written) as
// "LeFotoCandidato(" + ...: the class's name and LeBiometriaEleitor's are read from those texts. 1937 holds
// LeBiometriaEleitor behind a 576-byte frame of its own, an out-of-line function with one caller that binaryen inlined
// (docs/reference/facts/reading.md R10). It is defined in app/comum/dados/carregaarquivo.cpp, the TU of the other entity
// readers, where the target's data put the code that instantiates LeEntidadeBiometria
// (src/units/280-uenux2-processoeleitoral.mk has that evidence, src/units/98-uenux2-app-comum-dados.mk the forms
// measured). Chosen: that CLeitorASN is a class and LeBiometriaEleitor a static member, the parameters, and this
// header's path.
#include <string>

#include "app/comum/dados/md/eleitor/cbiometriaeleitor.h"

namespace comum::md {
class CParametro;
} // namespace comum::md

namespace comum {

class CLeitorASN {
public:
    static md::CBiometriaEleitor LeBiometriaEleitor(const std::string& arquivo, const md::CParametro& parametro);
};

} // namespace comum
