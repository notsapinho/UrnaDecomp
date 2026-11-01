#pragma once

#include <string>
#include <vector>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/estadoaplicacao/clocalidadeeleitoral.h"
#include "ecourna/api/uetypes.hpp"
#include "ecourna/app/dados/cidentificadorgeradormidia.hpp"

namespace comum::md::estadoaplicacao {

// A correspondencia's record: what comum::asn::CConversorDadoCorrespondencia::DoDesconverte (target fn 11400) reads from
// ModuloEstadoGeralUrna::DadoCorrespondencia and hands the constructor (fn 5630), which gives the offsets. The class name
// comes from the converter's RTTI; the member names follow the ASN.1 fields.
class CDadoCorrespondencia {
public:
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
