// vota::IConfirmaJustificativa: the reconstruction's notes are in iconfirmajustificativa.h and unit 174's fragment.
// Line 34 is the constructor's record (fn 3625); the lines above it and the destructor's below are chosen.
#include "app/vota/operador/justificativa/iconfirmajustificativa.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"

namespace vota {

// (original lines 12-29: content not recovered)
#line 30
IConfirmaJustificativa::IConfirmaJustificativa(const std::string& justificativa)
    : comum::CAppState(EVENTO_ENTRADA)
{
    if (justificativa.size() > 40) {
        throw CUeVotaError(EUE_VOTA_FRASE_JUSTIFICATIVA_MUITO_GRANDE, "Frase muito grande [" + justificativa + "]");
    }
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(justificativa, api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: justificar", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    m_form = builder.GetInteractiveForm("", true);
}

IConfirmaJustificativa::~IConfirmaJustificativa() = default;

} // namespace vota
