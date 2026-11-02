// vota::CMostraEleitorVotando (/home/rubio/tse/uenux2/src/app/vota/operador/aguardaeleitor/cmostraeleitorvotando.cpp).
// Reconstruction's note, not TSE's text. Records of the target: 10426's (ProcessInput) at line 64, column 22, and
// 10425's (ProcessKey, slot 6, not written) at 127 and 159, column 31. The other lines are a choice, and so is this
// file for comum::CEleitorDadosHabilitacao's constructor (2733): src/units/142-uenux2-app-vota-estados-448.mk says why.

#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"

#include "api/gui/cmtformbuilder.h"
#include "api/hwil/iinput.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cinfomtlcd.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/celeitordadoshabilitacao.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/cthreadoperador.h"

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

void CMostraEleitorVotando::StartState()
{
    *m_nome = CThreadOperador::GetInst().GetTextoEleitor();
    m_form->Slot2();
    comum::CInfoMTLCD::GetInst().MostraIconeBateria();
    m_pNextState = this;
}
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

namespace comum {

CEleitorDadosHabilitacao::CEleitorDadosHabilitacao(const md::CEleitorIdentidade& identidade, ETipoHabilitacao tipo,
                                                   int tipoAtivacaoAudio,
                                                   const md::CEleitorDadosHabilitacaoBiometrica& biometria,
                                                   const ecourna::app::dados::CApresentacaoFotoEleitor& apresentacaoFoto)
    : m_identidade(identidade)
    , m_tipo(tipo)
    , m_tipoAtivacaoAudio(tipoAtivacaoAudio)
    , m_biometria(biometria)
    , m_apresentacaoFoto(apresentacaoFoto)
{
}

} // namespace comum
