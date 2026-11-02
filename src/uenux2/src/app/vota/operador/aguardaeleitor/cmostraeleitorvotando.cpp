// vota::CMostraEleitorVotando (/home/rubio/tse/uenux2/src/app/vota/operador/aguardaeleitor/cmostraeleitorvotando.cpp).
// Reconstruction's note, not TSE's text. Its records are records of the target:
//   10426  virtual void ProcessInput()   record at line 64, column 22 (the default argument of CPolySingleton's instance)
//   10425  ProcessKey (slot 6)           records at lines 127 and 159, column 31 (not written)
// The other lines are a choice: src/units/142-uenux2-app-vota-estados-448.mk has them and the other notes.

#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"

#include "api/gui/cmtformbuilder.h"
#include "api/hwil/iinput.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"

namespace vota {

CMostraEleitorVotando::~CMostraEleitorVotando() = default;

namespace {

std::string TextoAudioAtivado()
{
    if ((CThreadEleitor::Existe() && CEstadoAudio::GetInst().Ativo()) || IsAudioAtivadoMesario()) {
        return "ÁUDIO ATIVADO";
    }
    return " ";
}

} // namespace

CMostraEleitorVotando::CMostraEleitorVotando()
    : comum::CAppState(EVENTO_TECLA | EVENTO_ENTRADA)
    , m_nome(std::make_shared<std::string>())
    , m_form(CriaForm(m_nome))
{
}

CMostraEleitorVotando& CMostraEleitorVotando::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMostraEleitorVotando());
    }
    return *s_inst;
}

std::unique_ptr<CMostraEleitorVotando> CMostraEleitorVotando::s_inst;
std::mutex CMostraEleitorVotando::s_mutex;

// (original lines 53-61: content not recovered)
#line 62
void CMostraEleitorVotando::ProcessInput()
{
    auto& terminal = api::CPolySingleton<api::IInputMT>::instance();
    if (terminal.HasKey()) {
        terminal.GetKey();
    }
}

std::shared_ptr<api::IForm<api::IScreenMT>> CMostraEleitorVotando::CriaForm(std::shared_ptr<std::string> nome)
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_1);
    if (comum::CAppInfo::EhTreinamentoEleitor()) {
        builder.AddTextField("TREINAMENTO DE ELEITORES", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    } else {
        builder.AddTextField(&comum::CEleitorDadoNomeParaUrna::Text, api::SPoint{1, 1}, "{:35}", api::ALINHAMENTO_ESQUERDA);
        builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
        builder.AddTextField("Seq:", api::SPoint{32, 2}, api::ALINHAMENTO_ESQUERDA);
        builder.AddTextField(&comum::CEleitorDadoSequencial::Text, api::SPoint{40, 2}, "{:04}", api::ALINHAMENTO_DIREITA);
        builder.AddTextField("Seção:", api::SPoint{30, 3}, api::ALINHAMENTO_ESQUERDA);
        builder.AddTextField(&comum::CEleitorDadoSecao::Text, api::SPoint{40, 3}, "{:04}", api::ALINHAMENTO_DIREITA);
    }
    builder.AddTextField(&TextoAudioAtivado, api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(api::CTextSource(nome), api::SPoint{1, 4});
    return builder.GetForm("");
}

} // namespace vota
