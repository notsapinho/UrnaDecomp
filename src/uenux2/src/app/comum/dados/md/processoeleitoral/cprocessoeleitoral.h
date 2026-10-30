#pragma once

#include <optional>

#include "app/comum/dados/md/processoeleitoral/cpleito.h"

namespace comum::md {

// Recovered: only what GetPleito2 (fn 1267) reads, a std::optional<CPleito> at +96 with its flag at +156. +36 to +95 is
// a CPleito's size, so a first pleito is the likely member there, which the name GetPleito2 suggests; nothing written
// here reads it, and that and the bytes under it are chosen, so nothing may construct this class yet.
class CProcessoEleitoral {
public:
    const CPleito& GetPleito2() const;

private:
    unsigned char m_cabecalho[36];
    CPleito m_pleito1;
    std::optional<CPleito> m_pleito2;
};

} // namespace comum::md
