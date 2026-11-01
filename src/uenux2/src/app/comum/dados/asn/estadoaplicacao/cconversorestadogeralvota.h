#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "asn1/modules/ModuloEstadoGeralVota.h"

namespace comum::asn {

// RTTI names the class and its base (vtable @1568960; fns 5329 and 7787 store its vptr). The records of
// cconversorestadogeralvota.cpp name the four private helpers and their signatures. No record names this header: its
// path is chosen, beside the .cpp.
class CConversorEstadoGeralVota
    : public IConversorASN<ModuloEstadoGeralVota::EstadoGeralVota, md::estadoaplicacao::CEstadoGeralVota> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    ModuloEstadoGeralVota::EstadoVota ConverteEstadoVota(const EEstadoVota estado) const;
    EEstadoVota DesconverteEstadoVota(const ModuloEstadoGeralVota::EstadoVota& estado) const;
    ModuloEstadoGeralVota::EstadoEncerramento ConverteEstadoEncerramento(const EEstadoEncerramento estado) const;
    EEstadoEncerramento DesconverteEstadoEncerramento(const ModuloEstadoGeralVota::EstadoEncerramento& estado) const;
};

} // namespace comum::asn
