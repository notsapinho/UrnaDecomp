#pragma once

#include <string>

#include "ecourna/api/uetypes.hpp"

namespace comum {

// The alias app/comum/dados/md/candidatura/ccandidatura.h declares too, with the same type.
using TCandidatoID = uedword;

namespace md {

// Recovered: the layout, 28 bytes: fn 11373 copies a std::vector of them with that stride, and the records of its
// constructor (crespostaconsulta.cpp:29 and :32) give a TCandidatoID and two strings. The constructor and the members'
// names are not recovered beyond that. GetNumero reads the number at +0, as the inlined code of fns 12621 and 11478 does
// from what GetCurrent returns; no record names it, so its name is chosen, and so is its being inline in the class.
class CRespostaConsulta {
public:
    CRespostaConsulta(TCandidatoID numero, const std::string& resposta, const std::string& textoFonetico);

    TCandidatoID GetNumero() const { return m_numero; }

private:
    TCandidatoID m_numero;
    std::string m_resposta;
    std::string m_textoFonetico;
};

} // namespace md
} // namespace comum
