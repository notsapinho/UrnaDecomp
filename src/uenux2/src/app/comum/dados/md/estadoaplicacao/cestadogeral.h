#pragma once

#include <string>
#include <vector>

#include "app/comum/dados/md/estadoaplicacao/cajustedatahora.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocarga.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/clocalidadeeleitoral.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md::estadoaplicacao {

// A urna's locality: the fields of ModuloEstadoGeralUrna::DadoLocal. The class name comes from
// comum::asn::CConversorDadoLocal's RTTI. CEstadoGeral's constructor (target fn 5637) moves the string and copies the two
// words and the word after it; only the layout is recovered, and the member names follow the ASN.1 fields.
class CDadoLocal {
private:
    std::string m_uf;
    CLocalidadeEleitoral m_secaoCarga;
    int m_tipoLocalVotacao;
};

// The urna's state: the fields of ModuloEstadoGeralUrna::EstadoGeralUrna. The offsets come from the constructor (target
// fn 5637) and DoConverte (fn 11397), which reads idPE from +4 and the state from +0. Only the layout is recovered, with the
// getters the bodies read. The member names follow the ASN.1 fields, and the types of the first two are the widths the
// bodies read.
class CEstadoGeral {
public:
    const CDadoCarga& GetDadoCarga() const { return m_dadoCarga; }
    const CDadoCorrespondencia& GetCorrespondencia() const { return m_correspondencia; }

private:
    int m_estadoUrna;
    int m_idPE;
    CDadoLocal m_dadoLocal;
    CDadoCarga m_dadoCarga;
    CAjusteDataHora m_ajusteDataHora;
    CDadoCorrespondencia m_correspondencia;
    std::string m_versao;
    std::vector<uebyte> m_hashVersoesPacotes;
};

} // namespace comum::md::estadoaplicacao
