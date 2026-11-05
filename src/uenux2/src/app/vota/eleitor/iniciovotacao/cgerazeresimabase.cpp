#include "app/vota/eleitor/iniciovotacao/cgerazeresimabase.h"

#include <string>

#include "api/gui/cpaperformbuilder.h"
#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CGeraZeresimaBase::CGeraZeresimaBase()
    : comum::CAppState(EVENTO_NENHUM), m_form(CTelasVota::GetInst().GetTelaGeraZeresima())
{
}

CGeraZeresimaBase::~CGeraZeresimaBase() = default;

void ImprimeAvisoSemVotos(api::CPaperFormBuilder& builder)
{
    builder.AddTextField(std::string(38, '='), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField("Não há votos ou justificativas registrados", static_cast<api::IPaper::EStyle>(2),
                         api::ALINHAMENTO_CENTRO);
    builder.AddTextField(std::string(38, '='), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
}

void ImprimeTituloExtratoRDV(api::CPaperFormBuilder& builder)
{
    builder.AddTextField("-----------EXTRATO DO RDV-------------", static_cast<api::IPaper::EStyle>(1),
                         api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
}

} // namespace vota
