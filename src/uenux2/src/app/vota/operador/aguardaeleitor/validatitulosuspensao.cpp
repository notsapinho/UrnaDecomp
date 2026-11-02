// The reconstruction's note, not TSE's text: vota::ValidaTituloSuspensao, which binaryen inlines into its one caller,
// vota::CPerguntaCodigoSuspensao::ProcessInput (target fn 10420): its own 48-byte frame opens there after the log
// call. No record, slot or RTTI names it: its name, its being a free function and this file are chosen, and the file is
// not the caller's, which the caller's rows require (src/units/142-uenux2-app-vota-estados-448.mk has the measurement).
#include "app/vota/operador/aguardaeleitor/cperguntacodigosuspensao.h"

#include <string>
#include <utility>

#include "app/comum/dados/md/cvalidadoridentidade.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"

namespace vota {

std::pair<bool, std::string> ValidaTituloSuspensao(const std::string& titulo)
{
    const std::string formatado = comum::md::FormataIdentidade(titulo, ecourna::app::dados::TipoIDInscricaoEleitoral);
    const std::string digitado =
        comum::md::FormataIdentidade(GetIdentidadeDigitada(), ecourna::app::dados::TipoIDInscricaoEleitoral);
    const bool diferente = digitado != formatado;
    const bool valido =
        comum::md::CValidadorIdentidade::GetInst().EhValida(ecourna::app::dados::TipoIDInscricaoEleitoral, formatado);
    return {valido && diferente, formatado};
}

} // namespace vota
