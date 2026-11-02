// comum::CRelUtil (/home/rubio/tse/uenux2/src/app/comum/relatorios/crelutil.cpp). The reconstruction's own note: the blank
// lines stand for text not recovered. Of the file's five records (lines 58, 69, 307, 412 and 554), four are written:
// TituloPartido's (line 58, column 15, target fn 11181), GetIDCargaFormatado's (line 69, column 15, fn 2786),
// DSCodigoVerificador's (line 412, column 27, fn 11182) and GetSeparadorFase's (line 554, column 23, fn 1919).
// IncluiCabecalhoEleicoesMZS (line 307) is not written. Each function's first line is chosen so that its throw, or its
// CPolySingleton<CCalculaCV>::instance() call, lands on its record's line. TituloPartido is in the anonymous namespace,
// as its record names it. IncluiAvisoModoDemonstracao (fn 5583) and FormTituloPartido have no record: their names and
// their lines are chosen. FormTituloPartido is defined last, and so is TituloPartido's first mention: in our link
// 11182's ld_index is then below 11181's, as the use band asks (docs/how-to-decompile.md step 3, "The order of two
// members").
#include "app/comum/relatorios/crelutil.h"

#include <format>

#include "api/gui/cpaperformbuilder.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/comum/relatorios/ccalculacv.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"

namespace comum {

// (original lines 27-50: content not recovered)
#line 51
namespace {

std::string TituloPartido()
{
    CPartidos& partidos = CPartidos::GetInst();

    if (partidos.IsFim()) {
        throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9084, "Partido não posicionado");
    }
    const md::CPartido* partido = partidos.GetCurrent();
    const ueword numero = partido->GetNumero();
    return md::CTradutorFrase::Traduz("<PLSN>") + ": " + std::to_string(numero) + " - " + partido->GetSigla();
}
} // namespace

std::string CRelUtil::GetIDCargaFormatado(const std::string& idCarga)
{
    if (idCarga.size() <= 20) {
        throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9085, "ID de carga inválido: [" + idCarga + "]");
    }
    return idCarga.substr(0, 3) + "." + idCarga.substr(3, 3) + "." + idCarga.substr(6, 3) + "." + idCarga.substr(9, 3) +
           "." + idCarga.substr(12, 3) + "." + idCarga.substr(15, 3) + "." + idCarga.substr(18, 3) + "." +
           idCarga.substr(21);
}

// (original lines 76-293: content not recovered)
#line 294
void CRelUtil::IncluiAvisoModoDemonstracao(api::CPaperFormBuilder& builder)
{
    const CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    if (informacao.EhModoDemonstracao()) {
        builder.AddTextField("IMPRESSO EM MODO DEMONSTRAÇÃO", static_cast<api::IPaper::EStyle>(1),
                             api::ALINHAMENTO_CENTRO);
        builder.AddNewLine(2);
    }
}

// <stubs>
// f1543 · 6279 B · unmatched · name unknown
// void f1543(i32, i32, i32, i32, i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 309-402: content not recovered)
#line 403
void CRelUtil::ImprimeSeparadorVia(api::CPaperFormBuilder& builder, unsigned int via, unsigned int totalVias)
{
    builder.AddTextField(std::format("-------------- {:02} / {:02} ---------------", via, totalVias),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
}

std::string CRelUtil::DSCodigoVerificador()
{
    CCalculaCV& calculo = api::CPolySingleton<CCalculaCV>::instance();
    const std::string codigo = calculo.CalculaCodigo();
    return std::format("Código Verificador: {}.{}.{}.{}", codigo.substr(0, 1), codigo.substr(1, 3), codigo.substr(4, 3),
                       codigo.substr(7, 3));
}

// (original lines 418-539: content not recovered)
#line 540
std::string CRelUtil::GetSeparadorFase(const EUrnaFase fase)
{
    const CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    if (informacao.EhModoDemonstracao()) {
        return "============DEMONSTRAÇÃO==============";
    } else {
        switch (fase) {
            case FASE_SIMULADO:
                return "===============SIMULADO===============";
            case FASE_TREINAMENTO:
                return "==============TREINAMENTO=============";
            case FASE_OFICIAL:
                return "======================================";
            default:
                throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9087, std::format("Fase inválida: {}", fase));
        }
    }
}

std::shared_ptr<api::IForm<api::IPaper>> CRelUtil::FormTituloPartido()
{
    api::CPaperFormBuilder builder;
    builder.AddTextField(TituloPartido, api::ALINHAMENTO_ESQUERDA);
    return builder.Build();
}

} // namespace comum
