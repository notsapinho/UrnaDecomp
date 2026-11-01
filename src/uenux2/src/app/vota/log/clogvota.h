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
// 10420). Their names are chosen from their messages too. So is LogaVotacaoEncerrada's, held inlined by its one
// caller, vota::CAplicacaoEncerrada::StartState (fn 12058; unit 138's fragment has its notes). This header's path is
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

private:
    CLogVota();
};

} // namespace vota
