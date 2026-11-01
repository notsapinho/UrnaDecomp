#pragma once

#include <string>

namespace api {

/**
 * Uma chave (nome = valor) de um arquivo INI.
 */
class CIniKey {
public:
    CIniKey(const std::string& nome, const std::string& valor)
        : m_nome(nome)
        , m_valor(valor)
    {
    }

    // Declared so that a key moves: api::CIniSection::SetKey (target fn 5482) moves a key's strings into its map's node,
    // and the user-declared operator= would leave the class no move constructor. `= default` is chosen
    // (src/units/175-uenux2-cinisection.mk).
    CIniKey(const CIniKey& chave) = default;
    CIniKey(CIniKey&& chave) = default;

    CIniKey& operator=(const CIniKey& chave);

    const std::string& GetNome() const { return m_nome; }
    const std::string& GetValor() const { return m_valor; }

private:
    std::string m_nome;
    std::string m_valor;
};

} // namespace api
