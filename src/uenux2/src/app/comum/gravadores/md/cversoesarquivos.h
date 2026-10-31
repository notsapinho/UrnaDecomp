#pragma once

#include <map>
#include <string>

namespace comum::md {

// Recovered: the layout, a string at +0 and a std::map at +12, from the constructor (target fn 5867), which copies its
// two arguments there: the map's copy inserts each node of 40 bytes with libc++'s hinted emplace (fn 1221), a string
// key and a string value. ValidaCriacao (records cversoesarquivos.cpp:28 and :33) tests the string's length and the
// map's size. The map's alias, the member and parameter names are chosen, from the messages ("Versão da TAG
// inválida", "Versões de arquivos inválida"). That ValidaCriacao is private is a choice too.
// comum::asn::CConversorVersoesArquivos::DoConverte (target fn 10264) reads the two members in place, the getters'
// code inlined: their names are chosen, and so is their being inline here.
class CVersoesArquivos {
public:
    using TMapVersoes = std::map<std::string, std::string>;

    CVersoesArquivos(const std::string& versaoTag, const TMapVersoes& versoes);

    const std::string& GetVersaoTag() const { return m_versaoTag; }
    const TMapVersoes& GetVersoes() const { return m_versoes; }

private:
    void ValidaCriacao() const;

    std::string m_versaoTag;
    TMapVersoes m_versoes;
};

} // namespace comum::md
