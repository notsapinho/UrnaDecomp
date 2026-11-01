#pragma once

#include "api/util/cdate.h"

namespace comum::md {

// Recovered: the layout only, 20 bytes, and the constructor's parameters, from its record (chorarioverao.cpp:29):
// fn 11384 holds the constructor, inlined by binaryen (a second stack-pointer prologue), which stores the two dates at
// +0 and +8 and the int at +16. The class is trivially
// copyable: the constructors that keep one in a std::optional copy it with two i64.store and one i32.store (fn 5674).
// The constructor is in chorarioverao.cpp, at its records' lines. The member names are not in the target. The getters
// are what comum::asn::CConversorHorarioVerao::DoConverte (fn 11385) reads, the dates by reference (fn 3802 takes their
// addresses); their names are chosen.
// Contem (no target function of its own) is whether a date lies in [m_inicio, m_fim), two CDate::operator<=> calls
// (fn 1261), which fn 11198, comum::CRelatorioTesteImpressora::EstaEmHorarioVerao, holds. It is out of line in
// chorarioverao.cpp, where binaryen inlines it into 11198, the form src/units/147-uenux2-chorarioverao.mk measures
// against the compares written in 11198. Its name is chosen.
class CHorarioVerao {
public:
    CHorarioVerao(const api::CDate& inicio, const api::CDate& fim, int diferenca);

    const api::CDate& GetInicio() const { return m_inicio; }
    const api::CDate& GetFim() const { return m_fim; }
    int GetDiferenca() const { return m_diferenca; }

    bool Contem(const api::CDate& data) const;

private:
    api::CDate m_inicio;
    api::CDate m_fim;
    int m_diferenca;
};

} // namespace comum::md
