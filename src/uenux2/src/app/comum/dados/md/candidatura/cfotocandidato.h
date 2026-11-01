#pragma once

#include <string>

#include "ecourna/app/dados/cfoto.hpp"

namespace comum::md {

// A candidate's photo. Recovered: the layout only, 28 bytes, from comum::asn::CConversorFotoCandidato::DoDesconverte
// (target fn 11440), which builds one from the entity's codigoCandidato (a copy of the string at +0) and the
// ecourna::app::dados::CFoto that the ecourna converter on its stack (CConversorFoto, vptr 1122824) gives through fn
// 5708 (its format word at +12, its image vector at +16). The record cfotos.cpp:39 names the type as the result of
// comum::GetFotoPara. No record names this file: the path is that of the class's family (md/candidatura/), and the
// members' names are chosen. The constructor has no target function of its own: fn 11440 holds it, inlined by binaryen
// (it reads the photo's vector back from the frame after copying it, a sign docs/reference/facts/reading.md R10 lists),
// so it is out of line in cfotocandidato.cpp, a path no record names; that it takes both by reference is chosen.
class CFotoCandidato {
public:
    CFotoCandidato(const std::string& codigo, const ecourna::app::dados::CFoto& foto);

private:
    std::string m_codigo;
    ecourna::app::dados::CFoto m_foto;
};

} // namespace comum::md
