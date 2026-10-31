#pragma once

#include <string>

#include "app/comum/dados/md/estadoaplicacao/clocalidadeeleitoral.h"
#include "app/comum/etipolocalvotacao.h"

namespace comum::md::estadoaplicacao {

// The fields of ModuloEstadoGeralUrna::DadoLocal: the state at +0, the section at +12, the kind of place at +20
// (target fn 5632, the constructor, and comum::asn::CConversorDadoLocal, target fns 11403, 11404). The constructor moves
// the string it takes by value and copies the section with one i64 load. No record names the class's file; its path
// is chosen, beside the classes of the family. The member and getter names follow the entity's fields.
class CDadoLocal {
public:
    CDadoLocal(std::string uf, const CLocalidadeEleitoral& secaoCarga, ETipoLocalVotacao tipoLocalVotacao);

    const std::string& GetUF() const { return m_uf; }
    const CLocalidadeEleitoral& GetSecaoCarga() const { return m_secaoCarga; }
    ETipoLocalVotacao GetTipoLocalVotacao() const { return m_tipoLocalVotacao; }

private:
    std::string m_uf;
    CLocalidadeEleitoral m_secaoCarga;
    ETipoLocalVotacao m_tipoLocalVotacao;
};

} // namespace comum::md::estadoaplicacao
