// comum::CGeradorResultados's constructor (fn 5824). No record names the file: its path, beside the recorders it holds,
// is chosen (src/units/195-uenux2-cgeradorresultados.mk).
#include "app/comum/gravadores/cgeradorresultados.h"

namespace comum {

CGeradorResultados::CGeradorResultados(const std::vector<std::shared_ptr<IGravador>>& gravadores,
    const std::vector<std::shared_ptr<IResultado>>& copiados, const CAssinador& assinador, bool copiaMV,
    std::shared_ptr<IGravador> gravador)
    : m_gravadores(gravadores), m_copiados(copiados), m_assinador(assinador), m_copiaMV(copiaMV), m_gravador(gravador)
{
}

} // namespace comum
