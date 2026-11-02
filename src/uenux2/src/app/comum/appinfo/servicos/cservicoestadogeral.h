#pragma once

#include "app/comum/appinfo/servicos/iservicoestado.h"
#include "app/comum/eflashorigem.h"

namespace comum::md::estadoaplicacao {

class CEstadoGeral;

} // namespace comum::md::estadoaplicacao

namespace comum::asn {

class CConversorEstadoGeral;

} // namespace comum::asn

namespace comum {

// RTTI names the class and its base (vtable @1558016, slot 2 target fn 11569). The constructor (fn 1941) stores the
// origin at +4 and the vptr; GetPathArquivo reads the origin there. Both are out of line in cservicoestadogeral.cpp, a
// reading for the constructor from the target keeping it as a function of its own that five functions call (2273, 3333,
// 3897, 10243, 11572). The parameter's and the data member's type are chosen as the origin GetPathDinamico takes, and
// so are the member's name and this header's and the source's paths (src/units/206-uenux2-app-comum-appinfo-servicos.mk
// says why).
class CServicoEstadoGeral : public IServicoEstado<md::estadoaplicacao::CEstadoGeral, asn::CConversorEstadoGeral> {
public:
    explicit CServicoEstadoGeral(EFlashOrigem origem);

    std::filesystem::path GetPathArquivo() override;

private:
    EFlashOrigem m_origem;
};

} // namespace comum
