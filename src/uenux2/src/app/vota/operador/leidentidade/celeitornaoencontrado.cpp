// vota::CEleitorNaoEncontrado: no record names this file or any of its members; the reconstruction's notes are in
// celeitornaoencontrado.h and src/units/161-uenux2-app-vota-operador-identidade.mk.
#include "app/vota/operador/leidentidade/celeitornaoencontrado.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"

namespace vota {

CEleitorNaoEncontrado::~CEleitorNaoEncontrado() = default;

CEleitorNaoEncontrado& CEleitorNaoEncontrado::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorNaoEncontrado());
    }
    return *s_inst;
}

std::unique_ptr<CEleitorNaoEncontrado> CEleitorNaoEncontrado::s_inst;
std::mutex CEleitorNaoEncontrado::s_mutex;

std::string TextoNaoCadastrado()
{
    const ecourna::app::dados::ETipoIdentificadorEleitor tipoDigitado = GetTipoIdentidadeDigitada();
    const ecourna::app::dados::ETipoIdentificadorEleitor tipoPrincipal =
        comum::CConfiguracaoEleicao::GetInst().GetTipoIdentificadorPrincipal();
    if (tipoDigitado == ecourna::app::dados::TipoIDCPF && tipoPrincipal == ecourna::app::dados::TipoIDInscricaoEleitoral) {
        return "CPF não encontrado. Digite o Título.";
    }
    return "NÃO CADASTRADO nesta urna";
}

namespace {

std::string TextoVazio()
{
    return " ";
}

} // namespace

CEleitorNaoEncontrado::CEleitorNaoEncontrado()
    : IEleitorImpedidoVotar(&TextoNaoCadastrado, &TextoVazio, 0)
{
}

void CEleitorNaoEncontrado::LogaImpedimento()
{
    CLogVota::GetInst().loga("Eleitor não encontrado para o identificador informado");
}

} // namespace vota
