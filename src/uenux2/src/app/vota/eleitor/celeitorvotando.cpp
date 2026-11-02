// Reconstruction's note, not TSE's text: vota::CEleitorVotando's members but ProcessKey, DescartaVotos and
// suspenderEleitor, and the free MostraCargoNoOperador, are written; 253, 254, 410 and 427 are records of members not
// written; the lines of the members with no record are chosen (src/units/197-uenux2-celeitorvotando.mk).
#include "app/vota/eleitor/celeitorvotando.h"

#include <string>

#include "api/gui/capplication.h"
#include "api/gui/iscreen.h"
#include "api/hwil/ibeep.h"
#include "api/hwil/iinput.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/crdvvota.h"
#include "app/vota/eleitor/cconfirmavotosemcandidato.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/cinstrucaovotacaoacessibilidade.h"
#include "app/vota/eleitor/csincronismoeleitor.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/votamajoritario/cpedemajoritario.h"
#include "app/vota/eleitor/votaproporcional/cpedeproporcional.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CEleitorVotando::CEleitorVotando()
    : comum::CAppState(EVENTO_TECLA | EVENTO_ENTRADA | EVENTO_TICK)
    , m_pEstado(nullptr)
    , m_emSuspensao(false)
    , m_vindoDaInstrucao(false)
    , m_contexto(api::CriaContextoAplicacao(11, "Erro inesperado durante a votação",
                                            "O voto do eleitor NÃO foi registrado",
                                            "Ocorreu um erro enquanto o eleitor registrava suas escolhas."))
{
    const auto& parametros = comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna();
    const uedword tempo = comum::CAppInfo::EhTreinamentoEleitor() ? parametros.GetTempoDispararSuspensaoTE()
                                                                   : parametros.GetTempoDispararSuspensao();
    m_tick = CThreadEleitor::GetInst().AddStoppedTick(tempo * 1000);
}

CEleitorVotando& CEleitorVotando::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorVotando());
    }
    return *s_inst;
}

std::unique_ptr<CEleitorVotando> CEleitorVotando::s_inst;
std::mutex CEleitorVotando::s_mutex;

CEleitorVotando::~CEleitorVotando() = default;

void CEleitorVotando::RegistraVoto(const comum::md::TCargoID cargo, const comum::md::CVoto::ETipo tipo,
                                   const std::string& numero)
{
    AdicionaVoto(cargo, comum::md::CVoto(tipo, numero));
    auto& log = CLogVota::GetInst();
    switch (tipo) {
    case comum::md::CVoto::BRANCO_APOS_SUSPENSAO:
        log.LogaVotoBrancoPorSuspensao(cargo);
        break;
    case comum::md::CVoto::NULO_APOS_SUSPENSAO:
        log.LogaVotoNuloPorSuspensao(cargo);
        break;
    case comum::md::CVoto::NULO_CARGO_SEM_CANDIDATO:
        log.LogaVotoCargoSemCandidato(cargo);
        break;
    case comum::md::CVoto::NULO_APOS_SUSPENSAO_CARGO_SEM_CANDIDATO:
        log.LogaVotoCargoSemCandidatoPorSuspensao(cargo);
        break;
    default:
        log.LogaVotoConfirmado(cargo);
        break;
    }
}

// (original lines 86-115: content not recovered)
#line 116
void CEleitorVotando::StartState()
{
    api::CApplication::PushContext(m_contexto);
    CThreadOperador::GetInst().GetMensagens().Post(6);
    IniciaCiclo();
}

void CEleitorVotando::IniciaCiclo()
{
    auto& monitor = api::CPolySingleton<api::IScreen>::instance();
    monitor.Clear(static_cast<api::TColor>(1));
    monitor.Refresh();
    monitor.Slot14();


    auto& keys = api::CPolySingleton<api::IInputKbd>::instance();
    keys.Slot7();
    CThreadEleitor::GetInst().StartTick(m_tick);
    m_emSuspensao = false;
    m_vindoDaInstrucao = false;
    m_pNextState = this;
    g_numeroDigitado.clear();
    g_votosEleitor.Limpa();
    g_escolhaAtual = 1;

    const auto abrangencia = comum::CEleitores::GetInst().GetCurrentAbrangenciaEleitor();
    auto& cargos = comum::CCargos::GetInst();
    cargos.FiltraPorAbrangencia(abrangencia);
    cargos.OrdenaPorAquisicao();
    cargos.Reset();
    keys.Clear();

    if (cargos.IsFim()) {
        TerminaEstado();
    } else if (CEstadoAudio::GetInst().Ativo()) {
        auto& operador = CThreadOperador::GetInst();
        operador.SetTextoEleitor("Tela de instrução de acessibilidade");
        operador.GetMensagens().Post(9);
        comum::CAppState* proximo = &CInstrucaoVotacaoAcessibilidade::GetInst();
        if (m_pEstado != nullptr) {
            m_pEstado->FinishState();
        }
        m_pEstado = proximo;
        SetNumeroDigitado("");
        m_vindoDaInstrucao = true;
        if (m_pEstado != nullptr) {
            m_pEstado->StartState();
        }
    } else {
        MostraCargoNoOperador(cargos.GetCurrent());
        ChamaEstadoProximoCargo();
    }
}

// (original lines 170-172: content not recovered)
#line 173
void CEleitorVotando::FinishState()
{
    CThreadOperador::GetInst().SetTextoEleitor(" ");
    api::CApplication::s_contextos.Pop(m_contexto);
}

