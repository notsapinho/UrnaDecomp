// vota::IEleitorImpedidoVotar: no record names this file or any of its members; the reconstruction's notes are in
// ieleitorimpedidovotar.h and src/units/161-uenux2-app-vota-operador-identidade.mk.
#include "app/vota/operador/leidentidade/ieleitorimpedidovotar.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"

namespace vota {

IEleitorImpedidoVotar::IEleitorImpedidoVotar(std::function<std::string()> linha2, std::function<std::string()> linha3,
                                             int tipo)
    : comum::CAppState(EVENTO_ENTRADA)
    , m_tipo(tipo)
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(linha2, api::SPoint{1, 2});
    builder.AddTextField(linha3, api::SPoint{1, 3});
    switch (m_tipo) {
    case 0:
        builder.AddTextField("CONFIRMA: retornar", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
        break;
    case 1:
        builder.AddTextField("CORRIGE: retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
        break;
    }
    builder.AddInputControl();
    m_form = builder.GetInteractiveForm("", true);
}

IEleitorImpedidoVotar::~IEleitorImpedidoVotar() = default;

} // namespace vota
