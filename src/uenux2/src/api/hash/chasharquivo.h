#pragma once

#include <string>

namespace api::hash {

// A file's name and its hash. The records of chasharquivo.cpp name the class and its ValidaObjeto (lines 26 and 30,
// fn 5364), which tests the string at +0 against "CHashArquivo: nome inválido." and the one at +12 against
// "CHashArquivo: hash inválido.", so the members are the name, then the hash; their names and the getters' are
// chosen. comum::asn::CConversorHashArquivo::DoConverte (target fn 10267) reads both strings in place, so the getters
// return them by reference. The constructor (fn 3600: copies the two strings, then calls ValidaObjeto) is defined in
// chasharquivo.cpp, which is not reconstructed yet.
class CHashArquivo {
public:
    CHashArquivo(const std::string& nome, const std::string& hash);

    const std::string& GetNome() const { return m_nome; }
    const std::string& GetHash() const { return m_hash; }

private:
    void ValidaObjeto() const;

    std::string m_nome;
    std::string m_hash;
};

} // namespace api::hash
