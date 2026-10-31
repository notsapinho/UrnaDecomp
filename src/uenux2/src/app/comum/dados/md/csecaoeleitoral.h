#pragma once

#include <vector>

#include "app/comum/etipolocalvotacao.h"
#include "app/comum/md/cidentificacaosecao.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// The layout, 8 bytes, from comum::asn::CConversorIdentificacaoAgregada::DoConverte (target fn 11456), which reads the
// type at +0 and a 16-bit word at +4 and hands them to the entity's tipoLocalOrigem and numero: the member and getter
// names are chosen from those fields. CConversorSecaoEleitoral::DoDesconverte's push_back (fn 11453) copies its elements
// with one i64.store. The class is named by the base of its converter, IConversorASN<ModuloLocal::IdentificacaoAgregada,
// comum::md::CIdentificacaoAgregada>. The constructor (fn 5672) is out of line, called by fns 5741 and 11455; its file is
// chosen, the file of the class beside it.
class CIdentificacaoAgregada {
public:
    CIdentificacaoAgregada(ueword numero, ETipoLocalVotacao tipoLocalOrigem);

    ueword GetNumero() const { return m_numero; }
    ETipoLocalVotacao GetTipoLocalOrigem() const { return m_tipoLocalOrigem; }

private:
    ETipoLocalVotacao m_tipoLocalOrigem;
    ueword m_numero;
};

using TVectorIdentificacaoAgregada = std::vector<CIdentificacaoAgregada>;

// Recovered: the layout, 36 bytes, and the constructor (records csecaoeleitoral.cpp:34 to :41), which fn 11453,
// comum::asn::CConversorSecaoEleitoral::DoDesconverte, holds inlined by binaryen (a second stack-pointer prologue): it
// stores the type at +0, copies the CIdentificacaoSecao to +4 and the vector to +24, and checks the aggregated sections
// it is given. GetIdentificacao's name is chosen.
class CSecaoEleitoral {
public:
    CSecaoEleitoral(ETipoLocalVotacao tipo, const CIdentificacaoSecao& identificacao,
        const TVectorIdentificacaoAgregada& agregadas);

    ETipoLocalVotacao GetTipo() const { return m_tipo; }
    const CIdentificacaoSecao& GetIdentificacao() const { return m_identificacao; }
    const TVectorIdentificacaoAgregada& GetAgregadas() const { return m_agregadas; }

private:
    ETipoLocalVotacao m_tipo;
    CIdentificacaoSecao m_identificacao;
    TVectorIdentificacaoAgregada m_agregadas;
};

} // namespace comum::md
