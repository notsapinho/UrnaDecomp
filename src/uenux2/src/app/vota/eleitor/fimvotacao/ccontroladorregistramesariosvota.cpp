// vota::CControladorRegistraMesariosVota: no record names this file or any of its members. The reconstruction's notes
// are in unit 119's fragment, and the members it leaves pending are in its -pending.cpp.

#include "app/vota/eleitor/fimvotacao/ccontroladorregistramesariosvota.h"

#include <format>
#include <string>
#include <vector>

#include "app/comum/appinfo/cappinfo.h"
#include "app/vota/eleitor/fimvotacao/cregistromesarioencerrado.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/cfinalizaoperador.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

uebyte CControladorRegistraMesariosVota::AddTick(size_t milissegundos) const
{
    return CThreadOperador::GetInst().AddTick(milissegundos);
}

void CControladorRegistraMesariosVota::StopTick(uebyte id) const
{
    CThreadOperador::GetInst().StopTick(id);
}

void CControladorRegistraMesariosVota::StartTick(uebyte id) const
{
    CThreadOperador::GetInst().StartTick(id);
}

int CControladorRegistraMesariosVota::Slot6() const
{
    switch (comum::CAppInfo::GetInst().GetVota().GetEstadoVota()) {
        case 55:
            return 1;
        case 56:
            return 2;
        case 58:
            return 3;
        default:
            return 0;
    }
}

bool CControladorRegistraMesariosVota::Slot8() const
{
    return true;
}

comum::CAppState& CControladorRegistraMesariosVota::Slot11() const
{
    return CRegistroMesarioEncerrado::GetInst();
}

comum::CAppState& CControladorRegistraMesariosVota::Slot12() const
{
    return CFinalizaOperador::GetInst();
}

const std::string& CControladorRegistraMesariosVota::GetTituloMesario() const
{
    return CThreadOperador::GetInst().GetTituloMesario();
}

void CControladorRegistraMesariosVota::SetTituloMesario(const std::string& titulo)
{
    CThreadOperador::GetInst().SetTituloMesario(titulo);
}

void CControladorRegistraMesariosVota::LogaMesarioRegistrado(const std::string& titulo) const
{
    CLogVota::GetInst().LogaMesarioRegistrado(titulo);
}

void CControladorRegistraMesariosVota::LogaRegistrandoMesariosAntesVotacao() const
{
    CLogVota::GetInst().loga("Registrando mesários antes da votação");
}

void CControladorRegistraMesariosVota::LogaRegistrandoMesariosDuranteVotacao() const
{
    CLogVota::GetInst().loga("Registrando mesários durante a votação");
}

void CControladorRegistraMesariosVota::LogaRegistrandoMesariosAposVotacao() const
{
    CLogVota::GetInst().loga("Registrando mesários após a votação");
}

void CControladorRegistraMesariosVota::LogaIndagaRegistroMesarios() const
{
    CLogVota::GetInst().LogaIndagaRegistroMesarios();
}

void CControladorRegistraMesariosVota::LogaConfirmouRegistroMesarios() const
{
    CLogVota::GetInst().loga("Operador confirmou o registro de mesários");
}

void CControladorRegistraMesariosVota::LogaCancelouRegistroMesarios() const
{
    CLogVota::GetInst().loga("Operador cancelou o registro de mesários");
}

void CControladorRegistraMesariosVota::LogaTituloInvalidoRegistroMesario() const
{
    CLogVota::GetInst().LogaTituloInvalidoRegistroMesario();
}

void CControladorRegistraMesariosVota::LogaMesarioJaRegistrado(const std::string& titulo) const
{
    CLogVota::GetInst().LogaMesarioJaRegistrado(titulo);
}

void CControladorRegistraMesariosVota::LogaLimiteMesariosAtingido() const
{
    CLogVota::GetInst().logaAlerta(std::format("Limite de mesários registrados atingido. Limite máximo: {}", 6u));
}

void CControladorRegistraMesariosVota::LogaEncerrouCicloRegistro() const
{
    CLogVota::GetInst().loga("Operador encerrou ciclo de registro de mesários");
}

void CControladorRegistraMesariosVota::LogaDigitalNaoCorresponde(const std::vector<int>& scores) const
{
    CLogVota::GetInst().loga(std::format("Digital capturada não corresponde a digital do eleitor: Polegar Direito [score {}], "
                                         "Polegar Esquerdo [score {}], Indicador Direito [score {}], Indicador Esquerdo [score {}]",
                                         scores[0], scores[1], scores[2], scores[3]));
}

void CControladorRegistraMesariosVota::LogaPedidoBiometriaMesario() const
{
    CLogVota::GetInst().loga(std::format("Pedido de leitura da biometria do mesário {}", CThreadOperador::GetInst().GetTituloMesario()));
}

void CControladorRegistraMesariosVota::LogaMesarioEleitorDaSecao() const
{
    CLogVota::GetInst().loga(std::format("Mesário {} é eleitor da seção", CThreadOperador::GetInst().GetTituloMesario()));
}

void CControladorRegistraMesariosVota::LogaMesarioNaoEleitorDaSecao() const
{
    CLogVota::GetInst().loga(std::format("Mesário {} não é eleitor da seção", CThreadOperador::GetInst().GetTituloMesario()));
}

void CControladorRegistraMesariosVota::LogaConferenciaBiometriaMesario() const
{
    CLogVota::GetInst().loga("Realizada a conferência da biometria do mesário");
}

void CControladorRegistraMesariosVota::LogaIndagaContinuaRegistro() const
{
    CLogVota::GetInst().loga("Operador indagado se continua registrando mesários");
}

void CControladorRegistraMesariosVota::LogaIndagaFinalizaRegistro() const
{
    CLogVota::GetInst().loga("Operador indagado se finaliza registro mesários");
}

} // namespace vota
