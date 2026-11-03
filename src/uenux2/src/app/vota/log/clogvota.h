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
// LogaImprimindoRelatorio, LogaMesarioIndagadoQualidadeBU, LogaQtdViasAdicionaisExcedeMaximo and
// LogaHabilitacaoCanceladaReconhecimentoBiometrico (fns 1127, 4551, 4556 and 2495) are out of line, each called with
// GetInst's result: 1127 by ten printing states' slots, 4551 by vota::CImprimindoBU's two, 4556 by
// vota::CLimiteCopiasBUAtingido::StartState (fn 12027) and fn 12081, and 2495 by four operador states' slots (unit 156's
// fragment has them). 1127 and 4551 call fn 233, which ieventoslog.cpp's members hold inlined, so they are in another
// TU, this one (a reading); 4556 and 2495 log through logaAlerta (fn 1398), and the target holds both as thunks of one
// merged body, fn 6115. Their names are chosen from their messages. LogaMesarioIndagadoQtdViasAdicionais and
// LogaMesarioNaoSolicitouViasAdicionais (fns 4563 and 4557) are 4551's shape, out of line and calling fn 233, each
// called with GetInst's result: 4563 by vota::CEmitirMaisBU::StartState (fn 12082) and ProcessInput (fn 12081), 4557
// twice by 12081; their names are chosen from their messages.
// LogaAguardandoHorarioZeresima (held inlined by vota::CVerificaHorarioZeresima::StartState, fn 11871) and
// LogaDataEleicaoInvalida (by vota::CVerificaEleicaoPassou::StartState, fn 11914) are the shape of the members held
// inlined above, GetInst called before the member's own stack frame opens, each calling api::CLoga::loga (fn 433) with
// +4, severity 1 and 2.
// LogaErroEstadoAplicativoDesconhecido (fn 3279: logaErro, fn 2282) and LogaFimTesteTecladoSucesso (fn 4511: loga, fn
// 233) are out of line, each called with GetInst's result: 3279 twice by fn 7160 and once by
// vota::CDefineRotaPosReinicio::NeedChangeState (fn 11858), 4511 twice by fn 11804. Their names are chosen from their
// messages.
// LogaTesteTecladoNaoExecutado is the shape of the members held inlined above: vota::testeteclado::CBase::ProcessInput
// (fn 11874) calls GetInst before the member's own stack frame opens and calls fn 233; its name is chosen from its
// message. LogaInicioTesteTeclado is that shape too: vota::testeteclado::CTesteTeclado::StartState (fn 11805) calls
// GetInst before the member's own stack frame opens and calls fn 233 with "Início do teste de Teclado do TE"; its name
// is chosen from its message.
// LogaAguardandoConfirmacaoZeresima is the same shape again: fn 5958, the StartState of
// vota::CConfirmaImpressaoZeresima and vota::CConfirmaRegerarZeresima (one body for both), calls GetInst before the
// member's own stack frame opens and calls fn 233; its name is chosen from its message. LogaMesarioConfirmouReinicioVotacao
// and LogaMesarioSelecionouOutrasOpcoes (held inlined by vota::CReinicioVotacao::ProcessInput, fn 11834),
// LogaApresentadaTelaReinicioVotacao (by vota::CReinicioVotacao::StartState, fn 11835) and
// LogaMesarioIndagadoHorarioUrna (by vota::CImpressaoZeresimaTardia::StartState, fn 11932) are the same shape: each
// caller calls GetInst before the member's own stack frame opens; the first three call api::CLoga::loga (fn 433) with +4
// and severity 1, the fourth calls fn 233. That they are members of this class and not of comum::IEventosLog follows the
// members above, a reading; their names are chosen from their messages. LogaTempoLimiteBateriaInterna (held inlined by
// vota::CExibeAlertaDesligamento::ProcessTick, fn 12017: api::CLoga::loga with +4 and severity 2),
// LogaErroIdentificacaoTipoCargo (by vota::CEleitorVotando::ChamaEstadoProximoCargo, fn 4459: logaErro, fn 2282) and
// LogaEleitorVoltouADigitar (by vota::CEleitorVotando::ProcessInput, fn 7345: loga, fn 233) are that shape too, GetInst
// called before the member's own stack frame opens; their names are chosen from their messages. This header's path is
// chosen, beside clogvota.cpp, and only the members written are declared.
// The five LogaVoto* members are out of line, each a 17-byte thunk of one body binaryen merged (fn 2302: the post's
// neutral name, comum::CConfiguracaoEleicao::GetCargo(cargo).GetNomeNeutro(), formatted into its message and passed to
// loga, fn 233), with the message's begin and end as the two constants: fns 3272, 4546, 4542, 4541 and 4537, each
// called with GetInst's result and a post's id by vota::CEleitorVotando::RegistraVoto (fn 4471) and by
// suspenderEleitor (fn 4442), which makes RegistraVoto's calls. Their names are chosen from their messages, and their
// parameter's type from GetCargo's.
// LogaQuantidade (fn 3268) is out of line, the last member of clogvota.cpp (its band puts it after fns 3279 and 3272),
// called three times by vota::CThreadMonitor::Run (fn 10226, unit 116's, written) with GetInst's result and a temporary
// of a name (a std::string at +0) and a 64-bit count (+16); it logs "Quantidade de {} [{}]" of the name and
// comum::FormataTamanho (fn 1947) of the count's low word, through fn 233. Its name, its being a member (a free
// function over a comum::IEventosLog& gives the same object) and the std::pair are chosen; fragment 234 has its
// evidence. Its iinterfaceinit.h include (comum::FormataTamanho) is in this header, not in clogvota.cpp, so that
// GetInst's record stays on line 37 of the .cpp: a choice made for that record's line.

