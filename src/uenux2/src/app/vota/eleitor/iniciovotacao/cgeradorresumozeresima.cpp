// vota's form builders 3873 and 3872 (cgeradorresumozeresima.h has their evidence and choices). The records of this
// file, lines 43 and 47, are vota::(anonymous namespace)::CriaTituloExtratoRDV's (fn 5971, not written), whose lines
// stay blank; the two functions' lines, below them, are chosen. The reconstruction's note, not TSE's text.
#include "app/vota/eleitor/iniciovotacao/cgeradorresumozeresima.h"

#include "api/gui/cpaperformbuilder.h"
#include "app/comum/dados/ccargods.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/crdvvota.h"
#include "app/comum/relatorios/cdatasourcesrelatorio.h"

namespace vota {











































std::shared_ptr<api::IForm<api::IPaper>> CriaCabecalhoDetalheZE()
{
    api::CPaperFormBuilder builder;
    builder.AddTextField(comum::CCargoDSLabelRelatorio::HeaderDetalheZE, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    return builder.Build();
}

std::shared_ptr<api::IForm<api::IPaper>> CriaDetalheCandidato(bool comVotos)
{
    using DataSources = comum::CDataSourcesRelatorio<comum::CRdvVota, comum::CEleitores>;
    api::CPaperFormBuilder builder;
    builder.AddTextField(comVotos ? DataSources::DetalheCandidato : DataSources::DetalheCandidatoZE,
                         api::ALINHAMENTO_ESQUERDA);
    return builder.Build();
}

} // namespace vota
