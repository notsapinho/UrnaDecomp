#include "app/comum/dados/asn/candidatura/cvisitantefoto.h"
#include "app/comum/dados/euecomumdadoserror.h"
namespace comum::asn {

CVisitanteFoto::~CVisitanteFoto() = default;

// (original lines 7-29: content not recovered)
#line 30
ASN1::IAbstractVisitor::EVisitorResult CVisitanteFoto::visit(int /*indice*/, const std::string& caminho,
                                                              ASN1::AbstractData& dado, size_t posicao, size_t tamanho)
{

    // (original lines 34-36: content not recovered)
#line 37
    if (caminho == "EntidadeFotosCandidatos.fotos.OF") {

        if (m_sequenciador != 0)
            throw CUeComumDadosError(EUE_COMUM_DADOS_7883, "Sequenciador com valor errado para o carregamento de fotos do candidato.");
        m_sequenciador = 1;
        m_indice = SIndiceFoto(posicao, tamanho);


    } else if (caminho == "EntidadeFotosCandidatos.fotos.codigoCandidato") {

        if (m_sequenciador != 1)
            throw CUeComumDadosError(EUE_COMUM_DADOS_7884, "Sequenciador com valor errado para o carregamento de codigo do candidato.");
        m_sequenciador = 0;

        // (original lines 51-52: content not recovered)
#line 53
        const ASN1::AbstractString* codigo = dynamic_cast<const ASN1::AbstractString*>(&dado);

        if (codigo == nullptr)
            throw CUeComumDadosError(EUE_COMUM_DADOS_7885, "Erro ao carregar codigo do candidato.");

        md::CIndiceFoto indice(codigo->c_str(), m_indice);
        m_indices.push_back(indice);


    } else {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7886, "Entidade visitada invalida " + caminho);
    }

    return CONSUMIDO;
}

} // namespace comum::asn
