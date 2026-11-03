// Reconstruction notes: comum::md::CEleicaoPE's ValidaOrdem and GetCargos (target fns 3714 and 2257), on their records'
// lines 70 and 144; the constructor, ValidaNome and ValidaCargos, which fn 11371 holds inlined (fragment 299), with
// their records on lines 63, 79, 87 and 92, the constructor's lines a choice. GetIDsCargos and PossuiCargoCandidato
// (fns 5654 and 5653) have no record: their file and their place, after GetCargos, are a choice
// (src/units/88-uenux2-app-comum-dados-md-processoeleitoral.mk says what the band shows).
#include "app/comum/dados/md/processoeleitoral/celeicaope.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 14-49: content not recovered)
#line 50
CEleicaoPE::CEleicaoPE(TEleicaoID id, unsigned int idPleito, TEleicaoID idEleicaoPleito2, const std::string& nome,
                       ETipoAbrangencia abrangencia, const TVectorCargo& cargos,
                       const std::vector<unsigned int>& municipios)
    : m_id(id), m_idPleito(idPleito), m_idEleicaoPleito2(idEleicaoPleito2), m_nome(nome), m_abrangencia(abrangencia),
      m_cargos(cargos), m_municipios(municipios)
{
    ValidaNome();
    ValidaCargos();
}

void CEleicaoPE::ValidaNome() const
{
    if (m_nome.empty() || m_nome.size() > 38) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8149, "Nome inválido.");
    }
}

void CEleicaoPE::ValidaOrdem(std::set<uebyte>& ordens, uebyte ordem, const std::string& nome) const
{
    if (!ordens.insert(ordem).second) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8153, std::format("Ordem de {} com valor {} repetido", nome, ordem));
    }
}

// (original lines 74-75: content not recovered)
#line 76
void CEleicaoPE::ValidaCargos() const
{
    if (m_cargos.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8150, "Lista de cargos vazia.");
    }
    std::set<TCargoID> ids;
    std::set<uebyte> ordensImpressao;
    std::set<uebyte> ordensAquisicao;
    std::set<uebyte> ordensApuracao;
    for (const CCargo& cargo : m_cargos) {
        if (m_abrangencia != cargo.GetAbrangencia()) {
            throw CUeComumDadosError(EUE_COMUM_DADOS_8151, "Há cargos com abrangência diferente.");
        }


        if (!ids.insert(cargo.GetID()).second) {
            throw CUeComumDadosError(EUE_COMUM_DADOS_8152, "Há cargos com mesmo identificador.");
        }
        ValidaOrdem(ordensImpressao, cargo.GetOrdemImpressao(), "impressão");
        ValidaOrdem(ordensAquisicao, cargo.GetOrdemAquisicao(), "aquisição");
        ValidaOrdem(ordensApuracao, cargo.GetOrdemApuracao(), "apuração");
    }
}

// (original lines 100-140: content not recovered)
#line 141
const TVectorCargo& CEleicaoPE::GetCargos() const
{
    if (m_cargos.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8154, "Eleição não tem cargos definidos.");
    }
    return m_cargos;
}

std::set<TCargoID> CEleicaoPE::GetIDsCargos() const
{
    std::set<TCargoID> ids;
    for (size_t i = 0; i < m_cargos.size(); ++i) {
        ids.insert(m_cargos[i].GetID());
    }
    return ids;
}

bool CEleicaoPE::PossuiCargoCandidato() const
{
    for (size_t i = 0; i < m_cargos.size(); ++i) {
        if (m_cargos[i].HasDetalheCandidato()) {
            return true;
        }
    }
    return false;
}

} // namespace comum::md
