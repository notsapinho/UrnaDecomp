// vota::CLogVota (/home/rubio/tse/uenux2/src/app/vota/log/clogvota.cpp). Its records are records of the target:
//   184    static CLogVota &GetInst()                                 record at line 37, column 37
//   10635  LogaEleitorImpedido(comum::md::ETipoImpedimento)            record at line 432, column 19 (not written)
// The members with no record sit at lines the reconstruction chose; unit 119's fragment says why and has the other
// notes, and unit 142's fragment for the three it added after LogaTituloInvalidoRegistroMesario.

#include "app/vota/log/clogvota.h"

#include <format>
#include <memory>
#include <string>

#include "api/pattern/cpolysingleton.h"
#include "api/uelog/cloga.h"

namespace vota {

CLogVota::CLogVota() : comum::IEventosLog(static_cast<api::ELogAplicativos>(1)) {}

void CLogVota::LogaMesarioRegistrado(const std::string& titulo)
{
    const std::string mensagem = std::format("Mesário {} registrado", titulo);
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaMesarioJaRegistrado(const std::string& titulo)
{
    const std::string mensagem = std::format("Mesário {} já registrado", titulo);
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

CLogVota& CLogVota::GetInst()
{
    if (!api::CPolySingletonList::has<comum::IEventosLog>()) {
        api::CPolySingleton<comum::IEventosLog>::set(std::unique_ptr<comum::IEventosLog>(new CLogVota));
    }
    return dynamic_cast<CLogVota &>(api::CPolySingleton<comum::IEventosLog>::instance());
}

void CLogVota::LogaIndagaRegistroMesarios()
{
    const std::string mensagem = "Operador indagado se ocorrerá registro de mesários";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaTituloInvalidoRegistroMesario()
{
    const std::string mensagem = "Digitado título inválido para o registro de mesário";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(2), mensagem);
}

void CLogVota::LogaJustificativaRecebida()
{
    const std::string mensagem = "Justificativa recebida";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaEleitorJaJustificou()
{
    const std::string mensagem = "Eleitor já justificou";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(2), mensagem);
}

void CLogVota::LogaPedidoTituloSuspensao()
{
    loga("Solicitado título eleitoral para suspensão do eleitor");
}

} // namespace vota

// <stubs>
// f10635 · 3870 B · unmatched · name unknown
// void f10635(i32) { ... }
// </stubs>
