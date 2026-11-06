// vota::CSincronizaVota (/home/rubio/tse/uenux2/src/app/vota/comum/csincronizavota.cpp). The reconstruction's own
// note: the records of VerificaUrnaDesligando's and SincronizaRelatorios's throws fix lines 47 and 392, and those of
// the anonymous SincronizaRDVInternoSeguro and SincronizaRDVExternoSeguro (fn 7174 holds both) lines 290 and 303.
// Every other line is chosen (src/units/205-uenux2-csincronizavota.mk).

#include "app/vota/comum/csincronizavota.h"

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

#include "api/gui/capplication.h"
#include "api/hwil/euedesligandoerror.h"
#include "api/util/csynchronizer.h"
#include "api/util/csystem.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/carquivossavd.h"
#include "app/comum/justificativa/cjustificador.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/cintegridadereferencial.h"
#include "app/comum/dados/crdv.h"
#include "app/comum/dados/crdvvota.h"
#include "app/vota/comum/cassinadorvota.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/euevotaerror.h"

namespace vota {

bool CSincronizaVota::s_urnaDesligando = false;

void CSincronizaVota::MarcaUrnaDesligando()
{
    s_urnaDesligando = true;
}

// (original lines 38-43: content not recovered)
#line 44
void CSincronizaVota::VerificaUrnaDesligando()
{
    if (s_urnaDesligando) {
        throw api::CUeDesligandoError();
    }
}

void CSincronizaVota::SincronizaAssinaturaVota()
{
    const comum::CArquivosSavd& arquivos = comum::CArquivosSavd::GetInst();
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    if (appInfo.GetGeral().GetDadoCarga().GetTurno() == comum::TURNO_1) {
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(122)], arquivos[comum::ESavdPacote(124)], false, true);
    } else {
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(123)], arquivos[comum::ESavdPacote(125)], false, true);
    }
}

void CSincronizaVota::GravaBancoDadosMV()
{
    const comum::CArquivosSavd& arquivos = comum::CArquivosSavd::GetInst();
    const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(4, "", "Gravando o banco de dados na MV", "Ocorreu um erro durante a persitência dos dados na MV.");
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    if (appInfo.GetGeral().GetDadoCarga().GetTurno() == comum::TURNO_1) {
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(199)], arquivos[comum::ESavdPacote(201)], false, true);
    } else {
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(200)], arquivos[comum::ESavdPacote(202)], false, true);
    }
}

void CSincronizaVota::AssinaRDVEBancoDados()
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    const CAssinadorVota assinador(appInfo.GetGeral().GetDadoCarga().GetTurno() == comum::TURNO_1 ? comum::ESavdPacote(122) : comum::ESavdPacote(123));
    assinador.Assina(comum::ESavdArquivoUE(83));
    assinador.Assina(comum::ESavdArquivoUE(110));
}

void CSincronizaVota::SincronizaBancoDados()
{
    VerificaUrnaDesligando();
    GravaBancoDadosMI();
}

namespace {

void AssinaESincroniza(comum::ESavdArquivoUE arquivo)
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    const CAssinadorVota assinador(appInfo.GetGeral().GetDadoCarga().GetTurno() == comum::TURNO_1 ? comum::ESavdPacote(122) : comum::ESavdPacote(123));
    assinador.Assina(arquivo);
    api::CSynchronizer::GetInst().Sync();
}

} // namespace

void CSincronizaVota::GravaBancoDadosMI()
{
    {
        const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(2, "", "Gravando o banco de dados na MI", "Ocorreu um erro durante a persitência dos dados na MI.");
        AssinaESincroniza(comum::ESavdArquivoUE(110));
        const comum::CArquivosSavd& arquivos = comum::CArquivosSavd::GetInst();
        const std::filesystem::path origem = comum::CPath::GetPathTrab(comum::FLASH_INTERNA) / arquivos[comum::ESavdArquivoUE(110)];
        const std::filesystem::path destino = comum::CPath::GetPathTrab(comum::FLASH_EXTERNA) / arquivos[comum::ESavdArquivoUE(111)];
        api::CSystem::CopyFile(origem.string(), destino.string(), false, true);
    }
    GravaBancoDadosMV();
    api::CSynchronizer::GetInst().Sync();
}

namespace {

void AssinaArquivo(comum::ESavdArquivoUE arquivo)
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    const CAssinadorVota assinador(appInfo.GetGeral().GetDadoCarga().GetTurno() == comum::TURNO_1 ? comum::ESavdPacote(122) : comum::ESavdPacote(123));
    assinador.Assina(arquivo);
}

} // namespace

