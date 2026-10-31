#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "asn1/modules/ModuloEstadoGeralUrna.h"

namespace comum::asn {

// RTTI names the class and its base (vtable @1568016). comum::asn::CConversorEstadoGeral::DoConverte (target fn 11397)
// builds one on its stack, the constructor inlined. Its two slots, DoConverte and DoDesconverte (target fns 11399 and
// 11400), are not reconstructed: 124-uenux2-app-comum-dados-asn-pending.cpp traps them. No record names this header's
// path: the directory is the family's, the file name the class's, chosen.
class CConversorDadoCorrespondencia
    : public IConversorASN<ModuloEstadoGeralUrna::DadoCorrespondencia, md::estadoaplicacao::CDadoCorrespondencia> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
