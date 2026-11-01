#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/processoeleitoral/celeicaope.h"
#include "asn1/modules/ModuloEleicao.h"

namespace comum::asn {

// Reads an election of the electoral process; the conversion the other way is the base's default DoConverte (the
// vtable's slot 2 is IConversorASN's, target fn 11370). RTTI names the class and its base (vtable @1570088). No record
// names its file: the directory mirrors md::CEleicaoPE's (docs/how-to-decompile.md step 3, rule 3) and the file name is
// the class's, both chosen.
class CConversorEleicaoPE : public IConversorASN<ModuloEleicao::EntidadeEleicao, md::CEleicaoPE> {
protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
