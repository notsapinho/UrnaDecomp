#pragma once

#include <vector>

#include "app/comum/md/cidentificacaosecao.h"

namespace comum::md {

// The type of a voting place, as CSecaoEleitoral's constructor spells it (md/csecaoeleitoral.cpp:34). Its enumerators
// are not recovered; that it is 4 bytes wide is read from the copy at +0 of the section (fn 11453).
enum ETipoLocalVotacao : int;

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
class CSecaoEleitoral {
public:
    const CIdentificacaoSecao& GetIdentificacao() const { return m_identificacao; }

private:
    ETipoLocalVotacao m_tipo;
    CIdentificacaoSecao m_identificacao;
    TVectorIdentificacaoAgregada m_agregadas;
};

} // namespace comum::md