void CSincronizaVota::SincronizaEstadoGeralVota()
{
    const std::vector<api::CApplicationContext>& contextos = api::CApplication::s_contextos.m_contextos;
    const std::optional<api::CApplicationContext> contexto =
        contextos.empty() ? std::nullopt : std::optional<api::CApplicationContext>(contextos.back());
    const std::string titulo = contexto ? contexto->m_titulo : "Erro de sincronização";
    comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    {
        const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(2, titulo, "Gravando o estado da urna", "Ocorreu um erro durante a sincronização do estado geral do VOTA.");
        VerificaUrnaDesligando();
        appInfo.SalvaVotaInterno();
        AssinaArquivo(comum::ESavdArquivoUE(31));
        api::CSynchronizer::GetInst().Sync();
    }
    {
        const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(4, titulo, "Gravando o estado da urna", "Ocorreu um erro durante a sincronização do estado geral do VOTA.");
        appInfo.SalvaVotaExterno();
        SincronizaAssinaturaVota();
        api::CSynchronizer::GetInst().Sync();
    }
}

void CSincronizaVota::SincronizaEstadoGeral()
{
    VerificaUrnaDesligando();
    const std::vector<api::CApplicationContext>& contextos = api::CApplication::s_contextos.m_contextos;
    const std::optional<api::CApplicationContext> contexto =
        contextos.empty() ? std::nullopt : std::optional<api::CApplicationContext>(contextos.back());
    const std::string titulo = contexto ? contexto->m_titulo : "Erro de sincronização";
    const comum::CArquivosSavd& arquivos = comum::CArquivosSavd::GetInst();
    comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    {
        const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(2, "", "Gravando o estado geral da urna na MI", "Ocorreu um erro durante a sincronização do estado geral da urna na MI.");
        const CAssinadorVota assinador(comum::ESavdPacote(120));
        appInfo.SalvaGeralInterno();
        assinador.Assina(comum::ESavdArquivoUE(25));
        api::CSynchronizer::GetInst().Sync();
    }
    {
        const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(4, "", "Gravando o estado geral da urna na MV", "Ocorreu um erro durante a sincronização do estado geral da urna na MV.");
        appInfo.SalvaGeralExterno();
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(120)], arquivos[comum::ESavdPacote(121)], false, true);
        api::CSynchronizer::GetInst().Sync();
    }
}

void CSincronizaVota::SincronizaJustificativa()
{
    VerificaUrnaDesligando();
    comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    comum::CJustificador& justificador = comum::CJustificador::GetInst();
    {
        const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(2, "", "Gravando a justificativa na MI", "Ocorreu um erro durante a sincronização da justificativa na MI.");
        appInfo.SalvaVotaInterno();
        justificador.SaveCurrentInternal();
        AssinaArquivo(comum::ESavdArquivoUE(31));
        api::CSynchronizer::GetInst().Sync();
    }
    GravaBancoDadosMI();
    {
        const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(4, "", "Gravando a justificativa na MV", "Ocorreu um erro durante a sincronização da justificativa na MV.");
        appInfo.SalvaVotaExterno();
        SincronizaAssinaturaVota();
        api::CSynchronizer::GetInst().Sync();
    }
}


void CSincronizaVota::CriaBancoDadosMI(const comum::CEleitores& eleitores)
{
    eleitores.DynamicCreate(comum::GetArquivoBancoDadosInterno());
}

void CSincronizaVota::CriaBancoDadosMV(const comum::CEleitores& eleitores)
{
    eleitores.DynamicCreate(comum::GetArquivoBancoDadosExterno());
}

void CSincronizaVota::SincronizaAssinaturaDadosDinamicos()
{
    const comum::CArquivosSavd& arquivos = comum::CArquivosSavd::GetInst();
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    if (appInfo.GetGeral().GetDadoCarga().GetTurno() == comum::TURNO_1) {
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(122)], arquivos[comum::ESavdPacote(124)], false, true);
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(199)], arquivos[comum::ESavdPacote(201)], false, true);
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(134)], arquivos[comum::ESavdPacote(136)], false, true);
    } else {
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(123)], arquivos[comum::ESavdPacote(125)], false, true);
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(200)], arquivos[comum::ESavdPacote(202)], false, true);
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(135)], arquivos[comum::ESavdPacote(137)], false, true);
    }
}

// (original lines 218-229: content not recovered)
#line 230
void CSincronizaVota::CopiaBancoDadosMV()
{
    const comum::CArquivosSavd& arquivos = comum::CArquivosSavd::GetInst();
    const std::filesystem::path origem = comum::CPath::GetPathTrab(comum::FLASH_INTERNA) / arquivos[comum::ESavdArquivoUE(110)];
    const std::filesystem::path destino = comum::CPath::GetPathTrab(comum::FLASH_EXTERNA) / arquivos[comum::ESavdArquivoUE(111)];
    api::CSystem::CopyFile(origem.string(), destino.string(), false, true);
    GravaBancoDadosMV();
}

