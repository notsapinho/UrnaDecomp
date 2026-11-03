// Reconstruction: setters and tests of comum::CCabecalhoQRCodeBuilder under chosen names: DefineCodigoCarga,
// DefineHistoricoCarga, DefineIdUrna, DefineSecao and DefineZona (target fns 5623, 5622, 5621, 5620, 5618), IsOrigemSA
// and IsOrigemRED (5617, 5616); the setters comum::CGeradorBUQRCode::GetCabecalho calls, preBuild() with its lambda (fn
// 2791, its record at line 284) and build(), which binaryen inlined into fn 5604 (each has one caller there; the
// setters leave a stack frame of their own), under chosen names too. That the members sit above line 284 is a choice;
// the first seven's order is the target's, the higher target index first in the object.
#include "app/comum/relatorios/ccabecalhoqrcodebuilder.h"

#include <cctype>
#include <format>
#include <functional>
#include <string_view>
#include <utility>

#include "api/util/cstringutils.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

using namespace std::string_view_literals;
CCabecalhoQRCodeBuilder::CCabecalhoQRCodeBuilder()
{
}

void CCabecalhoQRCodeBuilder::DefineCodigoCarga(const std::string& codigoCarga)
{
    m_codigoCarga = std::format("IDCA:{:.24s} ", codigoCarga);
}

void CCabecalhoQRCodeBuilder::DefineHistoricoCarga(const std::vector<std::string>& cargas)
{
    m_historicoCarga = std::format("HIQT:{} ", cargas.size());
    unsigned indice = 0;
    for (const std::string& carga : cargas) {
        m_historicoCarga += std::format("HICA:{}:{:.24s} ", ++indice, carga);
    }
}

void CCabecalhoQRCodeBuilder::DefineIdUrna(uedword idUrna)
{
    m_idUrna = std::format("IDUE:{} ", idUrna);
}

void CCabecalhoQRCodeBuilder::DefineSecao(ueword secao)
{
    m_secao = std::format("SECA:{} ", secao);
}

void CCabecalhoQRCodeBuilder::DefineZona(ueword zona)
{
    m_zona = std::format("ZONA:{} ", zona);
}

bool CCabecalhoQRCodeBuilder::IsOrigemSA() const
{
    return m_origem == std::format("ORIG:{} ", "SA"sv);
}

bool CCabecalhoQRCodeBuilder::IsOrigemRED() const
{
    return m_origem == std::format("ORIG:{} ", "RED"sv);
}

void CCabecalhoQRCodeBuilder::DefineOrigemProcessoEleitoralCOM()
{
    m_origemProcessoEleitoral = std::format("ORLC:{} ", "COM"sv);
}

void CCabecalhoQRCodeBuilder::DefineOrigemProcessoEleitoralLEG()
{
    m_origemProcessoEleitoral = std::format("ORLC:{} ", "LEG"sv);
}

void CCabecalhoQRCodeBuilder::DefineProcessoEleitoral(unsigned processo)
{
    m_processoEleitoral = std::format("PROC:{} ", processo);
}

void CCabecalhoQRCodeBuilder::DefineDataPleito(const api::CDate& data)
{
    m_dataPleito = std::format("DTPL:{} ", data.Format("YYYYMMDD"));
}

void CCabecalhoQRCodeBuilder::DefinePleito(unsigned pleito)
{
    m_pleito = std::format("PLEI:{} ", pleito);
}

void CCabecalhoQRCodeBuilder::DefineTurno(EUrnaTurno turno)
{
    m_turno = std::format("TURN:{} ", static_cast<char>(turno));
}

void CCabecalhoQRCodeBuilder::DefineFase(char fase)
{
    m_fase = std::format("FASE:{:c} ", std::toupper(fase));
}

void CCabecalhoQRCodeBuilder::DefineUF(const std::string& uf)
{
    m_uf = std::format("UNFE:{:2s} ", uf);
    ecourna::api::util::CStringUtils::ToUpper(m_uf);
}

void CCabecalhoQRCodeBuilder::DefineVersaoSoftware(const std::string& versao)
{
    m_versaoSoftware = std::format("VERS:{} ", api::CStringUtils::GetVersionNumber(versao));
}

// (original lines 111-276: content not recovered)
#line 277
void CCabecalhoQRCodeBuilder::preBuild() const
{
    const auto valida =
        [](
            const std::vector<std::pair<std::reference_wrapper<const std::string>, std::string>>& campos) {
                for (const auto& [valor, nome] : campos) {
                    if (valor.get().empty()) {
                        throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9050, std::format("Campo ({}) não informado.", nome));
                    }
                }
            };
    valida({{m_origem, "Origem"},
            {m_origemProcessoEleitoral, "OrigemProcessoEleitoral"},
            {m_processoEleitoral, "ProcessoEleitoral"},
            {m_dataPleito, "DataPleito"},
            {m_pleito, "Pleito"},
            {m_turno, "Turno"},
            {m_fase, "Fase"},
            {m_uf, "Uf"},
            {m_municipio, "Municipio"},
            {m_zona, "Zona"},
            {m_secao, "Secao"},
            {m_idUrna, "IdUrna"},
            {m_codigoCarga, "CodigoCarga"},
            {m_historicoCarga, "HistoricoCarga"},
            {m_versaoSoftware, "VersaoSoftware"}});
    if (IsOrigemSA()) {
        valida({{m_junta, "Junta"}, {m_turma, "Turma"}, {m_dataEmissao, "DataEmissao"}, {m_horaEmissao, "HoraEmissao"}});
    } else {
        valida({{m_local, "Local"},
                {m_qtdeAptos, "QtdeAptos"},
                {m_qtdeAptosDaSecao, "QtdeAptosDaSecao"},
                {m_qtdeAptosTTE, "QtdeAptosTTE"},
                {m_qtdeCompareceram, "QtdeCompareceram"},
                {m_qtdeFaltosos, "QtdeFaltosos"}});
        if (IsOrigemRED()) {
            valida({{m_dataEmissao, "DataEmissao"}, {m_horaEmissao, "HoraEmissao"}});
        }
    }
}

std::string CCabecalhoQRCodeBuilder::build() const
{
    preBuild();
    std::string cabecalho = "";
    cabecalho.append(m_origem)
        .append(m_origemProcessoEleitoral)
        .append(m_processoEleitoral)
        .append(m_dataPleito)
        .append(m_pleito)
        .append(m_turno)
        .append(m_fase)
        .append(m_uf)
        .append(m_municipio)
        .append(m_zona)
        .append(m_secao);
    if (!m_campo132.empty()) {
        cabecalho.append(m_campo132);
    }
    cabecalho.append(m_idUrna).append(m_codigoCarga).append(m_historicoCarga).append(m_versaoSoftware);
    if (IsOrigemSA()) {
        cabecalho.append(m_junta).append(m_turma).append(m_dataEmissao).append(m_horaEmissao);
    } else {
        cabecalho.append(m_local)
            .append(m_qtdeAptos)
            .append(m_qtdeAptosDaSecao)
            .append(m_qtdeAptosTTE)
            .append(m_qtdeCompareceram)
            .append(m_qtdeFaltosos)
            .append(m_campos264[0])
            .append(m_campos264[1])
            .append(m_campos264[2])
            .append(m_campos264[3])
            .append(m_campos264[4])
            .append(m_campos264[5])
            .append(m_campos264[6]);
        if (IsOrigemRED()) {
            cabecalho.append(m_dataEmissao).append(m_horaEmissao);
        }
    }
    return cabecalho;
}

} // namespace comum
