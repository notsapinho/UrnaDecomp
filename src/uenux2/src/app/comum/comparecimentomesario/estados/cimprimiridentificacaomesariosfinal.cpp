// comum::CImprimirIdentificacaoMesariosFinal
// (/home/rubio/tse/uenux2/src/app/comum/comparecimentomesario/estados/cimprimiridentificacaomesariosfinal.cpp):
// GetNomeMesario, target fn 5385, whose ASSERT is the record at line 229, column 84. The lines above it are the
// original file's, not recovered; the function's first lines are a choice around that record.

#include "app/comum/comparecimentomesario/estados/cimprimiridentificacaomesariosfinal.h"

#include "api/util/eueasserterror.h"
#include "app/comum/dados/celeitores.h"

namespace comum {

// (original lines 13-224: content not recovered)
#line 225
std::string CImprimirIdentificacaoMesariosFinal::GetNomeMesario(const std::string& titulo)
{
    const CEleitorDetalhe* mesario =
        CEleitores::GetInst().LocalizaEleitor(titulo, ecourna::app::dados::TipoIDInscricaoEleitoral);
    ASSERT(mesario, api::EUA_IMPRIMIRIDENTIFICACAOMESARIOSFINAL_MESARIO_INEXISTENTE);
    const md::CEleitorDecorator& eleitor = mesario->GetEleitor();
    if (!eleitor.GetNomeUrna().empty()) {
        return eleitor.GetNomeUrna().substr(0, 40);
    }
    return eleitor.GetNome().substr(0, 40);
}

} // namespace comum
