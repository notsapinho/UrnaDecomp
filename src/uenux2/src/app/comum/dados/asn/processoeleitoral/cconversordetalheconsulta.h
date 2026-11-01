#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/processoeleitoral/cdetalheconsulta.h"
#include "asn1/modules/ModuloEleicao.h"

namespace comum::asn {

// Reads a referendum question's details; the conversion the other way is the base's default DoConverte (the vtable's
// slot 2 is IConversorASN's, target fn 11376). RTTI names the class and its base (vtable @1569764). No record names its
// file: the directory mirrors md::CDetalheConsulta's (docs/how-to-decompile.md step 3, rule 3) and the file name is the
// class's, both chosen.
class CConversorDetalheConsulta : public IConversorASN<ModuloEleicao::DetalhePergunta, md::CDetalheConsulta> {
protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
