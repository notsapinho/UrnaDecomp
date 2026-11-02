// Reconstruction: comum::md::CDadosDisponiveisCarga's constructor, which target fn 11423 holds inlined (its records, lines
// 41 to 69, column 15, place its throws), and CMunicipioDisponivel's, which has no record. Where each begins is chosen.
#include "app/comum/dados/md/correspondencia/cdadosdisponiveiscarga.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 9-24: content not recovered)
#line 25
CDadosDisponiveisCarga::CDadosDisponiveisCarga(EUrnaFase fase, comum::TProcessoEleitoralID idPE, comum::TPleitoID idPleito,
                                               const std::string& serialFlashCarga, const std::string& pais,
                                               const std::string& siglaUF, const std::string& nomeUF, comum::TZonaID zona,
                                               const std::vector<CMunicipioDisponivel>& municipios, const std::vector<CCabecalhoPacote>& pacotes)
    : m_fase(fase),
      m_idPE(idPE),
      m_idPleito(idPleito),
      m_serialFlashCarga(serialFlashCarga),
      m_pais(pais),
      m_siglaUF(siglaUF),
      m_nomeUF(nomeUF),
      m_zona(zona),
      m_municipios(municipios),
      m_pacotes(pacotes)
{
    if (m_fase == FASE_INDEFINIDA) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8040, "Fase inválida.");
    }
    if (m_idPE == 0) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8041, "Processo eleitoral inválido.");
    }


    if (m_idPleito == 0) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8042, "Pleito inválido.");
    }
    if (m_serialFlashCarga.size() != 8) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8043, "Serial da mídia de carga inválido.");
    }


    if (m_pais.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8044, "País em branco.");
    }
    if (m_siglaUF.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8045, "Sigla da uf em branco.");
    }
    if (m_nomeUF.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8046, "Nome da uf em branco.");
    }
    if (m_zona == 0) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8047, "Zona inválida.");
    }
    if (m_municipios.size() == 0) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8048, "Deve existir no mínimo um município.");
    }
}

CMunicipioDisponivel::CMunicipioDisponivel(const CInfoMunicipio& municipio, const std::vector<CSecaoEleitoral>& secoes)
    : m_municipio(municipio), m_secoes(secoes)
{
}

} // namespace comum::md
