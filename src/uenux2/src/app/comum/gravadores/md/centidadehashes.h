#pragma once

#include <string>

#include "app/comum/eurnafase.h"
#include "app/comum/md/ccabecalhoentidade.h"

namespace comum::md {

// Recovered: the head of the layout, from ValidaCriacao (target fn 5855, records centidadehashes.cpp:59 and :62), which
// reads the phase at +20 and a string at +24 whose length must be 2 ("UF inválida"). The 20 bytes before it are taken
// as the entity's header, as in CEnvelopeGenerico, whose ValidaCriacao tests the phase at +20 the same way; the members
// follow ModuloHashes::EntidadeHashes's first fields (cabecalho, fase, siglaUF), and their types past the widths and
// names are chosen, and that ValidaCriacao is private. The members after +36 (identificacaoUrna, versaoUENUX, hashesArquivos) and the constructor are not
// recovered, so nothing may construct the class.
class CEntidadeHashes {
private:
    void ValidaCriacao() const;

    CCabecalhoEntidade m_cabecalho;
    EUrnaFase m_fase;
    std::string m_siglaUF;
};

} // namespace comum::md
