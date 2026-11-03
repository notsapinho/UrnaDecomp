// comum::IInterfaceInit (/home/rubio/tse/uenux2/src/app/comum/iinterfaceinit.cpp). The records of the target fix the lines
// of the throws below; iinterfaceinit.h has the class, and the unit's fragment which members are reconstructed.

#include "app/comum/iinterfaceinit.h"

#include <algorithm>
#include <filesystem>
#include <format>

#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "api/util/uedebug.h"
#include "app/comum/euecomumerror.h"
#include "app/comum/log/ieventoslog.h"
#include "ecourna/api/io/cfile.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

IInterfaceInit::IInterfaceInit() = default;

IInterfaceInit::~IInterfaceInit() = default;

// (original lines 25-42: content not recovered)
#line 43
EBootDeviceId IInterfaceInit::CurrentBootDevice()
{
    const std::vector<int> resposta = EnviarMensagem(37);
    if (resposta.empty()) {
        throw CUeComumError(EUE_COMUM_BOOT_DEVICE_RESPOSTA_NULA, "Resposta nula");
    }
    switch (resposta[0]) {
    case 1:
        return BOOT_DEVICE_1;
    case 2:
        return BOOT_DEVICE_2;
    default:
        return BOOT_DEVICE_DESCONHECIDO;
    }
}

// (original lines 59-69: content not recovered)
#line 70
void IInterfaceInit::HabilitarMR()
{
    EnviarMensagemThrowVoid(10, "habilitando MR");
    api::CSystem::Dorme(500);
}

void IInterfaceInit::DesabilitarMR()
{
    EnviarMensagemThrowVoid(11, "desabilitando MR");
    api::CSystem::Dorme(100);
}


std::string FormataTamanho(size_t tamanho)
{
    const size_t gb = tamanho / (1024 * 1024 * 1024);
    const size_t mb = tamanho / (1024 * 1024);
    const size_t kb = tamanho / 1024;
    if (gb > 0) {
        return std::format("{}.{} GB", gb, mb % 1024 * 10 / 1024);
    }
    if (mb > 0) {
        return std::format("{}.{} MB", mb, kb % 1024 * 10 / 1024);
    }
    if (kb > 0) {
        return std::format("{}.{} KB", kb, tamanho % 1024 * 10 / 1024);
    }
    return std::format("{} B", tamanho);
}

// (original lines 100-132: content not recovered)
#line 133
bool IInterfaceInit::IsMRPresenteSemHabilitar()
{
    const std::vector<int> resposta = EnviarMensagem(18);
    if (resposta.empty()) {
        throw CUeComumError(EUE_COMUM_MR_PRESENTE_RESPOSTA_NULA, "Resposta nula");
    }
    return resposta[0] == 0;
}

// (original lines 142-143: content not recovered)
#line 144
bool IInterfaceInit::IsMRMontadoSemHabilitar()
{
    const std::vector<int> resposta = EnviarMensagem(17);
    if (resposta.empty()) {
        throw CUeComumError(EUE_COMUM_MR_MONTADO_RESPOSTA_NULA, "Resposta nula");
    }
    return resposta[0] == 0;
}

// (original lines 153-154: content not recovered)
#line 155
void IInterfaceInit::MontarMRSemHabilitar()
{
    const std::vector<int> resposta = EnviarMensagem(34);
    if (resposta.empty()) {
        throw CUeComumError(EUE_COMUM_MONTAR_MR_RESPOSTA_NULA, "Resposta nula");
    }

    if (resposta[0] != 0) {
        throw CUeComumError(EUE_COMUM_MONTAR_MR_FALHA, std::format("Falha ao montar mídia de resultado ({})", resposta[0]));
    }

    const int dispositivo = DispositivoMR();
    const std::string serial = GetSerialNumberMR(dispositivo);

    if (m_serialMR != serial) {
        const std::string tamanho = FormataTamanho(TamanhoMR(dispositivo));

        auto& logs = api::CPolySingleton<IEventosLog>::instance();
        logs.loga(std::format("Tamanho da MR: {}", tamanho));
        DepuraInfo("Serial da MR: %s", serial.c_str());

        m_serialMR = serial;
    }
}

void IInterfaceInit::DesmontarMRSemDesabilitar()
{
    const std::vector<int> resposta = EnviarMensagem(58);
    if (resposta.empty()) {
        throw CUeComumError(EUE_COMUM_DESMONTAR_MR_RESPOSTA_NULA, "Resposta nula");
    }

    if (resposta[0] != 0) {
        throw CUeComumError(EUE_COMUM_DESMONTAR_MR_FALHA, std::format("Falha ao desmontar mídia de resultado ({})", resposta[0]));
    }
}

// (original lines 192-280: content not recovered)
#line 281
void IInterfaceInit::LogDiskInfo()
{
    const std::vector<int> resposta = EnviarMensagem(19);
    if (resposta.empty()) {
        throw CUeComumError(EUE_COMUM_LOG_DISK_INFO_RESPOSTA_NULA, "Resposta nula");
    }
    if (resposta[0] != 0) {
        DepuraInfo("%s: erro [%d] ao tentar logar informações sobre as partições", __func__, resposta[0]);
    }
}