void CSincronizaVota::SincronizaAssinaturaRDV()
{
    const comum::CArquivosSavd& arquivos = comum::CArquivosSavd::GetInst();
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    if (appInfo.GetGeral().GetDadoCarga().GetTurno() == comum::TURNO_1) {
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(122)], arquivos[comum::ESavdPacote(124)], false, true);
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(134)], arquivos[comum::ESavdPacote(136)], false, true);
    } else {
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(123)], arquivos[comum::ESavdPacote(125)], false, true);
        api::CSystem::CopyFile(arquivos[comum::ESavdPacote(135)], arquivos[comum::ESavdPacote(137)], false, true);
    }
}

// (original lines 252-282: content not recovered)
#line 283
namespace {

void SincronizaRDVInternoSeguro()
{
    const comum::CRdvVota& rdv = comum::CRdvVota::GetInst();
    rdv.SalvaTemporarioInterno();
    if (!rdv.ConfereTemporarioInterno()) {
        throw CUeVotaError(EUE_VOTA_FALHA_GRAVACAO_RDV_MI, "Falha na gravação do RDV na MI");
    }
    comum::VerificaIntegridadeVotos();
    comum::SubstituiRdvInterno();
}

// (original lines 296-297: content not recovered)
#line 298
void SincronizaRDVExternoSeguro()
{
    const comum::CRdvVota& rdv = comum::CRdvVota::GetInst();
    rdv.SalvaTemporarioExterno();
    if (!rdv.ConfereTemporarioExterno()) {
        throw CUeVotaError(EUE_VOTA_FALHA_GRAVACAO_RDV_MV, "Falha na gravação do RDV na MV");
    }
    comum::VerificaIntegridadeVotos();
    comum::SubstituiRdvExterno();
}

} // namespace

void CSincronizaVota::SincronizaVotoMI()
{
    VerificaUrnaDesligando();
    SincronizaRDVInternoSeguro();
    comum::CAppInfo::GetInst().SalvaVotaInterno();
    if (!comum::CAppInfo::EhTreinamentoEleitor()) {
        comum::CEleitores::GetInst().GravaEleitorCorrenteMI();
        api::CSynchronizer::GetInst().Sync();
        AssinaESincroniza(comum::ESavdArquivoUE(110));
    }
    {
        const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
        const CAssinadorVota assinador(appInfo.GetGeral().GetDadoCarga().GetTurno() == comum::TURNO_1 ? comum::ESavdPacote(122) : comum::ESavdPacote(123));
        assinador.Assina(comum::ESavdArquivoUE(83));
        assinador.Assina(comum::ESavdArquivoUE(31));
    }
    api::CSynchronizer::GetInst().Sync();
    VerificaAssinaturaMI("vota.vsu");
    VerificaAssinaturaMI("rdv.vsu");
    if (!comum::CAppInfo::EhTreinamentoEleitor()) {
        VerificaAssinaturaMI("uenux.vsu");
    }
}

void CSincronizaVota::SincronizaVotoMV()
{
    VerificaUrnaDesligando();
    SincronizaRDVExternoSeguro();
    comum::CAppInfo::GetInst().SalvaVotaExterno();
    if (!comum::CAppInfo::EhTreinamentoEleitor()) {
        CopiaBancoDadosMV();
    }
    SincronizaAssinaturaRDV();
    api::CSynchronizer::GetInst().Sync();
    VerificaAssinaturaMV("vota.vsu");
    VerificaAssinaturaMV("rdv.vsu");
    if (!comum::CAppInfo::EhTreinamentoEleitor()) {
        VerificaAssinaturaMV("uenux.vsu");
    }
}

