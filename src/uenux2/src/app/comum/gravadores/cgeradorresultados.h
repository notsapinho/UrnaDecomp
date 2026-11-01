#pragma once

#include <memory>
#include <vector>

#include "app/comum/gravadores/cassinador.h"
#include "app/comum/gravadores/igravador.h"

namespace comum {

// Recovered: the layout (84 bytes: the last store of fn 5824 is a word at +80) and the constructor, fn 5824, which
// vota::CGravaResultado::StartState (fn 12098) calls twice. No record, vtable slot or RTTI names the class, its file or
// a member, so they are chosen from what fn 12098 does with the object (src/units/195-uenux2-cgeradorresultados.mk).
// The constructor copies two vectors of 8-byte elements whose second word is a control block it increments (+0 and
// +12), stores CAssinador's vptr at +24 and copies a CAssinador's members after it (its implicit copy constructor
// inlined), stores a byte argument at +72 and copies a std::shared_ptr argument to +76 and +80. fn 12098 calls slot 4
// of each element of the first vector between two CLogComum::LogaGerandoResultados calls on the element's +32 (an
// IResultado's extension), and slot 2 of each element of the second before CLogComum::LogaCopiandoArqResParaFI on the
// same field: recorders, the first IGravador and the second IResultado here (the fragment says why). It calls slots 2
// and 4 of the object at +76, a recorder too, and tests the byte at +72 against 1 before it builds "Copiando
// resultados para a MV".
class CGeradorResultados {
public:
    CGeradorResultados(const std::vector<std::shared_ptr<IGravador>>& gravadores,
        const std::vector<std::shared_ptr<IResultado>>& copiados, const CAssinador& assinador, bool copiaMV,
        std::shared_ptr<IGravador> gravador);

private:
    std::vector<std::shared_ptr<IGravador>> m_gravadores;
    std::vector<std::shared_ptr<IResultado>> m_copiados;
    CAssinador m_assinador;
    bool m_copiaMV;
    std::shared_ptr<IGravador> m_gravador;
};

} // namespace comum
