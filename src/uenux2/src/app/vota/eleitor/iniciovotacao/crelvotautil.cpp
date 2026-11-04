// vota::CRelVotaUtil: no record names this file, its path is chosen (src/units/246-uenux2-crelvotautil.mk says why).
// The reconstruction's note, not TSE's text.
#include "app/vota/eleitor/iniciovotacao/crelvotautil.h"

#include "api/gui/cpaperformbuilder.h"
#include "api/gui/csubreport.h"
#include "api/hwil/clp.h"
#include "api/util/cdatetime.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/relatorios/celeitoresaptos.h"
#include "app/comum/relatorios/cgeradorbuqrcode.h"
#include "app/comum/relatorios/crelutil.h"

namespace vota {

void CRelVotaUtil::CortaPapel()
{
    api::CPaperFormBuilder builder;
    builder.AddNewLine(2);
    builder.AddCut();
    api::CLp::GetInst().Imprime(api::CSubReport("", "", false), [&builder] { builder.Build()->Slot2(); });
}

std::shared_ptr<api::IForm<api::IPaper>> CRelVotaUtil::CriaCabecalho(const std::string& titulo)
{
    const comum::md::estadoaplicacao::CEstadoGeral& geral = comum::CAppInfo::GetInst().GetGeral();
    const api::CDateTime agora = api::CDateTime::Now();
    const comum::CLocal& local = comum::CLocal::GetInst();
    api::CPaperFormBuilder builder;
    builder.AddNewLine(2);
    const comum::md::estadoaplicacao::CLocalidadeEleitoral& secao = geral.GetDadoLocal().GetSecaoCarga();
    comum::CRelUtil::IncluiCabecalhoEleicoesMZS(builder, titulo, secao.GetMunicipio(), secao.GetZona(),
                                                secao.GetSecao(), local.GetNomeMunicipio(),
                                                comum::CRelUtil::eCabecalhoSecao, false);
    builder.AddTextField(
        comum::CEleitoresAptos([]() { return comum::CEleitores::GetInst().QuantidadeAptos(); }).Formata(),
        static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    builder.AddTextField(comum::GetIdentificacaoUrna, api::ALINHAMENTO_ESQUERDA);
    comum::CRelUtil::ImprimeDataHora(builder, agora, "Data", "Hora");
    builder.AddNewLine(1);
    comum::CRelUtil::ImprimeResumoCorrespondencia(builder, geral.GetCorrespondencia());
    return builder.Build();
}

} // namespace vota
