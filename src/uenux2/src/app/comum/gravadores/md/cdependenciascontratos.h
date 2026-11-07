#pragma once

#include <string>

#include "api/io/cinifile.h"

namespace comum::md {

// Reconstruction: the records name the class, its constructor (cdependenciascontratos.cpp:27, which target fn 12098
// holds inlined: it runs the INI loader, fn 5480, on the object, then reads one value with GetValor and throws when it
// is not the one expected) and GetValor (line 59, fn 3826, a thunk of fn 6044, the body binaryen merged with
// CVersoesContratos::GetValor's). The object is the INI file it reads, 24 bytes: GetValor passes its own address to the
// key map's find and end (fn 6044), and comum::CGeracaoVersoesContratos holds the class at +0 (fns 12098 and 5866).
// Chosen: that the INI object is a member (a base would give the same layout; not measured), the member's and the
// parameters' names. The constructor is written in cdependenciascontratos.cpp, unrooted: its one caller, fn 12098,
// holds it inlined and is not written (the loader, fn 5480, is: src/units/379-uenux2-cinifile.mk).
class CDependenciasContratos {
public:
    CDependenciasContratos(const std::string& arquivo);

    const std::string GetValor(const std::string& chave);

private:
    api::CIniFile m_arquivo;
};

} // namespace comum::md