// (original lines 352-369: content not recovered)
#line 370
void CSincronizaVota::SincronizaRelatorios(const std::string& arquivo)
{
    VerificaUrnaDesligando();
    api::CSynchronizer::GetInst().Sync();

    const comum::CArquivosSavd& arquivos = comum::CArquivosSavd::GetInst();
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    const CAssinadorVota assinador(appInfo.GetGeral().GetDadoCarga().GetTurno() == comum::TURNO_1 ? comum::ESavdPacote(122) : comum::ESavdPacote(123));
    comum::ESavdArquivoUE tipo;
    if (arquivo == arquivos[comum::ESavdArquivoUE(86)]) {
        tipo = comum::ESavdArquivoUE(86);
    } else if (arquivo == arquivos[comum::ESavdArquivoUE(84)]) {
        tipo = comum::ESavdArquivoUE(84);
    } else if (arquivo == arquivos[comum::ESavdArquivoUE(88)]) {
        tipo = comum::ESavdArquivoUE(88);
    } else if (arquivo == arquivos[comum::ESavdArquivoUE(89)]) {
        tipo = comum::ESavdArquivoUE(89);
    } else if (arquivo == arquivos[comum::ESavdArquivoUE(106)]) {
        tipo = comum::ESavdArquivoUE(106);
    } else if (arquivo == arquivos[comum::ESavdArquivoUE(108)]) {
        tipo = comum::ESavdArquivoUE(108);
    } else {
        throw CUeVotaError(EUE_VOTA_RELATORIO_INVALIDO_SINCRONIZACAO, "O arquivo" + arquivo + " não é um relatório válido para sincronização");
    }
    assinador.Assina(tipo);
    api::CSynchronizer::GetInst().Sync();

    const std::filesystem::path origem = comum::CPath::GetPathTrab(comum::FLASH_INTERNA) / arquivo;
    const std::filesystem::path destino = comum::CPath::GetPathTrab(comum::FLASH_EXTERNA) / arquivo;
    api::CSystem::CopyFile(origem.string(), destino.string(), false, true);
    SincronizaAssinaturaRelatorio(arquivo);
    api::CSynchronizer::GetInst().Sync();
}

void CSincronizaVota::SincronizaAssinaturaRelatorio(const std::string& arquivo)
{
    const comum::CArquivosSavd& arquivos = comum::CArquivosSavd::GetInst();
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    if (appInfo.GetGeral().GetDadoCarga().GetTurno() == comum::TURNO_1) {
        if (arquivo == arquivos[comum::ESavdArquivoUE(86)]) {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(126)], arquivos[comum::ESavdPacote(128)], false, true);
        } else if (arquivo == arquivos[comum::ESavdArquivoUE(84)]) {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(130)], arquivos[comum::ESavdPacote(132)], false, true);
        } else if (arquivo == arquivos[comum::ESavdArquivoUE(88)]) {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(138)], arquivos[comum::ESavdPacote(140)], false, true);
        } else if (arquivo == arquivos[comum::ESavdArquivoUE(89)]) {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(142)], arquivos[comum::ESavdPacote(144)], false, true);
        } else if (arquivo == arquivos[comum::ESavdArquivoUE(106)]) {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(191)], arquivos[comum::ESavdPacote(193)], false, true);
        } else if (arquivo == arquivos[comum::ESavdArquivoUE(108)]) {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(195)], arquivos[comum::ESavdPacote(197)], false, true);
        } else {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(126)], arquivos[comum::ESavdPacote(128)], false, true);
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(130)], arquivos[comum::ESavdPacote(132)], false, true);
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(138)], arquivos[comum::ESavdPacote(140)], false, true);
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(142)], arquivos[comum::ESavdPacote(144)], false, true);
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(191)], arquivos[comum::ESavdPacote(193)], false, true);
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(195)], arquivos[comum::ESavdPacote(197)], false, true);
        }
    } else {
        if (arquivo == arquivos[comum::ESavdArquivoUE(86)]) {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(127)], arquivos[comum::ESavdPacote(129)], false, true);
        } else if (arquivo == arquivos[comum::ESavdArquivoUE(84)]) {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(131)], arquivos[comum::ESavdPacote(133)], false, true);
        } else if (arquivo == arquivos[comum::ESavdArquivoUE(88)]) {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(139)], arquivos[comum::ESavdPacote(141)], false, true);
        } else if (arquivo == arquivos[comum::ESavdArquivoUE(89)]) {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(143)], arquivos[comum::ESavdPacote(145)], false, true);
        } else if (arquivo == arquivos[comum::ESavdArquivoUE(106)]) {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(192)], arquivos[comum::ESavdPacote(194)], false, true);
        } else if (arquivo == arquivos[comum::ESavdArquivoUE(108)]) {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(196)], arquivos[comum::ESavdPacote(198)], false, true);
        } else {
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(127)], arquivos[comum::ESavdPacote(129)], false, true);
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(131)], arquivos[comum::ESavdPacote(133)], false, true);
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(139)], arquivos[comum::ESavdPacote(141)], false, true);
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(143)], arquivos[comum::ESavdPacote(145)], false, true);
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(192)], arquivos[comum::ESavdPacote(194)], false, true);
            api::CSystem::CopyFile(arquivos[comum::ESavdPacote(196)], arquivos[comum::ESavdPacote(198)], false, true);
        }
    }
}

} // namespace vota
