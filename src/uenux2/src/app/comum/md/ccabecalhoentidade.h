#pragma once

#include "api/util/cdatetime.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// The record of the constructor spells the type; its enumerators are not recovered. The constructor (target fn 1945)
// accepts 0 to 2.
enum ETipoCabecalho : int;

// The layout, 20 bytes, from the constructor (target fn 1945, records ccabecalhoentidade.cpp:24, :27), which is
// declared here and not written. It copies the date at +0 and stores the word at +12 and the type at +16. The member
// names are not in the target.
class CCabecalhoEntidade {
public:
    CCabecalhoEntidade(const api::CDateTime& dataGeracao, uedword codigo, ETipoCabecalho tipo);

private:
    api::CDateTime m_dataGeracao;
    uedword m_codigo;
    ETipoCabecalho m_tipo;
};

} // namespace comum::md
