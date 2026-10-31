// Reconstruction: comum::md::CCorrespondenciaResultado's constructor (target fn 2801), with ValidaCriacao, which binaryen
// inlines into it (its stack frame begins after the constructor's stores). ValidaCriacao's throws are records of the
// target (lines 42 to 57, column 15); the constructor has none, so its line is a choice, above the member it calls.

#include "app/comum/dados/md/correspondencia/ccorrespondenciaresultado.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

CCorrespondenciaResultado::CCorrespondenciaResultado(uedword municipio, ueword zona, ueword secao, const CCarga& carga,
    EUrnaTipo tipoUrna)
    : m_municipio(municipio), m_zona(zona), m_secao(secao), m_carga(carga), m_tipoUrna(tipoUrna)
{
    ValidaCriacao();
}

// (original lines 20-38: content not recovered)
#line 39
void CCorrespondenciaResultado::ValidaCriacao() const
{
    if (m_municipio >= 100000) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8027, std::format("Município inválido: {}", m_municipio));
    }


    if (m_zona >= 10000) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8028, std::format("Zona inválida: {}", m_zona));
    }


    if (m_secao >= 10000) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8029, std::format("Seção inválida: {}", m_secao));
    }


    if (m_tipoUrna < eUrnaVota || m_tipoUrna > eUrnaContingenciaVotaRecupera) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8030, std::format("Tipo de urna inválido: {}", static_cast<int>(m_tipoUrna)));
    }
}

} // namespace comum::md
