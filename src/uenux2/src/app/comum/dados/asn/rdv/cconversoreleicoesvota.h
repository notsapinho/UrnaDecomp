#pragma once

#include <map>
#include <vector>

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/comum/dados/md/rdv/cvotoseleicoesvota.h"
#include "asn1/modules/ModuloRegistroDigitalVoto.h"

namespace comum::asn {

// Converts the votes of an RDV's elections. RTTI names the class and its base (vtable @1571216); the records name the
// file (cconversoreleicoesvota.cpp:34 and :46, DoConverte; :69, :74, :94 and :104, DoDesconverte). The layout, 16 bytes,
// is what the destructors read (fns 11348 and 11347): a map from each election to its cargos at +4, destroyed by fn
// 1160, whose nodes hold a vector of 140-byte md::CCargo; DoConverte (fn 11350) looks an election up in it by its
// 32-bit id. The D2 does not begin with the class's vptr store, so the class is final. The constructor is not
// recovered (fn 7787 holds it). The member's name and the map's alias are chosen.
class CConversorEleicoesVota final : public IConversorASN<ModuloRegistroDigitalVoto::Eleicoes, md::CVotosEleicoesVota> {
public:
    using TCargosEleicao = std::map<md::TEleicaoID, std::vector<md::CCargo>>;

protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    TCargosEleicao m_cargos;
};

} // namespace comum::asn
