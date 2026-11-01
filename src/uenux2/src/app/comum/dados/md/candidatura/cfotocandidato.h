#pragma once

#include <string>

#include "ecourna/app/dados/cfoto.hpp"

namespace comum::md {

// A candidate's photo. Recovered: the layout only, 28 bytes, from comum::asn::CConversorFotoCandidato::DoDesconverte
// (target fn 11440), which builds one from the entity's codigoCandidato (a copy of the string at +0) and the
// ecourna::app::dados::CFoto that the ecourna converter on its stack (CConversorFoto, vptr 1122824) gives through fn
// 5708 (its format word at +12, its image vector at +16). The record cfotos.cpp:39 names the type as the result of
// comum::GetFotoPara. No record names this file: the path is that of the class's family (md/candidatura/), and the
// members' names are chosen. The constructor is not recovered, so nothing may construct the class.
class CFotoCandidato {
private:
    std::string m_codigo;
    ecourna::app::dados::CFoto m_foto;
};

} // namespace comum::md
