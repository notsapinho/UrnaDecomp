#pragma once

#include <vector>

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/processoeleitoral/csituacoeseleicoes.h"
#include "asn1/modules/ModuloSituacoesEleicoes.h"

namespace comum::asn {

// Reads the situations of the elections of a pleito; the conversion the other way is the base's default DoConverte
// (the vtable's slot 2 is IConversorASN's, target fn 11360).
class CConversorSituacoesEleicoes
    : public IConversorASN<ModuloSituacoesEleicoes::EntidadeSituacoesEleicoes, std::vector<md::CSituacoesEleicoes>> {
protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
