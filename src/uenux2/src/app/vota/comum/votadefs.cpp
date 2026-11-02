// vota's free functions (uenux2/src/app/vota/comum/votadefs.cpp). The reconstruction's own note: the file's records
// (lines 103, 110 and 135: vota::VerificaAssinaturaMI, VerificaAssinaturaMV, GetQuantidadeMaximaBUsAdicionais) are
// of functions not written, and their lines stay blank. EhTreinamento (target fn 1485) and AdicionaSeparador (fn 1387)
// have no record: their file and lines, after the last record, are a choice (src/units/168-uenux2-app-helpers.mk).
#include "app/vota/comum/votadefs.h"

#include <string>

#include "api/gui/cpaperformbuilder.h"
#include "app/comum/appinfo/cappinfo.h"

// (original lines 12-99: content not recovered)
#line 100
// <stubs>
// f3290 · 356 B · unmatched · name unknown
// void f3290(i32) { ... }
// </stubs>

// (original lines 105-106: content not recovered)
#line 107
// <stubs>
// f3288 · 356 B · unmatched · name unknown
// void f3288(i32) { ... }
// </stubs>

// (original lines 112-131: content not recovered)
#line 132
// <stubs>
// f4582 · 157 B · unmatched · name unknown
// ? f4582() { ... }
// </stubs>





namespace vota {

bool EhTreinamento()
{
    return comum::CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase() == comum::FASE_TREINAMENTO;
}

void AdicionaSeparador(api::CPaperFormBuilder& builder, api::ETextAlignment alinhamento)
{
    builder.AddTextField(std::string(38, '-'), static_cast<api::IPaper::EStyle>(1), alinhamento);
}

} // namespace vota
