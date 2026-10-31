// comum::md::CDadosCandidato's four constructors (the reconstruction's note, not TSE's text). The throws of the two
// that take a substitute's order sit on their records' lines (35 and 65); the other lines of the original are not
// recovered, and where each definition starts is a choice. The class is in cdadoscandidato.h.
#include "app/comum/dados/md/candidatura/cdadoscandidato.h"

#include <format>
#include <utility>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 13-21: content not recovered)
#line 22
CDadosCandidato::CDadosCandidato(std::string codigo, std::string nomeUrna, CSexo::ESexo sexo, ESituacao situacao)
    : m_codigo(std::move(codigo)), m_nomeUrna(std::move(nomeUrna)), m_sexo(sexo), m_situacao(situacao), m_ordem(0)
{
}

// (original lines 27-29: content not recovered)
#line 30
CDadosCandidato::CDadosCandidato(std::string codigo, std::string nomeUrna, CSexo::ESexo sexo, ESituacao situacao,
                                 uebyte ordem)
    : m_codigo(std::move(codigo)), m_nomeUrna(std::move(nomeUrna)), m_sexo(sexo), m_situacao(situacao), m_ordem(ordem)
{
    if (ordem < 1 || ordem > 9) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7998, std::format("Suplente com ordem inválida: {}", ordem));
    }
}

// (original lines 39-45: content not recovered)
#line 46
CDadosCandidato::CDadosCandidato(std::string codigo, std::string nomeUrna, std::string nomeFonetico, CSexo::ESexo sexo,
                                 ESituacao situacao)
    : m_codigo(std::move(codigo)), m_nomeUrna(std::move(nomeUrna)), m_nomeFonetico(std::move(nomeFonetico)),
      m_sexo(sexo), m_situacao(situacao), m_ordem(0)
{
}

// (original lines 53-58: content not recovered)
#line 59
CDadosCandidato::CDadosCandidato(std::string codigo, std::string nomeUrna, std::string nomeFonetico, CSexo::ESexo sexo,
                                 ESituacao situacao, uebyte ordem)
    : m_codigo(std::move(codigo)), m_nomeUrna(std::move(nomeUrna)), m_nomeFonetico(std::move(nomeFonetico)),
      m_sexo(sexo), m_situacao(situacao), m_ordem(ordem)
{
    if (ordem < 1 || ordem > 9) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7999, std::format("Suplente com ordem inválida: {}", ordem));
    }
}

} // namespace comum::md
