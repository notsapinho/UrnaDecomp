#pragma once

#include <string>

#include "app/comum/dados/md/estadoaplicacao/clocalidadeeleitoral.h"
#include "app/comum/etipolocalvotacao.h"

namespace comum::teste {
class CAppInfoBuilder;
}

namespace comum::md::estadoaplicacao {

// The fields of ModuloEstadoGeralUrna::DadoLocal: the state at +0, the section at +12, the kind of place at +20
// (target fn 5632, the constructor, and comum::asn::CConversorDadoLocal, target fns 11403, 11404). The constructor moves
// the string it takes by value and copies the section with one i64 load. No record names the class's file; its path
// is chosen, beside the classes of the family. The member and getter names follow the entity's fields.
class CDadoLocal {
public:
    // The default: "EE" (literal 331321, the tail of another), the default locality and LOCAL_VOTACAO_NORMAL, which
    // target fn 10268 stores at +8 to +28 of the builder's state (comum::teste::CAppInfoBuilder). Read as inline.
    CDadoLocal() : m_uf("EE"), m_tipoLocalVotacao(LOCAL_VOTACAO_NORMAL) {}
    CDadoLocal(std::string uf, const CLocalidadeEleitoral& secaoCarga, ETipoLocalVotacao tipoLocalVotacao);

    const std::string& GetUF() const { return m_uf; }
    const CLocalidadeEleitoral& GetSecaoCarga() const { return m_secaoCarga; }
    ETipoLocalVotacao GetTipoLocalVotacao() const { return m_tipoLocalVotacao; }

private:
    // The builder writes the UF and the locality directly (votaInit, target fn 7840; fn 10176): chosen.
    friend class teste::CAppInfoBuilder;

    std::string m_uf;
    CLocalidadeEleitoral m_secaoCarga;
    ETipoLocalVotacao m_tipoLocalVotacao;
};

} // namespace comum::md::estadoaplicacao
