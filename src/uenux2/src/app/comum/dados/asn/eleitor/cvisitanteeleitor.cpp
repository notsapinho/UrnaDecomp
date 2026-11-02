// Reconstruction: comum::asn::CVisitanteEleitor's destructor (target fns 5698 and 11408) and visit (11407), whose
// record is line 91. Where each function starts is a choice. Fragment 225 has the rest.
#include "app/comum/dados/asn/eleitor/cvisitanteeleitor.h"

#include "app/comum/dados/euecomumdadoserror.h"
#include "asn1/modules/ModuloTiposEleitorais.h"

namespace comum::asn {

// (original lines 10-55: content not recovered)
#line 56
CVisitanteEleitor::~CVisitanteEleitor() = default;

// (original lines 58-61: content not recovered)
#line 62
ASN1::IAbstractVisitor::EVisitorResult CVisitanteEleitor::visit(int, const std::string& path, ASN1::AbstractData& data,
                                                                size_t position, size_t length)
{
    if (path == "EntidadeEleitores.eleitores.eleitor.identificacaoEleitor.OF") {
        const auto& identificador = static_cast<const ModuloTiposEleitorais::IdentificadorEleitor&>(data);
        if (identificador.numeroInscricao_isSelected()) {
            m_inscricao = identificador.get_numeroInscricao();
        }
        if (identificador.numeroCPF_isSelected()) {
            m_cpf = identificador.get_numeroCPF();
        }
        if (identificador.identificacaoLivre_isSelected()) {
            m_identificacaoLivre = identificador.get_identificacaoLivre();
        }
        return NAO_CONSUMIDO;
    }
    if (path == "EntidadeEleitores.eleitores.eleitor.biometria") {
        m_biometria = md::CIndexer(position, length);
        if (!m_inscricao.empty()) {
            m_identidades.insert({md::CEleitorIdentidade(m_inscricao, ecourna::app::dados::TipoIDInscricaoEleitoral), m_biometria});
        }
        if (!m_cpf.empty()) {
            m_identidades.insert({md::CEleitorIdentidade(m_cpf, ecourna::app::dados::TipoIDCPF), m_biometria});
        }
        if (!m_identificacaoLivre.empty()) {
            m_identidades.insert({md::CEleitorIdentidade(m_identificacaoLivre, ecourna::app::dados::TipoIDNumeroLivre), m_biometria});
        }
        return CONSUMIDO;
    }
    throw CUeComumDadosError(EUE_COMUM_DADOS_7905, "Entidade visitada inválida: " + path);
}

} // namespace comum::asn
