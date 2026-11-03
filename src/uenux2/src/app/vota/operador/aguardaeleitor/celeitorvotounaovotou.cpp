#include "app/vota/operador/aguardaeleitor/celeitorvotounaovotou.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/ctextsource.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/operador/aguardaeleitor/cdesabilitaaudioeleitor.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CEleitorVotouNaoVotou::~CEleitorVotouNaoVotou() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela(std::shared_ptr<std::string> situacao,
                                                                                std::shared_ptr<std::string> complemento)
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(api::CTextSource(situacao), api::SPoint{1, 2}, "%s", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(api::CTextSource(complemento), api::SPoint{1, 3}, "%s", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: prosseguir", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CEleitorVotouNaoVotou::CEleitorVotouNaoVotou()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_bVotou(false)
    , m_situacao(std::make_shared<std::string>("pode/nao pode entregar comp"))
    , m_complemento(std::make_shared<std::string>(""))
    , m_form(MontaTela(m_situacao, m_complemento))
{
}

CEleitorVotouNaoVotou& CEleitorVotouNaoVotou::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorVotouNaoVotou());
    }
    return *s_inst;
}

std::unique_ptr<CEleitorVotouNaoVotou> CEleitorVotouNaoVotou::s_inst;
std::mutex CEleitorVotouNaoVotou::s_mutex;

void CEleitorVotouNaoVotou::StartState()
{
    *m_situacao = m_bVotou ? "VOTOU. Pode entregar o comprovante" : "NÃO VOTOU. Não entregar o comprovante";
    *m_complemento = " ";
    m_form->Slot2();
    m_pNextState = this;
}

void CEleitorVotouNaoVotou::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        if (CEstadoAudio::GetInst().Ativo()) {
            m_pNextState = &CDesabilitaAudioEleitor::GetInst();
        } else {
            m_pNextState = &CPedeIdentidade::GetInst();
        }
    }
}

} // namespace vota
