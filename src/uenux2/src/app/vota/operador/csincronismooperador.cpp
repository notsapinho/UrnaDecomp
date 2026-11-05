#include "app/vota/operador/csincronismooperador.h"

#include "api/gui/cmtformbuilder.h"
#include "api/ipc/cmessagequeue.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/operador/aguardaeleitor/cdesabilitaaudioeleitor.h"
#include "app/vota/operador/aguardaeleitor/celeitorvotounaovotou.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CSincronismoOperador::CSincronismoOperador()
    : comum::CAppState(EVENTO_TECLA)
    , m_bSincronizado(false)
{
}

CSincronismoOperador& CSincronismoOperador::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CSincronismoOperador());
    }
    return *s_inst;
}

std::unique_ptr<CSincronismoOperador> CSincronismoOperador::s_inst;
std::mutex CSincronismoOperador::s_mutex;

void CSincronismoOperador::StartState()
{
    if (!(comum::CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase() == comum::FASE_TREINAMENTO &&
          comum::CAppInfo::GetInst().GetVota().GetTreinamentoEleitor())) {
        comum::CEleitores::GetInst().MarcaVotou();
    }

    CThreadEleitor::GetInst().GetMensagens().Post(5);
    m_pNextState = this;
}

namespace {

void MostraTelaFalhaMemoria(int memoria)
{
    api::CMTFormBuilderBase builder;
    builder.AddLed(api::LED_OPERACAO_2);
    if (memoria == 1) {
        builder.AddTextField("FALHA NA ME: SUBSTITUA A ME", api::SPoint{20, 1}, api::ALINHAMENTO_CENTRO);
        builder.AddTextField("ÚLTIMO VOTO FOI COMPUTADO", api::SPoint{20, 3}, api::ALINHAMENTO_CENTRO);
    } else {
        builder.AddTextField("FALHA NA MI: SUBSTITUA A URNA", api::SPoint{20, 1}, api::ALINHAMENTO_CENTRO);
        builder.AddTextField("ELEITOR DEVE VOTAR NOVAMENTE", api::SPoint{20, 3}, api::ALINHAMENTO_CENTRO);
    }
    const std::shared_ptr<api::IForm<api::IScreenMT>> form = builder.GetForm("");
    form->Slot2();
}

} // namespace

void CSincronismoOperador::ProcessKey(uebyte tecla)
{
    comum::CAppState* proximo;
    switch (tecla) {
    case 1:
        if (m_bSincronizado) {
            if (!comum::CAppInfo::EhTreinamentoEleitor()) {
                CEleitorVotouNaoVotou::GetInst().SetVotou(true);
                proximo = &CEleitorVotouNaoVotou::GetInst();
            } else {
                proximo = &CPedeIdentidade::GetInst();
            }
        } else if (CEstadoAudio::GetInst().Ativo()) {
            proximo = &CDesabilitaAudioEleitor::GetInst();
        } else {
            proximo = &CPedeIdentidade::GetInst();
        }
        break;
    case 14:
        MostraTelaFalhaMemoria(2);
        proximo = this;
        break;
    case 15:
        MostraTelaFalhaMemoria(1);
        proximo = this;
        break;
    default:
        return;
    }
    m_pNextState = proximo;
}

} // namespace vota
