#pragma once

#include <cstddef>
#include <functional>
#include <source_location>
#include <string>
#include <vector>

#include "app/comum/dados/md/rdv/cvoto.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

using TQtdVoto = ueword;

class CVotos {
public:
    CVotos() = default;
    explicit CVotos(std::vector<CVoto> votos);

    void Insere(const CVoto& voto, size_t posicao);

    const std::vector<CVoto>& GetVotos() const { return m_votos; }
    TQtdVoto Total() const { return static_cast<TQtdVoto>(m_votos.size()); }
    TQtdVoto Candidato(const std::string& numero) const;
    TQtdVoto Legenda(const std::string& numero) const;
    TQtdVoto Partido(const std::string& numero) const;
    TQtdVoto TotalQue(bool (CVoto::*criterio)() const) const;

private:
    using TCriterio = std::function<bool(const CVoto&)>;

    TQtdVoto Conta(TCriterio criterio) const;
    // Throws "Posicao (...) fora do limite (...)" with the location its caller passes: Insere's record, cvotos.cpp:40
    // column 9, is a call there, and fn 4454 holds this body behind an 80-byte prologue of its own on the path that
    // throws only. A call of a [[noreturn]] function is cold, so clang keeps it out of line (-Rpass-missed=inline:
    // cost 400, threshold 0) and binaryen inlines it. Its name, that it is a private member and its parameter's
    // type are chosen.
    [[noreturn]] void ErroPosicao(size_t posicao,
                                  std::source_location local = std::source_location::current()) const;

    std::vector<CVoto> m_votos;
};

} // namespace comum::md
