// vota::CPedeIdentidade (the records' file). The reconstruction's notes are in cpedeidentidade.h and
// src/units/161-uenux2-app-vota-operador-identidade.mk.
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/iform.h"
#include "api/gui/iscreenmt.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cinfomtlcd.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/comum/telasoperador.h"
#include "app/vota/operador/confirmaidentidade/caguardainspecao.h"
#include "app/vota/operador/confirmaidentidade/cnomeeleitor.h"
#include "app/vota/operador/cthreadoperador.h"
#include "app/vota/operador/leidentidade/cvalidaidentidade.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"
#include "app/vota/operador/outrasopcoes/chorariovotacaoterminou.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace vota {

CPedeIdentidade::~CPedeIdentidade() = default;

std::unique_ptr<CPedeIdentidade> CPedeIdentidade::s_inst;
std::mutex CPedeIdentidade::s_mutex;

// (original lines 33-55: content not recovered)
#line 56
void CPedeIdentidade::StartState()
{
    CLogVota::GetInst().LogaAguardandoIdentificadorEleitor();
    impl::IInformacaoThreadOperador::GetInst().LimpaIdentidades();
    m_form->Slot2();
    m_pNextState = this;
    if (api::CPolySingleton<api::IUrna>::instance().Modelo() >= 2020) {
        api::CPolySingleton<api::IScreenMT>::instance().Slot19(0);
    }
    comum::CInfoMTLCD::GetInst().MostraIconeBateria();
    if (!EhTreinamento() && !IsVotacaoBloqueadaPorHorario()) {
        CThreadOperador::GetInst().StartTick(m_tickIdentidade);
    }
    if (!comum::CAppInfo::EhTreinamentoEleitor()) {
        CThreadOperador::GetInst().StartTick(m_tickEspera);
        CThreadOperador::GetInst().StartTick(m_tickAviso);
    }
}

void CPedeIdentidade::FinishState()
{
    CThreadOperador::GetInst().StopTick(m_tickIdentidade);
    CThreadOperador::GetInst().StopTick(m_tickEspera);
    CThreadOperador::GetInst().StopTick(m_tickAviso);
}

CPedeIdentidade& CPedeIdentidade::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeIdentidade());
    }
    return *s_inst;
}

CPedeIdentidade::CPedeIdentidade()
    : comum::CAppState(EVENTO_ENTRADA | EVENTO_TICK)
    , m_tickIdentidade(CThreadOperador::GetInst().AddStoppedTick(60000))
    , m_tickEspera(CThreadOperador::GetInst().AddStoppedTick(5000))
    , m_tickAviso(CThreadOperador::GetInst().AddStoppedTick(1000))
    , m_aviso(std::make_shared<std::string>(" "))
    , m_form(MontaTelaPedeIdentidade(m_aviso))
{
    AgendaInspecao();
}

void CPedeIdentidade::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        if (comum::CAppInfo::EhTreinamentoEleitor()) {
            m_pNextState = ProximoEstadoTreinamento();
        } else if (comum::CAppState* proximo = ProximoEstadoIdentidadeDigitada()) {
            m_pNextState = proximo;
        }
        break;
    case api::INPUT_CORRIGE:
        m_pNextState = &CEscolheOpcao::GetInst();
        break;
    default:
        break;
    }
}

void CPedeIdentidade::ProcessTick(uebyte id)
{
    if (id == m_tickIdentidade) {
        if (IsVotacaoBloqueadaPorHorario()) {
            CThreadOperador::GetInst().StopTick(m_tickIdentidade);
            CLogVota::GetInst().LogaVotacaoBloqueadaPorHorario();
        }
    } else if (id == m_tickEspera) {
        if (api::CDateTime::Now() >= impl::IInformacaoThreadOperador::GetInst().GetDataHoraInspecao()) {
            AgendaInspecao();
            CThreadEleitor::GetInst().GetMensagens().Post(12);
            m_pNextState = &CAguardaInspecao::GetInst();
        }
    } else if (id == m_tickAviso) {
        if (m_form->GetEntradaAtual()->GetTexto().empty()) {
            *m_aviso = "CORRIGE: outras opções";
        } else {
            *m_aviso = " ";
        }
    }
}

comum::CAppState* CPedeIdentidade::ProximoEstadoIdentidadeDigitada()
{
    const std::string identidade = m_form->GetEntradas().at(0)->GetTexto();
    if (identidade.empty()) {
        return nullptr;
    }
    CLogVota::GetInst().LogaIdentificadorDigitadoMesario();
    if (IsVotacaoBloqueadaPorHorario()) {
        return &CHorarioVotacaoTerminou::GetInst();
    }
    SetIdentidadeDigitada(ecourna::api::util::CStringUtils::PreencheAEsquerda(identidade, '0', 12));
    return &CValidaIdentidade::GetInst();
}

comum::CAppState* ProximoEstadoTreinamento()
{
    comum::CEleitores::GetInst().Reset();
    const comum::CEleitorDetalhe* detalhe = comum::CEleitores::GetInst().GetCurrent();
    const comum::md::CEleitorIdentidade identidade =
        detalhe->GetEleitor().GetIdentidadePorTipo(detalhe->GetEleitor().GetTipoIdentificador());
    SetIdentidadeDigitada(identidade.GetIdentificador());
    SetTipoIdentidadeDigitada(identidade.GetTipo());
    return &CNomeEleitor::GetInst();
}

} // namespace vota
