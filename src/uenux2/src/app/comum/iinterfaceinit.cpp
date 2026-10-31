// comum::IInterfaceInit (/home/rubio/tse/uenux2/src/app/comum/iinterfaceinit.cpp). The records of the target fix the lines
// of the throws below; iinterfaceinit.h has the class, and the unit's fragment which members are reconstructed.

#include "app/comum/iinterfaceinit.h"

#include <format>

#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "app/comum/euecomumerror.h"
#include "app/comum/log/ieventoslog.h"

namespace comum {

IInterfaceInit::IInterfaceInit() = default;

IInterfaceInit::~IInterfaceInit() = default;

// (original lines 19-42: content not recovered)
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

// (original lines 82-132: content not recovered)
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

// (original lines 153-155: content not recovered)
#line 156
// <stubs>
// f5896 · 5233 B · unmatched · name unknown
// void f5896(i32) { ... }
// </stubs>

// (original lines 161-179: content not recovered)
#line 180
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

// (original lines 192-519: content not recovered)
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

// (original lines 535-726: content not recovered)
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

} // namespace comum
