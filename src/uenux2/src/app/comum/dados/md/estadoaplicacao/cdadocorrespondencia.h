#pragma once

#include <string>
#include <vector>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/estadoaplicacao/clocalidadeeleitoral.h"
#include "ecourna/api/uetypes.hpp"
#include "ecourna/api/util/cstringutils.hpp"
#include "ecourna/app/dados/cidentificadorgeradormidia.hpp"

namespace comum::md::estadoaplicacao {

// A correspondencia's record: what comum::asn::CConversorDadoCorrespondencia::DoDesconverte (target fn 11400) reads from
// ModuloEstadoGeralUrna::DadoCorrespondencia and hands the constructor (fn 5630), which gives the offsets. The class name
// comes from the converter's RTTI; the member names follow the ASN.1 fields.
class CDadoCorrespondencia {
public:
    // The default, target fn 10261, which comum::teste::CAppInfoBuilder's constructor (fn 10268) calls for its
    // state's +60: the internal number 87654321, the serial "12345678", the load's date 31/12/2020 23:59:58, the
    // code "123456789012345678901234", the default locality, AssinaturaSimulada and the generator's default. It has
    // landing pads, so it is code at the executable TU's rule, the builder's: read as inline here.
    CDadoCorrespondencia()
        : m_numeroInternoUrna(87654321), m_numeroSerieFC("12345678"), m_dataHoraCarga("31122020235958"),
          m_codigoCarga("123456789012345678901234"), m_assinatura(AssinaturaSimulada())
    {
    }
    // Target fn 9963: 278 hex digits, "123456789abcdefABCDEF" (literal 466384, copied into a local array) appended
    // until the text has that many, as bytes (CStringUtils::HexStringToBytes, fn 3506). Its name, its being a static
    // member and inline are chosen; the landing pads say the executable TU's rule, as for the constructor.
    static std::vector<uebyte> AssinaturaSimulada()
    {
        const char digitos[] = "123456789abcdefABCDEF";
        std::string hex;
        hex.reserve(556);
        while (hex.size() < 278) {
            hex += digitos;
        }
        hex = hex.substr(0, 278);
        return ecourna::api::util::CStringUtils::HexStringToBytes(hex);
    }
    CDadoCorrespondencia(uedword numeroInternoUrna, std::string numeroSerieFC, api::CDateTime dataHoraCarga,
                         std::string codigoCarga, CLocalidadeEleitoral secaoCarga, std::vector<uebyte> assinatura,
                         ecourna::app::dados::CIdentificadorGeradorMidia identificadorGeradorMidia);

    // The getters below GetNumeroInternoUrna are what comum::asn::CConversorDadoCorrespondencia::DoConverte (fn 11399)
    // reads, each member by reference: the converter assigns or converts each from its place in the object with no copy.
    // Their names are chosen.
    uedword GetNumeroInternoUrna() const { return m_numeroInternoUrna; }
    const std::string& GetNumeroSerieFC() const { return m_numeroSerieFC; }
    const api::CDateTime& GetDataHoraCarga() const { return m_dataHoraCarga; }
    const std::string& GetCodigoCarga() const { return m_codigoCarga; }
    const CLocalidadeEleitoral& GetSecaoCarga() const { return m_secaoCarga; }
    const std::vector<uebyte>& GetAssinatura() const { return m_assinatura; }
    const ecourna::app::dados::CIdentificadorGeradorMidia& GetIdentificadorGeradorMidia() const
    {
        return m_identificadorGeradorMidia;
    }

private:
    uedword m_numeroInternoUrna;
    std::string m_numeroSerieFC;
    api::CDateTime m_dataHoraCarga;
    std::string m_codigoCarga;
    CLocalidadeEleitoral m_secaoCarga;
    std::vector<uebyte> m_assinatura;
    ecourna::app::dados::CIdentificadorGeradorMidia m_identificadorGeradorMidia;
};

} // namespace comum::md::estadoaplicacao
