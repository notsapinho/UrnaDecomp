#pragma once

#include <optional>

#include "app/comum/dados/md/chorarioverao.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 28 bytes, from the two constructors (target fns 5677, 5679): the code at +0, the optional
// daylight-saving period at +4. m_codigo is a plain uedword for the reason cinfomunicipio.h gives. The member names are
// not in the target.
class CHorarioVeraoMunicipio {
public:
    CHorarioVeraoMunicipio(uedword codigo, const CHorarioVerao& horarioVerao);
    explicit CHorarioVeraoMunicipio(uedword codigo);

    bool TemHorarioVerao() const { return m_horarioVerao.has_value(); }
    const CHorarioVerao& GetHorarioVerao() const;

private:
    void ValidaCriacao() const;

    uedword m_codigo;
    std::optional<CHorarioVerao> m_horarioVerao;
};

} // namespace comum::md
