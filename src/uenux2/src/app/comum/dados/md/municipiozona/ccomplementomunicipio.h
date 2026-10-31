#pragma once

#include <optional>

#include "app/comum/dados/md/chorarioverao.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 32 bytes, from the two constructors (target fns 3710, 3711): the code at +0, the time-zone
// offset at +4, the optional daylight-saving period at +8. m_codigo's type follows cinfomunicipio.h's; no body here tells
// it. The member names are not in the target.
class CComplementoMunicipio {
public:
    CComplementoMunicipio(uedword codigo, short fusoHorario, const CHorarioVerao& horarioVerao);
    CComplementoMunicipio(uedword codigo, short fusoHorario);

    uedword GetCodigo() const { return m_codigo; }
    short GetFusoHorario() const { return m_fusoHorario; }
    bool TemHorarioVerao() const { return m_horarioVerao.has_value(); }
    const CHorarioVerao& GetHorarioVerao() const;

private:
    void ValidaCriacao() const;

    uedword m_codigo;
    short m_fusoHorario;
    std::optional<CHorarioVerao> m_horarioVerao;
};

} // namespace comum::md
