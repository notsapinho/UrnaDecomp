#pragma once

#include <string>
#include <vector>

namespace comum {

// The header of the boletim de urna's QR code. The class and its file come from the record of fn 2791, the lambda of
// preBuild() in ccabecalhoqrcodebuilder.cpp, line 284. 2791's only caller is fn 5604, which passes it the fields of this
// object: comum::CGeradorBUQRCodeVota's constructor (fn 5603, by the vptrs it stores) copies the object to its +4 with fn
// 5608, and fns 1956 and 12110 fill it through fns 5618 to 5623 first.
//
// The layout: fn 5608 copies 33 std::strings at a stride of 12 and fn 5624, which those two callers construct it with,
// zeroes 396 bytes, so nothing else fits. The members from m_origem to m_versaoSoftware are named after the labels 5604
// passes with them; no label comes with +132 or with the 17 strings from +192, so those are chosen. The setters' names
// are chosen from the same labels: no record names them. preBuild(), the constructor and the other setters are not
// reconstructed.
class CCabecalhoQRCodeBuilder {
public:
    void DefineCodigoCarga(const std::string& codigoCarga);
    void DefineHistoricoCarga(const std::vector<std::string>& cargas);

private:
    std::string m_origem;
    std::string m_origemProcessoEleitoral;
    std::string m_processoEleitoral;
    std::string m_dataPleito;
    std::string m_pleito;
    std::string m_turno;
    std::string m_fase;
    std::string m_uf;
    std::string m_municipio;
    std::string m_zona;
    std::string m_secao;
    std::string m_campo132;
    std::string m_idUrna;
    std::string m_codigoCarga;
    std::string m_historicoCarga;
    std::string m_versaoSoftware;
    std::string m_demaisCampos[17];
};

} // namespace comum
