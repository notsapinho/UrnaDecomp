// vota::CEncerramentoHorarioInvalido (app/vota/operador/outrasopcoes/cencerramentohorarioinvalido.cpp). This comment is
// the reconstruction's: the records are StartState's, lines 60 and 73; every other line is a choice.
#include "app/vota/operador/outrasopcoes/cencerramentohorarioinvalido.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/cdatetime.h"
#include "api/util/iajustedatahora.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/iinterfaceinit.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CEncerramentoHorarioInvalido::~CEncerramentoHorarioInvalido() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Encerramento de votação inválido", api::SPoint{1, 2}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("Antes do horário", api::SPoint{1, 3}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("CORRIGE: retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CEncerramentoHorarioInvalido::CEncerramentoHorarioInvalido()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CEncerramentoHorarioInvalido& CEncerramentoHorarioInvalido::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEncerramentoHorarioInvalido());
    }
    return *s_inst;
}

std::unique_ptr<CEncerramentoHorarioInvalido> CEncerramentoHorarioInvalido::s_inst;
std::mutex CEncerramentoHorarioInvalido::s_mutex;

void CEncerramentoHorarioInvalido::StartState()
{
    m_form->Slot2();
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    const bool treinamentoMesario = appInfo.GetGeral().GetDadoCarga().GetFase() == comum::FASE_TREINAMENTO &&
                                    !appInfo.GetVota().GetTreinamentoEleitor();
    bool ehDemo = api::CPolySingleton<comum::IInterfaceInit>::instance().GetDemoMode();
    if (ehDemo || treinamentoMesario) {
        comum::md::estadoaplicacao::CEstadoGeral& geral = comum::CAppInfo::GetInst().GetGeral();
        const comum::CConfiguracaoEleicao& configuracao = comum::CConfiguracaoEleicao::GetInst();
        const time_t agora = api::CDateTime::Now().ConvertToLocalTime();
        const api::CDateTime& encerramento = configuracao.GetDataHoraEncerramento();
        const api::CDateTime novaDataHora(encerramento.GetData(), encerramento.GetHora() - 10);
        const time_t nova = novaDataHora.ConvertToLocalTime();

        // (original lines 69-72: content not recovered)
#line 73
        api::CPolySingleton<api::IAjusteDataHora>::instance().Ajusta(novaDataHora);
        comum::md::estadoaplicacao::CAjusteDataHora ajuste = geral.GetAjusteDataHora();
        ajuste.AdicionaDeltaT(nova - agora);
        geral.SetAjusteDataHora(ajuste);
        CSincronizaVota::SincronizaEstadoGeralVota();
        CSincronizaVota::SincronizaEstadoGeral();
    }
    SetNextState(this);
}

void CEncerramentoHorarioInvalido::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeIdentidade::GetInst();
    }
}

} // namespace vota
