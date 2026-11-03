#pragma once

#include <string>
#include <utility>
#include <vector>

#include "app/comum/dados/md/estadoaplicacao/cajustedatahora.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocarga.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/cdadolocal.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md::estadoaplicacao {

// The urna's state: the fields of ModuloEstadoGeralUrna::EstadoGeralUrna. The offsets come from the constructor (target
// fn 5637) and comum::asn::CConversorEstadoGeral::DoConverte (fn 11397), which reads the state from +0 (an EEstadoUrna,
// ConverteEstadoUrna's parameter in its record), idPE from +4, the locality from +8, the load from +32, the clock
// adjustment from +52, the correspondence from +60, the version from +156 and the packages' hash from +168. Only the
// layout is recovered, with the getters the bodies read. The member and getter names follow the ASN.1 fields; idPE is
// unsigned, the std::to_string(unsigned int) GetDadosQRCode (fn 5636) formats it with, and its width the bodies'. The
// locality's class is cdadolocal.h's, which has this layout.
class CEstadoGeral {
public:
    EEstadoUrna GetEstadoUrna() const { return m_estadoUrna; }
    uedword GetIdPE() const { return m_idPE; }
    const CDadoLocal& GetDadoLocal() const { return m_dadoLocal; }
    const CDadoCarga& GetDadoCarga() const { return m_dadoCarga; }
    const CAjusteDataHora& GetAjusteDataHora() const { return m_ajusteDataHora; }
    const CDadoCorrespondencia& GetCorrespondencia() const { return m_correspondencia; }
    const std::string& GetVersao() const { return m_versao; }
    const std::vector<uebyte>& GetHashVersoesPacotes() const { return m_hashVersoesPacotes; }

    // Target fn 5636, out of line in cestadogeral.cpp: the state as key and value pairs, in this order, PROC (idPE),
    // TURN (1 or 2, but for an urna of type eUrnaContingencia or eUrnaContingenciaVotaRecupera in its turn), FASE (the
    // load's phase letter in upper case), UNFE, MUNI, ZONA, SECA (only for eUrnaVota and eUrnaContingenciaVota), IDUE,
    // MDUE, IDFL, IDCA, DTCA and HRCA (the load's date and time), NOME, SERT, SERI (the media generator) and ASSI (the
    // signature in hex). Its target callers, fns 11200 (comum::CRelatorioTesteImpressora's slot 5) and 3059, pass the
    // state comum::CAppInfo::GetGeral returns and build a comum::CQRCodeDS of the result. The name and its being a
    // member (it reads the members above) are chosen.
    std::vector<std::pair<std::string, std::string>> GetDadosQRCode() const;

    // Target fn 3705, out of line in cestadogeral.cpp: its callers (7160, 7306, 10710) read the +52 adjustment inline,
    // change it with CAjusteDataHora::AdicionaDeltaT (fn 3702) and store it back through this call. The name is chosen:
    // no record, slot or RTTI names it.
    void SetAjusteDataHora(const CAjusteDataHora& ajusteDataHora);

private:
    EEstadoUrna m_estadoUrna;
    uedword m_idPE;
    CDadoLocal m_dadoLocal;
    CDadoCarga m_dadoCarga;
    CAjusteDataHora m_ajusteDataHora;
    CDadoCorrespondencia m_correspondencia;
    std::string m_versao;
    std::vector<uebyte> m_hashVersoesPacotes;
};

} // namespace comum::md::estadoaplicacao
