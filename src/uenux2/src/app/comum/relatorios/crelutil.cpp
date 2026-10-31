// comum::CRelUtil (/home/rubio/tse/uenux2/src/app/comum/relatorios/crelutil.cpp). The reconstruction's own note: the blank
// lines stand for text not recovered. Of the file's five records (lines 58, 69, 307, 412 and 554), only GetSeparadorFase's
// (line 554, column 23, target fn 1919) is written; the other lines stay blank, and the function's first line is chosen
// so that its throw lands on its record's.
#include "app/comum/relatorios/crelutil.h"

#include <format>

#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"

namespace comum {

// (original lines 16-54: content not recovered)
#line 55
// <stubs>
// f11181 · 549 B · unmatched · name unknown
// void f11181(i32) { ... }
// </stubs>

// (original lines 60-65: content not recovered)
#line 66
// <stubs>
// f2786 · 2458 B · unmatched · name unknown
// void f2786(i32, i32) { ... }
// </stubs>

// (original lines 71-303: content not recovered)
#line 304
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
