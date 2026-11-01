#pragma once

// vota::CLogVota: the vota application's comum::IEventosLog. RTTI gives the class, a si_class over comum::IEventosLog,
// and its vtable (@1532784) holds only the two destructors, the shared bodies 174 and 144, so it adds no virtual member.
// Fn 184, GetInst, allocates 8 bytes for it and stores the application code 1 at +4 through the base's constructor, so it
// adds no data member. GetInst's record is clogvota.cpp:37; LogaEleitorImpedido's (clogvota.cpp:432, in fn 10635) names a
// member not written here. The four Loga members have no record: each is held inlined by its one caller, a slot of
// vota::CControladorRegistraMesariosVota that calls GetInst first and then runs the member in a stack frame of its own
// (fns 6017, 10779, 10776), so they are members of the object GetInst returns, and their names are chosen from their
// messages. LogaJustificativaRecebida, LogaEleitorJaJustificou and LogaPedidoTituloSuspensao are the same shape: each is
// held inlined by one state's slot, which calls GetInst before the member's own stack frame opens (fn 10594, of
// vota::CJustificativaEfetuada, holds the first two; fn 10421, of vota::CPerguntaCodigoSuspensao, the third, which calls
// comum::IEventosLog::loga, fn 233). LogaIndagaEleitorVotando, LogaPedidoDesconexaoFone, LogaPedidoConexaoFone,
// LogaHorarioVotacaoTerminou and LogaInspecaoIniciada are that shape too, held inlined by the StartState of five states
// (fns 10416, 10436, 10524, 10758 and 11798); LogaAudioDesativadoFimVotacao and LogaSuspensaoAbortada (fns 4529 and
// 4535) are out of line, each called with GetInst's result by two states' slots (fns 10435 and 10646; 10407 and
// 10420). LogaEleitorJaVotou, LogaIdentificadorEleitorInvalido and LogaSolicitacaoDadoPessoalEleitor, right after
// GetInst, are that shape too, held inlined by fns 10642, 10669 and 10444; LogaHabilitacaoCanceladaConfirmacaoDado and
// LogaHabilitacaoCanceladaCapturaDigitalMesario (fns 2097 and 4522) are out of line, called with GetInst's result by
// five states' slots and by two slots of vota::CRegistraDigitalOperador (unit 161's fragment has them). Their names
// are chosen from their messages too. So is LogaVotacaoEncerrada's, held inlined by its one
// caller, vota::CAplicacaoEncerrada::StartState (fn 12058; unit 138's fragment has its notes).
// LogaAguardandoConfirmacaoZeresima is the same shape again: fn 5958, the StartState of
// vota::CConfirmaImpressaoZeresima and vota::CConfirmaRegerarZeresima (one body for both), calls GetInst before the
// member's own stack frame opens and calls fn 233; its name is chosen from its message. LogaMesarioConfirmouReinicioVotacao
// and LogaMesarioSelecionouOutrasOpcoes (held inlined by vota::CReinicioVotacao::ProcessInput, fn 11834) and
// LogaMesarioIndagadoHorarioUrna (by vota::CImpressaoZeresimaTardia::StartState, fn 11932) are the same shape: each
// caller calls GetInst before the member's own stack frame opens; the first two call api::CLoga::loga (fn 433) with +4
// and severity 1, the third calls fn 233. That they are members of this class and not of comum::IEventosLog follows the
// members above, a reading; their names are chosen from their messages. LogaTempoLimiteBateriaInterna (held inlined by
// vota::CExibeAlertaDesligamento::ProcessTick, fn 12017: api::CLoga::loga with +4 and severity 2),
// LogaErroIdentificacaoTipoCargo (by vota::CEleitorVotando::ChamaEstadoProximoCargo, fn 4459: logaErro, fn 2282) and
// LogaEleitorVoltouADigitar (by vota::CEleitorVotando::ProcessInput, fn 7345: loga, fn 233) are that shape too, GetInst
// called before the member's own stack frame opens; their names are chosen from their messages. This header's path is
// chosen, beside clogvota.cpp, and only the members written are declared.

#include <string>

#include "app/comum/log/ieventoslog.h"

namespace vota {

class CLogVota : public comum::IEventosLog {
public:
    static CLogVota& GetInst();

    void LogaEleitorJaVotou();
    void LogaIdentificadorEleitorInvalido();
    void LogaSolicitacaoDadoPessoalEleitor();
    void LogaHabilitacaoCanceladaConfirmacaoDado();
    void LogaHabilitacaoCanceladaCapturaDigitalMesario();

    void LogaMesarioRegistrado(const std::string& titulo);
    void LogaMesarioJaRegistrado(const std::string& titulo);
    void LogaIndagaRegistroMesarios();
    void LogaTituloInvalidoRegistroMesario();
    void LogaIndagaEleitorVotando();
    void LogaPedidoDesconexaoFone();
    void LogaPedidoConexaoFone();
    void LogaHorarioVotacaoTerminou();
    void LogaInspecaoIniciada();
    void LogaAudioDesativadoFimVotacao();
    void LogaSuspensaoAbortada();
    void LogaJustificativaRecebida();
    void LogaEleitorJaJustificou();
    void LogaPedidoTituloSuspensao();
    void LogaVotacaoEncerrada();
    void LogaAguardandoConfirmacaoZeresima();
    void LogaMesarioConfirmouReinicioVotacao();
    void LogaMesarioSelecionouOutrasOpcoes();
    void LogaMesarioIndagadoHorarioUrna();
    void LogaTempoLimiteBateriaInterna();
    void LogaErroIdentificacaoTipoCargo();
    void LogaEleitorVoltouADigitar();

private:
    CLogVota();
};

} // namespace vota
