#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/clocal.h"
#include "asn1/modules/ModuloLocal.h"

namespace comum::asn {

// Recovered: the class and its two slots, named by its RTTI (typeinfo 1562012, vtable 1561988), whose base is
// IConversorASN<ModuloLocal::Local, comum::md::CLocal>: DoConverte (slot 2, target fn 11451) and DoDesconverte (slot 3,
// fn 11452). Their records (cconversorlocal.cpp:70, :120 to :128) spell the results ModuloLocal::Local and md::CLocal.
// No record names this header: its path, beside the .cpp, is chosen.
class CConversorLocal : public IConversorASN<ModuloLocal::Local, md::CLocal> {
protected:
    ModuloLocal::Local DoConverte(const TDado& dado) const override;
    md::CLocal DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
