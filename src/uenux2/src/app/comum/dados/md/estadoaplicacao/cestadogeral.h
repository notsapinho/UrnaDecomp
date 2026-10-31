#pragma once

#include <string>
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
// layout is recovered, with the getters the bodies read. The member and getter names follow the ASN.1 fields; idPE's
// type is the width the bodies read. The locality's class is cdadolocal.h's, which has this layout.
class CEstadoGeral {
public:
    EEstadoUrna GetEstadoUrna() const { return m_estadoUrna; }
    int GetIdPE() const { return m_idPE; }
    const CDadoLocal& GetDadoLocal() const { return m_dadoLocal; }
    const CDadoCarga& GetDadoCarga() const { return m_dadoCarga; }
    const CAjusteDataHora& GetAjusteDataHora() const { return m_ajusteDataHora; }
    const CDadoCorrespondencia& GetCorrespondencia() const { return m_correspondencia; }
    const std::string& GetVersao() const { return m_versao; }
    const std::vector<uebyte>& GetHashVersoesPacotes() const { return m_hashVersoesPacotes; }

private:
    EEstadoUrna m_estadoUrna;
    int m_idPE;
    CDadoLocal m_dadoLocal;
    CDadoCarga m_dadoCarga;
    CAjusteDataHora m_ajusteDataHora;
    CDadoCorrespondencia m_correspondencia;
    std::string m_versao;
    std::vector<uebyte> m_hashVersoesPacotes;
};

} // namespace comum::md::estadoaplicacao
