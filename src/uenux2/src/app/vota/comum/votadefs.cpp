// vota's free functions (uenux2/src/app/vota/comum/votadefs.cpp). The reconstruction's own note: the file's records
// (lines 103, 110 and 135: vota::VerificaAssinaturaMI, VerificaAssinaturaMV, GetQuantidadeMaximaBUsAdicionais) are
// of functions not written, and their lines stay blank. EhTreinamento (target fn 1485), AdicionaSeparador (fn 1387),
// RegistraMesarios (fn 2520) and ExisteArquivoZeresima (no index: 11835 holds it inlined) have no record: their file
// and lines, after the last record, are a choice (src/units/168-uenux2-app-helpers.mk).
#include "app/vota/comum/votadefs.h"

#include <string>

#include "api/gui/cpaperformbuilder.h"
#include "api/util/csystem.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/informacao/cinformacaoeleicao.h"

// (original lines 18-99: content not recovered)
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

bool RegistraMesarios()
{
    return comum::CInformacaoEleicao(comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna()).ImprimeBJust() &&
           !(EhTreinamento() && comum::CAppInfo::GetInst().GetVota().GetTreinamentoEleitor());
}

bool ExisteArquivoZeresima()
{
    const std::filesystem::path arquivo = comum::CPath::GetPathTrab(comum::FLASH_INTERNA) / "ze.dat";
    return api::CSystem::ExistFile(arquivo);
}

} // namespace vota
