#include "app/comum/dados/asn/candidatura/cconversordadoscandidato.h"

#include "app/comum/asn/util.h"

namespace comum::asn {

CConversorDadosCandidato::TDado CConversorDadosCandidato::DoDesconverte(const TEntidade& entidade) const
{
    const std::string codigo = entidade.get_codigo();
    const std::string nomeUrna = entidade.get_nomeUrna();
    const md::CSexo::ESexo sexo = Utils::DesconverteSexo(entidade.get_sexo());
    const md::CDadosCandidato::ESituacao situacao = static_cast<md::CDadosCandidato::ESituacao>(!m_sinalizador);
    const bool temNomeFonetico = entidade.nomeFonetico_isPresent();
    if (entidade.ordemSuplencia_isPresent()) {
        const uebyte ordem = entidade.get_ordemSuplencia().getValue();
        if (temNomeFonetico) {
            const std::string nomeFonetico = entidade.get_nomeFonetico();
            return TDado(codigo, nomeUrna, nomeFonetico, sexo, situacao, ordem);
        }
        return TDado(codigo, nomeUrna, sexo, situacao, ordem);
    }
    if (temNomeFonetico) {
        const std::string nomeFonetico = entidade.get_nomeFonetico();
        return TDado(codigo, nomeUrna, nomeFonetico, sexo, situacao);
    }
    return TDado(codigo, nomeUrna, sexo, situacao);
}

} // namespace comum::asn
