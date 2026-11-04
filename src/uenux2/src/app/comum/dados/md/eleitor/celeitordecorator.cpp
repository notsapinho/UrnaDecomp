// The reconstruction's note, not TSE's text: the constructor from a CEleitor (no target function: fn 5772 holds it;
// its lines, above line 39, are chosen), GetIdentidadePorTipo (fn 708, record at line 39); GetAbrangencia (fn 3721),
// GetAnoNascimento (fn 5665) and operator<=> (fn 456, last) have no record: their lines, after line 39, are chosen.
#include "app/comum/dados/md/eleitor/celeitordecorator.h"

#include <algorithm>
#include <format>

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::md {

// (original lines 14-24: content not recovered)
#line 25
CEleitorDecorator::CEleitorDecorator(const CEleitor& eleitor, ecourna::app::dados::ETipoIdentificadorEleitor tipoIdentificador)
    : CEleitor(eleitor), m_tipoIdentificador(tipoIdentificador)
{
}


CEleitorIdentidade CEleitorDecorator::GetIdentidadePorTipo(ecourna::app::dados::ETipoIdentificadorEleitor tipo) const
{
    const auto identidade = std::find_if(m_identidades.begin(), m_identidades.end(),
                                         [tipo](const CEleitorIdentidade& item) { return item.GetTipo() == tipo; });
    if (identidade != m_identidades.end()) {
        return *identidade;
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7833, std::format("Tipo de identificador inválido: {}", static_cast<uebyte>(tipo)));
}

ETipoAbrangencia CEleitorDecorator::GetAbrangencia(const std::string& uf, const uedword municipio) const
{
    if (!IsTTE() || m_transferencia.GetMunicipio() == municipio) {
        return ABRANGENCIA_MUNICIPAL;
    }
    return m_transferencia.GetUF() == uf ? ABRANGENCIA_ESTADUAL : ABRANGENCIA_FEDERAL;
}

uedword CEleitorDecorator::GetAnoNascimento() const
{
    return ecourna::api::util::CStringUtils::ToDWord(GetDataNascimento().substr(0, 4));
}

std::strong_ordering CEleitorDecorator::operator<=>(const CEleitorDecorator& outro) const
{
    return GetIdentidadePorTipo(m_tipoIdentificador) <=> outro.GetIdentidadePorTipo(outro.m_tipoIdentificador);
}

} // namespace comum::md
