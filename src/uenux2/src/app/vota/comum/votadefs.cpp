// vota's free functions (uenux2/src/app/vota/comum/votadefs.cpp). The reconstruction's own note: the file's records
// (lines 103, 110 and 135: vota::VerificaAssinaturaMI, VerificaAssinaturaMV, GetQuantidadeMaximaBUsAdicionais) are
// of functions not written, and their lines stay blank. EhTreinamento (target fn 1485) and AdicionaSeparador (fn 1387)
// have no record: their file and lines, after the last record, are a choice (src/units/168-uenux2-app-helpers.mk), and
// so are those of CriaArquivoImprimindo, ExisteArquivoImprimindo and RemoveArquivoImprimindo (fns 1488, -, 1487).
#include "app/vota/comum/votadefs.h"

#include <string>

#include "api/gui/cpaperformbuilder.h"
#include "api/io/cfile.h"
#include "api/util/csynchronizer.h"
#include "api/util/csystem.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"

// (original lines 17-99: content not recovered)
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

void CriaArquivoImprimindo()
{
    api::CFile arquivo((comum::CPath::GetPathRootSemSA(comum::FLASH_INTERNA) / "dinamico/imprimindo").string(), "wb");
    arquivo.Close();
    api::CSynchronizer::GetInst().Sync();
}

bool ExisteArquivoImprimindo()
{
    return api::CSystem::ExistFile((comum::CPath::GetPathRootSemSA(comum::FLASH_INTERNA) / "dinamico/imprimindo").string());
}

void RemoveArquivoImprimindo()
{
    if (ExisteArquivoImprimindo()) {
        api::CSystem::RemoveFile((comum::CPath::GetPathRootSemSA(comum::FLASH_INTERNA) / "dinamico/imprimindo").string());
        api::CSynchronizer::GetInst().Sync();
    }
}

bool EhTreinamento()
{
    return comum::CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase() == comum::FASE_TREINAMENTO;
}

void AdicionaSeparador(api::CPaperFormBuilder& builder, api::ETextAlignment alinhamento)
{
    builder.AddTextField(std::string(38, '-'), static_cast<api::IPaper::EStyle>(1), alinhamento);
}

} // namespace vota
