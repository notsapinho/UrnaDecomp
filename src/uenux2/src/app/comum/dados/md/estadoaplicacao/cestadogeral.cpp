// Reconstruction's note: of comum::md::estadoaplicacao::CEstadoGeral's members this file holds only the constructor
// (target fn 5637), GetDadosQRCode (5636), SetAjusteDataHora (3705) and GetResumoHashVersoesPacotes (3703), the last
// three chosen names: no record, slot or RTTI names them. Line 147 is the record of RecuperarCertificado (fn 5635, not
// written) and holds its generated stub's last line; the lines of the members before it and after it are a choice
// (src/units/215-uenux2-api-app-leftovers.mk says what orders them).
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"

#include <cctype>

#include "ecourna/api/security/base64.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::md::estadoaplicacao {

CEstadoGeral::CEstadoGeral(EEstadoUrna estadoUrna, uedword idPE, CDadoLocal dadoLocal, CDadoCarga dadoCarga,
                           CAjusteDataHora ajusteDataHora, const CDadoCorrespondencia& correspondencia,
                           std::string versao, std::vector<uebyte> hashVersoesPacotes)
    : m_estadoUrna(estadoUrna),
      m_idPE(idPE),
      m_dadoLocal(std::move(dadoLocal)),
      m_dadoCarga(dadoCarga),
      m_ajusteDataHora(ajusteDataHora),
      m_correspondencia(correspondencia),
      m_versao(std::move(versao)),
      m_hashVersoesPacotes(std::move(hashVersoesPacotes))
{
}

// (original lines 29-110: content not recovered)
#line 111
std::vector<std::pair<std::string, std::string>> CEstadoGeral::GetDadosQRCode() const
{
    std::vector<std::pair<std::string, std::string>> dados;
    dados.push_back(std::make_pair("PROC", std::to_string(m_idPE)));
    const EUrnaTipo tipoUrna = m_dadoCarga.GetTipoUrna();
    if (tipoUrna != eUrnaContingencia && tipoUrna != eUrnaContingenciaVotaRecupera) {
        dados.push_back(std::make_pair("TURN", std::to_string(m_dadoCarga.GetTurno() == TURNO_1 ? 1 : 2)));
    }
    dados.push_back(std::make_pair("FASE", std::string(1, toupper(m_dadoCarga.GetFaseChar()))));
    dados.push_back(std::make_pair("UNFE", m_dadoLocal.GetUF()));
    const CLocalidadeEleitoral& secao = m_dadoLocal.GetSecaoCarga();
    dados.push_back(std::make_pair("MUNI", std::to_string(secao.GetMunicipio())));
    dados.push_back(std::make_pair("ZONA", std::to_string(secao.GetZona())));
    if (tipoUrna == eUrnaVota || tipoUrna == eUrnaContingenciaVota) {
        dados.push_back(std::make_pair("SECA", std::to_string(secao.GetSecao())));
    }
    dados.push_back(std::make_pair("IDUE", std::to_string(m_correspondencia.GetNumeroInternoUrna())));
    dados.push_back(std::make_pair("MDUE", std::to_string(m_dadoCarga.GetModelo())));
    dados.push_back(std::make_pair("IDFL", m_correspondencia.GetNumeroSerieFC()));
    dados.push_back(std::make_pair("IDCA", m_correspondencia.GetCodigoCarga()));
    dados.push_back(std::make_pair("DTCA", m_correspondencia.GetDataHoraCarga().GetData().Format("YYYYMMDD")));
    dados.push_back(std::make_pair("HRCA", m_correspondencia.GetDataHoraCarga().GetHora().Format("hhmmss")));
    const ecourna::app::dados::CIdentificadorGeradorMidia& gerador = m_correspondencia.GetIdentificadorGeradorMidia();
    dados.push_back(std::make_pair("NOME", gerador.GetNome()));
    dados.push_back(std::make_pair("SERT", gerador.GetSerialCertificadoTPM()));
    dados.push_back(std::make_pair("SERI", gerador.GetSerialInstalacao()));
    dados.push_back(
        std::make_pair("ASSI", ecourna::api::util::CStringUtils::BytesToHexString(m_correspondencia.GetAssinatura())));
    return dados;
}

// (original lines 142-143: content not recovered)
#line 144
// <stubs>
// f5635 · 279 B · unmatched · name unknown
// void f5635(i32) { ... }
// </stubs>

void CEstadoGeral::SetAjusteDataHora(const CAjusteDataHora& ajusteDataHora)
{
    m_ajusteDataHora = ajusteDataHora;
}

std::string CEstadoGeral::GetResumoHashVersoesPacotes() const
{
    const std::string hash = ecourna::api::security::EncodeBase64(m_hashVersoesPacotes);
    return hash.substr(0, 8);
}

} // namespace comum::md::estadoaplicacao