void MostraCargoNoOperador(const comum::md::CCargo& cargo)
{
    std::string texto = "";
    const char prefixo[] = "VOTANDO PARA: ";
    if (cargo.HasDetalheCandidato()) {
        texto = prefixo + (cargo.GetQtdeEscolhas() == 1
                               ? cargo.GetNomeNeutro()
                               : cargo.GetNomeNeutro() + " - " + cargo.GetOrdinalEscolha(g_escolhaAtual));
        if (texto.size() > 40) {
            texto = prefixo + (cargo.GetQtdeEscolhas() == 1
                                   ? cargo.GetNomeAbreviado()
                                   : cargo.GetNomeAbreviado() + " - " + cargo.GetOrdinalEscolha(g_escolhaAtual));
        }
    } else {
        texto = prefixo + cargo.GetNomeAbreviado();
        if (texto.size() > 40) {
            texto.resize(40);
        }
    }
    auto& operador = CThreadOperador::GetInst();
    operador.SetTextoEleitor(texto);
    operador.GetMensagens().Post(9);
}

// <stubs>
// f5500 · 6871 B · unmatched · placement: link order · name unknown
// void f5500(i32, i32) { ... }
// </stubs>

// (original lines 208-212: content not recovered)
#line 213
void CEleitorVotando::ChamaEstadoProximoCargo()
{
    const auto& cargos = comum::CCargos::GetInst();
    const auto& candidaturas = comum::CCandidaturas::GetInst();
    const auto& cargo = cargos.GetCurrent();
    const auto candidatos = candidaturas.GetCandidatos(cargo.GetID());
    comum::CAppState* proximo;
    if (candidatos.size() == 0 && !cargo.IsConsulta()) {
        proximo = &CConfirmaVotoSemCandidato::GetInst();
    } else {
        if (cargo.IsMajoritario() || cargo.IsConsulta()) {
            proximo = &CPedeMajoritario::GetInst();
        } else if (cargo.IsProporcional()) {
            proximo = &CPedeProporcional::GetInst();
        } else {
            CLogVota::GetInst().LogaErroIdentificacaoTipoCargo();
            throw CUeVotaError(EUE_VOTA_TIPO_CARGO_NAO_IDENTIFICADO, "Tipo de cargo nao identificado");
        }
    }
    if (m_pEstado != nullptr) {
        m_pEstado->FinishState();
    }
    m_pEstado = proximo;
    SetNumeroDigitado("");
    if (m_pEstado != nullptr) {
        m_pEstado->StartState();
    }
}

void CEleitorVotando::FinalizaEleitor()
{
    CThreadEleitor::GetInst().StopTick(m_tick);
    comum::CRdvVota::GetInst().RecebeCedula(g_votosEleitor);
    comum::CAppInfo::GetInst().GetVota().MarcaUltimoVoto();
    m_pNextState = &CSincronismoEleitor::GetInst();
    TerminaEstado();
}

// <stubs>
// f4449 · 352 B · unmatched · name unknown
// void f4449(i32) { ... }
// </stubs>

// (original lines 256-261: content not recovered)
#line 262
bool CEleitorVotando::NeedChangeState()
{
    if (m_pEstado == nullptr) {
        CThreadEleitor::GetInst().StopTick(m_tick);
        return true;
    }
    if (!m_pEstado->NeedChangeState()) {
        return false;
    }
    comum::CAppState* proximo = m_pEstado->GetNextState();
    if (proximo != nullptr) {
        if (m_pEstado != nullptr) {
            m_pEstado->FinishState();
        }
        m_pEstado = proximo;
        m_pEstado->StartState();
        return false;
    }
    if (m_vindoDaInstrucao) {
        m_vindoDaInstrucao = false;
    } else {
        auto& cargos = comum::CCargos::GetInst();
        if (!cargos.IsFim()) {
            if (cargos.GetCurrent().GetQtdeEscolhas() == g_escolhaAtual) {
                cargos.Next();
                g_escolhaAtual = 1;
            } else {
                g_escolhaAtual++;
            }
        }
    }
    auto& cargos = comum::CCargos::GetInst();
    auto& sinal = api::CPolySingleton<api::IBeep>::instance();
    const bool fim = cargos.IsFim();
    sinal.BeepConfirm(1);
    if (fim) {
        FinalizaEleitor();
        return true;
    }
    MostraCargoNoOperador(cargos.GetCurrent());
    ChamaEstadoProximoCargo();
    return false;
}

void CEleitorVotando::ProcessTick(uebyte tick)
{
    if (tick == m_tick) {
        CThreadEleitor::GetInst().StopTick(m_tick);
        if (comum::CCargos::GetInst().IsPrimeiro() && g_escolhaAtual == 1) {
            CThreadOperador::GetInst().GetMensagens().Post(3);
        } else {
            CThreadOperador::GetInst().GetMensagens().Post(4);
        }
        m_emSuspensao = true;
    } else if (m_pEstado != nullptr) {
        m_pEstado->ProcessTick(tick);
    }
}

void CEleitorVotando::ProcessInput()
{
    auto& thread = CThreadEleitor::GetInst();
    thread.StopTick(m_tick);
    thread.StartTick(m_tick);
    if (m_emSuspensao) {
        CThreadOperador::GetInst().GetMensagens().Post(5);
        CLogVota::GetInst().LogaEleitorVoltouADigitar();
        m_emSuspensao = false;
    }
    if (m_pEstado != nullptr) {
        m_pEstado->ProcessInput();
    }
}

} // namespace vota


// <stubs>
// f4442 · 1183 B · unmatched · name unknown
// void f4442(i32, i32) { ... }
// </stubs>
