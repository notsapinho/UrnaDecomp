// vota's free functions (uenux2/src/app/vota/comum/votadefs.cpp). The reconstruction's own note: the records of
// VerificaAssinaturaMI, VerificaAssinaturaMV and GetQuantidadeMaximaBUsAdicionais (target fns 3290, 3288 and 4582) fix
// lines 103, 110 and 135; every other line is a choice. EhTreinamento (fn 1485), AdicionaSeparador (1387),
// RegistraMesarios (2520), ExisteArquivoZeresima (no index: 11835 holds it inlined) and NaoAceitaJustificativa (4578)
// have no record: their file and lines, after the last record, are a choice (src/units/168-uenux2-app-helpers.mk), as
// are those of CriaArquivoImprimindo, ExisteArquivoImprimindo and RemoveArquivoImprimindo (fns 1488, -, 1487).
#include "app/vota/comum/votadefs.h"

#include <string>

#include "api/gui/cpaperformbuilder.h"
#include "api/io/cfile.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csynchronizer.h"
#include "api/util/csystem.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/iinterfacesavd.h"
#include "app/comum/informacao/cinformacaoeleicao.h"

// (original lines 24-89: content not recovered)
#line 90
namespace vota {

bool EhTreinamentoMesario()
{
    return EhTreinamento() && !comum::CAppInfo::GetInst().GetVota().GetTreinamentoEleitor();
}

// (original lines 97-100: content not recovered)
#line 101
void VerificaAssinaturaMI(const std::string& arquivo)
{
    auto& iSavd = api::CPolySingleton<comum::IInterfaceSavd>::instance();
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    comum::ValidarUE(iSavd, comum::SAVD_APLIC_VOTA, (comum::CPath::GetPathTrab(comum::FLASH_INTERNA, appInfo.GetGeral().GetDadoCarga().GetTurno()) / arquivo).string());
}

void VerificaAssinaturaMV(const std::string& arquivo)
{
    auto& iSavd = api::CPolySingleton<comum::IInterfaceSavd>::instance();
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    comum::ValidarUE(iSavd, comum::SAVD_APLIC_VOTA, (comum::CPath::GetPathTrab(comum::FLASH_EXTERNA, appInfo.GetGeral().GetDadoCarga().GetTurno()) / arquivo).string());
}

// (original lines 115-123: content not recovered)
#line 124
comum::TQtdImpresso GetQuantidadeMaximaBUsAdicionais()
{
    if (EhTreinamento() && comum::CAppInfo::GetInst().GetVota().GetTreinamentoEleitor()) {
        return 1;
    }

    const comum::md::estadoaplicacao::CEstadoGeralVota& vota = comum::CAppInfo::GetInst().GetVota();
    const comum::CInformacaoEleicao informacao(comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    const comum::TQtdImpresso numObrigatorias = informacao.GetNumViasBU();
    const comum::TQtdImpresso numAdicionais = informacao.GetNumViasBUAdicionais();
    const comum::TQtdImpresso numImpresso = vota.GetQtdBU();
    ASSERT(numImpresso >= numObrigatorias, api::EUA_QUANTIDADEMAXIMABUSADICIONAIS_IMPRESSO_MENOR);
    const comum::TQtdImpresso numAdicionaisImpressos = numImpresso - numObrigatorias;
    return numAdicionais - numAdicionaisImpressos;
}

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

bool NaoAceitaJustificativa()
{
    return !comum::CInformacaoEleicao(comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna()).AceitaJustificativa();
}

} // namespace vota
