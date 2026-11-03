#pragma once

#include <string>
#include <vector>

#include "app/comum/eaplicativosdeurna.h"
#include "app/comum/eurnaturno.h"
#include "app/comum/validamidia/ivalidamidia.h"

namespace comum {

// comum::CFabricaConteudoMidiaStart: its one record (cfabricaconteudomidiastart.cpp:62) names ConteudoIncializacao as a
// static member, spelled as the record prints it. The target has no function of its own for it: binaryen inlines it into
// its one caller, comum::impl::CValidaMidia::Valida (fn 11172). The class holds no other member any evidence shows; this
// header's path is chosen, beside the .cpp.
class CFabricaConteudoMidiaStart {
public:
    static std::vector<std::string> ConteudoIncializacao(const EAplicativosDeUrna aplicativo, const EUrnaTurno turno);
};

} // namespace comum

namespace comum::impl {

// The checks of a media directory against a list of expected names that CValidaMidia's slots call (target fns 5572, 2784
// and 5571), out of line in cfabricaconteudomidiastart.cpp (src/units/179-uenux2-cvalidamidia.mk says what places them
// there, a reading). No record names them: their names, their being free functions of comum::impl and this header are
// chosen.
// ValidaConteudo (fn 5572): the media's reason code, 1 or 2 when it is valid (empty or missing, or holding only
// permitted files and every expected one), 6 to 10 when not.
SResultadoValidacao ValidaConteudo(const std::string& caminho, const std::vector<std::string>& esperados);
// ConteudoValido (fn 2784): ValidaConteudo's verdict alone.
bool ConteudoValido(const std::string& caminho, const std::vector<std::string>& esperados);
// RemoveArquivosDeSistema (fn 5571): removes the files macOS and Windows leave on a medium.
void RemoveArquivosDeSistema(const std::string& caminho);

} // namespace comum::impl
