#pragma once

#include <optional>
#include <string>

#include "app/comum/dados/md/chorarioverao.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 44 bytes, from the two constructors (target fns 5674, 5676): the code at +0, the name at +4,
// the time-zone offset at +16, a flag at +18, the optional daylight-saving period at +20. Their records are
// GetHorarioVerao's and ValidaCriacao's, in cinfomunicipio.cpp. The parameter and member names are not in the target.
// m_urnaBiometrica's name is chosen: comum::CLocal::UrnaBiometrica (fn 820, named by its own literal) reads the flag.
// m_fusoHorario's type is a short: ValidaCriacao loads it signed and bounds it to ±720, and formats it as an int.
// m_codigo is a plain uedword, not comum::TMunicipioID as iresultado.h declares it. That is measured against the forms
// tried, not proved: ValidaCriacao's store order is what a member of that type gives, and two prvalues and a local
// copy, over this tree's CBaseType and over the member, do not (the fragment has the measurement).
class CInfoMunicipio {
public:
    CInfoMunicipio(uedword codigo, const std::string& nome, short fusoHorario, bool urnaBiometrica,
        const CHorarioVerao& horarioVerao);
    CInfoMunicipio(uedword codigo, const std::string& nome, short fusoHorario, bool urnaBiometrica);

    uedword GetCodigo() const { return m_codigo; }
    const std::string& GetNome() const { return m_nome; }
    bool EhUrnaBiometrica() const { return m_urnaBiometrica; }
    const CHorarioVerao& GetHorarioVerao() const;

private:
    void ValidaCriacao() const;

    uedword m_codigo;
    std::string m_nome;
    short m_fusoHorario;
    bool m_urnaBiometrica;
    std::optional<CHorarioVerao> m_horarioVerao;
};

} // namespace comum::md
