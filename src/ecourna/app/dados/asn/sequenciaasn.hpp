#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

#include "asn1/asn1.h"

namespace ecourna::app::dados::asn {

// The ASN.1 sequence of a vector of application data, one Converte per element. File and names are chosen: no record
// names them. Binaryen merges the instantiations of this template into fn 1970.
template <typename TConversor>
ASN1::SEQUENCE_OF<typename TConversor::TEntidade> ConverteSequencia(const std::vector<typename TConversor::TDado>& dados,
                                                                    const TConversor& conversor)
{
    ASN1::SEQUENCE_OF<typename TConversor::TEntidade> sequencia;
    std::transform(dados.begin(), dados.end(), std::back_inserter(sequencia),
                   [&conversor](const typename TConversor::TDado& dado) { return conversor.Converte(dado); });
    return sequencia;
}

// The application data of an ASN.1 sequence, one Deconverte per element.
template <typename TSequencia, typename TConversor>
std::vector<typename TConversor::TDado> DeconverteSequencia(const TSequencia& sequencia, const TConversor& conversor)
{
    std::vector<typename TConversor::TDado> dados;
    std::transform(sequencia.begin(), sequencia.end(), std::back_inserter(dados),
                   [&conversor](const typename TConversor::TEntidade& entidade) { return conversor.Deconverte(entidade); });
    return dados;
}

} // namespace ecourna::app::dados::asn
