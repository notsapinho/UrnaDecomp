// The reconstruction's note, not TSE's text: GetIdentidadePorTipo (fn 708, record at line 39), GetAbrangencia (fn
// 3721) and GetAnoNascimento (fn 5665), which have no record: their lines, after line 39, are chosen.
#include "app/comum/dados/md/eleitor/celeitordecorator.h"

#include <algorithm>
#include <format>

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::md {

// (original lines 13-30: content not recovered)
#line 31
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

} // namespace comum::md
