#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/rdv/cvoto.h"
#include "asn1/modules/ModuloRegistroDigitalVoto.h"

namespace comum::asn {

// RTTI names the class and its base (vtable @1570808, slots 2 and 3 target fns 11355 and 11354); the records name the
// file and the two static helpers (cconversorvoto.cpp:44, :71 and :75), which binaryen inlined into the slots.
class CConversorVoto : public IConversorASN<ModuloRegistroDigitalVoto::Voto, md::CVoto> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    static ModuloRegistroDigitalVoto::TipoVoto ConverteTipo(md::CVoto::ETipo tipo);
    static md::CVoto::ETipo DesconverteTipo(ModuloRegistroDigitalVoto::TipoVoto tipo);
};

} // namespace comum::asn
