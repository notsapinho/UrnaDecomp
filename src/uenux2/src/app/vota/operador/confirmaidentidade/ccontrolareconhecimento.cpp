// vota::CControlaReconhecimento (the records' file). The reconstruction's notes are in ccontrolareconhecimento.h and
// src/units/161-uenux2-app-vota-operador-identidade.mk.
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/ipc/cmessagequeue.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.h"

namespace vota {

int CControlaReconhecimento::s_tentativa = 1;
int CControlaReconhecimento::s_verificacao = 1;
int CControlaReconhecimento::s_tentativaRegistrada = 1;
uebyte CControlaReconhecimento::s_indiceDedo = 0;

CControlaReconhecimento::~CControlaReconhecimento() = default;

// (original lines 24-99: content not recovered)
#line 100
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaEleitorPodeVotar()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBeep(1);
    builder.AddTextField("ELEITOR(A) PODE VOTAR", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Assinar o caderno de votação antes de", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("votar", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: prosseguir", api::SPoint{1, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl(4);
    return builder.GetInteractiveForm("", true);
}

// (original lines 113-139: content not recovered)
#line 140
void CControlaReconhecimento::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        LimpaBiometria();
        if (IsAudioAtivado()) {
            m_pNextState = &CHabilitaAudioEleitor::GetInst();
        } else {
            CThreadEleitor::GetInst().GetMensagens().Post(1);
            m_pNextState = &CMostraEleitorVotando::GetInst();
        }
    }
}

// (original lines 153-160: content not recovered)
#line 161
void CControlaReconhecimento::AvancaTentativa()
{
    if (!AtingiuLimiteTentativas()) {
        s_indiceDedo = 0;
        ++s_tentativa;
    } else {
        throw CUeVotaError(EUE_VOTA_LIMITE_TENTATIVAS_ATINGIDO, "Limite de tentativas atingido.");
    }
}



















bool CControlaReconhecimento::AtingiuLimiteTentativas()
{
    const uebyte limite = comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetNumTentativasHabilitacao();
    return limite == s_tentativa;
}

bool CControlaReconhecimento::AtingiuLimiteVerificacoes()
{
    const uebyte limite = comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetNumTentativasVerificacao();
    return limite == s_verificacao;
}

bool CControlaReconhecimento::PrimeiraTentativa()
{
    return s_tentativa == 1;
}

} // namespace vota

// <stubs>
// f1256 · 109 B · unmatched · placement: link order · name unknown
// ? f1256() { ... }
// </stubs>
