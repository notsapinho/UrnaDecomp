// api::CReport::Imprime with DoPrintJob, which fn 11908 holds inlined, and api::GeraArquivoRelatorio (target fn 3654).
// The reconstruction's note, not TSE's text: no record names this file, whose path and name are chosen;
// src/units/317-uenux2-relatorios-aptos.mk says why these are in a TU apart from creport.cpp's.
#include "api/gui/reports/creport.h"

#include <functional>

#include "api/gui/csubreport.h"
#include "api/hwil/clp.h"

namespace api {

namespace {

void DoPrintJob(const CReport& relatorio, const std::string& titulo, const std::string& via)
{
    const CSubReport subRelatorio(titulo, via, true);
    CLp::GetInst().Imprime(subRelatorio, [&relatorio] { relatorio.ImprimePartes(); });
}

} // namespace

void CReport::Imprime(const std::string& titulo, const std::string& via) const
{
    DoPrintJob(*this, titulo, via);
}

void GeraArquivoRelatorio(const std::string& arquivo, const CReport& relatorio)
{
    const CScopedReportFile arquivoRelatorio(arquivo);
    relatorio.ImprimePartes();
}

} // namespace api
