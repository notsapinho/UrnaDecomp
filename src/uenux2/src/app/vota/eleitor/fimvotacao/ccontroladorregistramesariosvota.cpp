// vota::CControladorRegistraMesariosVota: no record names this file or any of its members. The reconstruction's notes
// are in unit 119's fragment, and the members it leaves pending are in its -pending.cpp.

#include "app/vota/eleitor/fimvotacao/ccontroladorregistramesariosvota.h"

#include <format>
#include <string>
#include <vector>

#include "app/vota/log/clogvota.h"
#include "app/vota/operador/cfinalizaoperador.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

uebyte CControladorRegistraMesariosVota::AddTick(size_t milissegundos)
{
    return CThreadOperador::GetInst().AddTick(milissegundos);
}

void CControladorRegistraMesariosVota::StopTick(uebyte id)
{
    CThreadOperador::GetInst().StopTick(id);
}

void CControladorRegistraMesariosVota::StartTick(uebyte id)
{
    CThreadOperador::GetInst().StartTick(id);
}

bool CControladorRegistraMesariosVota::Slot8()
{
    return true;
}

comum::CAppState& CControladorRegistraMesariosVota::Slot12()
{
    return CFinalizaOperador::GetInst();
}

const std::string& CControladorRegistraMesariosVota::GetTituloMesario()
{
    return CThreadOperador::GetInst().GetTituloMesario();
}

void CControladorRegistraMesariosVota::SetTituloMesario(const std::string& titulo)
{
    CThreadOperador::GetInst().SetTituloMesario(titulo);
}

void CControladorRegistraMesariosVota::LogaMesarioRegistrado(const std::string& titulo)
{
    CLogVota::GetInst().LogaMesarioRegistrado(titulo);
}

void CControladorRegistraMesariosVota::LogaRegistrandoMesariosAntesVotacao()
{
    CLogVota::GetInst().loga("Registrando mesários antes da votação");
}

void CControladorRegistraMesariosVota::LogaRegistrandoMesariosDuranteVotacao()
{
    CLogVota::GetInst().loga("Registrando mesários durante a votação");
}

void CControladorRegistraMesariosVota::LogaRegistrandoMesariosAposVotacao()
{
    CLogVota::GetInst().loga("Registrando mesários após a votação");
}

void CControladorRegistraMesariosVota::LogaIndagaRegistroMesarios()
{
    CLogVota::GetInst().LogaIndagaRegistroMesarios();
}

void CControladorRegistraMesariosVota::LogaConfirmouRegistroMesarios()
{
    CLogVota::GetInst().loga("Operador confirmou o registro de mesários");
}

void CControladorRegistraMesariosVota::LogaCancelouRegistroMesarios()
{
    CLogVota::GetInst().loga("Operador cancelou o registro de mesários");
}

void CControladorRegistraMesariosVota::LogaTituloInvalidoRegistroMesario()
{
    CLogVota::GetInst().LogaTituloInvalidoRegistroMesario();
}

void CControladorRegistraMesariosVota::LogaMesarioJaRegistrado(const std::string& titulo)
{
    CLogVota::GetInst().LogaMesarioJaRegistrado(titulo);
}

void CControladorRegistraMesariosVota::LogaEncerrouCicloRegistro()
{
    CLogVota::GetInst().loga("Operador encerrou ciclo de registro de mesários");
}

void CControladorRegistraMesariosVota::LogaDigitalNaoCorresponde(const std::vector<int>& scores)
{
    CLogVota::GetInst().loga(std::format("Digital capturada não corresponde a digital do eleitor: Polegar Direito [score {}], "
                                         "Polegar Esquerdo [score {}], Indicador Direito [score {}], Indicador Esquerdo [score {}]",
                                         scores[0], scores[1], scores[2], scores[3]));
}

void CControladorRegistraMesariosVota::LogaPedidoBiometriaMesario()
{
    CLogVota::GetInst().loga(std::format("Pedido de leitura da biometria do mesário {}", CThreadOperador::GetInst().GetTituloMesario()));
}

void CControladorRegistraMesariosVota::LogaMesarioEleitorDaSecao()
{
    CLogVota::GetInst().loga(std::format("Mesário {} é eleitor da seção", CThreadOperador::GetInst().GetTituloMesario()));
}

void CControladorRegistraMesariosVota::LogaMesarioNaoEleitorDaSecao()
{
    CLogVota::GetInst().loga(std::format("Mesário {} não é eleitor da seção", CThreadOperador::GetInst().GetTituloMesario()));
}

void CControladorRegistraMesariosVota::LogaConferenciaBiometriaMesario()
{
    CLogVota::GetInst().loga("Realizada a conferência da biometria do mesário");
}

void CControladorRegistraMesariosVota::LogaIndagaContinuaRegistro()
{
    CLogVota::GetInst().loga("Operador indagado se continua registrando mesários");
}

void CControladorRegistraMesariosVota::LogaIndagaFinalizaRegistro()
{
    CLogVota::GetInst().loga("Operador indagado se finaliza registro mesários");
}

} // namespace vota
