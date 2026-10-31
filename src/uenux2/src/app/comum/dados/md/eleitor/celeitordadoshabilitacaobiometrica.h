#pragma once

#include <optional>

#include "app/comum/dados/md/eleitor/cdedo.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// What the biometric reader and the mesario add to a voter's enabling. The record of GetTituloMesario
// (celeitordadoshabilitacaobiometrica.cpp:49) names the class and that member. Recovered: the layout, 32 bytes, from what
// CEleitorDetalhe::MarcaHabilitado (inlined into target fn 2825) reads at +24 to +55 of comum::CEleitorDadosHabilitacao:
// a 32-bit finger at +0, a 16-bit score at +4 and an 8-bit count at +6 that the biometric kind copies, a 32-bit error at
// +8 the mesario's kind copies with the count, and an optional identity at +12 (its flag at +28) whose value
// GetTituloMesario returns. Each width is the bodies'; the types are CEleitorDinamico's members they are copied into. The
// member names, the getters but GetTituloMesario, and this header's path, beside the record's .cpp, are chosen.
class CEleitorDadosHabilitacaoBiometrica {
public:
    CDedo::TipoDedo GetDedo() const { return m_dedo; }
    ueword GetScore() const { return m_score; }
    uebyte GetNumeroTentativa() const { return m_numeroTentativa; }
    int GetErroDecifrarBiometria() const { return m_erroDecifrarBiometria; }
    bool TemTituloMesario() const { return m_tituloMesario.has_value(); }
    const CEleitorIdentidade& GetTituloMesario() const;

private:
    CDedo::TipoDedo m_dedo;
    ueword m_score;
    uebyte m_numeroTentativa;
    int m_erroDecifrarBiometria;
    std::optional<CEleitorIdentidade> m_tituloMesario;
};

} // namespace comum::md
