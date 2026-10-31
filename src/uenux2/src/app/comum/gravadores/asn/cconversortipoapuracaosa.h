#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/gravadores/md/ctipoapuracaosa.h"
#include "asn1/modules/ModuloTiposResultadosEcoUrna.h"

namespace comum::asn {

// RTTI: comum::asn::CConversorTipoApuracaoSA, an si_class of IConversorASN<ModuloTiposResultadosEcoUrna::TipoApuracaoSA,
// comum::md::CTipoApuracaoSA>; vtable @1596856, DoConverte (fn 10283) in slot 2 and DoDesconverte (fn 10282) in slot 3.
// The four ConverteMotivo* members are declared as their records (cconversortipoapuracaosa.cpp:98, :117, :140, :165)
// print them; binaryen inlines them into DoConverte, their one caller (the target's DoConverte holds their stack
// frames, and our object keeps them out of line). That they are private is a choice. The path is chosen, beside the
// .cpp its records name.
class CConversorTipoApuracaoSA : public IConversorASN<ModuloTiposResultadosEcoUrna::TipoApuracaoSA, md::CTipoApuracaoSA> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    ModuloTiposResultadosEcoUrna::MotivoApuracaoManual ConverteMotivoApuracaoManual(const uebyte motivo) const;
    ModuloTiposResultadosEcoUrna::MotivoApuracaoEletronica ConverteMotivoApuracaoEletronica(const uebyte motivo) const;
    ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComBU ConverteMotivoApuracaoBU(const uebyte motivo) const;
    ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComMR ConverteMotivoApuracaoMR(const uebyte motivo) const;
};

} // namespace comum::asn
