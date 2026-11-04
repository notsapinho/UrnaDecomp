#pragma once

#include <optional>

#include "api/util/cdatetime.h"

namespace comum::md {

// The Vota application's part of the BU (ModuloBoletimUrna::DadosSecao). The class name is the one the records of
// cdadosbuvota.cpp (line 37, GetDataHoraDesligamentoVotoImpresso, held by target fn 10273) and centidadebu.cpp (line
// 186, CEntidadeBU::GetDadosVota) print. Recovered: the layout, 40 bytes, from comum::asn::CConversorEntidadeBU::DoConverte
// (fn 10273), which hands +0 and +12 to comum::asn::Utils::ConverteDataHoraJE (fn 1080, const api::CDateTime &) for
// DadosSecao's dataHoraAbertura and dataHoraEncerramento, and tests the byte at +36 before it reads the 12 bytes at +24
// for dataHoraDesligamentoVotoImpresso: a std::optional<api::CDateTime>. The record gives
// GetDataHoraDesligamentoVotoImpresso's signature (an api::CDateTime by value); the other getters' names, their
// returning references, the members' names and the header's path, beside cdadosbuvota.cpp, are chosen. The constructor
// is not recovered, so nothing may construct the class.
class CDadosBUVota {
public:
    const api::CDateTime& GetDataHoraAbertura() const { return m_dataHoraAbertura; }
    const api::CDateTime& GetDataHoraEncerramento() const { return m_dataHoraEncerramento; }
    bool TemDataHoraDesligamentoVotoImpresso() const { return m_dataHoraDesligamentoVotoImpresso.has_value(); }
    api::CDateTime GetDataHoraDesligamentoVotoImpresso() const;

private:
    api::CDateTime m_dataHoraAbertura;
    api::CDateTime m_dataHoraEncerramento;
    std::optional<api::CDateTime> m_dataHoraDesligamentoVotoImpresso;
};

} // namespace comum::md
