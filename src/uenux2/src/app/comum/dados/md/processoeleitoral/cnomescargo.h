#pragma once

#include <string>

namespace comum::md {

// The four names of a cargo, in the order of ModuloEleicao::NomesCargo's fields, which the constructor's records
// (cnomescargo.cpp:28 to :37) confirm by message. 48 bytes: comum::asn::CConversorNomesCargo::DoDesconverte (target fn
// 11369) builds them at +0, +12, +24 and +36. The member and accessor names are chosen from those fields.
class CNomesCargo {
public:
    CNomesCargo(const std::string& nomeNeutro, const std::string& nomeMasculino, const std::string& nomeFeminino,
                const std::string& nomeAbreviado);

    const std::string& GetNomeNeutro() const { return m_nomeNeutro; }
    const std::string& GetNomeMasculino() const { return m_nomeMasculino; }
    const std::string& GetNomeFeminino() const { return m_nomeFeminino; }
    const std::string& GetNomeAbreviado() const { return m_nomeAbreviado; }

private:
    std::string m_nomeNeutro;
    std::string m_nomeMasculino;
    std::string m_nomeFeminino;
    std::string m_nomeAbreviado;
};

} // namespace comum::md
