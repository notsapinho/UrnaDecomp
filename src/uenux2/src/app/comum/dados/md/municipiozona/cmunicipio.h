#pragma once

#include <string>

#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// The record of the constructor spells TMunicipioID, and every body here reads it as a plain word: DoDesconverte
// (target fn 11378) passes the entity's int to the constructor with no range check, which ecourna's CBaseType would add,
// so this alias is not comum::TMunicipioID of iresultado.h. Its scope is chosen.
using TMunicipioID = uedword;

// The layout, 20 bytes, from the constructor (target fn 3712, record cmunicipio.cpp:27): the code at +0, the name at +4,
// the flag at +16. comum::asn::CConversorMunicipio (target fns 11379, 11378) reads and writes the same three as
// ModuloTiposCadastro::Municipio's codigo, nome and comBiometria. The member and getter names are chosen from those
// fields.
class CMunicipio {
public:
    CMunicipio(TMunicipioID codigo, const std::string& nome, bool comBiometria);

    TMunicipioID GetCodigo() const { return m_codigo; }
    const std::string& GetNome() const { return m_nome; }
    bool GetComBiometria() const { return m_comBiometria; }

private:
    TMunicipioID m_codigo;
    std::string m_nome;
    bool m_comBiometria;
};

} // namespace comum::md
