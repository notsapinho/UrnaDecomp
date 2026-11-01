#pragma once

#include "api/util/cdatetime.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// The record of the constructor spells the type. The constructor (target fn 1945) accepts 0 to 2, and
// comum::asn::CConversorCabecalhoEntidade (fns 11589 and 11588) maps them to ModuloTiposEleitorais::IDEleitoral's
// idProcessoEleitoral, idPleito and idEleicao: the enumerators' names are chosen from that, no evidence names them.
enum ETipoCabecalho : int {
    TIPO_CABECALHO_PROCESSO_ELEITORAL,
    TIPO_CABECALHO_PLEITO,
    TIPO_CABECALHO_ELEICAO,
};

// The layout, 20 bytes, from the constructor (target fn 1945, records ccabecalhoentidade.cpp:24, :27): it copies the
// date at +0 and stores the word at +12 and the type at +16. The member names are not in the target. The getters are
// what comum::asn::CConversorCabecalhoEntidade::DoConverte (fn 11589) reads, by reference for the date (fn 1080 takes
// its address); their names are chosen.
class CCabecalhoEntidade {
public:
    CCabecalhoEntidade(const api::CDateTime& dataGeracao, uedword codigo, ETipoCabecalho tipo);

    const api::CDateTime& GetDataGeracao() const { return m_dataGeracao; }
    uedword GetCodigo() const { return m_codigo; }
    ETipoCabecalho GetTipo() const { return m_tipo; }

private:
    api::CDateTime m_dataGeracao;
    uedword m_codigo;
    ETipoCabecalho m_tipo;
};

} // namespace comum::md