// (original lines 292-519: content not recovered)
#line 520
void IInterfaceInit::DesligarUrna()
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    logs.loga("Urna desligada a pedido do aplicativo");

    const std::vector<int> resposta = EnviarMensagem(48);
    if (resposta.empty()) {
        throw CUeComumError(EUE_COMUM_DESLIGAR_URNA_RESPOSTA_NULA, "Resposta nula");
    }

    if (resposta[0] < 0) {
        throw CUeComumError(EUE_COMUM_DESLIGAR_URNA_FALHA, std::format("Erro ao desligar urna: {}", resposta[0]));
    }
}

// (original lines 535-626: content not recovered)
#line 627
int IInterfaceInit::DispositivoMR()
{
    HabilitarMR();
    const std::vector<int> resposta = EnviarMensagem(12);
    if (resposta.empty()) {
        throw CUeComumError(EUE_COMUM_DISPOSITIVO_MR_RESPOSTA_NULA, "Resposta nula");
    }

    if (resposta[0] == -1) {
        throw CUeComumError(EUE_COMUM_DISPOSITIVO_MR_FALHA, std::format("Falha ao obter dispositivo da MR: {}", resposta[0]));
    }
    return resposta[0];
}

// (original lines 641-726: content not recovered)
#line 727
inline void IInterfaceInit::EnviarMensagemThrowVoid(ueint32 mensagem, const std::string& descricao)
{
    const std::vector<int> resposta = EnviarMensagem(mensagem);
    if (resposta.empty()) {
        throw CUeComumError(EUE_COMUM_ENVIAR_MENSAGEM_RESPOSTA_NULA, std::format("{}: Resposta nula", descricao));
    }

    // (original lines 734-735: content not recovered)
#line 736
    if (resposta[0] != 0) {
        throw CUeComumError(EUE_COMUM_ENVIAR_MENSAGEM_FALHA, std::format("Falha ao enviar mensagem {}, {}: {}", mensagem, descricao, resposta[0]));
    }
}

// (original lines 741-744: content not recovered)
#line 745
bool IInterfaceInit::GetDemoMode()
{
    if (m_demoMode) {
        return *m_demoMode;
    }

    const std::vector<int> resposta = EnviarMensagem(67);
    if (resposta.empty()) {
        throw CUeComumError(EUE_COMUM_MODO_DEMO_RESPOSTA_NULA, "Resposta nula");
    }

    if (resposta[0] == -1) {
        throw CUeComumError(EUE_COMUM_MODO_DEMO_FALHA, std::format("Falha ao obter estado do modo de demonstração: {}", resposta[0]));
    }
    const bool demoMode = resposta[0] != 0;
    m_demoMode = std::shared_ptr<bool>(new bool(demoMode));
    return demoMode;
}

// (original lines 764-847: content not recovered)
#line 848
std::string IInterfaceInit::GetSerialNumberMR(int dispositivo)
{
    std::string serial;
    if (dispositivo > 0) {
        const std::string nome = std::format("sd{:c}", 'a' + dispositivo - 1);
        std::vector<std::string> caminhos;

        const auto modeloUrna = api::CPolySingleton<api::IUrna>::instance().Modelo();
        switch (modeloUrna) {
        case 2009:
        case 2010:
        case 2011:
        case 2013:
            caminhos.push_back("/sys/devices/pci0000:00/0000:00:1d.8/usb1/1-0/serial");
            caminhos.push_back("/sys/devices/pci0000:00/0000:00:1d.8/usb1/1-8/serial");
            break;
        case 2015:
            caminhos.push_back("/sys/devices/pci0000:00/0000:00:1d.7/usb1/1-0/serial");
            caminhos.push_back("/sys/devices/pci0000:00/0000:00:1d.7/usb1/1-7/serial");
            break;
        case 2020:
        case 2022:
            caminhos.push_back("/sys/devices/pci0000:00/0000:00:15.0/usb1/1-3/serial");
            caminhos.push_back("/sys/devices/pci0000:00/0000:00:15.0/usb2/2-3/serial");
            break;
        default:
            break;
        }

        const auto caminho = std::find_if(caminhos.begin(), caminhos.end(),
                                          [](const std::string& c) { return std::filesystem::exists(c); });
        if (caminho != caminhos.end()) {
            serial = ecourna::api::util::CStringUtils::Trim(ecourna::api::io::CFile::ReadFileContent(*caminho));
        }
    }
    return serial;
}

int TamanhoMR(int dispositivo)
{
    if (dispositivo <= 0) {
        return 0;
    }

    const std::string nome = std::format("sd{:c}", 'a' + dispositivo - 1);
    const int setores = ecourna::api::util::CStringUtils::ToInt32(
        ecourna::api::io::CFile::ReadFileContent(std::format("/sys/block/{}/size", nome)));
    const int tamanhoSetor = ecourna::api::util::CStringUtils::ToInt32(
        ecourna::api::io::CFile::ReadFileContent(std::format("/sys/block/{}/queue/logical_block_size", nome)));
    return setores * tamanhoSetor;
}

} // namespace comum
