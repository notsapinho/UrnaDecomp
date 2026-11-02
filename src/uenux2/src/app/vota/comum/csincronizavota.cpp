// vota::CSincronizaVota (/home/rubio/tse/uenux2/src/app/vota/comum/csincronizavota.cpp). The reconstruction's own
// note: the records of VerificaUrnaDesligando's and SincronizaRelatorios's throws fix lines 47 and 392; those of
// SincronizaRDVInternoSeguro and SincronizaRDVExternoSeguro (fn 7174 holds both), lines 290 and 303, are of functions
// not written: 290 holds 7174's stub, 303 a gap. Every other line is chosen (src/units/205-uenux2-csincronizavota.mk).

#include "app/vota/comum/csincronizavota.h"

#include <filesystem>
#include <string>

#include "api/gui/capplication.h"
#include "api/hwil/euedesligandoerror.h"
#include "api/util/csynchronizer.h"
#include "api/util/csystem.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/carquivossavd.h"
#include "app/comum/cpath.h"
#include "app/vota/comum/cassinadorvota.h"
#include "app/vota/euevotaerror.h"

namespace vota {

bool CSincronizaVota::s_urnaDesligando = false;

void CSincronizaVota::MarcaUrnaDesligando()
{
    s_urnaDesligando = true;
}

// (original lines 30-43: content not recovered)
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

// (original lines 114-369: content not recovered)
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
