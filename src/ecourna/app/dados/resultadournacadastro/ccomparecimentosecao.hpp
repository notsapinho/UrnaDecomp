#pragma once
#include <vector>

#include "ecourna/app/dados/cidentificacaosecaoeleitoral.hpp"
#include "ecourna/app/dados/resultadournacadastro/cestadocomparecimento.hpp"

namespace ecourna::app::dados {

using TVectorEstadoComparecimento = std::vector<CEstadoComparecimento>;

// The section's attendance: the section (@0, 16 B) and one CEstadoComparecimento (96 B) per voter (@16). 28 bytes.
class CComparecimentoSecao {
public:
    CComparecimentoSecao(const CIdentificacaoSecaoEleitoral& identificacao, const TVectorEstadoComparecimento& eleitores);

    const CIdentificacaoSecaoEleitoral& GetIdentificacao() const { return m_identificacao; }
    const TVectorEstadoComparecimento& GetEleitores() const { return m_eleitores; }

private:
    CIdentificacaoSecaoEleitoral m_identificacao;
    TVectorEstadoComparecimento m_eleitores;
};

} // namespace ecourna::app::dados
