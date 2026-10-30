#pragma once

#include <string>

#include "ecourna/api/uetypes.hpp"

namespace comum {

// The alias app/comum/dados/md/candidatura/ccandidatura.h declares too, with the same type.
using TCandidatoID = uedword;

namespace md {

// Recovered: the layout, 28 bytes: fn 11373 copies a std::vector of them with that stride, and the records of its
// constructor (crespostaconsulta.cpp:29 and :32) give a TCandidatoID and two strings. The constructor and the members'
// names are not recovered beyond that.
class CRespostaConsulta {
public:
    CRespostaConsulta(TCandidatoID numero, const std::string& resposta, const std::string& textoFonetico);

private:
    TCandidatoID m_numero;
    std::string m_resposta;
    std::string m_textoFonetico;
};

} // namespace md
} // namespace comum
