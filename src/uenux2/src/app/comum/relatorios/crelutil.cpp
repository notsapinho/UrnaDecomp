// comum::CRelUtil (/home/rubio/tse/uenux2/src/app/comum/relatorios/crelutil.cpp). The reconstruction's own note: the blank
// lines stand for text not recovered. Of the file's five records (lines 58, 69, 307, 412 and 554), GetIDCargaFormatado's
// (line 69, column 15, target fn 2786) and GetSeparadorFase's (line 554, column 23, fn 1919) are written; the other lines
// stay blank, and each function's first line is chosen so that its throw lands on its record's. IncluiAvisoModoDemonstracao
// (fn 5583) has no record: its name and its lines are chosen.
#include "app/comum/relatorios/crelutil.h"

#include <format>

#include "api/gui/cpaperformbuilder.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"

namespace comum {

// (original lines 18-54: content not recovered)
#line 55
// <stubs>
// f11181 · 549 B · unmatched · name unknown
// void f11181(i32) { ... }
// </stubs>

// (original lines 60-65: content not recovered)
#line 66
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

// (original lines 309-539: content not recovered)
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

} // namespace comum
