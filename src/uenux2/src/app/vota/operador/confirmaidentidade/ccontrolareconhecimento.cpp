// vota::CControlaReconhecimento (the records' file). The reconstruction's notes are in ccontrolareconhecimento.h and
// src/units/161-uenux2-app-vota-operador-identidade.mk.
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/ipc/cmessagequeue.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.h"
#include "app/vota/operador/confirmaidentidade/cparametrosimagemdigital.h"
#include "app/vota/operador/confirmaidentidade/cpededigital.h"

namespace vota {

int CControlaReconhecimento::s_tentativa = 1;
int CControlaReconhecimento::s_verificacao = 1;
int CControlaReconhecimento::s_tentativaRegistrada = 1;
comum::md::CDedo::TipoDedo CControlaReconhecimento::s_dedosVerificacao[10] = {
    static_cast<comum::md::CDedo::TipoDedo>(1), static_cast<comum::md::CDedo::TipoDedo>(6),
    static_cast<comum::md::CDedo::TipoDedo>(2), static_cast<comum::md::CDedo::TipoDedo>(7),
    static_cast<comum::md::CDedo::TipoDedo>(3), static_cast<comum::md::CDedo::TipoDedo>(4),
    static_cast<comum::md::CDedo::TipoDedo>(5), static_cast<comum::md::CDedo::TipoDedo>(8),
    static_cast<comum::md::CDedo::TipoDedo>(9), static_cast<comum::md::CDedo::TipoDedo>(10)};
uebyte CControlaReconhecimento::s_indiceDedo = 0;
std::vector<uebyte> CControlaReconhecimento::s_digitalCapturada;
std::vector<uebyte> CControlaReconhecimento::s_digitalRegistrada;
std::string CControlaReconhecimento::s_dedoRegistrado;
ueword CControlaReconhecimento::s_qualidadeCapturada = 0;
int CControlaReconhecimento::s_eleitoresTreinamento = 0;
int CControlaReconhecimento::s_faixaTentativa1 = 0;
int CControlaReconhecimento::s_faixaTentativa2 = 0;
int CControlaReconhecimento::s_faixaTentativa3 = 0;
int CControlaReconhecimento::s_faixaTentativa4 = 0;

CControlaReconhecimento::~CControlaReconhecimento() = default;

CControlaReconhecimento::CControlaReconhecimento()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTelaEleitorPodeVotar())
{
    CParametrosImagemDigital::GetInst();
}

CControlaReconhecimento& CControlaReconhecimento::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CControlaReconhecimento());
    }
    return *s_inst;
}

std::unique_ptr<CControlaReconhecimento> CControlaReconhecimento::s_inst;
std::mutex CControlaReconhecimento::s_mutex;

void CControlaReconhecimento::StartState()
{
    s_tentativa = 1;
    s_verificacao = 1;
    s_indiceDedo = 0;
    s_tentativaRegistrada = 1;
    s_digitalCapturada.clear();
    s_digitalRegistrada.clear();
    const bool treinamento = EhTreinamentoMesario();
    comum::CEleitores& eleitores = comum::CEleitores::GetInst();
    if (treinamento) {
        s_eleitoresTreinamento = eleitores.GetQuantidade();
        const int faixa = s_eleitoresTreinamento / 6;
        s_faixaTentativa1 = faixa;
        s_faixaTentativa2 = faixa;
        s_faixaTentativa3 = faixa;
        s_faixaTentativa4 = faixa;
        const int sequencial = comum::CEleitores::GetInst().GetCurrent()->GetEleitor().GetSequencial();
        if (sequencial > faixa * 5 && sequencial <= s_eleitoresTreinamento) {
            m_form->Slot2();
            SetNextState(this);
        } else {
            SetNextState(&CPedeDigital::GetInst());
        }
    } else if (!eleitores.GetCurrent()->GetEleitor().TemBiometria() ||
               !comum::CEleitores::GetInst().GetCurrentBiometriaEleitor().TemDedos()) {
        CLogVota::GetInst().LogaEleitorNaoPossuiBiometria();
        m_form->Slot2();
        m_pNextState = this;
    } else {
        SetNextState(&CPedeDigital::GetInst());
    }
}

// (original lines 97-99: content not recovered)
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
            SetNextState(&CHabilitaAudioEleitor::GetInst());
        } else {
            CThreadEleitor::GetInst().GetMensagens().Post(1);
            SetNextState(&CMostraEleitorVotando::GetInst());
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

void CControlaReconhecimento::AvancaVerificacao()
{
    if (!AtingiuLimiteVerificacoes()) {
        ++s_verificacao;
    } else {
        throw CUeVotaError(EUE_VOTA_LIMITE_VERIFICACOES_ATINGIDO,
                           "Limite de verificações de dado do eleitor atingido.");
    }
}


void CControlaReconhecimento::AvancaProximoDedo1x4()
{
    if (s_indiceDedo != 4) {
        ++s_indiceDedo;
    } else {
        throw CUeVotaError(EUE_VOTA_FIM_VERIFICACAO_1X4, "Fim da verificação 1x4 atingido.");
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

uebyte CControlaReconhecimento::GetLimiteTentativas()
{
    return comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetNumTentativasHabilitacao();
}

std::vector<api::SXYT> CControlaReconhecimento::GetMinuciasDedoCorrente()
{
    if (!comum::CEleitores::GetInst().GetCurrentBiometriaEleitor().TemDedo(s_dedosVerificacao[s_indiceDedo])) {
        return {};
    }
    return comum::CEleitores::GetInst()
        .GetCurrentBiometriaEleitor()
        .GetDedo(s_dedosVerificacao[s_indiceDedo])
        .GetMinucias();
}

bool CControlaReconhecimento::DigitalReconhecidaTreinamento()
{
    const ueword sequencial = comum::CEleitores::GetInst().GetCurrent()->GetEleitor().GetSequencial();
    int limite = s_faixaTentativa1;
    if (sequencial <= limite && s_tentativa == 1) {
        return true;
    }
    int inicio = limite;
    limite += s_faixaTentativa2;
    if (sequencial > inicio && sequencial <= limite && s_tentativa == 2) {
        return true;
    }
    inicio = limite;
    limite += s_faixaTentativa3;
    if (sequencial > inicio && sequencial <= limite && s_tentativa == 3) {
        return true;
    }
    inicio = limite;
    limite += s_faixaTentativa4;
    return sequencial > inicio && sequencial <= limite && s_tentativa == 4;
}

void CControlaReconhecimento::RegistraDigitalCapturada(const std::vector<uebyte>& digital)
{
    s_digitalCapturada = digital;
    s_tentativaRegistrada = s_tentativa;
}

} // namespace vota
