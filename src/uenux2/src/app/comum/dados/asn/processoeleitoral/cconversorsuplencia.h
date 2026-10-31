#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/processoeleitoral/csuplencia.h"
#include "asn1/modules/ModuloEleicao.h"

namespace comum::asn {

// Reads a cargo's substitute; the conversion the other way is the base's default DoConverte (the vtable's slot 2 is
// IConversorASN's, target fn 11358). RTTI names the class and its base (vtable @1570576); no record names its file:
// the directory mirrors md::CSuplencia's (docs/how-to-decompile.md step 3, rule 3), and the vtable lies among
// asn/processoeleitoral/'s converters, between CConversorSituacoesEleicoes' (@1570516) and
// CConversorTipoIdentificadorEleitor's (@1570668). The file name is the class's, chosen.
class CConversorSuplencia : public IConversorASN<ModuloEleicao::Suplencias, md::CSuplencia> {
protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
