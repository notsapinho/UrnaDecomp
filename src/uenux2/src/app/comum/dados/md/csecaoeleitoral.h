#pragma once

#include <vector>

#include "app/comum/md/cidentificacaosecao.h"

namespace comum::md {

// Recovered: the size only, 8 bytes: CConversorLocal::DoDesconverte's push_back (fn 11453) copies its elements with one
// i64.store. The class is named by the base of its converter, IConversorASN<ModuloLocal::IdentificacaoAgregada,
// comum::md::CIdentificacaoAgregada>. The members are not recovered.
class CIdentificacaoAgregada {
private:
    int m_palavras[2];
};

using TVectorIdentificacaoAgregada = std::vector<CIdentificacaoAgregada>;

// Recovered: the layout only, 36 bytes, read from fn 11453, which holds the constructor (records
// csecaoeleitoral.cpp:34 to :41), inlined by binaryen (a second stack-pointer prologue): the type at +0, the
// CIdentificacaoSecao at +4, the vector at +24. The file's only
// function is that constructor, so no csecaoeleitoral.cpp is written yet; GetIdentificacao's name is chosen.
// m_tipo is the ETipoLocalVotacao the constructor's record spells. The bodies give it 4 bytes and read no value, so it
// is the plainest type of that width, chosen, and this header declares no such enum: a plain enum of that name belongs
// with the conversions that read its values, and an opaque `: int` here could not stand beside it. The member takes
// the enum's type when the constructor is written.
class CSecaoEleitoral {
public:
    const CIdentificacaoSecao& GetIdentificacao() const { return m_identificacao; }

private:
    int m_tipo;
    CIdentificacaoSecao m_identificacao;
    TVectorIdentificacaoAgregada m_agregadas;
};

} // namespace comum::md
