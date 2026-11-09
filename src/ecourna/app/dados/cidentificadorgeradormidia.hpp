#pragma once
#include <string>

namespace ecourna::app::dados {

// Who generated a media: the generator's name, its TPM certificate serial and its installation serial. 36 bytes;
// layout from the constructor (fn 5109), the implicit copy constructor (fn 9872) and the converter
// (app/dados/asn/cconversoridentificadorgeradormidia.cpp, fns 9225/9224). Names from ModuloTiposEcoUrna's fields.
class CIdentificadorGeradorMidia {
public:
    // The default, target fn 9952, which the correspondence's default (fn 10261, uenux2's CDadoCorrespondencia) calls:
    // "nome_maquina", "12345678" and "99999999". It calls std::string's constructor (fn 148), which this tree's -O3
    // inlines, and has landing pads: code at the executable TU's rule, read as inline here.
    CIdentificadorGeradorMidia() : m_nome("nome_maquina"), m_serialCertificadoTPM("12345678"), m_serialInstalacao("99999999") {}
    CIdentificadorGeradorMidia(const std::string& nome, const std::string& serialCertificadoTPM,
                               const std::string& serialInstalacao);

    const std::string& GetNome() const { return m_nome; }
    const std::string& GetSerialCertificadoTPM() const { return m_serialCertificadoTPM; }
    const std::string& GetSerialInstalacao() const { return m_serialInstalacao; }

private:
    std::string m_nome;
    std::string m_serialCertificadoTPM;
    std::string m_serialInstalacao;
};

} // namespace ecourna::app::dados
