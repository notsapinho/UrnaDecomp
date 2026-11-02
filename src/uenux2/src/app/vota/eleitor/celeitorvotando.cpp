// Reconstruction's note, not TSE's text: vota::CEleitorVotando's constructor, GetInst, destructor, FinishState,
// RegistraVoto, ChamaEstadoProximoCargo (record :229), ProcessTick, ProcessInput and the free MostraCargoNoOperador
// are written; 125, 131, 253, 254, 294, 410 and 427 are records of members not written; other lines are chosen.
#include "app/vota/eleitor/celeitorvotando.h"

#include <string>

#include "api/gui/capplication.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/eleitor/cconfirmavotosemcandidato.h"
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

// (original lines 53-139: content not recovered)
#line 140
void CEleitorVotando::FinishState()
{
    CThreadOperador::GetInst().SetTextoEleitor(" ");
    api::CApplication::s_contextos.Pop(m_contexto);
}

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

// (original lines 199-212: content not recovered)
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

// (original lines 242-249: content not recovered)
#line 250
// <stubs>
// f4449 · 352 B · unmatched · name unknown
// void f4449(i32) { ... }
// </stubs>

// (original lines 255-299: content not recovered)
#line 300
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
