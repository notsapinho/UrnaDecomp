#pragma once

#include <cstddef>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"
#include "ecourna/app/dados/federacoes/cfederacao.hpp"

namespace comum {

// The party federations of the election. The records of Load (cfederacoes.cpp:141 and :149, which fn 7787 holds
// inlined) name the class and its file; this header's path is the lower-case rule beside them, chosen.
//
// Recovered: the layout, 28 bytes, from GetInst (target fn 2832, which allocates 28 and holds the constructor inlined)
// and the destructor (fn 5800): the federations at +0, a std::vector<ecourna::app::dados::CFederacao> (5800 destroys it
// with fn 1272, that vector's __destroy_vector), a word at +12 that the constructor zeroes and nothing written here
// reads, and a std::string at +16 that the constructor copies from a temporary built from the literal "CFederacoes", as
// comum::CPartidos's and api::CDataMap's constructors take their name. GetFederacao (fn 5799) walks the vector by its
// 40-byte stride and compares its argument, unmasked, with the 16-bit party numbers: a 16-bit integer parameter, not
// ecourna's TPartidoID class, which the body would mask. Chosen: the word's type (size_t) and the data members' names,
// GetFederacao's and GetInst's names, its parameter's type beyond those 16 bits (ueword), the statics' names, and a
// private constructor from the name rather than a base class that holds the three members.
class CFederacoes {
public:
    static CFederacoes& GetInst();

    CFederacoes();
    ~CFederacoes();

    const ecourna::app::dados::CFederacao* GetFederacao(ueword partido) const;

private:
    static std::unique_ptr<CFederacoes> s_inst;
    static std::mutex s_mutex;

    explicit CFederacoes(const std::string& nome) : m_atual(0), m_nome(nome) {}

    std::vector<ecourna::app::dados::CFederacao> m_federacoes;
    size_t m_atual;
    std::string m_nome;
};

} // namespace comum
