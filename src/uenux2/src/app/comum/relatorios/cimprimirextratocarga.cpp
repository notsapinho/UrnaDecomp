// comum::CImprimirExtratoCarga's one out-of-line member. The reconstruction's own note: no record names this file or its
// lines; cimprimirextratocarga.h says what places the member here, and src/units/123-uenux2-crelatoriotesteimpressora.mk
// what the bytes decide.
#include "app/comum/relatorios/cimprimirextratocarga.h"

#include <format>

#include "api/util/cdatetime.h"

namespace comum {

void CImprimirExtratoCarga::ImprimeDataHoraEmissao(api::CPaperFormBuilder& builder) const
{
    builder.AddNewLine(1);
    builder.AddTextField("EMISSÃO DO RELATÓRIO", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(std::format("DATA: {:.10}       HORA: {:.8}", api::CDateTime::FormatCurrentDate("DD/MM/YYYY"),
                                     api::CDateTime::FormatCurrentTime("hh:mm:ss")),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
}

} // namespace comum
