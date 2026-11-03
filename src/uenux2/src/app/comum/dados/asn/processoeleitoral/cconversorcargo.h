#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "asn1/modules/ModuloEleicao.h"

namespace comum::asn {

// Reads an office's question; the conversion the other way is the base's default DoConverte (the vtable's slot 2 is
// IConversorASN's, target fn 11372). RTTI names the class and its base (vtable @1569964); records put DoDesconverte (fn
// 11373) in cconversorcargo.cpp, and this header beside it is a chosen path. DoDesconverte stores the word at +4 of the
// converter as the office's abrangencia (+8 of md::CCargo), so the class holds it; its name is chosen.
// DesconverteTipoCargo is a record's (cconversorcargo.cpp:83), static. The constructor is out of line in
// cconversorcargo.cpp, as measured (fragments 191 and 299: inline, fn 11371 scores 91 over 1512; out of line, 84 over
// 1509); binaryen inlines it into 11371, which stores the vptr and the abrangencia on its frame; explicit is chosen.
class CConversorCargo : public IConversorASN<ModuloEleicao::CargoPergunta, md::CCargo> {
public:
    explicit CConversorCargo(md::ETipoAbrangencia abrangencia);

protected:
    md::CCargo DoDesconverte(const TEntidade& entidade) const override;

private:
    static md::CCargo::ETipo DesconverteTipoCargo(ModuloTiposEleitorais::TipoCargoConsulta::NamedNumber tipo);

    md::ETipoAbrangencia m_abrangencia;
};

} // namespace comum::asn
