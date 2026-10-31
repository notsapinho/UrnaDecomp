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

    uedword GetNumeroInternoUrna() const { return m_numeroInternoUrna; }
    std::string GetCodigoCarga() const { return m_codigoCarga; }

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