#include <cstdint>
#include <string>
#include <utility>

#include "app/comum/iinterfaceinit.h"
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
    // Held inlined by vota::CRegistraDigitalOperador::StartState (fn 10454), its one caller, which calls GetInst before
    // the member's own stack frame opens and calls fn 233 with the message. The name is chosen from its message, and
    // its place here and in clogvota.cpp, after LogaHabilitacaoCanceladaCapturaDigitalMesario, is chosen: it has no
    // index to order.
    void LogaSolicitaDigitalMesario();
    // Held inlined by vota::CPedeIdentidade::ProximoEstadoIdentidadeDigitada (inlined into fn 10677), its one caller,
    // which calls GetInst before the member's own stack frame opens; it calls api::CLoga::loga (fn 433) with +4 and
    // severity 1. The name is chosen from its message, and its place here and in clogvota.cpp is chosen: it has no
    // index to order.
    void LogaIdentificadorDigitadoMesario();
    // Out of line (fn 4550: logaErro, fn 2282), called with GetInst's result by vota::CVotacaoStateAudio::FormatPartyName
    // (fn 6954) and vota::CPedeMajoritario's fn 11683. Its name is chosen from its message.
    void LogaErroPartidoNaoEncontrado();
    // Held inlined by vota::CVotacaoStateAudio::PlayKey (fn 1455), its one caller, which calls GetInst before the
    // member's own stack frame opens; it logs "Tecla indevida pressionada" through loga (fn 233), a literal only fn
    // 1455 loads. Its name is chosen from its message, and its place here and in clogvota.cpp, after
    // LogaErroPartidoNaoEncontrado, is chosen: it has no index to order.
    void LogaTeclaIndevida();
    // Held inlined by the slot 17 of vota::CConfirmaVotoNominal and vota::CMajoritarioValido (fn 5925, one body for
    // both), which calls GetInst before the member's own stack frame opens; it logs "Eleitor corrigiu na tela de confirmação de candidato"
    // through loga (fn 233). Its name is chosen from its message, and its place here and in clogvota.cpp, after
    // LogaTeclaIndevida, is chosen: it has no index to order.
    void LogaEleitorCorrigiuConfirmacaoCandidato();

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
    // "Áudio ativado conforme cadastro": vota::CHabilitaAudioEleitor::ProcessInput (target fn 10523) holds it as binaryen
    // inlines a function into its one caller (a second stack frame around the literal and comum::IEventosLog::loga, fn
    // 233). The member's name is chosen from its text, as its neighbours' are.
    void LogaAudioAtivadoConformeCadastro();
    void LogaSuspensaoAbortada();
    void LogaJustificativaRecebida();
    void LogaEleitorJaJustificou();
    void LogaPedidoTituloSuspensao();
    // Held inlined by vota::CPerguntaCodigoSuspensao::ProcessInput (fn 10420), their one caller, after GetInst: the
    // first logs through loga (fn 233), the other two format the title into their message and log through logaAlerta
    // (fn 1398). The names are chosen from their messages.
    void LogaTituloSuspensaoDigitado();
    void LogaTituloSuspensaoInvalido(const std::string& titulo);
    void LogaTituloSuspensaoValido(const std::string& titulo);
    // The copy number is byte-wide: every target caller that passes a computed number masks it to 8 bits (11852, 11855
    // and 11991 their loop counter, 12065 and 12081 a byte plus one), which a uebyte parameter gives; its spelling is
    // chosen.
    void LogaImprimindoRelatorio(comum::ERelatoriosUE relatorio, uebyte via);
    void LogaMesarioIndagadoQtdViasAdicionais();
    void LogaMesarioNaoSolicitouViasAdicionais();
    void LogaMesarioIndagadoQualidadeBU();
    void LogaQtdViasAdicionaisExcedeMaximo();
    void LogaHabilitacaoCanceladaReconhecimentoBiometrico();
    void LogaVotacaoEncerrada();
    void LogaAguardandoConfirmacaoZeresima();
    void LogaAguardandoHorarioZeresima();
    // Held inlined by vota::CPedeIdentidade::StartState (fn 10680), its one caller, the shape of
    // LogaAguardandoHorarioZeresima (CLoga::loga, fn 433, with +4 and severity 1). The name is chosen from its message,
    // and its place here and in clogvota.cpp, after LogaAguardandoHorarioZeresima, is chosen: it has no index to order.
    void LogaAguardandoIdentificadorEleitor();
    void LogaDataEleicaoInvalida();
    void LogaErroEstadoAplicativoDesconhecido();
    void LogaFimTesteTecladoSucesso();
    void LogaTesteTecladoNaoExecutado();
    void LogaInicioTesteTeclado();
    void LogaMesarioConfirmouReinicioVotacao();
    void LogaMesarioSelecionouOutrasOpcoes();
    void LogaApresentadaTelaReinicioVotacao();
    void LogaMesarioIndagadoHorarioUrna();
    // The shape of LogaMesarioIndagadoHorarioUrna, GetInst called before the member's own stack frame opens, each
    // calling loga (fn 233): held inlined by vota::CImpressaoZeresimaTardia::ProcessInput (fn 11931), the first on
    // CORRIGE, the second on CONFIRMA. Their names, and their place here and in clogvota.cpp, after
    // LogaMesarioIndagadoHorarioUrna, are chosen from their messages: they have no index to order.
    void LogaMesarioConfirmaHorarioUrnaErrado();
    void LogaMesarioConfirmaHorarioUrnaCorreto();
    // The same shape, calling loga (fn 233): held inlined by vota::CImprimindoBU::ProcessInput (fn 12077), the first on
    // CORRIGE, the second on CONFIRMA. Names and place chosen as above.
    void LogaMesarioIndicouReimprimirBU();
    void LogaMesarioIndicouQualidadeBU();
    // The same shape, calling api::CLoga::loga (fn 433) with +4 and severity 1: held inlined by
    // vota::CRetirarMR::StartState (fn 12031), before and after its wait for the removal of the results medium. Names
    // and place chosen as above.
    void LogaSolicitadaRetiradaMR();
    void LogaMRRetirada();
    // The same shape, calling loga (fn 233) with the count formatted as unsigned (argument code 6) and "via adicional"
    // or "vias adicionais" appended, the latter the tail of LogaMesarioIndagadoQtdViasAdicionais's text: held inlined
    // by vota::CEmitirMaisBU::ProcessInput (fn 12081). Name, parameter type and place chosen as above.
    void LogaSolicitadaEmissaoViasAdicionais(uebyte quantidade);
    void LogaTempoLimiteBateriaInterna();
    void LogaErroIdentificacaoTipoCargo();
    void LogaEleitorVoltouADigitar();
    void LogaVotoCargoSemCandidatoPorSuspensao(uebyte cargo);
    void LogaVotoBrancoPorSuspensao(uebyte cargo);
    void LogaVotoCargoSemCandidato(uebyte cargo);
    void LogaVotoNuloPorSuspensao(uebyte cargo);
    void LogaVotoConfirmado(uebyte cargo);
    // The shape of the members held inlined above, GetInst called before the member's own stack frame opens:
    // LogaErroVerificacaoComparecimento ("Erro na verificação do comparecimento", logaErro, fn 2282) by
    // vota::CQuerReimprimirZeresima::StartState (fn 11849), which logs it before it throws the same text;
    // LogaFinalizacaoAplicativo and LogaDesligandoUrna ("Finalização de aplicativo", "Desligando a urna", api::CLoga::loga,
    // fn 433, with +4 and severity 1) by vota::CInformacaoZeresimaTardia::ProcessInput (fn 11982), one after the other.
    // Their names are chosen from their messages.
    void LogaErroVerificacaoComparecimento();
    void LogaFinalizacaoAplicativo();
    void LogaDesligandoUrna();

    // Held inlined by vota::CThreadMonitor::Run (fn 10226), each after a call of GetInst and in a stack frame of its own:
    // the first logs through api::CLoga::loga (fn 433) with +4 and severity 1, the other four format
    // comum::FormataTamanho (fn 1947) of the low word of their 64-bit argument into their message and log through loga
    // (fn 233). Their names, and their parameter's type (a 64-bit unsigned, what GetFreeSpace and GetUsedSpace return),
    // are chosen from their messages and their callers.
    void LogaMudancaChaveUrnaDesligada();
    void LogaEspacoLivreMI(uintmax_t espaco);
    void LogaEspacoLivreMV(uintmax_t espaco);
    void LogaEspacoUtilizadoMI(uintmax_t espaco);
    void LogaEspacoUtilizadoMV(uintmax_t espaco);

    // The shape of the members held inlined above, each calling loga (fn 233), each held by its one caller, which calls
    // GetInst before the member's own stack frame opens: LogaInspecaoTerminada ("Inspeção da urna terminada") by
    // vota::CConfirmaInspecionada::ProcessInput (fn 10527); LogaEleitorSuspensoTreinamento ("Eleitor foi suspenso
    // automaticamente no treinamento eleitor"), LogaEleitorSuspensoPeloMesario ("Eleitor foi suspenso pelo mesário")
    // and LogaEleitorVotouParcialmenteSuspenso ("Eleitor votou parcialmente e em seguida foi suspenso") by
    // vota::CEleitorVotando::suspenderEleitor (fn 4442), the first two after one call of GetInst; and
    // LogaEleitorSuspensoSemVoto ("Eleitor foi suspenso e não confirmou nenhum voto") by
    // vota::CEleitorVotando::DescartaVotos (fn 4449). Each literal is loaded by its caller alone. Their names are chosen
    // from their messages, and their place here and in clogvota.cpp, before LogaQuantidade, is chosen: they have no
    // index to order.
    void LogaInspecaoTerminada();
    void LogaEleitorSuspensoTreinamento();
    void LogaEleitorSuspensoPeloMesario();
    void LogaEleitorVotouParcialmenteSuspenso();
    void LogaEleitorSuspensoSemVoto();

    void LogaQuantidade(const std::pair<std::string, uint64_t>& quantidade);

private:
    CLogVota();
};

} // namespace vota
